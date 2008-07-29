#pragma once

namespace FahProxy
{
	public ref class NormalProxyHandler
	{
	public:
		NormalProxyHandler(System::String^ localHost, System::String^ method, System::String^ url, System::String^ protocolVersion, System::Net::Sockets::NetworkStream^ ns, System::IO::MemoryStream^ headers);
		~NormalProxyHandler();
		virtual void HandleIt();
	protected:
		void PassThroughRequestHeaders();
		void PassThroughRequestContent();
		void PassThroughResponseHeaders();
		void PassThroughResponseContent();
		void PassThroughEverything();
		void CopyBytes(System::IO::Stream^ stream1, System::IO::Stream^ stream2, int contentLength);
		void WriteTrace(System::String^ line);
		void WriteTrace(array<unsigned char,1>^ buffer, int index, int count);

		System::String^ m_requestMethod;
		System::String^ m_protocolVersion;
		System::String^ m_host;
		System::String^ m_localHost;
		System::IO::MemoryStream^ m_headersStream;
		int m_port;
		System::String^ m_path;
		int m_contentLength;
		int m_requestContentLength;
		System::Net::Sockets::NetworkStream^ m_requestStream;
		System::Net::Sockets::NetworkStream^ m_proxyStream;
		array<unsigned char, 1>^ m_buffer;
		System::IO::FileStream^ m_traceStream;
		
		static const int BUFFER_LENGTH = 10240;

	private:
	};
}