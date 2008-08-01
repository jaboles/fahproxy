#pragma once

#include "NormalProxyHandler.h"

namespace FahProxy
{
	public __gc class UploadManager;

	public __gc class FahUploadProxyHandler : public NormalProxyHandler
	{
	public:
		FahUploadProxyHandler(System::String* localHost, System::String* method, System::String* url, System::String* protocolVersion, System::Net::Sockets::NetworkStream* ns, System::IO::MemoryStream* headers, UploadManager* uploadManager);
		virtual void HandleIt();
	private:
		System::IO::FileStream* m_wuStream;
		System::IO::FileStream* m_metadataStream;
		UploadManager* m_uploadManager;
	};
}
