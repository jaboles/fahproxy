#include "NormalProxyHandler.h"
#include "Utils.h"

using namespace FahProxy;
using namespace System::Net;
using namespace System::IO;
using namespace System::Net::Sockets;
using namespace System::Text;
using namespace System;

NormalProxyHandler::NormalProxyHandler(System::String^ method, System::String^ url, System::String^ protocolVersion, System::Net::Sockets::NetworkStream^ ns)
{
	m_requestMethod = method;
	if (m_requestMethod == "CONNECT")
	{
		array<wchar_t>^ splitChars = {':'};
		array<String^>^ parts = url->Split(splitChars);

		m_host = parts[0];
		m_port = Convert::ToInt32(parts[1]);
	}
	else
	{
		System::Uri^ uri = gcnew System::Uri(url);
		m_host = uri->Host;
		m_port = uri->Port > 0? uri->Port : 80;
		m_path = uri->AbsoluteUri;

	}
	m_protocolVersion = protocolVersion;
	m_proxyStream = ns;
	m_buffer = gcnew array<unsigned char, 1>(BUFFER_LENGTH);
}

NormalProxyHandler::~NormalProxyHandler()
{
}

void NormalProxyHandler::HandleIt()
{
	Socket ^webRequestSocket = gcnew Socket(AddressFamily::InterNetwork, SocketType::Stream, ProtocolType::Tcp);
	int contentLength = 0;

	try
	{
		webRequestSocket->Connect(m_host, m_port);
		m_requestStream = gcnew NetworkStream(webRequestSocket, true);

		if (m_requestMethod == "CONNECT")
		{
			// Trash the headers
			for
			(
				String^ line = Utils::ReadLineFromStream(m_proxyStream);
				line != "";
				line = Utils::ReadLineFromStream(m_proxyStream)
			)
			{
			}
			
			// Send 200 OK to indicate that the tunnel has been established.
			Utils::WriteLineToStream(m_proxyStream, "HTTP/1.1 200 Connection established");
			Utils::WriteLineToStream(m_proxyStream, "Connection: close");
			Utils::WriteLineToStream(m_proxyStream, "");
			m_proxyStream->Flush();

			PassThroughEverything();
		}
		else
		{
			String^ requestLine;
			requestLine = String::Concat(m_requestMethod, " ", m_path);
			requestLine = String::Concat(requestLine, " ", m_protocolVersion);
			Utils::WriteLineToStream(m_requestStream, requestLine);

			PassThroughRequestHeaders();
			if (m_requestMethod == "POST")
			{
				PassThroughRequestContent();
			}
			PassThroughResponseHeaders();
			PassThroughResponseContent();
		}
	}
	catch (System::IO::IOException^) {}
	catch (System::Net::Sockets::SocketException^) {}
	finally
	{
		m_requestStream->Close();
		webRequestSocket->Close();
	}
}

void NormalProxyHandler::PassThroughRequestHeaders()
{
	for
	(
		String^ line = Utils::ReadLineFromStream(m_proxyStream);
		line != "";
		line = Utils::ReadLineFromStream(m_proxyStream)
	)
	{
		Utils::WriteLineToStream(m_requestStream, line);
		if (line->StartsWith("Content-Length:"))
		{
			m_requestContentLength = Convert::ToInt32(line->Substring(16));
		}
	}

	// Blank line to separate
	Utils::WriteLineToStream(m_requestStream, "");
	m_requestStream->Flush();
}

void NormalProxyHandler::PassThroughRequestContent()
{
	for
	(
		int bytesRead = 0;
		(m_requestContentLength == 0 || bytesRead < m_requestContentLength);
	)
	{
		int b = m_proxyStream->Read(m_buffer, 0, BUFFER_LENGTH);
		if (b == 0)
		{
			break;
		}
		bytesRead += b;
		m_requestStream->Write(m_buffer, 0, b);
	}
	m_requestStream->Flush();
}

void NormalProxyHandler::PassThroughResponseHeaders()
{
	for
	(
		String^ line = Utils::ReadLineFromStream(m_requestStream);
		line != "";
		line = Utils::ReadLineFromStream(m_requestStream)
	)
	{
		Utils::WriteLineToStream(m_proxyStream, line);
		if (line->StartsWith("Content-Length:"))
		{
			m_contentLength = Convert::ToInt32(line->Substring(16));
		}
	}

	// Blank line to separate
	Utils::WriteLineToStream(m_proxyStream, "");
	m_proxyStream->Flush();
}

void NormalProxyHandler::PassThroughResponseContent()
{
	// Pass through data
	for
	(
		int bytesRead = 0;
		(m_contentLength == 0 || bytesRead < m_contentLength);
	)
	{
		int b = m_requestStream->Read(m_buffer, 0, BUFFER_LENGTH);
		if (b == 0)
		{
			break;
		}
		bytesRead += b;
		m_proxyStream->Write(m_buffer, 0, b);
	}
	m_proxyStream->Flush();
}

void NormalProxyHandler::PassThroughEverything()
{
	int bytesRead = -1;

	while (true)
	{
		if (m_proxyStream->DataAvailable)
		{
			bytesRead = m_proxyStream->Read(m_buffer, 0, BUFFER_LENGTH);
			if (bytesRead = 0)
			{
				break;
			}
			m_requestStream->Write(m_buffer, 0, bytesRead);
			m_requestStream->Flush();
		}
		if (m_requestStream->DataAvailable)
		{
			bytesRead = m_requestStream->Read(m_buffer, 0, BUFFER_LENGTH);
			if (bytesRead = 0)
			{
				break;
			}
			m_proxyStream->Write(m_buffer, 0, bytesRead);
			m_proxyStream->Flush();
		}
	}
}