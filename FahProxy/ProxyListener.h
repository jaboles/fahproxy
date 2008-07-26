#pragma once

namespace FahProxy
{
	public ref class ProxyListener
	{
	public:
		ProxyListener(int port);
		~ProxyListener();
		void Start();
		void Stop();
		
	private:
		void ThreadEntry();

		int m_port;
		System::Threading::Thread^ m_listenThread;
		System::Net::Sockets::Socket^ m_listenSocket;

		static const int MAX_LISTEN_BACKLOG = 10;
	};
}