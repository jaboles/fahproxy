#include "UploadManager.h"
#include "WorkUnit.h"
#include "Uploader.h"
#include "MainForm.h"

using namespace FahProxy;
using namespace System;
using namespace System::IO;
using namespace System::Collections;
using namespace System::Threading;

UploadQueueEntry::UploadQueueEntry(WorkUnit* wu)
{
	m_workUnit = wu;
	m_lastFailed = 0;
}

WorkUnit* UploadQueueEntry::GetWorkUnit()
{
	return m_workUnit;
}

void UploadQueueEntry::SetStatus(int status)
{
	m_status = status;
	if (status == UploadQueueEntry::UPLOAD_FAILED)
	{
		m_lastFailed = System::DateTime::Now.Ticks;
	}
}

int UploadQueueEntry::GetStatus()
{
	return m_status;
}

void UploadQueueEntry::SetErrorString(System::String* errorString)
{
	m_errorString = errorString;
}

System::String* UploadQueueEntry::GetErrorString()
{
	return m_errorString;
}

bool UploadQueueEntry::FailedRecently(int seconds)
{
	if (m_lastFailed == 0) false;
	__int64 now = System::DateTime::Now.Ticks;
	return ((now - m_lastFailed) / 10000000) < seconds;
}




UploadManager::UploadManager(MainForm* mainForm)
{
	m_mainForm = mainForm;
	m_running = true;
	m_uploaders = gcnew ArrayList();
	m_masterList = gcnew ArrayList();

	String* folder = String::Concat(System::Environment::GetEnvironmentVariable("appdata"), "\\FahProxy\\");
	String* fileList __gc [] = Directory::GetFiles(folder, "*.wu", SearchOption::TopDirectoryOnly);
	for (int i = 0; i < fileList->Length; i++)
	{
		// Strip off the '.wu' and the path.
		String* basename = (new FileInfo(fileList[i]))->Name;
		basename = basename->Substring(0, basename->Length - 3);

		AddToQueue(new WorkUnit(basename));
	}

	for (int i = 0; i < m_simultaneousUploads; i++)
	{
		Uploader* u = new Uploader(i);
		u->ProgressChanged += new System::EventHandler(this, &UploadManager::ProgressChanged);
		u->UploadComplete += new System::EventHandler(this, &UploadManager::UploadFinished);
		u->UploadFailed += new System::EventHandler(this, &UploadManager::UploadFailed);
		m_uploaders->Add(u);
	}

	ThreadStart* ts = new ThreadStart(this, &UploadManager::UploadDispatchThread);
	(new Thread(ts))->Start();
}

UploadManager::~UploadManager()
{
}

void UploadManager::AddToQueue(WorkUnit* wu)
{
	UploadQueueEntry* qe = new UploadQueueEntry(wu);
	qe->SetStatus(UploadQueueEntry::WAITING);

	m_masterList->Add(qe);

	//if (m_mainForm && m_mainForm->Visible)
	{
		m_mainForm->AddQueueItem
		(
			0,
			wu->GetTime().ToString(),
			wu->GetHostReceivedFrom(),
			wu->GetDataSize(),
			wu->GetUsername(),
			wu->GetTeam(),
			wu->GetUserId(),
			wu->GetMachineId(),
			String::Concat(wu->GetUploadHost(), ":", Convert::ToString(wu->GetUploadPort())),
			qe->GetStatus()
		);
	}
}

void UploadManager::Stop()
{
	m_running = false;
}

void UploadManager::UploadDispatchThread()
{
	while (m_running)
	{
		System::Threading::Thread::Sleep(1000);

		for (int i = 0; i < m_uploaders->Count; i++)
		{
			Uploader* u = static_cast<Uploader*>(m_uploaders->Item[i]);

			if (!u->IsActive())
			{
				for (int j = 0; j < m_masterList->Count; j++)
				{
					UploadQueueEntry^ qe = static_cast<UploadQueueEntry^>(m_masterList[j]);

					if
					(
						(qe->GetStatus() == UploadQueueEntry::WAITING || qe->GetStatus() == UploadQueueEntry::UPLOAD_FAILED) &&
						!qe->FailedRecently(120)
					)
					{
						u->DoUpload(qe);
					}
				}
			}
		}
	}
}

void UploadManager::UploadFinished(System::Object* sender, System::EventArgs* e)
{
	Uploader* u = static_cast<Uploader*>(sender);
	UploadQueueEntry* qe = u->GetCurrentQueueEntry();

	qe->GetWorkUnit()->CleanUpFile();

	// Find the queue entry in the master list.
	for (int i = 0; i < m_masterList->Count; i++)
	{
		if (static_cast<UploadQueueEntry*>(m_masterList->Item[i]) == qe/* && m_mainForm && m_mainForm->Visible*/)
		{
			m_mainForm->UpdateQueueItemStatus(i, qe->GetStatus(), u->GetProgress(), qe->GetErrorString());
		}
	}
}

void UploadManager::UploadFailed(System::Object* sender, System::EventArgs* e)
{
	Uploader* u = static_cast<Uploader*>(sender);
	UploadQueueEntry* qe = u->GetCurrentQueueEntry();

	// Find the queue entry in the master list.
	for (int i = 0; i < m_masterList->Count; i++)
	{
		if (static_cast<UploadQueueEntry*>(m_masterList->Item[i]) == qe/* && m_mainForm && m_mainForm->Visible*/)
		{
			m_mainForm->UpdateQueueItemStatus(i, qe->GetStatus(), u->GetProgress(), qe->GetErrorString());
		}
	}
}

void UploadManager::ProgressChanged(System::Object* sender, System::EventArgs* e)
{
	Uploader* u = static_cast<Uploader*>(sender);
	UploadQueueEntry* qe = u->GetCurrentQueueEntry();

	// Find the queue entry in the master list.
	for (int i = 0; i < m_masterList->Count; i++)
	{
		if (static_cast<UploadQueueEntry*>(m_masterList->Item[i]) == qe/* && m_mainForm && m_mainForm->Visible*/)
		{
			m_mainForm->UpdateQueueItemStatus(i, qe->GetStatus(), u->GetProgress(), qe->GetErrorString());
		}
	}
}