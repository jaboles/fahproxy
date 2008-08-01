#pragma once

namespace FahProxy
{
	public __gc class UploadManager;

	public __gc class ProxyListener
	{
	public:
		ProxyListener(UploadManager* uploadManager, int port);
		~ProxyListener();
		void Start();
		void Stop();
		
	private:
		void ThreadEntry();

		int m_port;
		System::Threading::Thread* m_listenThread;
		System::Net::Sockets::Socket* m_listenSocket;
		UploadManager* m_uploadManager;
		bool m_running;

		static const int MAX_LISTEN_BACKLOG = 10;
	};
}