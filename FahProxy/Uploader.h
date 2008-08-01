#pragma once

namespace FahProxy
{
	public __gc class WorkUnit;
	public __gc class UploadQueueEntry;

	public __gc class Uploader
	{
	public:
		Uploader(int index);
		~Uploader();

		void DoUpload(UploadQueueEntry* wu);
		UploadQueueEntry* GetCurrentQueueEntry();
		int GetIndex();
		double GetProgress();
		bool IsActive();

		__event System::EventHandler* UploadComplete;
		__event System::EventHandler* UploadFailed;
		__event System::EventHandler* ProgressChanged;

		static const int BUFFER_SIZE = 4000;
	private:
		void UploadThreadEntry();

		System::IO::Stream* m_metadataStream;
		System::IO::Stream* m_wuStream;
		System::IO::Stream* m_networkStream;
		System::Net::Sockets::Socket* m_socket;
		UploadQueueEntry* m_currentUpload;
		int m_bytesUploaded;
		int m_index;
		bool m_isactive;
		unsigned char m_buffer __gc [];
	};
}