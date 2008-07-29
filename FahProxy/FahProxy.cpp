// FahProxy.cpp : main project file.

#include "MainForm.h"
#include "FahProxy.h"
#include "ProxyListener.h"
#include "UploadManager.h"

using namespace FahProxy;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Create the main window and run it
	gcnew FoldingAtHomeProxy();
	return 0;
}

FoldingAtHomeProxy::FoldingAtHomeProxy()
{
	MainForm^ mainForm = gcnew MainForm();


	m_uploadManager = gcnew UploadManager(mainForm);

	m_proxyListener = gcnew ProxyListener(m_uploadManager, 8080);
	m_proxyListener->Start();


	Application::Run(mainForm);

	m_proxyListener->Stop();
	m_uploadManager->Stop();
}

FoldingAtHomeProxy::~FoldingAtHomeProxy()
{
}

