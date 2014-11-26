#pragma once

#include "FormImager.h"
#include "SetForm.h"
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Diagnostics;
using namespace System::Net;
using namespace System::Threading;
using namespace System::Net::Sockets;
using namespace System::Text;
////���紫��//
//using namespace System::Net::Sockets;
//using namespace System::Text;
////���߳�
//using namespace System::Threading;
#define IMAGERCOUNT 2

//���ݿ�
//using System::Collections::Generic;
//using System::Linq;
using namespace System::Data::SqlClient;


namespace IPCSample {

	/// <summary>
	/// Zusammenfassung f�r FormMulti
	///
	/// Warnung: Wenn Sie den Namen dieser Klasse �ndern, m�ssen Sie auch
	///          die Ressourcendateiname-Eigenschaft f�r das Tool zur Kompilierung verwalteter Ressourcen �ndern,
	///          das allen RESX-Dateien zugewiesen ist, von denen diese Klasse abh�ngt.
	///          Anderenfalls k�nnen die Designer nicht korrekt mit den lokalisierten Ressourcen
	///          arbeiten, die diesem Formular zugewiesen sind.
	/// </summary>
	/*public ref struct IPCMatchData{
		double IPCVerifyValue;
		double IPCAngle;
		array<short> ^IPCMatchValue;
	public : 
	IPCMatchData (double IPCVerifyValue,double IPCAngle,array<short> ^IPCMatchValue)
	{
		this->IPCVerifyValue = IPCVerifyValue;
		this->IPCAngle = IPCAngle;
		this->IPCMatchValue = IPCMatchValue;
	}
	};*/

