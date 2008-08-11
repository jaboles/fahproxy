#pragma once

#include "FahProxy.h"

namespace FahProxy {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	ref class ProxyListener;

	/// <summary>
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			m_disposed = false;
			InitializeComponent();
			this->Text = String::Concat((String^)"FAH Proxy v", (String^)FoldingAtHomeProxy::VERSION);
		}
		
		void AddQueueItem(int index, System::String^ time, String^ receivedFrom, int size, System::String^ username, System::String^ team, System::String^ userId, int machineId, System::String^ destServer, int status);
		void UpdateQueueItemStatus(int index, int status, double progress, System::String^ errorString);
		void UpdateQueueItemStatus(int index, int status);
		void RemoveQueueItem(int index);

		// Form accessors
		bool IsUploadEnabledModeOnChecked();
		bool IsUploadEnabledModeOffChecked();
		bool IsUploadEnabledModeSchedulerChecked();
		System::TimeSpan GetUploadSchedulerStartTime();
		System::TimeSpan GetUploadSchedulerEndTime();

		static System::String^ UploadStatusString(int index);

		delegate void SetUploadQueueTextDelegate(int, int, System::String^);
		delegate void AddUploadQueueItemDelegate(System::Windows::Forms::ListViewItem^);

		event System::EventHandler^ UploadEnabledModeChanged;
		event System::EventHandler^ UploadScheduleTimeChanged;
		event System::EventHandler^ ClearCompletedButtonClicked;
		event System::EventHandler^ OpenCacheFolderButtonClicked;

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			m_disposed = true;

			if (components)
			{
				delete components;
			}
		}
	
		void SetUploadQueueText(int index, int subItemIndex, System::String^ text);
		void AddUploadQueueItem(System::Windows::Forms::ListViewItem^ item);
		void UploadEnabledModeRadioButtons_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
		void UploadScheduleTime_ValueChanged(System::Object^ sender, System::EventArgs^ e);
		void ClearCompletedButton_Click(System::Object^ sender, System::EventArgs^ e);
		void OpenCacheFolderButton_Click(System::Object^ sender, System::EventArgs^ e);

		bool m_disposed;


	private:
		System::ComponentModel::IContainer^  components;
		System::Windows::Forms::ListView^  m_uploadList;
		System::Windows::Forms::ColumnHeader^  m_numberColumn;
		System::Windows::Forms::ColumnHeader^  m_timeColumn;
		System::Windows::Forms::ColumnHeader^  m_sizeColumn;
		System::Windows::Forms::ColumnHeader^  m_usernameColumn;
		System::Windows::Forms::ColumnHeader^  m_teamColumn;
		System::Windows::Forms::ColumnHeader^  m_userIdColumn;
		System::Windows::Forms::ColumnHeader^  m_machineNameColumn;
		System::Windows::Forms::ColumnHeader^  m_destinationColumn;
		System::Windows::Forms::ColumnHeader^  m_statusColumn;
		System::Windows::Forms::GroupBox^  m_uploadControlGroupBox;
		System::Windows::Forms::RadioButton^  m_uploadScheduleRadioButton;
		System::Windows::Forms::RadioButton^  m_uploadOffRadioButton;
		System::Windows::Forms::RadioButton^  m_uploadOnRadioButton;
		System::Windows::Forms::DateTimePicker^  m_uploadEndTime;
		System::Windows::Forms::DateTimePicker^  m_uploadStartTime;
		System::Windows::Forms::NumericUpDown^  numericUpDown1;
		System::Windows::Forms::CheckBox^  m_limitUploadSpeedCheckbox;
	private: System::Windows::Forms::Button^  m_clearCompletedButton;
	private: System::Windows::Forms::Button^  m_openCacheFolderButton;
			 System::Windows::Forms::ColumnHeader^  m_receivedFromIpColumn;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->m_uploadList = (gcnew System::Windows::Forms::ListView());
			this->m_numberColumn = (gcnew System::Windows::Forms::ColumnHeader());
			this->m_timeColumn = (gcnew System::Windows::Forms::ColumnHeader());
			this->m_receivedFromIpColumn = (gcnew System::Windows::Forms::ColumnHeader());
			this->m_sizeColumn = (gcnew System::Windows::Forms::ColumnHeader());
			this->m_usernameColumn = (gcnew System::Windows::Forms::ColumnHeader());
			this->m_teamColumn = (gcnew System::Windows::Forms::ColumnHeader());
			this->m_userIdColumn = (gcnew System::Windows::Forms::ColumnHeader());
			this->m_machineNameColumn = (gcnew System::Windows::Forms::ColumnHeader());
			this->m_destinationColumn = (gcnew System::Windows::Forms::ColumnHeader());
			this->m_statusColumn = (gcnew System::Windows::Forms::ColumnHeader());
			this->m_uploadControlGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->numericUpDown1 = (gcnew System::Windows::Forms::NumericUpDown());
			this->m_uploadEndTime = (gcnew System::Windows::Forms::DateTimePicker());
			this->m_uploadStartTime = (gcnew System::Windows::Forms::DateTimePicker());
			this->m_uploadScheduleRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->m_uploadOffRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->m_uploadOnRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->m_limitUploadSpeedCheckbox = (gcnew System::Windows::Forms::CheckBox());
			this->m_clearCompletedButton = (gcnew System::Windows::Forms::Button());
			this->m_openCacheFolderButton = (gcnew System::Windows::Forms::Button());
			this->m_uploadControlGroupBox->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown1))->BeginInit();
			this->SuspendLayout();
			// 
			// m_uploadList
			// 
			this->m_uploadList->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->m_uploadList->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(10) {this->m_numberColumn, 
				this->m_timeColumn, this->m_receivedFromIpColumn, this->m_sizeColumn, this->m_usernameColumn, this->m_teamColumn, this->m_userIdColumn, 
				this->m_machineNameColumn, this->m_destinationColumn, this->m_statusColumn});
			this->m_uploadList->FullRowSelect = true;
			this->m_uploadList->HeaderStyle = System::Windows::Forms::ColumnHeaderStyle::Nonclickable;
			this->m_uploadList->Location = System::Drawing::Point(-1, 104);
			this->m_uploadList->Name = L"m_uploadList";
			this->m_uploadList->Size = System::Drawing::Size(899, 203);
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
			// m_receivedFromIpColumn
			// 
			this->m_receivedFromIpColumn->Text = L"Received From";
			this->m_receivedFromIpColumn->Width = 86;
			// 
			// m_sizeColumn
			// 
			this->m_sizeColumn->Text = L"Size";
			this->m_sizeColumn->Width = 52;
			// 
			// m_usernameColumn
			// 
			this->m_usernameColumn->Text = L"User";
			this->m_usernameColumn->Width = 91;
			// 
			// m_teamColumn
			// 
			this->m_teamColumn->Text = L"Team";
			this->m_teamColumn->Width = 41;
			// 
			// m_userIdColumn
			// 
			this->m_userIdColumn->Text = L"User ID";
			this->m_userIdColumn->Width = 131;
			// 
			// m_machineNameColumn
			// 
			this->m_machineNameColumn->Text = L"Mach ID";
			this->m_machineNameColumn->Width = 56;
			// 
			// m_destinationColumn
			// 
			this->m_destinationColumn->Text = L"Destination Server";
			this->m_destinationColumn->Width = 111;
			// 
			// m_statusColumn
			// 
			this->m_statusColumn->Text = L"Status";
			this->m_statusColumn->Width = 174;
			// 
			// m_uploadControlGroupBox
			// 
			this->m_uploadControlGroupBox->Controls->Add(this->numericUpDown1);
			this->m_uploadControlGroupBox->Controls->Add(this->m_uploadEndTime);
			this->m_uploadControlGroupBox->Controls->Add(this->m_uploadStartTime);
			this->m_uploadControlGroupBox->Controls->Add(this->m_uploadScheduleRadioButton);
			this->m_uploadControlGroupBox->Controls->Add(this->m_uploadOffRadioButton);
			this->m_uploadControlGroupBox->Controls->Add(this->m_uploadOnRadioButton);
			this->m_uploadControlGroupBox->Controls->Add(this->m_limitUploadSpeedCheckbox);
			this->m_uploadControlGroupBox->Location = System::Drawing::Point(5, 4);
			this->m_uploadControlGroupBox->Name = L"m_uploadControlGroupBox";
			this->m_uploadControlGroupBox->Size = System::Drawing::Size(370, 94);
			this->m_uploadControlGroupBox->TabIndex = 1;
			this->m_uploadControlGroupBox->TabStop = false;
			this->m_uploadControlGroupBox->Text = L"Upload Control";
			// 
			// numericUpDown1
			// 
			this->numericUpDown1->Location = System::Drawing::Point(304, 19);
			this->numericUpDown1->Name = L"numericUpDown1";
			this->numericUpDown1->Size = System::Drawing::Size(57, 20);
			this->numericUpDown1->TabIndex = 6;
			this->numericUpDown1->Visible = false;
			// 
			// m_uploadEndTime
			// 
			this->m_uploadEndTime->Format = System::Windows::Forms::DateTimePickerFormat::Time;
			this->m_uploadEndTime->Location = System::Drawing::Point(231, 64);
			this->m_uploadEndTime->Name = L"m_uploadEndTime";
			this->m_uploadEndTime->ShowUpDown = true;
			this->m_uploadEndTime->Size = System::Drawing::Size(85, 20);
			this->m_uploadEndTime->TabIndex = 4;
			this->m_uploadEndTime->Value = System::DateTime(1984, 9, 20, 7, 0, 0, 0);
			this->m_uploadEndTime->ValueChanged += gcnew System::EventHandler(this, &MainForm::UploadScheduleTime_ValueChanged);
			// 
			// m_uploadStartTime
			// 
			this->m_uploadStartTime->Format = System::Windows::Forms::DateTimePickerFormat::Time;
			this->m_uploadStartTime->Location = System::Drawing::Point(140, 64);
			this->m_uploadStartTime->Name = L"m_uploadStartTime";
			this->m_uploadStartTime->ShowUpDown = true;
			this->m_uploadStartTime->Size = System::Drawing::Size(85, 20);
			this->m_uploadStartTime->TabIndex = 3;
			this->m_uploadStartTime->Value = System::DateTime(1984, 9, 20, 1, 0, 0, 0);
			this->m_uploadStartTime->ValueChanged += gcnew System::EventHandler(this, &MainForm::UploadScheduleTime_ValueChanged);
			// 
			// m_uploadScheduleRadioButton
			// 
			this->m_uploadScheduleRadioButton->AutoSize = true;
			this->m_uploadScheduleRadioButton->Location = System::Drawing::Point(18, 66);
			this->m_uploadScheduleRadioButton->Name = L"m_uploadScheduleRadioButton";
			this->m_uploadScheduleRadioButton->Size = System::Drawing::Size(120, 17);
			this->m_uploadScheduleRadioButton->TabIndex = 2;
			this->m_uploadScheduleRadioButton->TabStop = true;
			this->m_uploadScheduleRadioButton->Text = L"Only between times:";
			this->m_uploadScheduleRadioButton->UseVisualStyleBackColor = true;
			this->m_uploadScheduleRadioButton->CheckedChanged += gcnew System::EventHandler(this, &MainForm::UploadEnabledModeRadioButtons_CheckedChanged);
			// 
			// m_uploadOffRadioButton
			// 
			this->m_uploadOffRadioButton->AutoSize = true;
			this->m_uploadOffRadioButton->Location = System::Drawing::Point(18, 43);
			this->m_uploadOffRadioButton->Name = L"m_uploadOffRadioButton";
			this->m_uploadOffRadioButton->Size = System::Drawing::Size(39, 17);
			this->m_uploadOffRadioButton->TabIndex = 1;
			this->m_uploadOffRadioButton->TabStop = true;
			this->m_uploadOffRadioButton->Text = L"Off";
			this->m_uploadOffRadioButton->UseVisualStyleBackColor = true;
			this->m_uploadOffRadioButton->CheckedChanged += gcnew System::EventHandler(this, &MainForm::UploadEnabledModeRadioButtons_CheckedChanged);
			// 
			// m_uploadOnRadioButton
			// 
			this->m_uploadOnRadioButton->AutoSize = true;
			this->m_uploadOnRadioButton->Checked = true;
			this->m_uploadOnRadioButton->Location = System::Drawing::Point(18, 20);
			this->m_uploadOnRadioButton->Name = L"m_uploadOnRadioButton";
			this->m_uploadOnRadioButton->Size = System::Drawing::Size(39, 17);
			this->m_uploadOnRadioButton->TabIndex = 0;
			this->m_uploadOnRadioButton->TabStop = true;
			this->m_uploadOnRadioButton->Text = L"On";
			this->m_uploadOnRadioButton->UseVisualStyleBackColor = true;
			this->m_uploadOnRadioButton->CheckedChanged += gcnew System::EventHandler(this, &MainForm::UploadEnabledModeRadioButtons_CheckedChanged);
			// 
			// m_limitUploadSpeedCheckbox
			// 
			this->m_limitUploadSpeedCheckbox->AutoSize = true;
			this->m_limitUploadSpeedCheckbox->Location = System::Drawing::Point(139, 20);
			this->m_limitUploadSpeedCheckbox->Name = L"m_limitUploadSpeedCheckbox";
			this->m_limitUploadSpeedCheckbox->Size = System::Drawing::Size(166, 17);
			this->m_limitUploadSpeedCheckbox->TabIndex = 7;
			this->m_limitUploadSpeedCheckbox->Text = L"Limit Upload Speed (kbyte/s):";
			this->m_limitUploadSpeedCheckbox->UseVisualStyleBackColor = true;
			this->m_limitUploadSpeedCheckbox->Visible = false;
			// 
			// m_clearCompletedButton
			// 
			this->m_clearCompletedButton->Location = System::Drawing::Point(381, 10);
			this->m_clearCompletedButton->Name = L"m_clearCompletedButton";
			this->m_clearCompletedButton->Size = System::Drawing::Size(121, 23);
			this->m_clearCompletedButton->TabIndex = 2;
			this->m_clearCompletedButton->Text = L"Clear Completed";
			this->m_clearCompletedButton->UseVisualStyleBackColor = true;
			this->m_clearCompletedButton->Click += gcnew System::EventHandler(this, &MainForm::ClearCompletedButton_Click);
			// 
			// m_openCacheFolderButton
			// 
			this->m_openCacheFolderButton->Location = System::Drawing::Point(381, 39);
			this->m_openCacheFolderButton->Name = L"m_openCacheFolderButton";
			this->m_openCacheFolderButton->Size = System::Drawing::Size(121, 23);
			this->m_openCacheFolderButton->TabIndex = 3;
			this->m_openCacheFolderButton->Text = L"WU Cache Folder";
			this->m_openCacheFolderButton->UseVisualStyleBackColor = true;
			this->m_openCacheFolderButton->Click += gcnew System::EventHandler(this, &MainForm::OpenCacheFolderButton_Click);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(897, 306);
			this->Controls->Add(this->m_openCacheFolderButton);
			this->Controls->Add(this->m_clearCompletedButton);
			this->Controls->Add(this->m_uploadControlGroupBox);
			this->Controls->Add(this->m_uploadList);
			this->Name = L"MainForm";
			this->Text = L"FAH Proxy by JB";
			this->m_uploadControlGroupBox->ResumeLayout(false);
			this->m_uploadControlGroupBox->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown1))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
};
}

