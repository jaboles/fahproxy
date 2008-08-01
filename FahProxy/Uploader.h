#pragma once

namespace FahProxy
{
	ref class WorkUnit;
	ref class UploadQueueEntry;

	public ref class Uploader
	{
	public:
		Uploader(int index);
		~Uploader();

		void DoUpload(UploadQueueEntry^ wu);
		UploadQueueEntry^ GetCurrentQueueEntry();
		int GetIndex();
		double GetProgress();
		bool IsActive();

		event System::EventHandler^ UploadComplete;
		event System::EventHandler^ UploadFailed;
		event System::EventHandler^ ProgressChanged;

		static const int BUFFER_SIZE = 4000;
	private:
		void UploadThreadEntry();

		System::IO::Stream^ m_metadataStream;
		System::IO::Stream^ m_wuStream;
		System::IO::Stream^ m_networkStream;
		System::Net::Sockets::Socket^ m_socket;
		UploadQueueEntry^ m_currentUpload;
		int m_bytesUploaded;
		int m_index;
		bool m_isactive;
		array<unsigned char, 1>^ m_buffer;
	};
}