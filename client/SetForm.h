#pragma once

namespace IPCSample {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for SetForm
	/// </summary>
	public ref class SetForm : public System::Windows::Forms::Form
	{
	public:
		SetForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~SetForm()
		{
			if (components)
			{
				delete components;


			}
		}
	private: System::Windows::Forms::GroupBox^  groupBox1;
	protected: 
	private: System::Windows::Forms::TrackBar^  trackBar3;
	private: System::Windows::Forms::TrackBar^  trackBar2;
	private: System::Windows::Forms::TrackBar^  trackBar1;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::GroupBox^  groupBox3;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::TrackBar^  trackBar4;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::TrackBar^  trackBar5;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Button^  button1;
	//private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Button^  button3;

	private:
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
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->trackBar1 = (gcnew System::Windows::Forms::TrackBar());
			this->trackBar2 = (gcnew System::Windows::Forms::TrackBar());
			this->trackBar3 = (gcnew System::Windows::Forms::TrackBar());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->trackBar4 = (gcnew System::Windows::Forms::TrackBar());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->trackBar5 = (gcnew System::Windows::Forms::TrackBar());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			//this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar4))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar5))->BeginInit();
			this->SuspendLayout();
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->label4);
			this->groupBox1->Controls->Add(this->label3);
			this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Controls->Add(this->pictureBox1);
			this->groupBox1->Controls->Add(this->trackBar2);
			this->groupBox1->Controls->Add(this->trackBar1);
			this->groupBox1->Location = System::Drawing::Point(9, 8);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(457, 161);
			this->groupBox1->TabIndex = 0;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"画面设置";
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->label10);
			this->groupBox2->Controls->Add(this->label9);
			this->groupBox2->Controls->Add(this->label8);
			this->groupBox2->Controls->Add(this->label7);
			this->groupBox2->Controls->Add(this->trackBar5);
			this->groupBox2->Controls->Add(this->label6);
			this->groupBox2->Controls->Add(this->label5);
			this->groupBox2->Controls->Add(this->trackBar4);
			this->groupBox2->Controls->Add(this->trackBar3);
			this->groupBox2->Location = System::Drawing::Point(477, 8);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(305, 161);
			this->groupBox2->TabIndex = 1;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"报警设置";
			// 
			// groupBox3
			// 
			this->groupBox3->Location = System::Drawing::Point(12, 175);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(454, 79);
			this->groupBox3->TabIndex = 2;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"网络设置";
			// 
			// trackBar1
			// 
			this->trackBar1->Location = System::Drawing::Point(104, 19);
			this->trackBar1->Maximum = 120;
			this->trackBar1->Name = L"trackBar1";
			this->trackBar1->Size = System::Drawing::Size(225, 45);
			this->trackBar1->TabIndex = 0;
			this->trackBar1->Value = 20;
			// 
			// trackBar2
			// 
			this->trackBar2->Location = System::Drawing::Point(104, 89);
			this->trackBar2->Maximum = 120;
			this->trackBar2->Minimum = 1;
			this->trackBar2->Name = L"trackBar2";
			this->trackBar2->Size = System::Drawing::Size(225, 45);
			this->trackBar2->TabIndex = 1;
			this->trackBar2->Value = 10;
			// 
			// trackBar3
			// 
			this->trackBar3->Location = System::Drawing::Point(73, 23);
			this->trackBar3->Maximum = 121;
			this->trackBar3->Minimum = 1;
			this->trackBar3->Name = L"trackBar3";
			this->trackBar3->Size = System::Drawing::Size(206, 45);
			this->trackBar3->TabIndex = 2;
			this->trackBar3->Value = 70;
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(356, 19);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(36, 101);
			this->pictureBox1->TabIndex = 3;
			this->pictureBox1->TabStop = false;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(21, 27);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(83, 12);
			this->label1->TabIndex = 4;
			this->label1->Text = L"最小显示温度:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(21, 97);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(83, 12);
			this->label2->TabIndex = 5;
			this->label2->Text = L"显示温度区间:";
			// 
			// trackBar4
			// 
			this->trackBar4->Location = System::Drawing::Point(73, 68);
			this->trackBar4->Maximum = 120;
			this->trackBar4->Name = L"trackBar4";
			this->trackBar4->Size = System::Drawing::Size(206, 45);
			this->trackBar4->TabIndex = 6;
			this->trackBar4->Value = 70;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(398, 17);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(35, 12);
			this->label3->TabIndex = 6;
			this->label3->Text = L"30°C";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(398, 108);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(35, 12);
			this->label4->TabIndex = 7;
			this->label4->Text = L"20°C";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(11, 27);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(59, 12);
			this->label5->TabIndex = 8;
			this->label5->Text = L"温度阈值:";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(11, 74);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(47, 12);
			this->label6->TabIndex = 9;
			this->label6->Text = L"CO阈值:";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(11, 116);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(53, 12);
			this->label7->TabIndex = 11;
			this->label7->Text = L"CH4阈值:";
			// 
			// trackBar5
			// 
			this->trackBar5->Location = System::Drawing::Point(71, 110);
			this->trackBar5->Maximum = 100;
			this->trackBar5->Name = L"trackBar5";
			this->trackBar5->Size = System::Drawing::Size(206, 45);
			this->trackBar5->TabIndex = 6;
			this->trackBar5->Value = 25;
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(174, 12);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(35, 12);
			this->label8->TabIndex = 12;
			this->label8->Text = L"70°C";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(179, 53);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(35, 12);
			this->label9->TabIndex = 13;
			this->label9->Text = L"70ppm";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(120, 96);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(23, 12);
			this->label10->TabIndex = 14;
			this->label10->Text = L"25%";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(473, 200);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(97, 47);
			this->button1->TabIndex = 3;
			this->button1->Text = L"恢复默认设置";
			this->button1->UseVisualStyleBackColor = true;
			// 
			//// button2
			//// 
			//this->button2->Location = System::Drawing::Point(579, 200);
			//this->button2->Name = L"button2";
			//this->button2->Size = System::Drawing::Size(97, 47);
			//this->button2->TabIndex = 4;
			//this->button2->Text = L"应用";
			//this->button2->UseVisualStyleBackColor = true;
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(688, 200);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(97, 47);
			this->button3->TabIndex = 5;
			this->button3->Text = L"取消";
			this->button3->UseVisualStyleBackColor = true;
			// 
			// SetForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(794, 271);
			this->Controls->Add(this->button3);
			//this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->groupBox3);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"SetForm";
			this->Text = L"设置";
			this->Load += gcnew System::EventHandler(this, &SetForm::SetForm_Load);
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar4))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar5))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void SetForm_Load(System::Object^  sender, System::EventArgs^  e) {
			 }
	};
}
