#pragma once

namespace FahProxy
{
	ref class WorkUnit;
	ref class MainForm;

	public ref class UploadQueueEntry
	{
	public:
		UploadQueueEntry(WorkUnit^ wu);
		WorkUnit^ GetWorkUnit();
		void SetErrorString(System::String^ errorString);
		void SetStatus(int status);
		System::String^ GetErrorString();
		int GetStatus();
		bool FailedRecently(int seconds);

		static const int WAITING = 1;
		static const int UPLOADING = 2;
		static const int UPLOAD_COMPLETED = 3;
		static const int UPLOAD_FAILED = 4;
	protected:
		WorkUnit^ m_workUnit;
		int m_status;
		System::String^ m_errorString;
		__int64 m_lastFailed;
	};

	public ref class UploadManager
	{
	public:
		UploadManager(MainForm^ mainForm);
		~UploadManager();
		void AddToQueue(WorkUnit^ wu);

		static const int m_simultaneousUploads = 1;

	protected:
		void UploadDispatchThread();

		void UploadFinished(System::Object^ sender, System::EventArgs^ e);
		void UploadFailed(System::Object^ sender, System::EventArgs^ e);
		void ProgressChanged(System::Object^ sender, System::EventArgs^ e);

		System::Collections::ArrayList^ m_masterList;
		System::Collections::Queue^ m_uploadQueue;
		System::Collections::ArrayList^ m_uploaders;
		MainForm^ m_mainForm;
	};
}
