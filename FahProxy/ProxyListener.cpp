#include "ProxyListener.h"
#include "ProxyHandlerArbitrator.h"
#include "UploadManager.h"

using namespace FahProxy;
using namespace System::Threading;
using namespace System::Net;
using namespace System::Net::Sockets;
using namespace System::IO;

ProxyListener::ProxyListener(UploadManager^ uploadManager, int port)
{
	m_port = port;
	m_uploadManager = uploadManager;
	m_running = false;
}

ProxyListener::~ProxyListener()
{
}

void ProxyListener::Start()
{
	m_running = true;
	ThreadStart^ ts = gcnew ThreadStart(this, &ProxyListener::ThreadEntry);
	m_listenThread = gcnew Thread(ts);
	m_listenThread->Start();
}

void ProxyListener::Stop()
{
	//m_listenSocket->Shutdown(SocketShutdown::Both);
	m_running = false;
	m_listenSocket->Close();
}

void ProxyListener::ThreadEntry()
{
	m_listenSocket = gcnew Socket(AddressFamily::InterNetwork, SocketType::Stream, ProtocolType::Tcp);
	m_listenSocket->Bind(gcnew IPEndPoint(IPAddress::Any, m_port));
	m_listenSocket->Listen(MAX_LISTEN_BACKLOG);

	while (m_running)
	{
		try
		{
			Socket^ s = m_listenSocket->Accept();

			ProxyHandlerArbitrator^ a = gcnew ProxyHandlerArbitrator(s, m_uploadManager);

			ThreadStart^ ts = gcnew ThreadStart(a, &ProxyHandlerArbitrator::HandleIt);
			Thread^ t = gcnew Thread(ts);
			t->Start();
		}
		catch (System::Net::Sockets::SocketException^)
		{
			// Squelched!!
		}
	}
}