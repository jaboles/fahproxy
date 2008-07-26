#pragma once

namespace FahProxy
{
	public ref class ProxyHandlerArbitrator
	{
	public:
		ProxyHandlerArbitrator(System::Net::Sockets::Socket^ clientSocket);
		~ProxyHandlerArbitrator();
		void HandleIt();

	private:
		System::Net::Sockets::Socket^ m_clientSocket;
		System::Net::Sockets::NetworkStream^ m_networkStream;
	};
}