	public ref class FormMulti : public System::Windows::Forms::Form
	{
	public:
		FormMulti(HWND hostHandle);
		property System::Version^ Version
		{
			System::Version^ get()
			{
				Reflection::Assembly^ assembly = Reflection::Assembly::GetExecutingAssembly();
				return assembly->GetName()->Version;
			}
		}
	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		~FormMulti()
		{
			if (components)
			{
				delete components;
			}
		}
                /*FormImager ��IPC�Դ��࣬һ��formsImager ��Ӧһ��������*/
		array<FormImager^> ^formsImager;
                IPC^ ipc;
                /*���öԻ��򣬿�����Ϊ��ʾ�¶ȵĶԻ�������*/
		SetForm ^m_SetForm;

		
		double m_MaxTempValue; //��ǰ���������
		double m_MaxMatchTempValue;//����ú��������£����ڲɼ��˲���Ҫ��ʾ����ú�ѵ����ݣ���������ò���.
		double m_AverageTempValue;
		int m_AlarmTemp;  //�����¶�
		Bitmap^ m_BmpImage;//��ʾ����
		Bitmap^ m_MatchBmpImage;//����ú���Ļ��棬���ڲɼ��˲���Ҫ��ʾ����ú�ѵ����ݣ���������ò���.
		int Lin_CurrentAngle;//ת���ĽǶ�
		int Lin_OldAngle;
		int Lin_RangeAngle;//һ��ͼ������ʾ������ӽ�//
		bool Connected;  //�Ƿ�������������
		bool Lin_BMoving; //���û�õ�������ȥ��
		double Lin_MoveTimeInterval;  //���Ƕ��йأ����û�õ�������ȥ��
		double Lin_AngleInterval;     //���Ƕ��йأ����û�õ�������ȥ��
                /*�ӷ������˽��սǶȣ����ʹ����ת��������ȡ�Ƕȣ���ô����Ĵ������ȥ��*/  
		Socket ^connectionSocket; 
		bool Lin_BNetConnect;
		ThreadStart ^Lin_ThreadStart;
		Thread ^Lin_RecvThread;
		String ^Lin_RecvStr;
                /*�ӷ������˽��սǶȣ����ʹ����ת��������ȡ�Ƕȣ���ô����Ĵ������ȥ��*/  
	private: System::Windows::Forms::GroupBox^  groupBoxVideo;


	private: System::Windows::Forms::GroupBox^  SetgroupBox;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::Label^  AngleLabel;
	private: System::Windows::Forms::Timer^  MyTimer10;
	protected: 

	protected: 
		bool Painted;
	private:
		short TempMinTrackBarValue;
		short TempRangTrackBarValue;
		
		int SetFormPos;//���غ���ʾ����//
		System::Drawing::Pen^ myBlackPen;
		System::Drawing::Font^ myBigFront;
		System::Drawing::Font^ mySmallFront;
		System::Drawing::Pen^ myWhitePen;
		System::Drawing::Pen^ myBulePen;
		System::Drawing::Pen^ myRedPen;
private: System::Data::DataSet^  dataSet1;

private: System::Windows::Forms::Button^  SetButton;
private: System::Windows::Forms::Label^  label4;
private: System::Windows::Forms::Label^  label3;
private: System::Windows::Forms::TextBox^  InitialCatalogtextBox;

private: System::Windows::Forms::TextBox^  DataSourcetextBox;

private: System::Windows::Forms::GroupBox^  groupBox2;
private: System::Windows::Forms::Button^  button1;
private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Timer^  MyTimerSaveData;

	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::Timer^  MyTimerDeleteDB;
	private: System::Windows::Forms::Timer^  MyTimerLinkToLocalDB;

	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::Timer^  MyTimerShowRecvStr;

		System::Drawing::Brush ^myBrush;

                //pos��ʾ�ڼ����㣬�ܹ���FrameSize = FrameWidth*FrameHeight���㣬�������ص�����꣬���磬��382���㣬���أ�0��1������һ�еڶ���
		Point whu_GetValuePositon(short pos,int width,int height);
		/*��ǰ������¶ȴ���*/
		int m_MousePositionX,m_MousePositionY;// ����λ��

		void whu_GetRGBValue(short m_value ,Byte *m_RGBValue);//������ת����RGB����ֵ����GetBitmap�е����˴˺���//
		void GetBitmap(Bitmap^ Bmp, array<short>^values);//������ת����ͼƬ//
		void GetValuesData(array<short>^values0,array<short>^values1,array<short>^values2);//�ϳ����������ǵ�����//
		array<short>^Values;//���������ǵõ��������¶���Ϣ//
		array<Byte>^rgbValues;//
		array<double>^ whu_AllTemValues;//��ǰ���棺˫�����ǵ��¶�
		array<double>^ whu_AllSelectRectValues;//��ǰ���棺ѡ��������¶�//
		Point m_MaxTempValuePoint;      //�¶���ߵ�
		Point m_MaxMatchTempValuePoint;  //û�õ�
		int FrameWidth ;      //����Imager���泤��
		int FrameHeight;      //����Imager����߶�
		int FrameSize;        //FrameSize = FrameWidth*FrameHeight; �����м������ص㡣

/////////////////////////���ڲɼ������˲�������ˣ��������Щ����ȥ��///////////////////////////////////////////////////////////////
		bool whu_BSHowRectangle; //����ڻ����ϻ�һ�����ο���ʾ���¶ȵ���Ϣ��whu_BSHowRectangle�����Ƿ���Ҫ��ʾ������ο�.
		bool whu_BKeepRectangle; //�Ƿ���Ҫ����ס��껭�ľ��ο�
		bool whu_BShowMouseTemp; //�Ƿ���Ҫ��ʾ������¶�
		double whu_MouseTempValue; //������¶�
		System::Drawing::Rectangle ^whu_SelectRectangle; //���ο�

	        
////////////////////////////���ڲɼ��˲���Ҫ��ʾ����ú�ѵ�����,��˴�Match���۵ı������Ǻ������ò���///////////////////////////////////

		/* ����ú�ѵ��¶ȴ���*/
		//void whu_ShowHighTempToChart();
		void whu_AddMatchValue(double CurrentAngle,array<double>^ InputValue);//

                //�õ�ƴ��ͼƬ�����ڲɼ��˲���Ҫ��ʾ����ú�ѵ����ݣ����ԣ��������û�õ�,�����ϴ�Match���۵ı������Ǻ������ò���//	
		void whu_GetMatchingImg(array<double>^InputValues,array<double>^InputAngle,Bitmap ^MatchBmp);
		Bitmap^ whu_ResizeImage(Bitmap^ Bmp,int NewWidth,int NewHeight);//����ͼƬ
		double whu_GetCurrentAngle();
		array<double>^ whu_MatchValues;
		//array<IPCMatchData^>^ whu_IPCMatchData;
		
		array<Byte>^ rgbMatchValues;	
		array<double>^ whu_AllMatchTempValues;//ɨ������Ժ�ú�����¶�MatchWidth*MatchHeight//
		array<double>^ whu_OutputPolarTemp;
		array<double>^ whu_AllSelectMatchTempValues;//ѡ������¶���Ϣ//
		array<double>^ whu_AllAngles;//ת���ĽǶ�//
		int MatchWidth;
		int MatchHeight;
		int InnerCircleR;
		int TwoFrameWidth;
		int m_MatchMousePositionX,m_MatchMousePositionY;
		bool whu_BMatchSHowRectangle;
		bool whu_BMatchKeepRectangle;
		bool whu_BMatchShowMouseTemp;
		double whu_MatchMouseTempValue;
		System::Drawing::Rectangle ^whu_MatchSelectRectangle;
		int LineCount ;//ɨ�����س���//
		int m_MatchSelectRectShowTime;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	
		//���ݿ��ȡ����//
                int AngleAccuracy;//ɨ��ľ���
		SqlConnection ^ConnSql;
		bool whu_SaveDataToDB();
		double whu_ReadDataFromDB(array<short>^ DestData);
		String ^Lin_DataSource;
		String ^Lin_DataName;
		String ^Lin_ListName;
		bool Lin_BConnectToDB;
		bool Lin_BMoveDone;//�ʼ�Ĵ��淽���Ƚ��鷳�������ĳ����ڵ���У��λ�ķ���������Lin_BMoveDoneû�õ�
		bool Lin_BDBSaveDone;//�ʼ�Ĵ��淽���Ƚ��鷳�������ĳ����ڵ���У��λ�ķ���������Lin_BDBSaveDoneû�õ�
		unsigned short Lin_SameAngleCount;//�ʼ�Ĵ��淽���Ƚ��鷳�������ĳ����ڵ���У��λ�ķ���������Lin_SameAngleCountû�õ�
		array<short>^ Lin_AngleWithValues;
               
                //�����µĴ��淽��������ˢ���Ժ󣬵���whu_UpdateAngleWithValues��������Lin_AngleWithValues��У��λ����Ϊ0xffff����ʾ��Ҫ���� 
		void whu_UpdateAngleWithValues(int CurrentAngle,array<short>^InputValues);

                //�����µĴ��淽����������д�����ݿ��Ժ󣬵���whu_ClearAngleWithValues��������Lin_AngleWithValues��У��λ����Ϊ0����ʾ�Ѿ�����
		void whu_ClearAngleWithValues();  

		//socket�����շ������˷��͹����ĽǶȣ����ʹ����ת������������������ò���//
		void whu_RecvData();
private: System::Windows::Forms::Timer^  MyTimerGetData;

	private: System::Windows::Forms::TrackBar^  trackBar1;
	private: System::Windows::Forms::TrackBar^  trackBar2;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Timer^  MyTimer100;


	private: System::Windows::Forms::PictureBox^  pictureBox;
	private: System::ComponentModel::IContainer^  components;
	protected: 

	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode f�r die Designerunterst�tzung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor ge�ndert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(FormMulti::typeid));
			this->MyTimerGetData = (gcnew System::Windows::Forms::Timer(this->components));
			this->trackBar1 = (gcnew System::Windows::Forms::TrackBar());
			this->trackBar2 = (gcnew System::Windows::Forms::TrackBar());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->MyTimer100 = (gcnew System::Windows::Forms::Timer(this->components));
			this->pictureBox = (gcnew System::Windows::Forms::PictureBox());
			this->groupBoxVideo = (gcnew System::Windows::Forms::GroupBox());
			this->SetgroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->InitialCatalogtextBox = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->DataSourcetextBox = (gcnew System::Windows::Forms::TextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->AngleLabel = (gcnew System::Windows::Forms::Label());
			this->MyTimer10 = (gcnew System::Windows::Forms::Timer(this->components));
			this->dataSet1 = (gcnew System::Data::DataSet());
			this->SetButton = (gcnew System::Windows::Forms::Button());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->MyTimerSaveData = (gcnew System::Windows::Forms::Timer(this->components));
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->MyTimerDeleteDB = (gcnew System::Windows::Forms::Timer(this->components));
			this->MyTimerLinkToLocalDB = (gcnew System::Windows::Forms::Timer(this->components));
			this->MyTimerShowRecvStr = (gcnew System::Windows::Forms::Timer(this->components));
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox))->BeginInit();
			this->groupBoxVideo->SuspendLayout();
			this->SetgroupBox->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataSet1))->BeginInit();
			this->SuspendLayout();
			// 
			// MyTimerGetData
			// 
			this->MyTimerGetData->Enabled = true;
			this->MyTimerGetData->Interval = 10;
			this->MyTimerGetData->Tick += gcnew System::EventHandler(this, &FormMulti::MyTimer1000_Tick);
			// 
			// trackBar1
			// 
			this->trackBar1->Location = System::Drawing::Point(114, 20);
			this->trackBar1->Maximum = 120;
			this->trackBar1->Name = L"trackBar1";
			this->trackBar1->Size = System::Drawing::Size(167, 45);
			this->trackBar1->TabIndex = 1;
			this->trackBar1->Value = 65;
			this->trackBar1->Scroll += gcnew System::EventHandler(this, &FormMulti::trackBar1_Scroll);
			// 
			// trackBar2
			// 
			this->trackBar2->Location = System::Drawing::Point(114, 94);
			this->trackBar2->Maximum = 120;
			this->trackBar2->Minimum = 1;
			this->trackBar2->Name = L"trackBar2";
			this->trackBar2->Size = System::Drawing::Size(167, 45);
			this->trackBar2->TabIndex = 2;
			this->trackBar2->Value = 20;
			this->trackBar2->Scroll += gcnew System::EventHandler(this, &FormMulti::trackBar2_Scroll);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(20, 28);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(83, 12);
			this->label1->TabIndex = 3;
			this->label1->Text = L"��С��ʾ�¶�:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(19, 99);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(89, 12);
			this->label2->TabIndex = 4;
			this->label2->Text = L"��ʾ�¶����䣺";
			// 
			// MyTimer100
			// 
			this->MyTimer100->Enabled = true;
			this->MyTimer100->Tick += gcnew System::EventHandler(this, &FormMulti::MyTimer100_Tick);
			// 
			// pictureBox
			// 
			this->pictureBox->Location = System::Drawing::Point(6, 12);
			this->pictureBox->Name = L"pictureBox";
			this->pictureBox->Size = System::Drawing::Size(764, 288);
			this->pictureBox->TabIndex = 12;
			this->pictureBox->TabStop = false;
			this->pictureBox->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &FormMulti::pictureBox_Paint);
			this->pictureBox->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &FormMulti::pictureBox_MouseClick);
			this->pictureBox->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &FormMulti::pictureBox_MouseDown);
			this->pictureBox->MouseLeave += gcnew System::EventHandler(this, &FormMulti::pictureBox_MouseLeave);
			this->pictureBox->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &FormMulti::pictureBox_MouseMove);
			this->pictureBox->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &FormMulti::pictureBox_MouseUp);
			// 
			// groupBoxVideo
			// 
			this->groupBoxVideo->Controls->Add(this->pictureBox);
			this->groupBoxVideo->Location = System::Drawing::Point(5, 3);
			this->groupBoxVideo->Name = L"groupBoxVideo";
			this->groupBoxVideo->Size = System::Drawing::Size(778, 305);
			this->groupBoxVideo->TabIndex = 14;
			this->groupBoxVideo->TabStop = false;
			// 
			// SetgroupBox
			// 
			this->SetgroupBox->Controls->Add(this->groupBox1);
			this->SetgroupBox->Location = System::Drawing::Point(9, 357);
			this->SetgroupBox->Name = L"SetgroupBox";
			this->SetgroupBox->Size = System::Drawing::Size(772, 188);
			this->SetgroupBox->TabIndex = 13;
			this->SetgroupBox->TabStop = false;
			this->SetgroupBox->Enter += gcnew System::EventHandler(this, &FormMulti::SetgroupBox_Enter);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->label12);
			this->groupBox1->Controls->Add(this->label11);
			this->groupBox1->Controls->Add(this->groupBox2);
			this->groupBox1->Controls->Add(this->trackBar1);
			this->groupBox1->Controls->Add(this->label6);
			this->groupBox1->Controls->Add(this->trackBar2);
			this->groupBox1->Controls->Add(this->label5);
			this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Controls->Add(this->pictureBox1);
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Location = System::Drawing::Point(6, 20);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(760, 157);
			this->groupBox1->TabIndex = 8;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"�������";
			this->groupBox1->Enter += gcnew System::EventHandler(this, &FormMulti::groupBox1_Enter);
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(259, 135);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(53, 12);
			this->label12->TabIndex = 17;
			this->label12->Text = L"���յ�..";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(38, 133);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(77, 12);
			this->label11->TabIndex = 16;
			this->label11->Text = L"����IP��ַ��";
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->button3);
			this->groupBox2->Controls->Add(this->button1);
			this->groupBox2->Controls->Add(this->InitialCatalogtextBox);
			this->groupBox2->Controls->Add(this->label4);
			this->groupBox2->Controls->Add(this->label3);
			this->groupBox2->Controls->Add(this->DataSourcetextBox);
			this->groupBox2->Location = System::Drawing::Point(361, 17);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(390, 106);
			this->groupBox2->TabIndex = 12;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"���ݿ�����";
			// 
			// button3
			// 
			this->button3->Enabled = false;
			this->button3->Location = System::Drawing::Point(286, 58);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(72, 39);
			this->button3->TabIndex = 13;
			this->button3->Text = L"�Ͽ�";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &FormMulti::button3_Click_1);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(286, 15);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(72, 39);
			this->button1->TabIndex = 12;
			this->button1->Text = L"����";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &FormMulti::button1_Click_1);
			// 
			// InitialCatalogtextBox
			// 
			this->InitialCatalogtextBox->Location = System::Drawing::Point(95, 68);
			this->InitialCatalogtextBox->Name = L"InitialCatalogtextBox";
			this->InitialCatalogtextBox->Size = System::Drawing::Size(171, 21);
			this->InitialCatalogtextBox->TabIndex = 9;
			this->InitialCatalogtextBox->Text = L"Meidui";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(27, 72);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(53, 12);
			this->label4->TabIndex = 11;
			this->label4->Text = L"���ݿ⣺";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(27, 30);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(53, 12);
			this->label3->TabIndex = 10;
			this->label3->Text = L"��������";
			// 
			// DataSourcetextBox
			// 
			this->DataSourcetextBox->Location = System::Drawing::Point(95, 27);
			this->DataSourcetextBox->Name = L"DataSourcetextBox";
			this->DataSourcetextBox->Size = System::Drawing::Size(171, 21);
			this->DataSourcetextBox->TabIndex = 8;
			this->DataSourcetextBox->Text = L"SHELMYLIN-PC";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(320, 21);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(35, 12);
			this->label6->TabIndex = 7;
			this->label6->Text = L"65��C";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(320, 107);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(35, 12);
			this->label5->TabIndex = 6;
			this->label5->Text = L"20��C";
			// 
			// pictureBox1
			// 
			this->pictureBox1->ImageLocation = L"D:\\ú�Ѳ���\\�¶���ɫ����.jpg";
			this->pictureBox1->Location = System::Drawing::Point(284, 17);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(25, 106);
			this->pictureBox1->TabIndex = 5;
			this->pictureBox1->TabStop = false;
			// 
			// AngleLabel
			// 
			this->AngleLabel->AutoSize = true;
			this->AngleLabel->Font = (gcnew System::Drawing::Font(L"SimSun", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->AngleLabel->Location = System::Drawing::Point(101, 324);
			this->AngleLabel->Name = L"AngleLabel";
			this->AngleLabel->Size = System::Drawing::Size(147, 21);
			this->AngleLabel->TabIndex = 22;
			this->AngleLabel->Text = L"��ת�Ƕȣ�0��";
			// 
			// MyTimer10
			// 
			this->MyTimer10->Enabled = true;
			this->MyTimer10->Interval = 10;
			this->MyTimer10->Tick += gcnew System::EventHandler(this, &FormMulti::MyTimer10_Tick);
			// 
			// dataSet1
			// 
			this->dataSet1->DataSetName = L"NewDataSet";
			// 
			// SetButton
			// 
			this->SetButton->Location = System::Drawing::Point(5, 314);
			this->SetButton->Name = L"SetButton";
			this->SetButton->Size = System::Drawing::Size(82, 38);
			this->SetButton->TabIndex = 16;
			this->SetButton->Text = L"����";
			this->SetButton->UseVisualStyleBackColor = true;
			this->SetButton->Click += gcnew System::EventHandler(this, &FormMulti::SetButton_Click);
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"SimSun", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->label7->Location = System::Drawing::Point(500, 328);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(128, 16);
			this->label7->TabIndex = 23;
			this->label7->Text = L"IPCͨ��δ������";
			// 
			// MyTimerSaveData
			// 
			this->MyTimerSaveData->Enabled = true;
			this->MyTimerSaveData->Interval = 1000;
			this->MyTimerSaveData->Tick += gcnew System::EventHandler(this, &FormMulti::MyTimer5Mins_Tick);
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Font = (gcnew System::Drawing::Font(L"SimSun", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->label8->Location = System::Drawing::Point(641, 329);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(120, 16);
			this->label8->TabIndex = 26;
			this->label8->Text = L"���ݿ�δ���ӣ�";
			this->label8->Click += gcnew System::EventHandler(this, &FormMulti::label8_Click);
			// 
			// MyTimerDeleteDB
			// 
			this->MyTimerDeleteDB->Enabled = true;
			this->MyTimerDeleteDB->Tick += gcnew System::EventHandler(this, &FormMulti::MyTimerDeleteDB_Tick);
			// 
			// MyTimerLinkToLocalDB
			// 
			this->MyTimerLinkToLocalDB->Enabled = true;
			this->MyTimerLinkToLocalDB->Interval = 1000;
			this->MyTimerLinkToLocalDB->Tick += gcnew System::EventHandler(this, &FormMulti::MyTimerLinkToLocalDB_Tick);
			// 
			// MyTimerShowRecvStr
			// 
			this->MyTimerShowRecvStr->Enabled = true;
			this->MyTimerShowRecvStr->Tick += gcnew System::EventHandler(this, &FormMulti::MyTimerShowRecvStr_Tick);
			// 
			// FormMulti
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(792, 547);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->AngleLabel);
			this->Controls->Add(this->SetgroupBox);
			this->Controls->Add(this->SetButton);
			this->Controls->Add(this->groupBoxVideo);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"FormMulti";
			this->Text = L" ";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &FormMulti::FormMulti_FormClosing);
			this->Load += gcnew System::EventHandler(this, &FormMulti::FormMulti_Load);
			this->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &FormMulti::pictureBox_MouseClick);
			this->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &FormMulti::pictureBox_MouseDown);
			this->MouseLeave += gcnew System::EventHandler(this, &FormMulti::pictureBox_MouseLeave);
			this->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &FormMulti::pictureBox_MouseMove);
			this->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &FormMulti::pictureBox_MouseUp);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox))->EndInit();
			this->groupBoxVideo->ResumeLayout(false);
			this->SetgroupBox->ResumeLayout(false);
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataSet1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void FormMulti_Load(System::Object^  sender, System::EventArgs^  e);
	private: System::Void FormMulti_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e);
	private: System::Void FormImager_OnResize(System::Object^  sender, System::EventArgs^  e);
	private: System::Void MyTimer1000_Tick(System::Object^  sender, System::EventArgs^  e)
			 {
				 if (Connected)
				 {
					label7->Text = "IPCͨ���ѿ�����";
					//button2->Enabled = true;
					//Lin_OldAngle = Lin_CurrentAngle;
					//Lin_CurrentAngle = whu_GetCurrentAngle();//�������ĵط��õ�Lin_CurrentAngle��ֵ�ˡ�
					if (Lin_OldAngle!=Lin_CurrentAngle)
					{
						AngleLabel->Text = String::Format("��ת�Ƕȣ�{0:##0.0}��",(double)Lin_CurrentAngle/AngleAccuracy);
						array<short>^ m_value = gcnew array<short>(Lin_AngleWithValues->Length/(AngleAccuracy*360)-2);
						int ValueSrc = FrameSize;
						for (int j=0;j<m_value->Length;j++,ValueSrc++)
						{
							m_value[j] = Values[ValueSrc];
						}
						whu_UpdateAngleWithValues(Lin_CurrentAngle,m_value); 
					}
					
				}else{
					label7->Text = "IPCͨ��δ������";
					//button2->Enabled = false;
				}
				 /*if (Lin_BConnectToDB == true)
				 { 
					 label8->Text = "���ݿ������ӣ�";
				 }else{
					 label8->Text = "���ݿ�δ���ӣ�";
				 } */
				///*��ģ�鲻��Ҫ*/
				// //�õ����������ǵĵ�ǰ����¶Ⱥ�ƽ���¶�//
				// double TempValue[IMAGERCOUNT];
				// //double AverageTempValue[IMAGERCOUNT];
				// double allAverageValue =0;
				// for (int i=0;i<IMAGERCOUNT;i++)
				// {
				//	 TempValue[i] = formsImager[i]->m_MaxTempValue;
				//	 //AverageTempValue[i] = formsImager[i]->m_AverageTempValue;
				// }
				// m_MaxTempValue = TempValue[0];
				// for (int i=0;i<IMAGERCOUNT;i++)
				// {
				//	 if ( m_MaxTempValue < TempValue[i])
				//	 { 
				//		 m_MaxTempValue = TempValue[i];
				//	 } 
				// }
				 //if (Connected)
				 //{
					 //��ʾ�ϳ�ͼ���������¶�//
					 //if (whu_BMatchKeepRectangle)//�����˾��ο�
					 //{
						 //AverTempLabel->Show();
						 //this->MyChart->Series["�����¶�"]->Points->AddXY(m_MatchSelectRectShowTime,whu_AllSelectMatchTempValues[0]);
						 //AverTempLabel->Text = String::Format("{0:##0.0}��C", whu_AllSelectMatchTempValues[0]); 
						 //m_MatchSelectRectShowTime++;
						 //if (m_MatchSelectRectShowTime>=360)
						 //{
							 //this->MyChart->Series["�����¶�"]->Points->Clear();
							 //m_MatchSelectRectShowTime = 0;
						 //}
					 //} 
					// else
					// {
						// this->MyChart->Series["�����¶�"]->Points->Clear();
						// m_MatchSelectRectShowTime = 0;
						// AverTempLabel->Hide();
						// AverTempLabel->Text = String::Format("��C"); 
					 //}

				 //}
				 
				

			 }
