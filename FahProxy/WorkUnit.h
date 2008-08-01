#pragma once

namespace FahProxy
{
	public __gc class WorkUnit
	{
	public:
		WorkUnit(System::String* filename);
		~WorkUnit();
		System::DateTime GetTime();
		int GetDataSize();
		System::String* GetHostReceivedFrom();
		System::String* GetUsername();
		System::String* GetUserId();
		int GetMachineId();
		System::String* GetTeam();
		System::String* GetUploadHost();
		int GetUploadPort();
		System::IO::Stream* GetDataStream();
		System::IO::Stream* GetTranslatedResponseStream();
		void WriteReceipt(unsigned char receiptBuffer __gc []);
		void CleanUpFile();

		static const int FAH_RESPONSE_BUFFER_SIZE = 512;

	private:

		System::String* m_baseFilename;
		System::String* m_path;
		System::String* m_uploadHost;
		System::String* m_hostReceivedFrom;
		int m_uploadPort;
		int m_wuDataSize;
		System::DateTime m_time;
		unsigned char m_info __gc [];
	};
}