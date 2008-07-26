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
			//
			//TODO: Add the constructor code here
			//
		}

		static const System::String^ VERSION = "0.01.000";

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
	
		void StartButton_Click(System::Object^ sender, System::EventArgs^ e);
		void StopButton_Click(System::Object^ sender, System::EventArgs^ e);

		ProxyListener^ m_proxyListener;

	private:
		System::Windows::Forms::Label^  m_startStopLabel;
		System::Windows::Forms::Button^  m_startButton;
		System::Windows::Forms::Button^  m_stopButton;
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
			this->m_startStopLabel = (gcnew System::Windows::Forms::Label());
			this->m_startButton = (gcnew System::Windows::Forms::Button());
			this->m_stopButton = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// m_startStopLabel
			// 
			this->m_startStopLabel->AutoEllipsis = true;
			this->m_startStopLabel->AutoSize = true;
			this->m_startStopLabel->Location = System::Drawing::Point(12, 23);
			this->m_startStopLabel->Name = L"m_startStopLabel";
			this->m_startStopLabel->Size = System::Drawing::Size(56, 13);
			this->m_startStopLabel->TabIndex = 0;
			this->m_startStopLabel->Text = L"Start/Stop";
			// 
			// m_startButton
			// 
			this->m_startButton->Location = System::Drawing::Point(92, 18);
			this->m_startButton->Name = L"m_startButton";
			this->m_startButton->Size = System::Drawing::Size(75, 23);
			this->m_startButton->TabIndex = 1;
			this->m_startButton->Text = L"Start";
			this->m_startButton->UseVisualStyleBackColor = true;
			this->m_startButton->Click += gcnew System::EventHandler(this, &MainForm::StartButton_Click);
			// 
			// m_stopButton
			// 
			this->m_stopButton->Location = System::Drawing::Point(173, 18);
			this->m_stopButton->Name = L"m_stopButton";
			this->m_stopButton->Size = System::Drawing::Size(75, 23);
			this->m_stopButton->TabIndex = 2;
			this->m_stopButton->Text = L"Stop";
			this->m_stopButton->UseVisualStyleBackColor = true;
			this->m_stopButton->Click += gcnew System::EventHandler(this, &MainForm::StopButton_Click);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(292, 273);
			this->Controls->Add(this->m_stopButton);
			this->Controls->Add(this->m_startButton);
			this->Controls->Add(this->m_startStopLabel);
			this->Name = L"MainForm";
			this->Text = L"FAH Proxy by JB";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	};
}