private: System::Void trackBar1_Scroll(System::Object^  sender, System::EventArgs^  e) {
				 //ͳһ����ͼ��//
				 for (int i=0;i<IMAGERCOUNT;i++)
				 {
					 formsImager[i]->TempMinTrackBarValue = trackBar1->Value;			 
				 }

				 TempMinTrackBarValue = trackBar1->Value - 20;
				 label5->Text = String::Format("{0:##0}��C", trackBar1->Value-20);
				 label6->Text = String::Format("{0:##0}��C", trackBar1->Value + trackBar2->Value-20);

			 }
private: System::Void trackBar2_Scroll(System::Object^  sender, System::EventArgs^  e) {
			// for (int i=0;i<IMAGERCOUNT;i++)
			// {
				// formsImager[i]->TempRangTrackBarValue = trackBar2->Value;			 
			 //}
			 TempRangTrackBarValue = trackBar2->Value;
			 label6->Text = String::Format("{0:##0}��C", trackBar1->Value + trackBar2->Value);
		 }
private: System::Void pictureBox_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) 
		 {  
			 if (Connected)
			 {
				 e->Graphics->DrawImage( m_BmpImage, 0, 0 ); 
				 e->Graphics->DrawRectangle(myWhitePen,*whu_SelectRectangle);
				 if (whu_BKeepRectangle&&(whu_SelectRectangle->Left != whu_SelectRectangle->Right)&&(whu_SelectRectangle->Top!=whu_SelectRectangle->Bottom))
				 {
					 double m_TempValue = 0;
					 double m_All = 0;
					 int m_Count = 0;
					 Point RectHighTempPoint;
					 double RectHighTemp = 0;
					 for (int i=whu_SelectRectangle->Top;i<whu_SelectRectangle->Height+whu_SelectRectangle->Top;i++ )
					 {
						 for (int j=whu_SelectRectangle->Left;j<whu_SelectRectangle->Width+whu_SelectRectangle->Left;j++)
						 {
							 int pos = i*FrameWidth*2 + j;
							 if (pos<FrameSize*2)
							 {
								 m_All = m_All + whu_AllTemValues[pos];
								 m_Count ++;
								 if (whu_AllTemValues[pos]>RectHighTemp)
								 {
									 RectHighTemp = whu_AllTemValues[pos];
									 RectHighTempPoint.X = j;
									 RectHighTempPoint.Y = i;
								 }
							 }
							 

						 } 
					 }
					 //��ʾ�����¶�//
					 if (m_Count>=1)
					 {
						 m_TempValue = m_All/m_Count;
						 whu_AllSelectRectValues[0] = m_TempValue;
						 String ^StrRectTemp = String::Format("ƽ���¶ȣ�{0:##0.0}��C", m_TempValue);
						 
						 e->Graphics->DrawString(StrRectTemp,mySmallFront,myBrush,whu_SelectRectangle->X,whu_SelectRectangle->Y-30);
						 //������ǰ��������¶ȵ�//
						 System::Drawing::Rectangle ^m_MaxTempValuePointRect = gcnew System::Drawing::Rectangle(RectHighTempPoint.X-5,RectHighTempPoint.Y-5,10,10);
						 Point StartPoint1,StartPoint2,EndPoint1,EndPoint2; 
						 StartPoint1.X = RectHighTempPoint.X-20;
						 StartPoint1.Y = RectHighTempPoint.Y;
						 EndPoint1.X = RectHighTempPoint.X+20;
						 EndPoint1.Y = RectHighTempPoint.Y;
						 StartPoint2.X = RectHighTempPoint.X;
						 StartPoint2.Y = RectHighTempPoint.Y-20;
						 EndPoint2.X = RectHighTempPoint.X;
						 EndPoint2.Y = RectHighTempPoint.Y+20;			 
						 e->Graphics->DrawEllipse(myRedPen,*m_MaxTempValuePointRect);
						 e->Graphics->DrawLine(myRedPen,StartPoint1,EndPoint1);
						 e->Graphics->DrawLine(myRedPen,StartPoint2,EndPoint2);

						 String ^StrRectHighTemp = String::Format("��������¶ȣ�{0:##0.0}��C", RectHighTemp);
						 e->Graphics->DrawString(StrRectHighTemp,mySmallFront,myBrush,RectHighTempPoint.X,RectHighTempPoint.Y);

					 }
					
				 }


				 //�¶���ߵ�
				 System::Drawing::Rectangle ^m_MaxTempValuePointRect = gcnew System::Drawing::Rectangle(m_MaxTempValuePoint.X-8,m_MaxTempValuePoint.Y-8,16,16);
				 Point StartPoint1,StartPoint2,EndPoint1,EndPoint2;
				 StartPoint1.X = m_MaxTempValuePoint.X-30;
				 StartPoint1.Y = m_MaxTempValuePoint.Y;
				 EndPoint1.X = m_MaxTempValuePoint.X+30;
				 EndPoint1.Y = m_MaxTempValuePoint.Y;
				 StartPoint2.X = m_MaxTempValuePoint.X;
				 StartPoint2.Y = m_MaxTempValuePoint.Y-30;
				 EndPoint2.X = m_MaxTempValuePoint.X;
				 EndPoint2.Y = m_MaxTempValuePoint.Y+30;			 
				 e->Graphics->DrawEllipse(myRedPen,*m_MaxTempValuePointRect);
				 e->Graphics->DrawLine(myRedPen,StartPoint1,EndPoint1);
				 e->Graphics->DrawLine(myRedPen,StartPoint2,EndPoint2);
				 String ^StrMaxTempValue = String::Format("��ǰ����£�{0:##0.0}��C",m_MaxTempValue);
				 int PosX = pictureBox->Width/30;
				 int PosY = pictureBox->Height/20;
				 e->Graphics->DrawString(StrMaxTempValue,myBigFront,myBrush,PosX,PosY);
				 //StrMaxTempValue = String::Format("���µ㣺{0:##0.0}��C",m_MaxTempValue);
				 //e->Graphics->DrawString(StrMaxTempValue,mySmallFront,myBrush,m_MaxTempValuePoint);
				 //��ʾ�����¶�//
				 if (whu_BShowMouseTemp)
				 {
					 String ^StrTempValue = String::Format("{0:##0.0}��C",whu_MouseTempValue);
					 e->Graphics->DrawString(StrTempValue,myBigFront,myBrush,m_MousePositionX+5,m_MousePositionY+8);
				 }

			 }
			 


			 
		 }
