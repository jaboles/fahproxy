#pragma once

namespace FahProxy
{
	public ref class WorkUnit
	{
	public:
		WorkUnit(System::String^ filename);
		~WorkUnit();
		System::DateTime GetTime();
		int GetDataSize();
		System::String^ GetUsername();
		System::String^ GetUserId();
		int GetMachineId();
		System::String^ GetTeam();
		System::String^ GetUploadHost();
		int GetUploadPort();
		System::IO::Stream^ GetDataStream();
		System::IO::Stream^ GetTranslatedResponseStream();

		static const int FAH_RESPONSE_BUFFER_SIZE = 512;

	private:

		System::String^ m_baseFilename;
		System::String^ m_path;
		System::String^ m_uploadHost;
		int m_uploadPort;
		int m_wuDataSize;
		System::DateTime m_time;
		array<unsigned char, 1>^ m_info;
	};
}