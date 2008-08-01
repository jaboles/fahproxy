#pragma once

namespace FahProxy
{
	public __gc class Utils
	{
	public:
		static void WriteLineToStream(System::IO::Stream* stream, System::String* line);
		static System::String* ReadLineFromStream(System::IO::Stream* stream);

		static const int MAX_LINE_READ_BYTES = 10000;
	};
}