private: System::Void pictureBox_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs ^  e) 
		 {
			 int Height = this->pictureBox->Height;
			 int Width = this->pictureBox->Width;
			 /*int m_MousePositionX,m_MousePositionY;*/
			 m_MousePositionX = e->X;
			 m_MousePositionY = e->Y;
			 if ((m_MousePositionX < Width)&&(m_MousePositionY<Height ))
			 {
				 whu_BShowMouseTemp = true;
				 int pos = m_MousePositionY*FrameWidth*2+m_MousePositionX;
				 if (pos<FrameSize*2&&m_MousePositionX<FrameWidth*2&&m_MousePositionY<FrameHeight)
				 {
					 whu_MouseTempValue = whu_AllTemValues[pos];
				  }
				 if (whu_BSHowRectangle&&!whu_BKeepRectangle)//������ѡ������// 
				 {
					 whu_SelectRectangle = gcnew System::Drawing::Rectangle(whu_SelectRectangle->Left,whu_SelectRectangle->Top,e->X-whu_SelectRectangle->X,e->Y-whu_SelectRectangle->Y);
				 }

			 }


		 }
private: System::Void pictureBox_MouseLeave(System::Object^  sender, System::EventArgs ^  e) 
		 {
			 whu_BShowMouseTemp = false;
			 whu_BShowMouseTemp = false;
		 }
