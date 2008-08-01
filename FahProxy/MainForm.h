#pragma once

#include "FahProxy.h"

namespace FahProxy {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public __gc class ProxyListener;

	/// <summary>
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public __gc class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			m_disposed = false;
			InitializeComponent();
			this->Text = String::Concat(S"FAH Proxy v", FoldingAtHomeProxy::VERSION);
		}
		
		void AddQueueItem(int index, System::String* time, String* receivedFrom, int size, System::String* username, System::String* team, System::String* userId, int machineId, System::String* destServer, int status);
		void UpdateQueueItemStatus(int index, int status, double progress, System::String* errorString);
		void UpdateQueueItemStatus(int index, int status);
		void RemoveQueueItem(int index);

		static System::String* UploadStatusString(int index);

	private: System::Windows::Forms::ListView*  m_uploadList;
	private: System::Windows::Forms::ColumnHeader*  m_numberColumn;
	private: System::Windows::Forms::ColumnHeader*  m_timeColumn;
	private: System::Windows::Forms::ColumnHeader*  m_sizeColumn;
	private: System::Windows::Forms::ColumnHeader*  m_usernameColumn;
	private: System::Windows::Forms::ColumnHeader*  m_teamColumn;
	private: System::Windows::Forms::ColumnHeader*  m_userIdColumn;
	private: System::Windows::Forms::ColumnHeader*  m_machineNameColumn;
	private: System::Windows::Forms::ColumnHeader*  m_destinationColumn;
	private: System::Windows::Forms::ColumnHeader*  m_statusColumn;
	private: System::Windows::Forms::Label*  m_uploadQueueLabel;
	private: System::Windows::Forms::ColumnHeader*  m_receivedFromIpColumn;
	public: 

		__delegate void SetUploadQueueTextDelegate(int, int, System::String*);
		__delegate void AddUploadQueueItemDelegate(System::Windows::Forms::ListViewItem*);

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			m_disposed = true;

			if (components)
			{
				//delete components;
			}
		}
	
	private:


		void SetUploadQueueText(int index, int subItemIndex, System::String* text);
		void AddUploadQueueItem(System::Windows::Forms::ListViewItem* item);

		bool m_disposed;

		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container *components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->m_uploadList = (new System::Windows::Forms::ListView());
			this->m_numberColumn = (new System::Windows::Forms::ColumnHeader());
			this->m_timeColumn = (new System::Windows::Forms::ColumnHeader());
			this->m_sizeColumn = (new System::Windows::Forms::ColumnHeader());
			this->m_usernameColumn = (new System::Windows::Forms::ColumnHeader());
			this->m_teamColumn = (new System::Windows::Forms::ColumnHeader());
			this->m_userIdColumn = (new System::Windows::Forms::ColumnHeader());
			this->m_machineNameColumn = (new System::Windows::Forms::ColumnHeader());
			this->m_destinationColumn = (new System::Windows::Forms::ColumnHeader());
			this->m_statusColumn = (new System::Windows::Forms::ColumnHeader());
			this->m_uploadQueueLabel = (new System::Windows::Forms::Label());
			this->m_receivedFromIpColumn = (new System::Windows::Forms::ColumnHeader());
			this->SuspendLayout();
			// 
			// m_uploadList
			// 
			this->m_uploadList->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->m_uploadList->Columns->AddRange(new System::Windows::Forms::ColumnHeader* [10] {this->m_numberColumn, 
				this->m_timeColumn, this->m_receivedFromIpColumn, this->m_sizeColumn, this->m_usernameColumn, this->m_teamColumn, this->m_userIdColumn, 
				this->m_machineNameColumn, this->m_destinationColumn, this->m_statusColumn});
			this->m_uploadList->FullRowSelect = true;
			this->m_uploadList->HeaderStyle = System::Windows::Forms::ColumnHeaderStyle::Nonclickable;
			this->m_uploadList->Location = System::Drawing::Point(-1, 25);
			this->m_uploadList->Name = L"m_uploadList";
			this->m_uploadList->Size = System::Drawing::Size(899, 197);
			this->m_uploadList->TabIndex = 0;
			this->m_uploadList->UseCompatibleStateImageBehavior = false;
			this->m_uploadList->View = System::Windows::Forms::View::Details;
			// 
			// m_numberColumn
			// 
			this->m_numberColumn->Text = L"#";
			this->m_numberColumn->Width = 17;
			// 
			// m_timeColumn
			// 
			this->m_timeColumn->Text = L"Time";
			this->m_timeColumn->Width = 125;
			// 
			// m_sizeColumn
			// 
			this->m_sizeColumn->DisplayIndex = 3;
			this->m_sizeColumn->Text = L"Size";
			this->m_sizeColumn->Width = 52;
			// 
			// m_usernameColumn
			// 
			this->m_usernameColumn->DisplayIndex = 4;
			this->m_usernameColumn->Text = L"User";
			this->m_usernameColumn->Width = 91;
			// 
			// m_teamColumn
			// 
			this->m_teamColumn->DisplayIndex = 5;
			this->m_teamColumn->Text = L"Team";
			this->m_teamColumn->Width = 41;
			// 
			// m_userIdColumn
			// 
			this->m_userIdColumn->DisplayIndex = 6;
			this->m_userIdColumn->Text = L"User ID";
			this->m_userIdColumn->Width = 131;
			// 
			// m_machineNameColumn
			// 
			this->m_machineNameColumn->DisplayIndex = 7;
			this->m_machineNameColumn->Text = L"Mach ID";
			this->m_machineNameColumn->Width = 56;
			// 
			// m_destinationColumn
			// 
			this->m_destinationColumn->DisplayIndex = 8;
			this->m_destinationColumn->Text = L"Destination Server";
			this->m_destinationColumn->Width = 111;
			// 
			// m_statusColumn
			// 
			this->m_statusColumn->DisplayIndex = 9;
			this->m_statusColumn->Text = L"Status";
			this->m_statusColumn->Width = 174;
			// 
			// m_uploadQueueLabel
			// 
			this->m_uploadQueueLabel->AutoSize = true;
			this->m_uploadQueueLabel->Location = System::Drawing::Point(12, 9);
			this->m_uploadQueueLabel->Name = L"m_uploadQueueLabel";
			this->m_uploadQueueLabel->Size = System::Drawing::Size(79, 13);
			this->m_uploadQueueLabel->TabIndex = 1;
			this->m_uploadQueueLabel->Text = L"Upload Queue:";
			// 
			// m_receivedFromIpColumn
			// 
			this->m_receivedFromIpColumn->DisplayIndex = 2;
			this->m_receivedFromIpColumn->Text = L"Received From";
			this->m_receivedFromIpColumn->Width = 86;
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(897, 221);
			this->Controls->Add(this->m_uploadQueueLabel);
			this->Controls->Add(this->m_uploadList);
			this->Name = L"MainForm";
			this->Text = L"FAH Proxy by JB";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	};
}

