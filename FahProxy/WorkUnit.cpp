#include "WorkUnit.h"
#include "Utils.h"

using namespace FahProxy;
using namespace System;
using namespace System::IO;

WorkUnit::WorkUnit(String^ filename)
{
	m_baseFilename = filename;
	m_path = String::Concat(System::Environment::GetEnvironmentVariable("appdata"), "\\FahProxy\\", m_baseFilename);

	String^ wuDataFilename = String::Concat(m_path, ".wu");
	FileInfo^ fi = gcnew FileInfo(wuDataFilename);
	m_wuDataSize = fi->Length;
	m_time = fi->CreationTime;

	// Read data
	Stream^ fs = GetDataStream();
	m_info = gcnew array<unsigned char, 1>(FAH_RESPONSE_BUFFER_SIZE);
	fs->Read(m_info, 0, m_info->Length);
	fs->Close();

	// Read metadata
	fs = gcnew FileStream(String::Concat(m_path, ".txt"), FileMode::Open, FileAccess::Read);
	m_uploadHost = Utils::ReadLineFromStream(fs);
	m_uploadPort = Convert::ToInt32(Utils::ReadLineFromStream(fs));
	m_hostReceivedFrom = Utils::ReadLineFromStream(fs);
	fs->Close();

}

WorkUnit::~WorkUnit()
{
}

DateTime WorkUnit::GetTime()
{
	return m_time;
}

int WorkUnit::GetDataSize()
{
	return m_wuDataSize;
}

System::String^ WorkUnit::GetHostReceivedFrom()
{
	return m_hostReceivedFrom;
}

System::String^ WorkUnit::GetUserId()
{
	array<int,1>^ a = gcnew array<int,1>(8);
	Array::Copy(m_info, 288, a, 0, 8);

	__int64 userId = 0;
	for (int i = 0; i < 8; i++)
	{
		userId += ((__int64)a[i] << ((7-i) * 8));
	}

	userId -= GetMachineId();

	return userId.ToString("X");
}

String^ WorkUnit::GetUsername()
{
	return System::Text::Encoding::ASCII->GetString(m_info, 160, 64);
}

int WorkUnit::GetMachineId()
{
	return (int)m_info[87];
}

String^ WorkUnit::GetTeam()
{
	return System::Text::Encoding::ASCII->GetString(m_info, 224, 64);
}

System::String^ WorkUnit::GetUploadHost()
{
	return m_uploadHost;
}

int WorkUnit::GetUploadPort()
{
	return m_uploadPort;
}

System::IO::Stream^ WorkUnit::GetDataStream()
{
	String^ filename = String::Concat(m_path, ".wu");
	return gcnew FileStream(filename, FileMode::Open, FileAccess::Read);
}

System::IO::Stream^ WorkUnit::GetTranslatedResponseStream()
{

	MemoryStream^ ms = gcnew MemoryStream();
	array<unsigned char, 1>^ a = gcnew array<unsigned char, 1>(4);

	// decimal 400 (offset 0)
	ms->WriteByte(0x00); ms->WriteByte(0x00); ms->WriteByte(0x01); ms->WriteByte(0x90);

	// decimal 17 (offset 4)
	ms->WriteByte(0x00); ms->WriteByte(0x00); ms->WriteByte(0x00); ms->WriteByte(0x11);

	// ? (offset 8)
	Array::Copy(m_info, 8, a, 0, 4); 
	Array::Reverse(a);
	ms->Write(a, 0, a->Length);

	// ? (offset 12)
	Array::Copy(m_info, 12, a, 0, 4); 
	Array::Reverse(a);
	ms->Write(a, 0, a->Length);

	// zeros (offset 16)
	ms->Write(m_info, 16, 64);

	// Machine ID (offset 80)
	ms->Write(m_info, 80, 8);

	// IP address (offset 88)
	ms->Write(m_info, 88, 4);

	// Zeros (offset 92)
	ms->Write(m_info, 92, 68);

	// Username (offset 160)
	ms->Write(m_info, 160, 64);

	// Team number as string (offset 224)
	ms->Write(m_info, 224, 64);

	// User ID + machine ID
	ms->Write(m_info, 288, 8);

	// Zeros (offset 296)
	ms->Write(m_info, 296, 8);

	// ? (reversed in response) (offset 304)
	Array::Copy(m_info, 304, a, 0, 4); 
	Array::Reverse(a);
	ms->Write(a, 0, a->Length);
	
	// ? (reversed in response) (offset 308)
	Array::Copy(m_info, 308, a, 0, 4); 
	Array::Reverse(a);
	ms->Write(a, 0, a->Length);
	
	// ? (reversed in response) (offset 312)
	Array::Copy(m_info, 312, a, 0, 4); 
	Array::Reverse(a);
	ms->Write(a, 0, a->Length);

	// ? (reversed in response) (offset 316)
	Array::Copy(m_info, 316, a, 0, 4); 
	Array::Reverse(a);
	ms->Write(a, 0, a->Length);

	// Zeros (offset 320)
	ms->Write(m_info, 320, 24);

	// IP address (offset 344)
	ms->Write(m_info, 344, 4);

	// Zeros (offset 348)
	ms->Write(m_info, 348, 8);

	// ? (reversed in response) (offset 356)
	Array::Copy(m_info, 356, a, 0, 4); 
	Array::Reverse(a);
	ms->Write(a, 0, a->Length);

	// Zeros (offset 360)
	ms->Write(m_info, 360, 80);

	// decimal 513? (offset 440)
	ms->Write(m_info, 440, 8);

	// Zeros (offset 448)
	ms->Write(m_info, 448, 64);

	// There. that should be 512 bytes.
	ms->Seek(0, SeekOrigin::Begin);
	return ms;
}

void WorkUnit::WriteReceipt(array<unsigned char,1>^ receiptBuffer)
{
	Stream^ f = gcnew FileStream(String::Concat(m_path, ".receipt"), FileMode::Create);
	f->Write(receiptBuffer, 0, 512);
	f->Close();
}

void WorkUnit::CleanUpFile()
{
	try
	{
		File::Delete(String::Concat(m_path, ".wu"));
		File::Delete(String::Concat(m_path, ".txt"));
	}
	catch (System::IO::IOException^)
	{
		// Ignore.
	}
}