private: System::Void pictureBox_MouseDown(System::Object^ sender,System::Windows::Forms::MouseEventArgs ^  e){
			 whu_SelectRectangle = gcnew System::Drawing::Rectangle(e->X,e->Y,0,0);
			 whu_BSHowRectangle = true;
			 whu_BKeepRectangle = false;
		 }
private: System::Void pictureBox_MouseUp(System::Object^ sender,System::Windows::Forms::MouseEventArgs ^  e)
		 {
			 whu_SelectRectangle = gcnew System::Drawing::Rectangle(whu_SelectRectangle->Left,whu_SelectRectangle->Top,e->X-whu_SelectRectangle->Left,e->Y-whu_SelectRectangle->Top);
			 if ((whu_SelectRectangle->Left != whu_SelectRectangle->Right)&&(whu_SelectRectangle->Top!=whu_SelectRectangle->Bottom))
			 {
				 whu_BSHowRectangle = true;
				whu_BKeepRectangle = true;
			 }



		 }
private: System::Void pictureBox_MouseClick(System::Object ^sender,System::Windows::Forms::MouseEventArgs ^  e)
		 {
			 //whu_BSHowRectangle = false;
		 }
private: System::Void MyTimer100_Tick(System::Object^  sender, System::EventArgs^  e) {
			//��ø��������ǵ�ͼ��,������Ҫ������ǰ����//
			 if (Connected)
			 {

				 
				 //������������ͼƬ�򵥺ϵ�һ��//
				 GetValuesData(Values,formsImager[0]->Values,formsImager[1]->Values);
				 
				 ////���浽���ݿ�//
				 //array<short>^ m_SaveToDBValue = gcnew array<short>(LineCount);
				 //for (int i = (Values->Length)/2,j=0;i<(Values->Length)/2+LineCount;i++,j++)
				 //{
					// m_SaveToDBValue[j] = Values[i];
				 //}
				/* m_CurrentAngle = whu_GetCurrentAngle();
				 AngleLabel->Text = String::Format("��ת�Ƕȣ�{0:##0}��",m_CurrentAngle);
				 whu_SaveDataToDB(m_CurrentAngle,Values);*/
				 //whu_ReadDataFromDB(Values);
				 GetBitmap(m_BmpImage,Values);
				 pictureBox->Invalidate();
				 //��ʾ����¶�//
				 //MaxTempLabel->Text = String::Format("{0:##0.0}��C",m_MaxTempValue);
				 //ˢ�������¶�//
				 if (whu_BShowMouseTemp)
				 {
					 int pos = m_MousePositionY*FrameWidth*2+m_MousePositionX;
					 if (pos<FrameSize*2)
					 {
						 whu_MouseTempValue = whu_AllTemValues[pos];
					 }
				 }
				 
			 }
			

			

		 }
private: System::Void MyTimer200_Tick(System::Object^  sender, System::EventArgs^  e) {
			 /*������ƴ�Ӻϳ�ͼ����,��ģ�鲻��Ҫ*/
			 //
			 //if (Connected)
			 //{
				// // whu_ReadDataFromDB(Values);
				// array<double>^ m_value = gcnew array<double>(whu_MatchValues->Length/(AngleAccuracy*360)-2);
				// int ValueSrc = 0;
				// int StartAnglePos = m_CurrentAngle - m_RangeAngle/2;
				// for (int i=StartAnglePos*AngleAccuracy;i<AngleAccuracy*(m_CurrentAngle+m_RangeAngle/2);i++)
				// {
				//	 double angle = i/(double)AngleAccuracy;
				//	 for (int j=0;j<m_value->Length;j++,ValueSrc++)
				//	 {
				//		 m_value[j] = Values[ValueSrc];
				//		 if (ValueSrc==FrameSize*2-1)
				//		 {
				//			 ValueSrc=0;
				//		 }
				//	 }
				//	 whu_AddMatchValue(angle,m_value);
				// }
				//

				// whu_GetMatchingImg(whu_MatchValues,whu_AllAngles,m_MatchBmpImage);
				// MatchPictureBox->Invalidate();

				// //��ʾ������¶�
				// if (whu_BMatchShowMouseTemp)
				// {
				//	 int pos = m_MatchMousePositionY*MatchWidth+m_MatchMousePositionX;
				//	 if (pos<MatchWidth*MatchHeight)
				//	 {
				//		 whu_MatchMouseTempValue = whu_AllMatchTempValues[pos];	 
				//	 }
				// }

				// //�������¶���Ϣ�Ļ�ȡ//
				// for (int i=0;i<360;i++)
				// {
				//	 int VerifyPos = i*(1+1+LineCount);
				//	 if (whu_OutputPolarTemp[VerifyPos]!=0xffff)
				//	 {
				//		 whu_OutputPolarTemp[VerifyPos]=0xffff;//У��λ˵��

				//	 }else{
				//		 whu_OutputPolarTemp[VerifyPos+1] = i;//�Ƕ�
				//		 for (int j=0;j<LineCount;j++)
				//		 {
				//			 int dst = j+i*whu_MatchValues->Length/360+2;
				//			 whu_OutputPolarTemp[VerifyPos+j+2] = (whu_MatchValues[dst]-1000)/10.0;//�¶���Ϣ//
				//		 }

				//	 }
				// }
				// //360���Ƕȵ��¶����ֵ��ʾ//
				// this->MyChart->Series["ÿ�������"]->Points->Clear();
				// for (int angle=0;angle<360;angle++)
				// {
				//	 int VerifyPos = angle*(1+1+LineCount);
				//	 if (whu_OutputPolarTemp[VerifyPos]==0xffff)
				//	 {
				//		 //int angle = whu_OutputPolarTemp[VerifyPos+1];//�Ƕ�,
				//		 double maxtemp = 0;
				//		 for (int j=0;j<LineCount;j++)
				//		 {
				//			 if (whu_OutputPolarTemp[VerifyPos+j+2]>maxtemp)
				//			 {
				//				 maxtemp = whu_OutputPolarTemp[VerifyPos+j+2];//ȡ�������
				//			 }
				//		 }
				//		 this->MyChart->Series["ÿ�������"]->Points->AddXY(angle,maxtemp);
				//		 //MaxTempLabel->Text = String::Format("{0:##0.0}��C",maxtemp);

				//	 }
				//	 
				// }
			 //}
			 


		 }
