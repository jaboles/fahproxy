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
	m_proxyListener = gcnew ProxyListener(8080);
	m_proxyListener->Start();

	MainForm^ mainForm = gcnew MainForm();

	m_uploadManager = gcnew UploadManager(mainForm);

	Application::Run(mainForm);
}

FoldingAtHomeProxy::~FoldingAtHomeProxy()
{
}

