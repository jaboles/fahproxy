#pragma once


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
			InitializeComponent();
		}
		
		void AddQueueItem(int index, System::String^ time, int size, System::String^ username, System::String^ team, System::String^ userId, int machineId, System::String^ destServer, int status);
		void UpdateQueueItemStatus(int index, int status, double progress, System::String^ errorString);
		void UpdateQueueItemStatus(int index, int status);
		void RemoveQueueItem(int index);

		static System::String^ UploadStatusString(int index);

	private: System::Windows::Forms::ListView^  m_uploadList;
	private: System::Windows::Forms::ColumnHeader^  m_numberColumn;
	private: System::Windows::Forms::ColumnHeader^  m_timeColumn;
	private: System::Windows::Forms::ColumnHeader^  m_sizeColumn;
	private: System::Windows::Forms::ColumnHeader^  m_usernameColumn;
	private: System::Windows::Forms::ColumnHeader^  m_teamColumn;
	private: System::Windows::Forms::ColumnHeader^  m_userIdColumn;
	private: System::Windows::Forms::ColumnHeader^  m_machineNameColumn;
	private: System::Windows::Forms::ColumnHeader^  m_destinationColumn;
	private: System::Windows::Forms::ColumnHeader^  m_statusColumn;
	private: System::Windows::Forms::Label^  m_uploadQueueLabel;
	public: 

		static const System::String^ VERSION = "0.01.000";

		delegate void SetUploadQueueTextDelegate(int, int, System::String^);

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	
	private:


		void SetUploadQueueText(int index, int subItemIndex, System::String^ text);

		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

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
			this->m_sizeColumn = (gcnew System::Windows::Forms::ColumnHeader());
			this->m_usernameColumn = (gcnew System::Windows::Forms::ColumnHeader());
			this->m_teamColumn = (gcnew System::Windows::Forms::ColumnHeader());
			this->m_userIdColumn = (gcnew System::Windows::Forms::ColumnHeader());
			this->m_machineNameColumn = (gcnew System::Windows::Forms::ColumnHeader());
			this->m_destinationColumn = (gcnew System::Windows::Forms::ColumnHeader());
			this->m_statusColumn = (gcnew System::Windows::Forms::ColumnHeader());
			this->m_uploadQueueLabel = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// m_uploadList
			// 
			this->m_uploadList->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->m_uploadList->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(9) {this->m_numberColumn, 
				this->m_timeColumn, this->m_sizeColumn, this->m_usernameColumn, this->m_teamColumn, this->m_userIdColumn, this->m_machineNameColumn, 
				this->m_destinationColumn, this->m_statusColumn});
			this->m_uploadList->FullRowSelect = true;
			this->m_uploadList->GridLines = true;
			this->m_uploadList->HeaderStyle = System::Windows::Forms::ColumnHeaderStyle::Nonclickable;
			this->m_uploadList->Location = System::Drawing::Point(-1, 56);
			this->m_uploadList->Name = L"m_uploadList";
			this->m_uploadList->Size = System::Drawing::Size(740, 270);
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
			this->m_timeColumn->Width = 106;
			// 
			// m_sizeColumn
			// 
			this->m_sizeColumn->Text = L"Size";
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
			this->m_userIdColumn->Width = 89;
			// 
			// m_machineNameColumn
			// 
			this->m_machineNameColumn->Text = L"Mach. ID";
			this->m_machineNameColumn->Width = 56;
			// 
			// m_destinationColumn
			// 
			this->m_destinationColumn->Text = L"Dest. Server";
			this->m_destinationColumn->Width = 87;
			// 
			// m_statusColumn
			// 
			this->m_statusColumn->Text = L"Status";
			this->m_statusColumn->Width = 174;
			// 
			// m_uploadQueueLabel
			// 
			this->m_uploadQueueLabel->AutoSize = true;
			this->m_uploadQueueLabel->Location = System::Drawing::Point(7, 37);
			this->m_uploadQueueLabel->Name = L"m_uploadQueueLabel";
			this->m_uploadQueueLabel->Size = System::Drawing::Size(79, 13);
			this->m_uploadQueueLabel->TabIndex = 1;
			this->m_uploadQueueLabel->Text = L"Upload Queue:";
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(738, 325);
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

