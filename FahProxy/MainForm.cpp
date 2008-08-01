#include "MainForm.h"
#include "ProxyListener.h"
#include "UploadManager.h"

using namespace FahProxy;
using namespace System;
using namespace System::Windows::Forms;

void MainForm::AddQueueItem(int index, String* time, String* receivedFrom, int size, String* username, String* team, System::String* userId, int machineId, String* destServer, int status)
{
	if (m_disposed) return;

	ListViewItem* lvi = new ListViewItem();
	lvi->Text = "";
	lvi->SubItems->Add(time);
	lvi->SubItems->Add(receivedFrom);
	lvi->SubItems->Add(String::Format(S"{0:0.00} M", __box((double)size / 1048576.0)));
	lvi->SubItems->Add(username);
	lvi->SubItems->Add(team);
	lvi->SubItems->Add(userId);
	lvi->SubItems->Add(Convert::ToString(machineId));
	lvi->SubItems->Add(destServer);
	lvi->SubItems->Add(UploadStatusString(status));

	if (this->InvokeRequired)
	{
		Object* args __gc[] = new Object* __gc [1];
		args[0] = lvi;
		BeginInvoke(new AddUploadQueueItemDelegate(this, &MainForm::AddUploadQueueItem), args);
	}
	else
	{
		m_uploadList->Items->Add(lvi);
	}
}

void MainForm::UpdateQueueItemStatus(int index, int status, double progress, System::String* errorString)
{
	if (m_disposed) return;

	String* statusString = UploadStatusString(status);
	if (progress > 0)
	{
		statusString = String::Concat(statusString, String::Format(S" ({0:0.00}%)", __box(progress * 100.0)));
	}
	if (status == UploadQueueEntry::UPLOAD_FAILED)
	{
		statusString = String::Concat(statusString, String::Format(S" ({0})", errorString));
	}

	if (this->InvokeRequired)
	{
		System::Object* args __gc [] = new System::Object* __gc [3];
		args[0] = __box(index);
		args[1] = __box(9);
		args[2] = statusString;
		BeginInvoke(new SetUploadQueueTextDelegate(this, &MainForm::SetUploadQueueText), args);
	}
	else
	{
		m_uploadList->Items->Item[index]->SubItems->Item[9]->Text = statusString;
	}
}

void MainForm::UpdateQueueItemStatus(int index, int status)
{
	UpdateQueueItemStatus(index, status, -1, "");
}

void MainForm::RemoveQueueItem(int index)
{
	if (m_disposed) return;

	m_uploadList->Items->RemoveAt(index);
}

System::String* MainForm::UploadStatusString(int index)
{
	switch (index)
	{
	case UploadQueueEntry::WAITING:
		return "Waiting";
	case UploadQueueEntry::UPLOADING:
		return "Uploading";
	case UploadQueueEntry::UPLOAD_COMPLETED:
		return "Upload Completed";
	case UploadQueueEntry::UPLOAD_FAILED:
		return "Retrying Shortly";
	default:
		return "Unknown";
	}
}

void MainForm::SetUploadQueueText(int index, int subItemIndex, System::String* text)
{
	m_uploadList->Items->Item[index]->SubItems->Item[subItemIndex]->Text = text;
}

void MainForm::AddUploadQueueItem(System::Windows::Forms::ListViewItem *item)
{
	m_uploadList->Items->Add(item);
}