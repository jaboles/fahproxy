#pragma once

namespace FahProxy
{
	public ref class Utils
	{
	public:
		static void WriteLineToStream(System::IO::Stream^ stream, System::String^ line);
		static System::String^ ReadLineFromStream(System::IO::Stream^ stream);
	};
}