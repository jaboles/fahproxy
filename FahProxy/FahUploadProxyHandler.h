#pragma once

#include "NormalProxyHandler.h"

namespace FahProxy
{
	public ref class FahUploadProxyHandler : NormalProxyHandler
	{
	public:
		FahUploadProxyHandler(System::String^ method, System::String^ url, System::String^ protocolVersion, System::Net::Sockets::NetworkStream^ ns, System::IO::MemoryStream^ headers);
		virtual void HandleIt() override;
	private:
		System::IO::FileStream^ m_wuStream;
		System::IO::FileStream^ m_metadataStream;
	};
}
