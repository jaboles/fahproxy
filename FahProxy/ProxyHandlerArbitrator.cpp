#include "ProxyHandlerArbitrator.h"
#include "NormalProxyHandler.h"

using namespace FahProxy;
using namespace System::Net::Sockets;
using namespace System::IO;
#include "Utils.h"

using namespace System;

ProxyHandlerArbitrator::ProxyHandlerArbitrator(Socket^ clientSocket)
{
	m_clientSocket = clientSocket;
	m_networkStream = gcnew NetworkStream(m_clientSocket);
}

ProxyHandlerArbitrator::~ProxyHandlerArbitrator()
{
}

void ProxyHandlerArbitrator::HandleIt()
{
	try
	{
		String^ requestLine = Utils::ReadLineFromStream(m_networkStream);
		array<wchar_t>^ splitChars = {' '};
		array<String^>^ requestComponents = requestLine->Split(splitChars);

		String^ method = requestComponents[0];
		String^ url = requestComponents[1];
		String^ protocol = requestComponents[2];

		NormalProxyHandler^ h = gcnew NormalProxyHandler(method, url, protocol, m_networkStream);
		h->HandleIt();
	}
	catch (System::IO::IOException^)
	{
	}
	finally
	{
		m_networkStream->Close();
		m_clientSocket->Close();
	}
}