private: System::Void FrmChild_PassDataBetweenForm(bool show)
		 {
			
		 }
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
			 //���ɱ���//
			 String ^filename = L"C:\\sb.bmp";
			 for (int i=0;i<IMAGERCOUNT;i++)
			 {
			 	if (formsImager[i]->Connected)
			 	{
			 		formsImager[i]->SaveImage();
			 	}
			 }
			 LPCWSTR folder = L"D:\\ImagerData";
			 LPCWSTR mode = L"open";
			 //ShellExecute(NULL, mode, folder, NULL, NULL, SW_SHOWNORMAL);
		  }
private: System::Void SetButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 
			 static bool show = true;
			 if (show == false)
			 {
				 ClientSize = Drawing::Size(SetFormPos, SetgroupBox->Top);
				 show = true;
			 }else{
				 ClientSize = Drawing::Size(SetFormPos, SetgroupBox->Bottom+10);
				 show = false;
			 }


		 }
private: System::Void groupBox2_Enter(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void label9_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void SetgroupBox_Enter(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void MyTimer10_Tick(System::Object^  sender, System::EventArgs^  e) {
			 if (Connected == false)
			 {
				 bool m_Connect[IMAGERCOUNT];
				 for (int i = 0;i < IMAGERCOUNT;i++)
				 {
					 m_Connect[i] = false;
				 }
				 for (int num=0;num<IMAGERCOUNT;num++)
				 {
					 if (formsImager[num]->Connected)
					 {
						 m_Connect[num] = true;
					 }
				 }
				 for (int i = 0;i < IMAGERCOUNT;i++)
				 {
					 if (m_Connect[i] == true)
					 {
 						 Connected = true;
					 }else{
						 Connected = false;
					 }
				 }
			 }else{

			 }
			
		 }
private: System::Void ContactButton_Click(System::Object^  sender, System::EventArgs^  e) {
			
		 }
private: System::Void MatchPictureBox_Pain(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) 
		 {  
			 /*������ƴ�Ӻϳ�ͼ����,��ģ�鲻��Ҫ*/
			 //if (Connected)
			 //{
				// m_MatchBmpImage = whu_ResizeImage(m_MatchBmpImage,MatchPictureBox->Width,MatchPictureBox->Height);
				// e->Graphics->DrawImage( m_MatchBmpImage, 0, 0 );
				// //
				// if (whu_BMatchShowMouseTemp&&whu_MatchMouseTempValue!=-100)
				// {
				//	 String ^StrTempValue = String::Format("{0:##0.0}��C",whu_MatchMouseTempValue);
				//	 e->Graphics->DrawString(StrTempValue,myBigFront,myBrush,m_MousePositionX+8,m_MousePositionY+8);
				// }
				// //�¶���ߵ�,����ͼ�������ˣ������Ҫת��������//
				// m_MaxMatchTempValuePoint.X =  m_MaxMatchTempValuePoint.X*MatchPictureBox->Width/(double)MatchWidth;
				// m_MaxMatchTempValuePoint.Y =  m_MaxMatchTempValuePoint.Y*MatchPictureBox->Height/(double)MatchHeight;
				// System::Drawing::Rectangle ^m_Rect = gcnew System::Drawing::Rectangle(m_MaxMatchTempValuePoint.X-8,m_MaxMatchTempValuePoint.Y-8,16,16);
				// Point StartPoint1,StartPoint2,EndPoint1,EndPoint2;
				// StartPoint1.X = m_MaxMatchTempValuePoint.X-30;
				// StartPoint1.Y = m_MaxMatchTempValuePoint.Y;
				// EndPoint1.X = m_MaxMatchTempValuePoint.X+30;
				// EndPoint1.Y = m_MaxMatchTempValuePoint.Y;
				// StartPoint2.X = m_MaxMatchTempValuePoint.X;
				// StartPoint2.Y = m_MaxMatchTempValuePoint.Y-30;
				// EndPoint2.X = m_MaxMatchTempValuePoint.X;
				// EndPoint2.Y = m_MaxMatchTempValuePoint.Y+30;			 
				// e->Graphics->DrawEllipse(myRedPen,*m_Rect);
				// e->Graphics->DrawLine(myRedPen,StartPoint1,EndPoint1);
				// e->Graphics->DrawLine(myRedPen,StartPoint2,EndPoint2);

				// String ^StrMaxTempValue = String::Format("ú������£�{0:##0.0}��C",m_MaxMatchTempValue);
				// int PosX = MatchPictureBox->Width/30;
				// int PosY = MatchPictureBox->Height/20;
				// e->Graphics->DrawString(StrMaxTempValue,myBigFront,myBrush,PosX,PosY);


				// //�����¶�//
				// e->Graphics->DrawRectangle(myWhitePen,*whu_MatchSelectRectangle);
				// if (whu_BMatchKeepRectangle&&(whu_MatchSelectRectangle->Left != whu_MatchSelectRectangle->Right)&&(whu_MatchSelectRectangle->Top!=whu_MatchSelectRectangle->Bottom))
				// {
				//	 double m_TempValue = 0;
				//	 double m_All = 0;
				//	 int m_Count = 0;
				//	 Point RectHighTempPoint;
				//	 double RectHighTemp = 0;
				//	 double MyWidthIndex = MatchWidth/(double)MatchPictureBox->Width;
				//	 double MyHeightIndex = MatchHeight/(double)MatchPictureBox->Height;
				//	 int iStart = whu_MatchSelectRectangle->Top*MyHeightIndex;
				//	 int iEnd = (whu_MatchSelectRectangle->Height+whu_MatchSelectRectangle->Top)*MyHeightIndex;
				//	 int jStart = whu_MatchSelectRectangle->Left*MyWidthIndex;
				//	 int jEnd = (whu_MatchSelectRectangle->Width+whu_MatchSelectRectangle->Left)*MyWidthIndex;
				//	 for (int i=iStart;i<iEnd;i++ )
				//	 {
				//		 for (int j=jStart;j<jEnd;j++)
				//		 {
				//			 int pos = i*MatchWidth + j;
				//			 if (pos<MatchWidth*MatchHeight)
				//			 {
				//				 if(whu_AllMatchTempValues[pos]!=-100)
				//				 {
				//					 m_All = m_All + whu_AllMatchTempValues[pos];
				//					 m_Count ++;
				//					 if (whu_AllMatchTempValues[pos]>RectHighTemp)
				//					 {
				//						 RectHighTemp = whu_AllMatchTempValues[pos];
				//						 RectHighTempPoint.X = j/MyWidthIndex;
				//						 RectHighTempPoint.Y = i/MyHeightIndex;
				//					 }
				//				 }

				//			 }

				//		 } 
				//	 }
				//	 //��ʾ�����¶�//
				//	 if (m_Count>=1)
				//	 {
				//		 m_TempValue = m_All/m_Count;
				//		 whu_AllSelectMatchTempValues[0] = m_TempValue;
				//		 String ^RectTemp = String::Format("�����¶ȣ�{0:##0.0}��C", m_TempValue);
				//		 e->Graphics->DrawString(RectTemp,mySmallFront,myBrush,whu_MatchSelectRectangle->X,whu_MatchSelectRectangle->Y-30);
				//		 //������ǰ��������¶ȵ�//
				//		 System::Drawing::Rectangle ^m_MaxTempValuePointRect = gcnew System::Drawing::Rectangle(RectHighTempPoint.X-5,RectHighTempPoint.Y-5,10,10);
				//		 Point StartPoint1,StartPoint2,EndPoint1,EndPoint2; 
				//		 StartPoint1.X = RectHighTempPoint.X-20;
				//		 StartPoint1.Y = RectHighTempPoint.Y;
				//		 EndPoint1.X = RectHighTempPoint.X+20;
				//		 EndPoint1.Y = RectHighTempPoint.Y;
				//		 StartPoint2.X = RectHighTempPoint.X;
				//		 StartPoint2.Y = RectHighTempPoint.Y-20;
				//		 EndPoint2.X = RectHighTempPoint.X;
				//		 EndPoint2.Y = RectHighTempPoint.Y+20;			 
				//		 e->Graphics->DrawEllipse(myRedPen,*m_MaxTempValuePointRect);
				//		 e->Graphics->DrawLine(myRedPen,StartPoint1,EndPoint1);
				//		 e->Graphics->DrawLine(myRedPen,StartPoint2,EndPoint2);

				//		 String ^StrRectHighTemp = String::Format("��������¶ȣ�{0:##0.0}��C", RectHighTemp);
				//		 e->Graphics->DrawString(StrRectHighTemp,mySmallFront,myBrush,RectHighTempPoint.X,RectHighTempPoint.Y);
				//	 
				//	 }
				//	 
				// }
				// //���ƽǶȵ�ָʾ��ͷ//
				// double angleData = (m_CurrentAngle-m_RangeAngle/2)*Math::PI/180.0;
				// double RangeAngleData = m_RangeAngle*Math::PI/180.0;
				// double MyWidthIndex = MatchWidth/(double)MatchPictureBox->Width;
				// double MyHeightIndex = MatchHeight/(double)MatchPictureBox->Height;

				// Point m_StartPoint,m_EndPoint1,m_EndPoint2; 
				// m_StartPoint.X = MatchPictureBox->Width/2;
				// m_StartPoint.Y = MatchPictureBox->Height/2;
				// m_EndPoint1.X = (int)(((MatchWidth/2)*System::Math::Cos(angleData)+MatchWidth/2)/MyWidthIndex);//������ԭ���ھ��ε�����//
				// m_EndPoint1.Y = (int)((-(MatchHeight/2)*System::Math::Sin(angleData)+MatchHeight/2)/MyHeightIndex);
				// m_EndPoint2.X = (int)(((MatchWidth/2)*System::Math::Cos(angleData+RangeAngleData)+MatchWidth/2)/MyWidthIndex);//������ԭ���ھ��ε�����//
				// m_EndPoint2.Y = (int)((-(MatchHeight/2)*System::Math::Sin(angleData+RangeAngleData)+MatchHeight/2)/MyHeightIndex);	 
				// //e->Graphics->DrawEllipse(myWhitePen,m_CenterRect);
				// e->Graphics->DrawLine(myWhitePen,m_StartPoint,m_EndPoint1);
				// e->Graphics->DrawLine(myWhitePen,m_StartPoint,m_EndPoint2);

				// //��ʾ����2
				// //���ƽǶȵ�ָʾ��ͷ//
				// //double angleData = (m_CurrentAngle)*Math::PI/180.0;
				// //double RangeAngleData = m_RangeAngle*Math::PI/180.0;
				// //double MyWidthIndex = MatchWidth/(double)MatchPictureBox->Width;
				// //double MyHeightIndex = MatchHeight/(double)MatchPictureBox->Height;

				// //Point m_StartPoint,m_EndPoint1; 
				// //m_StartPoint.X = MatchPictureBox->Width/2;
				// //m_StartPoint.Y = MatchPictureBox->Height/2;
				// //m_EndPoint1.X = (int)(((MatchWidth/2)*System::Math::Cos(angleData)+MatchWidth/2)/MyWidthIndex);//������ԭ���ھ��ε�����//
				// //m_EndPoint1.Y = (int)((-(MatchHeight/2)*System::Math::Sin(angleData)+MatchHeight/2)/MyHeightIndex);
				// //e->Graphics->DrawLine(myWhitePen,m_StartPoint,m_EndPoint1);
	

			 //}

			 


		 }
private: System::Void MatchPictureBox_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs ^  e) 
		 {
			 /*������ƴ�Ӻϳ�ͼ����,��ģ�鲻��Ҫ*/
			// int Height = this->MatchPictureBox->Height;
			// int Width = this->MatchPictureBox->Width;
			// /*int m_MousePositionX,m_MousePositionY;*/
			// m_MousePositionX = e->X;
			// m_MousePositionY = e->Y;
			// m_MatchMousePositionX = m_MousePositionX*MatchWidth/MatchPictureBox->Width;
			// m_MatchMousePositionY = m_MousePositionY*MatchHeight/MatchPictureBox->Height;
			// if ((m_MousePositionX < Width)&&(m_MousePositionY<Height ))
			// {

			//	 int pos = m_MatchMousePositionY*MatchWidth+m_MatchMousePositionX;
			//	 if (pos<MatchWidth*MatchHeight)
			//	 {
			//		 whu_MatchMouseTempValue = whu_AllMatchTempValues[pos];
			//		 whu_BMatchShowMouseTemp = true; 		 
			//	 }
			//	 if (whu_BMatchSHowRectangle&&!whu_BMatchKeepRectangle)//������ѡ������// 
			//	 {
			//		 whu_MatchSelectRectangle = gcnew System::Drawing::Rectangle(whu_MatchSelectRectangle->Left,whu_MatchSelectRectangle->Top,e->X-whu_MatchSelectRectangle->X,e->Y-whu_MatchSelectRectangle->Y);
			//	 }

			//	 if (whu_BMatchSHowRectangle&&!whu_BMatchKeepRectangle)//������ѡ������// 
			//	 {
			//		 whu_MatchSelectRectangle = gcnew System::Drawing::Rectangle(whu_MatchSelectRectangle->Left,whu_MatchSelectRectangle->Top,e->X-whu_MatchSelectRectangle->X,e->Y-whu_MatchSelectRectangle->Y);
			//	 }


			//}


		 }
private: System::Void MatchPictureBox_MouseLeave(System::Object^  sender, System::EventArgs ^  e) 
		 {
			 /*������ƴ�Ӻϳ�ͼ����,��ģ�鲻��Ҫ*/
			 //whu_BMatchShowMouseTemp = false;
			 
		 }
private: System::Void MatchPictureBox_MouseDown(System::Object^ sender,System::Windows::Forms::MouseEventArgs ^  e){
			 /*������ƴ�Ӻϳ�ͼ����,��ģ�鲻��Ҫ*/
			 /*whu_MatchSelectRectangle = gcnew System::Drawing::Rectangle(e->X,e->Y,0,0);
			 whu_BMatchSHowRectangle = true;
			 whu_BMatchKeepRectangle = false;*/
			 
		 }
private: System::Void MatchPictureBox_MouseUp(System::Object^ sender,System::Windows::Forms::MouseEventArgs ^  e)
		 {
			 /*������ƴ�Ӻϳ�ͼ����,��ģ�鲻��Ҫ*/
			 /* whu_MatchSelectRectangle = gcnew System::Drawing::Rectangle(whu_MatchSelectRectangle->Left,whu_MatchSelectRectangle->Top,e->X-whu_MatchSelectRectangle->Left,e->Y-whu_MatchSelectRectangle->Top);
			 if ((whu_MatchSelectRectangle->Left != whu_MatchSelectRectangle->Right)&&(whu_MatchSelectRectangle->Top!=whu_MatchSelectRectangle->Bottom))
			 {
			 whu_BMatchSHowRectangle = true;
			 whu_BMatchKeepRectangle = true;
			 }*/



		 }
private: System::Void MatchPictureBox_MouseClick(System::Object ^sender,System::Windows::Forms::MouseEventArgs ^  e)
		 {
			 //whu_BSHowRectangle = false;
		 }

private: System::Void button1_Click_1(System::Object^  sender, System::EventArgs^  e) {
			 //�˺���Ϊ�������ݿ�//
			 Lin_DataSource = DataSourcetextBox->Text;
			 Lin_DataName = InitialCatalogtextBox->Text;
			 String^ strConn = "Data Source = " + Lin_DataSource
				 + ";Initial Catalog = " + Lin_DataName
				 + ";Integrated Security=True";
			 ConnSql = gcnew SqlConnection(strConn); //Sql�������ʵ����

			 try
			 {
				 ConnSql->Open();//�����ݿ�
				 if (ConnSql->State == ConnectionState::Open)
				 {
					 Lin_BConnectToDB = true;
					 button1->Enabled = false;
					 button3->Enabled = true;
					 label8->Text = "���ݿ������ӣ�";
				 }
			 }
			 catch (Exception ^sb)
			 {
				 MessageBox::Show("�޷��������ݿ⣡");
				 label8->Text = "���ݿ�δ���ӣ�";
				 Lin_BConnectToDB = false;
			 }		 


		 }
private: System::Void MyTimer5Mins_Tick(System::Object^  sender, System::EventArgs^  e) {
			 if (Connected)
			 {  
				 if (Lin_BConnectToDB == true)
				 {
					whu_SaveDataToDB();
					//�Ѿ����������ˣ�����Lin_AngleWithValues,У��λ���,�´δ洢ֱ������//
					whu_ClearAngleWithValues();
				 }

			 }

		 }

private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
			 /* if (Lin_MoveTimeInterval<20)
			 {
			 Lin_MoveTimeInterval = Lin_MoveTimeInterval + 0.1;
			 }else{
			 Lin_MoveTimeInterval = 20;
			 button3->Enabled = false;
			 }*/
			 Lin_MoveTimeInterval = 1;
		 }
