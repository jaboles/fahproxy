#include "MainForm.h"
#include "ProxyListener.h"
#include "UploadManager.h"

using namespace FahProxy;
using namespace System;
using namespace System::Windows::Forms;

void MainForm::AddQueueItem(int index, String^ time, String^ receivedFrom, int size, String^ username, String^ team, System::String^ userId, int machineId, String^ destServer, int status)
{
	if (m_disposed) return;

	ListViewItem^ lvi = gcnew ListViewItem();
	lvi->Text = "";
	lvi->SubItems->Add(time);
	lvi->SubItems->Add(receivedFrom);
	lvi->SubItems->Add(String::Format("{0:0.00} M", (double)size / 1048576.0));
	lvi->SubItems->Add(username);
	lvi->SubItems->Add(team);
	lvi->SubItems->Add(userId);
	lvi->SubItems->Add(Convert::ToString(machineId));
	lvi->SubItems->Add(destServer);
	lvi->SubItems->Add(UploadStatusString(status));

	if (this->InvokeRequired)
	{
		array<Object^>^ args = gcnew array<Object^>(1);
		args[0] = lvi;
		BeginInvoke(gcnew AddUploadQueueItemDelegate(this, &MainForm::AddUploadQueueItem), args);
	}
	else
	{
		m_uploadList->Items->Add(lvi);
	}
}

void MainForm::UpdateQueueItemStatus(int index, int status, double progress, System::String^ errorString)
{
	if (m_disposed) return;

	String^ statusString = UploadStatusString(status);
	if (progress > 0)
	{
		statusString = String::Concat(statusString, String::Format(" ({0:0.00}%)", progress * 100.0));
	}
	if (status == UploadQueueEntry::UPLOAD_FAILED)
	{
		statusString = String::Concat(statusString, String::Format(" ({0})", errorString));
	}

	if (this->InvokeRequired)
	{
		array<Object^>^ args = gcnew array<Object^>(3);
		args[0] = index;
		args[1] = 9;
		args[2] = statusString;
		BeginInvoke(gcnew SetUploadQueueTextDelegate(this, &MainForm::SetUploadQueueText), args);
	}
	else
	{
		m_uploadList->Items[index]->SubItems[9]->Text = statusString;
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

bool MainForm::IsUploadEnabledModeOnChecked()
{
	return m_uploadOnRadioButton->Checked;
}

bool MainForm::IsUploadEnabledModeOffChecked()
{
	return m_uploadOffRadioButton->Checked;
}

bool MainForm::IsUploadEnabledModeSchedulerChecked()
{
	return m_uploadScheduleRadioButton->Checked;
}

System::TimeSpan MainForm::GetUploadSchedulerStartTime()
{
	return m_uploadStartTime->Value.TimeOfDay;
}

System::TimeSpan MainForm::GetUploadSchedulerEndTime()
{
	return m_uploadEndTime->Value.TimeOfDay;
}


System::String^ MainForm::UploadStatusString(int index)
{
	switch (index)
	{
	case UploadQueueEntry::WAITING:
		return "Queued";
	case UploadQueueEntry::UPLOADING:
		return "Uploading";
	case UploadQueueEntry::UPLOAD_COMPLETED:
		return "Upload Completed";
	case UploadQueueEntry::UPLOAD_FAILED:
		return "Failed, retrying shortly";
	default:
		return "Unknown";
	}
}

void MainForm::SetUploadQueueText(int index, int subItemIndex, System::String^ text)
{
	m_uploadList->Items[index]->SubItems[subItemIndex]->Text = text;
}

void MainForm::AddUploadQueueItem(System::Windows::Forms::ListViewItem ^item)
{
	m_uploadList->Items->Add(item);
}

void MainForm::UploadEnabledModeRadioButtons_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
{
	UploadEnabledModeChanged(sender, e);
}

void MainForm::UploadScheduleTime_ValueChanged(System::Object^ sender, System::EventArgs^ e)
{
	UploadScheduleTimeChanged(sender, e);
}

void MainForm::ClearCompletedButton_Click(System::Object^ sender, System::EventArgs^ e)
{
	ClearCompletedButtonClicked(sender, e);
}

void MainForm::OpenCacheFolderButton_Click(System::Object^ sender, System::EventArgs^ e)
{
	OpenCacheFolderButtonClicked(sender, e);
}