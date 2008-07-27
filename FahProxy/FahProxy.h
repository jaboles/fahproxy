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

	protected:
		ProxyListener^ m_proxyListener;
		UploadManager^ m_uploadManager;
	};
}