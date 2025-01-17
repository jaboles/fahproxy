#include "ProxyHandlerArbitrator.h"
#include "NormalProxyHandler.h"
#include "FahUploadProxyHandler.h"
#include "UploadManager.h"
#include "Utils.h"

using namespace FahProxy;
using namespace System::Net::Sockets;
using namespace System::Net;
using namespace System::IO;

using namespace System;

ProxyHandlerArbitrator::ProxyHandlerArbitrator(Socket^ clientSocket, UploadManager^ uploadManager)
{
	m_clientSocket = clientSocket;
	m_networkStream = gcnew NetworkStream(m_clientSocket);
	m_uploadManager = uploadManager;
}

ProxyHandlerArbitrator::~ProxyHandlerArbitrator()
{
}

void ProxyHandlerArbitrator::HandleIt()
{
	try
	{
		String^ requestLine = Utils::ReadLineFromStream(m_networkStream);
		array<wchar_t>^ splitChars = {' '};
		array<String^>^ requestComponents = requestLine->Split(splitChars);

		String^ method = requestComponents[0];
		String^ url = requestComponents[1];
		String^ protocol = requestComponents[2];
		System::IO::MemoryStream^ headers = gcnew System::IO::MemoryStream();
		int contentLength = 0;

		for
		(
			String^ line = Utils::ReadLineFromStream(m_networkStream);
			line != "";
			line = Utils::ReadLineFromStream(m_networkStream)
		)
		{
			Utils::WriteLineToStream(headers, line);
			if (line->StartsWith("Content-Length:"))
			{
				contentLength = Convert::ToInt32(line->Substring(16));
			}
		}
		// Blank line to separate
		Utils::WriteLineToStream(headers, "");

		NormalProxyHandler^ h;
		String^ localHost = static_cast<IPEndPoint^>(m_clientSocket->RemoteEndPoint)->Address->ToString();
		if
		(
			method == "POST" && contentLength > 2048 && 
			(
				url->StartsWith("http://171.64.") &&
				url->EndsWith(":8080/")
			/*url == "http://171.64.65.20:8080/" ||
			url == "http://171.64.122.76:8080/" ||
			url == "http://171.64.122.74:8080/" ||
			false*/
			)
		)
		{
			h = gcnew FahUploadProxyHandler(localHost, method, url, protocol, m_networkStream, headers, m_uploadManager);
		}
		else
		{
			h = gcnew NormalProxyHandler(localHost, method, url, protocol, m_networkStream, headers);
		}
		h->HandleIt();
	}
	catch (System::IO::IOException^)
	{
	}
	finally
	{
		m_networkStream->Close();
		m_clientSocket->Close();
	}
}