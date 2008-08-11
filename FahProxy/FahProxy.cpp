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
	m_mainForm = gcnew MainForm();
	m_uploadManager = gcnew UploadManager(m_mainForm);
	m_proxyListener = gcnew ProxyListener(m_uploadManager, 8080);

	m_proxyListener->Start();

	m_mainForm->UploadEnabledModeChanged += gcnew System::EventHandler(this, &FoldingAtHomeProxy::UploadEnabledMode_Changed);
	m_mainForm->UploadScheduleTimeChanged += gcnew System::EventHandler(this, &FoldingAtHomeProxy::UploadScheduleTime_Changed);
	m_mainForm->ClearCompletedButtonClicked += gcnew System::EventHandler(this, &FoldingAtHomeProxy::ClearCompletedButton_Click);
	m_mainForm->OpenCacheFolderButtonClicked += gcnew System::EventHandler(this, &FoldingAtHomeProxy::OpenCacheFolderButton_Click);

	Application::Run(m_mainForm);

	m_proxyListener->Stop();
	m_uploadManager->Stop();
}

FoldingAtHomeProxy::~FoldingAtHomeProxy()
{
}

void FoldingAtHomeProxy::UploadEnabledMode_Changed(System::Object^ sender, System::EventArgs^ e)
{
	if (m_mainForm->IsUploadEnabledModeOnChecked())
	{
		m_uploadManager->SetUploadsEnabled(UploadManager::UPLOAD_ENABLE_MODE_ON);
	}
	else if (m_mainForm->IsUploadEnabledModeOffChecked())
	{
		m_uploadManager->SetUploadsEnabled(UploadManager::UPLOAD_ENABLE_MODE_OFF);
	}
	else if (m_mainForm->IsUploadEnabledModeSchedulerChecked())
	{
		m_uploadManager->SetUploadsEnabledStartTime(m_mainForm->GetUploadSchedulerStartTime());
		m_uploadManager->SetUploadsEnabledEndTime(m_mainForm->GetUploadSchedulerEndTime());
		m_uploadManager->SetUploadsEnabled(UploadManager::UPLOAD_ENABLE_MODE_SCHEDULER);
	}
}

void FoldingAtHomeProxy::UploadScheduleTime_Changed(System::Object^ sender, System::EventArgs^ e)
{
	m_uploadManager->SetUploadsEnabledStartTime(m_mainForm->GetUploadSchedulerStartTime());
	m_uploadManager->SetUploadsEnabledEndTime(m_mainForm->GetUploadSchedulerEndTime());
}

void FoldingAtHomeProxy::ClearCompletedButton_Click(System::Object^ sender, System::EventArgs^ e)
{
	m_uploadManager->ClearCompleted();
}

void FoldingAtHomeProxy::OpenCacheFolderButton_Click(System::Object^ sender, System::EventArgs^ e)
{
	String^ appDataFolder = System::Environment::GetEnvironmentVariable("appdata");
	System::Diagnostics::Process::Start("explorer.exe", String::Concat(appDataFolder, "\\FahProxy"));
}