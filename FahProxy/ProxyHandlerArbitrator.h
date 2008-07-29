#pragma once

namespace FahProxy
{
	ref class UploadManager;

	public ref class ProxyHandlerArbitrator
	{
	public:
		ProxyHandlerArbitrator(System::Net::Sockets::Socket^ clientSocket, UploadManager^ uploadManager);
		~ProxyHandlerArbitrator();
		void HandleIt();

	private:
		System::Net::Sockets::Socket^ m_clientSocket;
		System::Net::Sockets::NetworkStream^ m_networkStream;
		UploadManager^ m_uploadManager;
	};
}