#pragma once
namespace IPCSample {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	using namespace System::Data::SqlClient;
	/// <summary>
	/// Summary for SetForm02
	/// </summary>
	public ref class SetForm02 : public System::Windows::Forms::Form
	{
	public:
		SetForm02(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			
			InitializeValues();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~SetForm02()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TrackBar^  trackBar1;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::TrackBar^  trackBar2;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::Button^  buttonCancel;

	private: System::Windows::Forms::Button^  buttonSave;

	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::CheckBox^  checkBox6;
	private: System::Windows::Forms::TextBox^  textBox3;
	private: System::Windows::Forms::CheckBox^  checkBox4;
	private: System::Windows::Forms::CheckBox^  checkBox3;
	private: System::Windows::Forms::CheckBox^  checkBox2;
	private: System::Windows::Forms::CheckBox^  checkBox1;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Button^  buttonConnectToDB;
	private: System::Windows::Forms::GroupBox^  groupBox5;
	private: System::Windows::Forms::TextBox^  textBoxInitialCatalog;
	private: System::Windows::Forms::TextBox^  textBoxDataSource;
	private: System::Windows::Forms::Label^  label14;
	private: System::Windows::Forms::Label^  label13;


	private: System::Windows::Forms::Button^  buttonConnectToRemoteDB;
	private: System::Windows::Forms::TextBox^  textBoxRemoteDataBase;
	private: System::Windows::Forms::Label^  label17;
	private: System::Windows::Forms::TextBox^  textBoxRemoteDataSource;
	private: System::Windows::Forms::Label^  label16;
	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::Label^  label15;
	private: System::Windows::Forms::TextBox^  textBoxPWD;
	private: System::Windows::Forms::GroupBox^  groupBox7;
	private: System::Windows::Forms::TextBox^  textBoxUser;
	protected: 
	public:
		int Lin_AlarmTemp;
		int Lin_AirRefreshTime;
		int Lin_AlarmCO;
		int Lin_AlarmCH4;
		int TempMinTrackBarValue;
		int TempRangTrackBarValue;
		SqlConnection ^Lin_LocalConnSql;
		SqlConnection ^Lin_RemoteConnSql;
		String ^Lin_RemoteDataSource;
		String ^Lin_RemoteDataBaseName;
		String ^Lin_RemoteUserName;
		String ^ Lin_RemoteUserPwd;
		String ^Lin_LocalDataSource;
		String ^Lin_LocalDataBaseName;
		String ^Lin_IP;
		bool Lin_Saved;
	private: System::Windows::Forms::Label^  label19;
	public: 
	private: System::Windows::Forms::GroupBox^  groupBox3;
	private: System::Windows::Forms::TextBox^  IpAddress;

		
		void InitializeValues();
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
			this->trackBar1 = (gcnew System::Windows::Forms::TrackBar());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->trackBar2 = (gcnew System::Windows::Forms::TrackBar());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->buttonCancel = (gcnew System::Windows::Forms::Button());
			this->buttonSave = (gcnew System::Windows::Forms::Button());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->checkBox6 = (gcnew System::Windows::Forms::CheckBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->checkBox4 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox3 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox2 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->buttonConnectToDB = (gcnew System::Windows::Forms::Button());
			this->groupBox5 = (gcnew System::Windows::Forms::GroupBox());
			this->textBoxInitialCatalog = (gcnew System::Windows::Forms::TextBox());
			this->textBoxDataSource = (gcnew System::Windows::Forms::TextBox());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->buttonConnectToRemoteDB = (gcnew System::Windows::Forms::Button());
			this->textBoxRemoteDataBase = (gcnew System::Windows::Forms::TextBox());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->textBoxRemoteDataSource = (gcnew System::Windows::Forms::TextBox());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->textBoxPWD = (gcnew System::Windows::Forms::TextBox());
			this->groupBox7 = (gcnew System::Windows::Forms::GroupBox());
			this->textBoxUser = (gcnew System::Windows::Forms::TextBox());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->IpAddress = (gcnew System::Windows::Forms::TextBox());
			this->groupBox1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
			this->groupBox2->SuspendLayout();
			this->groupBox5->SuspendLayout();
			this->groupBox7->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->SuspendLayout();
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->trackBar1);
			this->groupBox1->Controls->Add(this->label6);
			this->groupBox1->Controls->Add(this->trackBar2);
			this->groupBox1->Controls->Add(this->label5);
			this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Controls->Add(this->pictureBox1);
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Location = System::Drawing::Point(10, 9);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(279, 195);
			this->groupBox1->TabIndex = 0;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"画面调节";
			// 
			// trackBar1
			// 
			this->trackBar1->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->trackBar1->Location = System::Drawing::Point(10, 44);
			this->trackBar1->Maximum = 120;
			this->trackBar1->Name = L"trackBar1";
			this->trackBar1->Size = System::Drawing::Size(167, 45);
			this->trackBar1->TabIndex = 8;
			this->trackBar1->Value = 40;
			this->trackBar1->Scroll += gcnew System::EventHandler(this, &SetForm02::trackBar1_Scroll);
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(227, 44);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(35, 12);
			this->label6->TabIndex = 13;
			this->label6->Text = L"40°C";
			// 
			// trackBar2
			// 
			this->trackBar2->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->trackBar2->Location = System::Drawing::Point(10, 124);
			this->trackBar2->Maximum = 120;
			this->trackBar2->Minimum = 1;
			this->trackBar2->Name = L"trackBar2";
			this->trackBar2->Size = System::Drawing::Size(167, 45);
			this->trackBar2->TabIndex = 9;
			this->trackBar2->Value = 20;
			this->trackBar2->Scroll += gcnew System::EventHandler(this, &SetForm02::trackBar2_Scroll);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(227, 155);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(35, 12);
			this->label5->TabIndex = 12;
			this->label5->Text = L"20°C";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(10, 100);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(89, 12);
			this->label2->TabIndex = 10;
			this->label2->Text = L"显示温度区间：";
			// 
			// pictureBox1
			// 
			this->pictureBox1->ImageLocation = L"D:\\煤堆测温\\温度颜色调节.jpg";
			this->pictureBox1->Location = System::Drawing::Point(191, 40);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(20, 129);
			this->pictureBox1->TabIndex = 11;
			this->pictureBox1->TabStop = false;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(9, 21);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(83, 12);
			this->label1->TabIndex = 4;
			this->label1->Text = L"最小显示温度:";
			// 
			// buttonCancel
			// 
			this->buttonCancel->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->buttonCancel->Cursor = System::Windows::Forms::Cursors::Hand;
			this->buttonCancel->Font = (gcnew System::Drawing::Font(L"SimSun", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->buttonCancel->Location = System::Drawing::Point(609, 305);
			this->buttonCancel->Name = L"buttonCancel";
			this->buttonCancel->Size = System::Drawing::Size(75, 40);
			this->buttonCancel->TabIndex = 25;
			this->buttonCancel->Text = L"取消";
			this->buttonCancel->UseVisualStyleBackColor = false;
			this->buttonCancel->Click += gcnew System::EventHandler(this, &SetForm02::buttonCancel_Click);
			// 
			// buttonSave
			// 
			this->buttonSave->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->buttonSave->Cursor = System::Windows::Forms::Cursors::Hand;
			this->buttonSave->Font = (gcnew System::Drawing::Font(L"SimSun", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->buttonSave->Location = System::Drawing::Point(609, 377);
			this->buttonSave->Name = L"buttonSave";
			this->buttonSave->Size = System::Drawing::Size(75, 40);
			this->buttonSave->TabIndex = 24;
			this->buttonSave->Text = L"保存";
			this->buttonSave->UseVisualStyleBackColor = false;
			this->buttonSave->Click += gcnew System::EventHandler(this, &SetForm02::buttonSave_Click);
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(22, 116);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(65, 12);
			this->label10->TabIndex = 23;
			this->label10->Text = L"报警方式：";
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->label11);
			this->groupBox2->Controls->Add(this->label9);
			this->groupBox2->Controls->Add(this->textBox1);
			this->groupBox2->Controls->Add(this->label4);
			this->groupBox2->Controls->Add(this->label10);
			this->groupBox2->Controls->Add(this->checkBox6);
			this->groupBox2->Controls->Add(this->textBox3);
			this->groupBox2->Controls->Add(this->checkBox4);
			this->groupBox2->Controls->Add(this->checkBox3);
			this->groupBox2->Controls->Add(this->checkBox2);
			this->groupBox2->Controls->Add(this->checkBox1);
			this->groupBox2->Controls->Add(this->label8);
			this->groupBox2->Controls->Add(this->label7);
			this->groupBox2->Controls->Add(this->label3);
			this->groupBox2->Location = System::Drawing::Point(311, 12);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(370, 192);
			this->groupBox2->TabIndex = 10;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"报警设置";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(335, 29);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(29, 12);
			this->label11->TabIndex = 29;
			this->label11->Text = L"分钟";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(142, 29);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(23, 12);
			this->label9->TabIndex = 28;
			this->label9->Text = L"°C";
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(298, 24);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(33, 21);
			this->textBox1->TabIndex = 27;
			this->textBox1->Text = L"10";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(172, 28);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(125, 12);
			this->label4->TabIndex = 26;
			this->label4->Text = L"气体传感器刷新时间：";
			// 
			// checkBox6
			// 
			this->checkBox6->AutoSize = true;
			this->checkBox6->Location = System::Drawing::Point(122, 116);
			this->checkBox6->Name = L"checkBox6";
			this->checkBox6->Size = System::Drawing::Size(48, 16);
			this->checkBox6->TabIndex = 21;
			this->checkBox6->Text = L"声音";
			this->checkBox6->UseVisualStyleBackColor = true;
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(105, 25);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(33, 21);
			this->textBox3->TabIndex = 19;
			this->textBox3->Text = L"70";
			// 
			// checkBox4
			// 
			this->checkBox4->AutoSize = true;
			this->checkBox4->Location = System::Drawing::Point(231, 83);
			this->checkBox4->Name = L"checkBox4";
			this->checkBox4->Size = System::Drawing::Size(96, 16);
			this->checkBox4->TabIndex = 18;
			this->checkBox4->Text = L"级别2（40%）";
			this->checkBox4->UseVisualStyleBackColor = true;
			// 
			// checkBox3
			// 
			this->checkBox3->AutoSize = true;
			this->checkBox3->Checked = true;
			this->checkBox3->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBox3->Location = System::Drawing::Point(122, 84);
			this->checkBox3->Name = L"checkBox3";
			this->checkBox3->Size = System::Drawing::Size(96, 16);
			this->checkBox3->TabIndex = 17;
			this->checkBox3->Text = L"级别1（25%）";
			this->checkBox3->UseVisualStyleBackColor = true;
			// 
			// checkBox2
			// 
			this->checkBox2->AutoSize = true;
			this->checkBox2->Location = System::Drawing::Point(230, 54);
			this->checkBox2->Name = L"checkBox2";
			this->checkBox2->Size = System::Drawing::Size(114, 16);
			this->checkBox2->TabIndex = 15;
			this->checkBox2->Text = L"级别2（100ppm）";
			this->checkBox2->UseVisualStyleBackColor = true;
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Checked = true;
			this->checkBox1->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBox1->Location = System::Drawing::Point(121, 54);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(108, 16);
			this->checkBox1->TabIndex = 14;
			this->checkBox1->Text = L"级别1（70ppm）";
			this->checkBox1->UseVisualStyleBackColor = true;
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(22, 85);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(83, 12);
			this->label8->TabIndex = 10;
			this->label8->Text = L"CH4浓度阈值：";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(24, 55);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(77, 12);
			this->label7->TabIndex = 8;
			this->label7->Text = L"CO浓度阈值：";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(15, 28);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(89, 12);
			this->label3->TabIndex = 6;
			this->label3->Text = L"报警温度阈值：";
			// 
			// buttonConnectToDB
			// 
			this->buttonConnectToDB->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->buttonConnectToDB->Cursor = System::Windows::Forms::Cursors::Hand;
			this->buttonConnectToDB->FlatAppearance->BorderColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->buttonConnectToDB->FlatAppearance->BorderSize = 2;
			this->buttonConnectToDB->FlatAppearance->MouseDownBackColor = System::Drawing::Color::DodgerBlue;
			this->buttonConnectToDB->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)), 
				static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(128)));
			this->buttonConnectToDB->Font = (gcnew System::Drawing::Font(L"SimSun", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->buttonConnectToDB->Location = System::Drawing::Point(172, 113);
			this->buttonConnectToDB->Name = L"buttonConnectToDB";
			this->buttonConnectToDB->Size = System::Drawing::Size(75, 40);
			this->buttonConnectToDB->TabIndex = 0;
			this->buttonConnectToDB->Text = L"测试";
			this->buttonConnectToDB->UseVisualStyleBackColor = false;
			this->buttonConnectToDB->Click += gcnew System::EventHandler(this, &SetForm02::buttonConnectToDB_Click);
			// 
			// groupBox5
			// 
			this->groupBox5->Controls->Add(this->textBoxInitialCatalog);
			this->groupBox5->Controls->Add(this->textBoxDataSource);
			this->groupBox5->Controls->Add(this->label14);
			this->groupBox5->Controls->Add(this->label13);
			this->groupBox5->Controls->Add(this->buttonConnectToDB);
			this->groupBox5->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->groupBox5->Location = System::Drawing::Point(6, 206);
			this->groupBox5->Name = L"groupBox5";
			this->groupBox5->Size = System::Drawing::Size(283, 164);
			this->groupBox5->TabIndex = 26;
			this->groupBox5->TabStop = false;
			this->groupBox5->Text = L"本地数据库配置";
			// 
			// textBoxInitialCatalog
			// 
			this->textBoxInitialCatalog->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->textBoxInitialCatalog->Font = (gcnew System::Drawing::Font(L"SimSun", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->textBoxInitialCatalog->Location = System::Drawing::Point(93, 73);
			this->textBoxInitialCatalog->Name = L"textBoxInitialCatalog";
			this->textBoxInitialCatalog->Size = System::Drawing::Size(164, 26);
			this->textBoxInitialCatalog->TabIndex = 5;
			this->textBoxInitialCatalog->Text = L"Meidui";
			// 
			// textBoxDataSource
			// 
			this->textBoxDataSource->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->textBoxDataSource->Font = (gcnew System::Drawing::Font(L"SimSun", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->textBoxDataSource->Location = System::Drawing::Point(93, 21);
			this->textBoxDataSource->Name = L"textBoxDataSource";
			this->textBoxDataSource->Size = System::Drawing::Size(164, 26);
			this->textBoxDataSource->TabIndex = 4;
			this->textBoxDataSource->Text = L"SHELMYLIN-PC";
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Font = (gcnew System::Drawing::Font(L"SimSun", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->label14->Location = System::Drawing::Point(12, 79);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(72, 16);
			this->label14->TabIndex = 3;
			this->label14->Text = L"数据库：";
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Font = (gcnew System::Drawing::Font(L"SimSun", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->label13->Location = System::Drawing::Point(11, 26);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(72, 16);
			this->label13->TabIndex = 2;
			this->label13->Text = L"服务器：";
			// 
			// buttonConnectToRemoteDB
			// 
			this->buttonConnectToRemoteDB->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->buttonConnectToRemoteDB->Cursor = System::Windows::Forms::Cursors::Hand;
			this->buttonConnectToRemoteDB->FlatAppearance->BorderColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->buttonConnectToRemoteDB->FlatAppearance->BorderSize = 2;
			this->buttonConnectToRemoteDB->FlatAppearance->MouseDownBackColor = System::Drawing::Color::DodgerBlue;
			this->buttonConnectToRemoteDB->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)), 
				static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(128)));
			this->buttonConnectToRemoteDB->Font = (gcnew System::Drawing::Font(L"SimSun", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->buttonConnectToRemoteDB->Location = System::Drawing::Point(177, 167);
			this->buttonConnectToRemoteDB->Name = L"buttonConnectToRemoteDB";
			this->buttonConnectToRemoteDB->Size = System::Drawing::Size(75, 40);
			this->buttonConnectToRemoteDB->TabIndex = 6;
			this->buttonConnectToRemoteDB->Text = L"测试";
			this->buttonConnectToRemoteDB->UseVisualStyleBackColor = false;
			this->buttonConnectToRemoteDB->Click += gcnew System::EventHandler(this, &SetForm02::buttonConnectToRemoteDB_Click);
			// 
			// textBoxRemoteDataBase
			// 
			this->textBoxRemoteDataBase->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->textBoxRemoteDataBase->Font = (gcnew System::Drawing::Font(L"SimSun", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->textBoxRemoteDataBase->Location = System::Drawing::Point(92, 55);
			this->textBoxRemoteDataBase->Name = L"textBoxRemoteDataBase";
			this->textBoxRemoteDataBase->Size = System::Drawing::Size(164, 26);
			this->textBoxRemoteDataBase->TabIndex = 7;
			this->textBoxRemoteDataBase->Text = L"LinDatabase";
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Font = (gcnew System::Drawing::Font(L"SimSun", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->label17->Location = System::Drawing::Point(14, 61);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(72, 16);
			this->label17->TabIndex = 6;
			this->label17->Text = L"数据库：";
			// 
			// textBoxRemoteDataSource
			// 
			this->textBoxRemoteDataSource->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->textBoxRemoteDataSource->Font = (gcnew System::Drawing::Font(L"SimSun", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->textBoxRemoteDataSource->Location = System::Drawing::Point(92, 21);
			this->textBoxRemoteDataSource->Name = L"textBoxRemoteDataSource";
			this->textBoxRemoteDataSource->Size = System::Drawing::Size(164, 26);
			this->textBoxRemoteDataSource->TabIndex = 7;
			this->textBoxRemoteDataSource->Text = L"MICROSOF-8B4B5C";
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Font = (gcnew System::Drawing::Font(L"SimSun", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->label16->Location = System::Drawing::Point(14, 26);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(72, 16);
			this->label16->TabIndex = 6;
			this->label16->Text = L"服务器：";
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Font = (gcnew System::Drawing::Font(L"SimSun", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->label12->Location = System::Drawing::Point(14, 95);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(72, 16);
			this->label12->TabIndex = 6;
			this->label12->Text = L"用户名：";
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Font = (gcnew System::Drawing::Font(L"SimSun", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->label15->Location = System::Drawing::Point(14, 129);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(56, 16);
			this->label15->TabIndex = 7;
			this->label15->Text = L"密码：";
			// 
			// textBoxPWD
			// 
			this->textBoxPWD->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->textBoxPWD->Font = (gcnew System::Drawing::Font(L"SimSun", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->textBoxPWD->Location = System::Drawing::Point(92, 123);
			this->textBoxPWD->Name = L"textBoxPWD";
			this->textBoxPWD->PasswordChar = '*';
			this->textBoxPWD->Size = System::Drawing::Size(164, 26);
			this->textBoxPWD->TabIndex = 9;
			this->textBoxPWD->Text = L"123456";
			// 
			// groupBox7
			// 
			this->groupBox7->Controls->Add(this->buttonConnectToRemoteDB);
			this->groupBox7->Controls->Add(this->textBoxRemoteDataBase);
			this->groupBox7->Controls->Add(this->label17);
			this->groupBox7->Controls->Add(this->textBoxRemoteDataSource);
			this->groupBox7->Controls->Add(this->label16);
			this->groupBox7->Controls->Add(this->label12);
			this->groupBox7->Controls->Add(this->label15);
			this->groupBox7->Controls->Add(this->textBoxPWD);
			this->groupBox7->Controls->Add(this->textBoxUser);
			this->groupBox7->Location = System::Drawing::Point(317, 210);
			this->groupBox7->Name = L"groupBox7";
			this->groupBox7->Size = System::Drawing::Size(262, 211);
			this->groupBox7->TabIndex = 27;
			this->groupBox7->TabStop = false;
			this->groupBox7->Text = L"远程数据库配置";
			// 
			// textBoxUser
			// 
			this->textBoxUser->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->textBoxUser->Font = (gcnew System::Drawing::Font(L"SimSun", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->textBoxUser->Location = System::Drawing::Point(92, 89);
			this->textBoxUser->Name = L"textBoxUser";
			this->textBoxUser->Size = System::Drawing::Size(164, 26);
			this->textBoxUser->TabIndex = 8;
			this->textBoxUser->Text = L"sa";
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->Location = System::Drawing::Point(18, 25);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(71, 12);
			this->label19->TabIndex = 14;
			this->label19->Text = L"主机IP地址:";
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->label19);
			this->groupBox3->Controls->Add(this->IpAddress);
			this->groupBox3->Location = System::Drawing::Point(6, 376);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(283, 45);
			this->groupBox3->TabIndex = 28;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"网络设置";
			// 
			// IpAddress
			// 
			this->IpAddress->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->IpAddress->Location = System::Drawing::Point(98, 21);
			this->IpAddress->Name = L"IpAddress";
			this->IpAddress->Size = System::Drawing::Size(115, 21);
			this->IpAddress->TabIndex = 0;
			this->IpAddress->Text = L"192.168.1.143";
			// 
			// SetForm02
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(692, 428);
			this->ControlBox = false;
			this->Controls->Add(this->groupBox3);
			this->Controls->Add(this->groupBox5);
			this->Controls->Add(this->groupBox7);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->buttonCancel);
			this->Controls->Add(this->buttonSave);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Name = L"SetForm02";
			this->Text = L"SetForm02";
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->groupBox5->ResumeLayout(false);
			this->groupBox5->PerformLayout();
			this->groupBox7->ResumeLayout(false);
			this->groupBox7->PerformLayout();
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void buttonSave_Click(System::Object^  sender, System::EventArgs^  e) {
				 
				 Lin_LocalDataSource = textBoxDataSource->Text;
				 Lin_LocalDataBaseName = textBoxInitialCatalog->Text;
				 Lin_RemoteDataSource = textBoxRemoteDataSource->Text;
				 Lin_RemoteDataBaseName = textBoxRemoteDataBase->Text;
				 Lin_RemoteUserName = textBoxUser->Text;
				 Lin_RemoteUserPwd = textBoxPWD->Text;
				 Lin_IP = IpAddress->Text;
				 Lin_Saved = true;
				 //做一些保存工作
				 this->Hide();
			 }
private: System::Void buttonCancel_Click(System::Object^  sender, System::EventArgs^  e) {

			 textBoxDataSource->Text = Lin_LocalDataSource;
			 textBoxInitialCatalog->Text = Lin_LocalDataBaseName;
			 textBoxRemoteDataSource->Text = Lin_RemoteDataSource;
			 textBoxRemoteDataBase->Text = Lin_RemoteDataBaseName;
			 textBoxUser->Text = Lin_RemoteUserName;
			 textBoxPWD->Text = Lin_RemoteUserPwd;
			 IpAddress->Text = Lin_IP;


			 this->Hide();
		 }
private: System::Void trackBar1_Scroll(System::Object^  sender, System::EventArgs^  e) {
			 
			 TempMinTrackBarValue = trackBar1->Value - 20;
			 label5->Text = String::Format("{0:##0}°C", trackBar1->Value-20);
			 label6->Text = String::Format("{0:##0}°C", trackBar1->Value + trackBar2->Value-20);
			 
		 }
private: System::Void trackBar2_Scroll(System::Object^  sender, System::EventArgs^  e) {
			 
			 TempRangTrackBarValue = trackBar2->Value;
			 label5->Text = String::Format("{0:##0}°C", trackBar1->Value-20);
			 label6->Text = String::Format("{0:##0}°C", trackBar1->Value + trackBar2->Value-20);
		 }
private: System::Void buttonConnectToDB_Click(System::Object^  sender, System::EventArgs^  e) {
			 //测试本地数据库连接情况
			buttonConnectToDB->Enabled = false;
            bool Lin_BConnectedToLocalDB = false;
			Lin_LocalDataSource = textBoxDataSource->Text;
			Lin_LocalDataBaseName = textBoxInitialCatalog->Text;
			//String^ strConn = "Data Source = " + Lin_DataSource + ";Initial Catalog=" + Lin_DataBaseName + ";Integrated Security=True";//SQL Server链接字符串
			String^ strConn = "Data Source = " + Lin_LocalDataSource + ";Initial Catalog=" + Lin_LocalDataBaseName + ";uid = sa;pwd = 123456";//SQL Server链接字符串
			Lin_LocalConnSql = gcnew SqlConnection(strConn); //Sql链接类的实例化
			try
			{
				Lin_LocalConnSql->Open();//打开数据库
				if (Lin_LocalConnSql->State == ConnectionState::Open)
				{
					Lin_BConnectedToLocalDB = true;
					MessageBox::Show("本地数据库连通正常");
				}
			}
			catch (Exception ^m_Exceptin)
			{

				MessageBox::Show("无法连接本地数据库");
			}
			if (Lin_BConnectedToLocalDB)
			{
				Lin_LocalConnSql->Close();//关闭数据库
				Lin_BConnectedToLocalDB = false;
			} 
			buttonConnectToDB->Enabled = true;

		 }
private: System::Void buttonConnectToRemoteDB_Click(System::Object^  sender, System::EventArgs^  e) {
			 //测试远程数据库连接情况
			buttonConnectToRemoteDB->Enabled = false;
			bool Lin_BConnectedToRemoteDB = false;
			String ^m_DataSource = textBoxRemoteDataSource->Text;
			String ^m_DataBaseName = textBoxRemoteDataBase->Text;
			String ^m_User = textBoxUser->Text;
			String ^m_Password = textBoxPWD->Text;
			String^ strConn = "Data Source = " + m_DataSource + ";Initial Catalog=" + m_DataBaseName + ";uid = "+ m_User + ";pwd = "+m_Password;//SQL Server链接字符串
			Lin_RemoteConnSql = gcnew SqlConnection(strConn); //Sql链接类的实例化
			try
			{
				Lin_RemoteConnSql->Open();//打开数据库
				if (Lin_RemoteConnSql->State == ConnectionState::Open)
				{
					Lin_BConnectedToRemoteDB = true;
					MessageBox::Show("远程数据库连接正常");
				}
			}
			catch (Exception ^m_Exceptin)
			{
				MessageBox::Show("无法连接远程数据库，请检查数据库名称、账号密码及网络联通情况");
			}
			//下面断开连接
			if (Lin_BConnectedToRemoteDB)
			{
				Lin_RemoteConnSql->Close();//关闭数据库
				Lin_BConnectedToRemoteDB = false;		
			}
			buttonConnectToRemoteDB->Enabled = true;
		 }
};
}