private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
			 /* if (Lin_MoveTimeInterval>0.1)
			 {
			 Lin_MoveTimeInterval = Lin_MoveTimeInterval - 0.1;
			 }else{
			 Lin_MoveTimeInterval = 0.1;
			 button4->Enabled = false;
			 }*/
			 Lin_MoveTimeInterval = 1;
		 }
private: System::Void MyTimer3000_Tick(System::Object^  sender, System::EventArgs^  e) {

			   

		 }
private: System::Void ButtonSaveToDB_Click(System::Object^  sender, System::EventArgs^  e) {
			 if (Lin_BConnectToDB)
			 {
				 whu_SaveDataToDB();
				 whu_ClearAngleWithValues();
			 }
		 }
private: System::Void button3_Click_1(System::Object^  sender, System::EventArgs^  e) {
			 //�˺���Ϊ�Ͽ����ݿ�����//
			 if (Lin_BConnectToDB)
			 {
				 Lin_BConnectToDB = false;
				 ConnSql->Close();
				 button1->Enabled = true;
				 button3->Enabled = false;
				 label8->Text = "���ݿ�δ���ӣ�";
				 
			 }

		 }
private: System::Void MyTimerDeleteDB_Tick(System::Object^  sender, System::EventArgs^  e) {
			 //if (Lin_BConnectToDB)
			 //{
				// DateTime ^now = DateTime::Now;
				// DateTime m_HistoryTime;
				// String ^strSQL = "SELECT time FROM  dbo.SourceData2 order by time ";//�õ���ɵ�ʱ��
				// array<byte>^ m_byte = gcnew array<byte>(sizeof(DateTime));
				// SqlCommand ^cmd = gcnew SqlCommand();
				// cmd->Connection = ConnSql;
				// cmd->CommandText = strSQL;
				// SqlDataReader ^sdr = cmd->ExecuteReader();
				// while(sdr->Read())
				// {
				//	 //m_HistoryTime = sdr["time"];
				//	 int test =1;
				//	 test++;
				//	 //sdr->GetBytes(0,0,m_byte,0,m_byte->Length);
				//	 //System::Buffer::BlockCopy(m_byte,0,DestData,0,m_byte->Length);
				//	// m_BRead = true;
				// }
				// sdr->Close();
			 //}

		 }
