#include "Utils.h"

using namespace FahProxy;
using namespace System;
using namespace System::IO;
using namespace System::Text;

void Utils::WriteLineToStream(System::IO::Stream^ stream, System::String^ line)
{
	Encoding^ enc = Encoding::Default;

	array<unsigned char,1>^ bytes = enc->GetBytes(line);
	stream->Write(bytes, 0, bytes->Length);
	stream->WriteByte(13);
	stream->WriteByte(10);
}

System::String^ Utils::ReadLineFromStream(System::IO::Stream^ stream)
{
	Encoding^ enc = Encoding::Default;

	StringBuilder^ sb = gcnew StringBuilder();	
	
	array<unsigned char,1>^ bytes = gcnew array<unsigned char,1>(1);
	for (int i = 0; bytes[0] != 13 && bytes[0] != 10; i++)
	{
		stream->Read(bytes, 0, 1);

		if (bytes[0] != 13 && bytes[0] != 10)
		{
			sb->Append(enc->GetString(bytes));
		}

		if (i > MAX_LINE_READ_BYTES)
		{
			break;
		}
	}

	// If it's a \r, read the \n.
	if (bytes[0] == 13)
	{
		stream->ReadByte();
	}

	return sb->ToString();
}

