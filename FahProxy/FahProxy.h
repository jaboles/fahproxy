#pragma once

namespace FahProxy
{
	ref class ProxyListener;
	ref class UploadManager;

	public ref class FoldingAtHomeProxy
	{
	public:
		FoldingAtHomeProxy();
		~FoldingAtHomeProxy();

		static const System::String^ VERSION = "0.01.000";

	protected:
		ProxyListener^ m_proxyListener;
		UploadManager^ m_uploadManager;
	};
}