#include "FahUploadProxyHandler.h"
#include "Utils.h"
#include "WorkUnit.h"
#include "UploadManager.h"

using namespace FahProxy;
using namespace System;
using namespace System::IO;
using namespace System::Net;

FahUploadProxyHandler::FahUploadProxyHandler(System::String^ localHost, System::String^ method, System::String^ url, System::String^ protocolVersion, System::Net::Sockets::NetworkStream^ ns, System::IO::MemoryStream^ headers, UploadManager^ uploadManager)
: NormalProxyHandler(localHost, method, url, protocolVersion, ns, headers)
{
	m_uploadManager = uploadManager;
}

void FahUploadProxyHandler::HandleIt()
{
	try 
	{
		int wuDataSize = 0;

		System::Random^ r = gcnew System::Random();
		String^ folderName = String::Concat(System::Environment::GetEnvironmentVariable("appdata"), "\\FahProxy\\");	
		String^ fileName = String::Concat(Convert::ToString(System::DateTime::Now.Ticks), "-", Convert::ToString(r->Next()));

		if (!Directory::Exists(folderName))
		{
			Directory::CreateDirectory(folderName);
		}

		m_wuStream = gcnew FileStream(String::Concat(folderName, fileName, ".wu"), FileMode::Create);
		m_metadataStream = gcnew FileStream(String::Concat(folderName, fileName, ".txt"), FileMode::Create);

		Utils::WriteLineToStream(m_metadataStream, m_host);
		Utils::WriteLineToStream(m_metadataStream, Convert::ToString(m_port));
		Utils::WriteLineToStream(m_metadataStream, m_localHost);
		m_metadataStream->Close();

		// Discard the request headers (we don't need them)
		m_headersStream->Seek(0, SeekOrigin::Begin);
		for
		(
			String^ line = Utils::ReadLineFromStream(m_headersStream);
			line != "";
			line = Utils::ReadLineFromStream(m_headersStream)
		)
		{
			if (line->StartsWith("Content-Length:"))
			{
				wuDataSize = Convert::ToInt32(line->Substring(16));
			}
		}

		// Now decide what to do. If the "WU" data size is small (i.e. 512 bytes) it
		// isn't a work-unit upload, it's actually an work-unit request. Or
		// it might be a really small work unit. So we'll let it thru.

		// Store the WU being uploaded in the file.
		CopyBytes(m_proxyStream, m_wuStream, wuDataSize);
		m_wuStream->Close();

		WorkUnit^ wu = gcnew WorkUnit(fileName);

		// Produce the response stream.
		Utils::WriteLineToStream(m_proxyStream, "HTTP/1.1 200 OK");
		Utils::WriteLineToStream(m_proxyStream, "Content-Type: text/html");
		Utils::WriteLineToStream(m_proxyStream, "Cache-Control: no-cache");
		Utils::WriteLineToStream(m_proxyStream, "Transfer-Encoding: chunked");
		Utils::WriteLineToStream(m_proxyStream, "");
		Utils::WriteLineToStream(m_proxyStream, "200");
		Stream^ simulatedStanfordResponse = wu->GetTranslatedResponseStream();
		CopyBytes(simulatedStanfordResponse, m_proxyStream, simulatedStanfordResponse->Length);
		Utils::WriteLineToStream(m_proxyStream, "0");
		Utils::WriteLineToStream(m_proxyStream, "");

		m_uploadManager->AddToQueue(wu);
	}
	catch (System::IO::IOException^) {}
	catch (System::Net::Sockets::SocketException^) {}
	finally
	{
		if (m_wuStream)
		{
			m_wuStream->Close();
		}

		if (m_metadataStream)
		{
			m_metadataStream->Close();
		}

		if (m_traceStream)
		{
			m_traceStream->Close();
		}
	}
}