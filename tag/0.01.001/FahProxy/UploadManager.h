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
		void ClearCompleted();
		void Stop();
		void SetUploadsEnabled(int mode);
		void SetUploadsEnabledStartTime(System::TimeSpan t);
		void SetUploadsEnabledEndTime(System::TimeSpan t);

		static const int m_simultaneousUploads = 1;

		static const int UPLOAD_ENABLE_MODE_ON = 1;
		static const int UPLOAD_ENABLE_MODE_OFF = 2;
		static const int UPLOAD_ENABLE_MODE_SCHEDULER = 3;

	protected:
		void UploadDispatchThread();

		void UploadFinished(System::Object^ sender, System::EventArgs^ e);
		void UploadFailed(System::Object^ sender, System::EventArgs^ e);
		void ProgressChanged(System::Object^ sender, System::EventArgs^ e);

		System::Collections::ArrayList^ m_masterList;
		System::Collections::ArrayList^ m_uploaders;
		MainForm^ m_mainForm;
		bool m_running;
		int m_uploadEnableMode;
		System::TimeSpan m_uploadsEnabledStartTime;
		System::TimeSpan m_uploadsEnabledEndTime;
	};
}
