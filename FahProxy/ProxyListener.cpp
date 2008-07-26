#include "ProxyListener.h"
#include "ProxyHandlerArbitrator.h"

using namespace FahProxy;
using namespace System::Threading;
using namespace System::Net;
using namespace System::Net::Sockets;
using namespace System::IO;

ProxyListener::ProxyListener(int port)
{
	m_port = port;
}

ProxyListener::~ProxyListener()
{
}

void ProxyListener::Start()
{
	ThreadStart^ ts = gcnew ThreadStart(this, &ProxyListener::ThreadEntry);
	m_listenThread = gcnew Thread(ts);
	m_listenThread->Start();
}

void ProxyListener::Stop()
{
	//m_listenSocket->Shutdown(SocketShutdown::Both);
}

void ProxyListener::ThreadEntry()
{
	m_listenSocket = gcnew Socket(AddressFamily::InterNetwork, SocketType::Stream, ProtocolType::Tcp);
	m_listenSocket->Bind(gcnew IPEndPoint(IPAddress::Any, m_port));
	m_listenSocket->Listen(MAX_LISTEN_BACKLOG);

	while (true)
	{
		Socket^ s = m_listenSocket->Accept();
		ProxyHandlerArbitrator^ a = gcnew ProxyHandlerArbitrator(s);
		a->HandleIt();
	}
}