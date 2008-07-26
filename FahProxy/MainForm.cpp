#include "MainForm.h"
#include "ProxyListener.h"

using namespace FahProxy;
using namespace System::Windows::Forms;

void MainForm::StartButton_Click(System::Object^ sender, System::EventArgs^ e)
{
	m_proxyListener = gcnew ProxyListener(8080);
	m_proxyListener->Start();
}

void MainForm::StopButton_Click(System::Object^ sender, System::EventArgs^ e)
{
	m_proxyListener->Stop();
}
