#pragma once

namespace FahProxy
{
	public ref class NormalProxyHandler
	{
	public:
		NormalProxyHandler(System::String^ method, System::String^ url, System::String^ protocolVersion, System::Net::Sockets::NetworkStream^ ns);
		~NormalProxyHandler();
		void HandleIt();
	protected:
		void PassThroughRequestHeaders();
		void PassThroughRequestContent();
		void PassThroughResponseHeaders();
		void PassThroughResponseContent();
		void PassThroughEverything();
	private:
		System::String^ m_requestMethod;
		System::String^ m_protocolVersion;
		System::String^ m_host;
		int m_port;
		System::String^ m_path;
		int m_contentLength;
		int m_requestContentLength;
		System::Net::Sockets::NetworkStream^ m_requestStream;
		System::Net::Sockets::NetworkStream^ m_proxyStream;
		array<unsigned char, 1>^ m_buffer;
		
		static const int BUFFER_LENGTH = 10240;
	};
}