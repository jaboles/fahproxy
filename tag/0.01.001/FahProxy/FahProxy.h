#pragma once

namespace FahProxy
{
	ref class ProxyListener;
	ref class UploadManager;
	ref class MainForm;

	public ref class FoldingAtHomeProxy
	{
	public:
		FoldingAtHomeProxy();
		~FoldingAtHomeProxy();

		static const System::String^ VERSION = "0.01.000";

	protected:
		void UploadEnabledMode_Changed(System::Object^ sender, System::EventArgs^ e);
		void UploadScheduleTime_Changed(System::Object^ sender, System::EventArgs^ e);
		void ClearCompletedButton_Click(System::Object^ sender, System::EventArgs^ e);
		void OpenCacheFolderButton_Click(System::Object^ sender, System::EventArgs^ e);

		ProxyListener^ m_proxyListener;
		UploadManager^ m_uploadManager;
		MainForm^ m_mainForm;
	};
}