private: System::Void MyTimerLinkToLocalDB_Tick(System::Object^  sender, System::EventArgs^  e) {
			 if (!Lin_BConnectToDB&&button3->Enabled == true)
			 {
				 //�˺���Ϊ�������ݿ�//
				 String^ strConn = "Data Source = MICROSOF-8B4B5C;Initial Catalog=LinDataBase;Integrated Security=True";//SQL Server�����ַ���
				 ConnSql = gcnew SqlConnection(strConn); //Sql�������ʵ����
				 try
				 {
					 ConnSql->Open();//�����ݿ�
					 if (ConnSql->State == ConnectionState::Open)
					 {
						 Lin_BConnectToDB = true;
						 button1->Enabled = false;
						 button3->Enabled = true;
						 label8->Text = "���ݿ������ӣ�";
						 
					 }
				 }catch (Exception ^sb)
				 {
					 label8->Text = "���ݿ�δ���ӣ�";
					 Lin_BConnectToDB = false;
				 }		 
			 }
	

		 }
private: System::Void button4_Click_1(System::Object^  sender, System::EventArgs^  e) {
			 if (Lin_BConnectToDB)
			 {
				 //DateTime ^now = DateTime::Now;
				 //DateTime ^m_DeleteTime = DateTime::Now;
				 //String ^m_strtest;
				 //m_strtest = String::Format("{0:##0}-{1:##0}-{2:##0}",now->Year,now->Month,now->Day);
				 //m_DeleteTime->AddDays(-7);
				 //String ^ m_str = m_DeleteTime->ToString("yyyy-MM-dd");
				 //String ^strSQL = "delete dbo.SourceData2 where time < "+ m_strtest;//ɾ��7��ǰ�����ݡ�//�����7���Ƿ��ǿɵ��ڵġ�---->>>>����ɾ��������⡣��ɾ��ȫ��//
				 //array<byte>^ m_byte = gcnew array<byte>(sizeof(DateTime));
				 //SqlCommand ^cmd = gcnew SqlCommand();
				 //cmd->Connection = ConnSql;
				 //cmd->CommandText = strSQL;
				 //cmd->ExecuteNonQuery();


				 //SqlDataReader ^sdr = cmd->ExecuteReader();
				 //while(sdr->Read())
				 //{
					// m_HistoryTime = (DateTime^)sdr["time"];
					// int day1 = now->Day;
					// int day2 = m_HistoryTime->Day;
					// if ((now->Day - m_HistoryTime->Day)>3)
					// {
					//	 MessageBox::Show("����3����");
					// }
					// String ^ m_str = m_HistoryTime->ToString();
					// //m_HistoryTime = sdr["time"]->GetValue(0);
					//// sdr->GetBytes(0,0,m_byte,0,m_byte->Length);
					// //System::Buffer::BlockCopy(m_byte,0,DestData,0,m_byte->Length);
					// // m_BRead = true;
				 //}
				
				 //sdr->Close();
			 }
		 }
private: System::Void label8_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void groupBox1_Enter(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void label10_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void MyTimerShowRecvStr_Tick(System::Object^  sender, System::EventArgs^  e) {
			 label12->Text = Lin_RecvStr;
			 if (Lin_RecvStr == "��ʼ")
			 {
				 Lin_BNetConnect = true;
			 }else if(Lin_RecvStr == "ֹͣ")
			 {
				 Lin_BNetConnect = false;
			 }
			 else
			 {
				 //˵�����յ����ǽǶ���Ϣ//
				 if (Lin_BNetConnect == true)
				 {
					 int m_angle  = System::Int32::Parse(Lin_RecvStr);
					 if (m_angle<360*AngleAccuracy&&m_angle>=0)
					 {
						 Lin_OldAngle = Lin_CurrentAngle;
						 Lin_CurrentAngle = m_angle;
						 AngleLabel->Text = String::Format("��ת�Ƕȣ�{0:##0.0}��",(double)Lin_CurrentAngle/AngleAccuracy);
					 }
				 }
			 }
		 }
};


}