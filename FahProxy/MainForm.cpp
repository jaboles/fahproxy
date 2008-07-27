#include "MainForm.h"
#include "ProxyListener.h"
#include "UploadManager.h"

using namespace FahProxy;
using namespace System;
using namespace System::Windows::Forms;

void MainForm::AddQueueItem(int index, String^ time, int size, String^ username, String^ team, System::String^ userId, int machineId, String^ destServer, int status)
{
	ListViewItem^ lvi = gcnew ListViewItem();
	lvi->Text = "";
	lvi->SubItems->Add(time);
	lvi->SubItems->Add(Convert::ToString(size));
	lvi->SubItems->Add(username);
	lvi->SubItems->Add(team);
	lvi->SubItems->Add(userId);
	lvi->SubItems->Add(Convert::ToString(machineId));
	lvi->SubItems->Add(destServer);
	lvi->SubItems->Add(UploadStatusString(status));
	m_uploadList->Items->Add(lvi);
}

void MainForm::UpdateQueueItemStatus(int index, int status, double progress, System::String^ errorString)
{
	String^ statusString = UploadStatusString(status);
	if (progress > 0)
	{
		statusString = String::Concat(statusString, " (", Convert::ToString(progress * 100.0));
		statusString = String::Concat(statusString, "%)");
	}
	if (status == UploadQueueEntry::UPLOAD_FAILED)
	{
		statusString = String::Concat(statusString, " (", errorString);
		statusString = String::Concat(statusString, ")");
	}

	array<Object^>^ args = gcnew array<Object^>(3);
	args[0] = index;
	args[1] = 8;
	args[2] = statusString;
	BeginInvoke(gcnew SetUploadQueueTextDelegate(this, &MainForm::SetUploadQueueText), args);
}

void MainForm::UpdateQueueItemStatus(int index, int status)
{
	UpdateQueueItemStatus(index, status, -1, "");
}

void MainForm::RemoveQueueItem(int index)
{
	m_uploadList->Items->RemoveAt(index);
}

System::String^ MainForm::UploadStatusString(int index)
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

void MainForm::SetUploadQueueText(int index, int subItemIndex, System::String^ text)
{
	m_uploadList->Items[index]->SubItems[subItemIndex]->Text = text;
}