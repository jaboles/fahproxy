#include "Uploader.h"
#include "WorkUnit.h"
#include "Utils.h"
#include "UploadManager.h"

using namespace FahProxy;
using namespace System;
using namespace System::IO;
using namespace System::Net;
using namespace System::Net::Sockets;
using namespace System::Threading;

Uploader::Uploader(int index)
{
	m_index = index;
	m_buffer = new unsigned char __gc [BUFFER_SIZE];
}

Uploader::~Uploader()
{
}

void Uploader::DoUpload(UploadQueueEntry* qe)
{
	m_currentUpload = qe;

	ThreadStart* ts = new ThreadStart(this, &Uploader::UploadThreadEntry);
	(new Thread(ts))->Start();
}

void Uploader::UploadThreadEntry()
{
	m_bytesUploaded = 0;
	m_isactive = true;

	m_currentUpload->SetStatus(UploadQueueEntry::UPLOADING);
	ProgressChanged(this, System::EventArgs::Empty);

	Stream* wuDataStream;

	try
	{
		m_socket = new Socket(AddressFamily::InterNetwork, SocketType::Stream, ProtocolType::Tcp);
		wuDataStream = m_currentUpload->GetWorkUnit()->GetDataStream();
		m_socket->Connect(m_currentUpload->GetWorkUnit()->GetUploadHost(), m_currentUpload->GetWorkUnit()->GetUploadPort());
		m_networkStream = new System::Net::Sockets::NetworkStream(m_socket, true);

		Utils::WriteLineToStream(m_networkStream, "POST / HTTP/1.1");
		Utils::WriteLineToStream(m_networkStream, String::Format(S"Host: {0}:{1}", __box(m_currentUpload->GetWorkUnit()->GetUploadHost(), m_currentUpload->GetWorkUnit()->GetUploadPort())));
		Utils::WriteLineToStream(m_networkStream, "Connection: Keep-Alive");
		Utils::WriteLineToStream(m_networkStream, String::Format(S"Content-Length: {0}", __box(m_currentUpload->GetWorkUnit()->GetDataSize())));
		Utils::WriteLineToStream(m_networkStream, "");
		m_networkStream->Flush();

		for (m_bytesUploaded = 0; m_bytesUploaded < m_currentUpload->GetWorkUnit()->GetDataSize();)
		{
			int b = wuDataStream->Read(m_buffer, 0, BUFFER_SIZE);
			m_bytesUploaded += b;
			//m_networkStream->WriteByte(15);
			m_networkStream->Write(m_buffer, 0, b);
			ProgressChanged(this, System::EventArgs::Empty);
		}
		m_networkStream->Flush();
		wuDataStream->Close();

		unsigned char receiptBuffer __gc [] = new unsigned char __gc [512];
		int responseContentLength = 0;
		int httpResponseCode = 0;
		String* httpResponseLine;
		String* line1;
		String* line2;
		String* line3;
		for
		(
			String* line = Utils::ReadLineFromStream(m_networkStream);
			line != "";
			line = Utils::ReadLineFromStream(m_networkStream)
		)
		{
			if (line->StartsWith("HTTP/"))
			{
				httpResponseCode = Convert::ToInt32(line->Substring(9, 3));
				httpResponseLine = line->Substring(9);
			}

			// Stanford server doesn't specify content-length in the response.
			/*if (line->StartsWith("Content-Length:"))
			{
				responseContentLength = Convert::ToInt32(line->Substring(16));
			}*/
		}

		if (httpResponseCode == 200)
		{
			//if (responseContentLength > 0)
			{
				line1 = Utils::ReadLineFromStream(m_networkStream);
				responseContentLength -= (line1->Length + 2);
			}
			//if (responseContentLength > 0)
			{
				// Read the 512-byte receipt
				m_networkStream->Read(receiptBuffer, 0, 512);
				responseContentLength -= 512;
			}
			//if (responseContentLength > 0)
			{
				line2 = Utils::ReadLineFromStream(m_networkStream);
				responseContentLength -= (line2->Length + 2);
			}
			//if (responseContentLength > 0)
			{
				line3 = Utils::ReadLineFromStream(m_networkStream);
				responseContentLength -= (line3->Length + 2);
			}

			m_currentUpload->SetStatus(UploadQueueEntry::UPLOAD_COMPLETED);
			m_currentUpload->GetWorkUnit()->WriteReceipt(receiptBuffer);
			UploadComplete(this, System::EventArgs::Empty);	
		}
		else
		{
			m_currentUpload->SetStatus(UploadQueueEntry::UPLOAD_FAILED);
			m_currentUpload->SetErrorString(httpResponseLine);
			UploadFailed(this, System::EventArgs::Empty);	
		}
	}
	catch (System::Exception* ex)
	{
		m_currentUpload->SetStatus(UploadQueueEntry::UPLOAD_FAILED);
		m_currentUpload->SetErrorString(ex->Message);
		UploadFailed(this, System::EventArgs::Empty);	
	}
	__finally
	{
		//ProgressChanged(this, System::EventArgs::Empty);

		if (wuDataStream)
		{
			wuDataStream->Close();
		}

		if (m_networkStream)
		{
			m_networkStream->Close();
		}

		if (m_socket)
		{
			m_socket->Close();
		}

		m_isactive = false;
	}
}

UploadQueueEntry* Uploader::GetCurrentQueueEntry()
{
	return m_currentUpload;
}

int Uploader::GetIndex()
{
	return m_index;
}

double Uploader::GetProgress()
{
	if (m_currentUpload->GetStatus() == UploadQueueEntry::UPLOADING &&
		m_currentUpload->GetWorkUnit()->GetDataSize() > 0)
	{
		return ((double)m_bytesUploaded / (double)m_currentUpload->GetWorkUnit()->GetDataSize());;
	}
	else
	{
		return -1;
	}
}

bool Uploader::IsActive()
{
	return m_isactive;
}