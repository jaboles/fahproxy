#pragma once

namespace FahProxy
{
	ref class UploadManager;

	public ref class ProxyListener
	{
	public:
		ProxyListener(UploadManager^ uploadManager, int port);
		~ProxyListener();
		void Start();
		void Stop();
		
	private:
		void ThreadEntry();

		int m_port;
		System::Threading::Thread^ m_listenThread;
		System::Net::Sockets::Socket^ m_listenSocket;
		UploadManager^ m_uploadManager;
		bool m_running;
		System::Collections::ArrayList^ m_arbitratorList;

		static const int MAX_LISTEN_BACKLOG = 10;
	};
}