#pragma once

namespace FahProxy
{
	public __gc class ProxyListener;
	public __gc class UploadManager;

	public __gc class FoldingAtHomeProxy
	{
	public:
		FoldingAtHomeProxy();
		~FoldingAtHomeProxy();

		static System::String* VERSION = "0.01.000";

	protected:
		ProxyListener* m_proxyListener;
		UploadManager* m_uploadManager;
	};
}