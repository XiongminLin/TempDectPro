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
////网络传输//
//using namespace System::Net::Sockets;
//using namespace System::Text;
////多线程
//using namespace System::Threading;
#define IMAGERCOUNT 2

//数据库
//using System::Collections::Generic;
//using System::Linq;
using namespace System::Data::SqlClient;


namespace IPCSample {

	/// <summary>
	/// Zusammenfassung f黵 FormMulti
	///
	/// Warnung: Wenn Sie den Namen dieser Klasse 鋘dern, m黶sen Sie auch
	///          die Ressourcendateiname-Eigenschaft f黵 das Tool zur Kompilierung verwalteter Ressourcen 鋘dern,
	///          das allen RESX-Dateien zugewiesen ist, von denen diese Klasse abh鋘gt.
	///          Anderenfalls k鰊nen die Designer nicht korrekt mit den lokalisierten Ressourcen
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
                /*FormImager 是IPC自带类，一个formsImager 对应一个热像仪*/
		array<FormImager^> ^formsImager;
                IPC^ ipc;
                /*设置对话框，可能作为显示温度的对话框来用*/
		SetForm ^m_SetForm;

		
		double m_MaxTempValue; //当前画面最高温
		double m_MaxMatchTempValue;//整个煤场的最高温，由于采集端不需要显示整个煤堆的数据，因此这里用不到.
		double m_AverageTempValue;
		int m_AlarmTemp;  //警戒温度
		Bitmap^ m_BmpImage;//显示画面
		Bitmap^ m_MatchBmpImage;//整个煤场的画面，由于采集端不需要显示整个煤堆的数据，因此这里用不到.
		int Lin_CurrentAngle;//转动的角度
		int Lin_OldAngle;
		int Lin_RangeAngle;//一幅图像能显示的最宽视角//
		bool Connected;  //是否连接上热像仪
		bool Lin_BMoving; //这个没用到，可以去掉
		double Lin_MoveTimeInterval;  //跟角度有关，这个没用到，可以去掉
		double Lin_AngleInterval;     //跟角度有关，这个没用到，可以去掉
                /*从服务器端接收角度，如果使用旋转编码器获取角度，那么下面的代码可以去掉*/  
		Socket ^connectionSocket; 
		bool Lin_BNetConnect;
		ThreadStart ^Lin_ThreadStart;
		Thread ^Lin_RecvThread;
		String ^Lin_RecvStr;
                /*从服务器端接收角度，如果使用旋转编码器获取角度，那么上面的代码可以去掉*/  
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
		
		int SetFormPos;//隐藏和显示设置//
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

                //pos表示第几个点，总共有FrameSize = FrameWidth*FrameHeight个点，函数返回点的坐标，比如，第382个点，返回（0，1）即第一列第二行
		Point whu_GetValuePositon(short pos,int width,int height);
		/*当前画面的温度处理*/
		int m_MousePositionX,m_MousePositionY;// 鼠标点位置

		void whu_GetRGBValue(short m_value ,Byte *m_RGBValue);//将数据转化成RGB像素值，在GetBitmap中调用了此函数//
		void GetBitmap(Bitmap^ Bmp, array<short>^values);//将数据转化成图片//
		void GetValuesData(array<short>^values0,array<short>^values1,array<short>^values2);//合成两个热像仪的数据//
		array<short>^Values;//两个热像仪得到的所有温度信息//
		array<Byte>^rgbValues;//
		array<double>^ whu_AllTemValues;//当前画面：双热像仪的温度
		array<double>^ whu_AllSelectRectValues;//当前画面：选中区域的温度//
		Point m_MaxTempValuePoint;      //温度最高点
		Point m_MaxMatchTempValuePoint;  //没用到
		int FrameWidth ;      //单个Imager画面长度
		int FrameHeight;      //单个Imager画面高度
		int FrameSize;        //FrameSize = FrameWidth*FrameHeight; 代表有几个像素点。

/////////////////////////由于采集端无人操作，因此，下面的这些可以去掉///////////////////////////////////////////////////////////////
		bool whu_BSHowRectangle; //鼠标在画面上划一个矩形框，显示其温度的消息，whu_BSHowRectangle代表是否需要显示这个矩形框.
		bool whu_BKeepRectangle; //是否需要保持住鼠标画的矩形框。
		bool whu_BShowMouseTemp; //是否需要显示鼠标点的温度
		double whu_MouseTempValue; //鼠标点的温度
		System::Drawing::Rectangle ^whu_SelectRectangle; //矩形框

	        
////////////////////////////由于采集端不需要显示整个煤堆的数据,因此带Match字眼的变量或是函数都用不到///////////////////////////////////

		/* 整个煤堆的温度处理*/
		//void whu_ShowHighTempToChart();
		void whu_AddMatchValue(double CurrentAngle,array<double>^ InputValue);//

                //得到拼接图片，由于采集端不需要显示整个煤堆的数据，所以，这个函数没用到,基本上带Match字眼的变量或是函数都用不到//	
		void whu_GetMatchingImg(array<double>^InputValues,array<double>^InputAngle,Bitmap ^MatchBmp);
		Bitmap^ whu_ResizeImage(Bitmap^ Bmp,int NewWidth,int NewHeight);//缩放图片
		double whu_GetCurrentAngle();
		array<double>^ whu_MatchValues;
		//array<IPCMatchData^>^ whu_IPCMatchData;
		
		array<Byte>^ rgbMatchValues;	
		array<double>^ whu_AllMatchTempValues;//扫描完成以后，煤场的温度MatchWidth*MatchHeight//
		array<double>^ whu_OutputPolarTemp;
		array<double>^ whu_AllSelectMatchTempValues;//选定框的温度信息//
		array<double>^ whu_AllAngles;//转动的角度//
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
		int LineCount ;//扫描像素长度//
		int m_MatchSelectRectShowTime;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	
		//数据库读取操作//
                int AngleAccuracy;//扫描的精度
		SqlConnection ^ConnSql;
		bool whu_SaveDataToDB();
		double whu_ReadDataFromDB(array<short>^ DestData);
		String ^Lin_DataSource;
		String ^Lin_DataName;
		String ^Lin_ListName;
		bool Lin_BConnectToDB;
		bool Lin_BMoveDone;//最开始的储存方案比较麻烦，后来改成现在的用校验位的方法，所以Lin_BMoveDone没用到
		bool Lin_BDBSaveDone;//最开始的储存方案比较麻烦，后来改成现在的用校验位的方法，所以Lin_BDBSaveDone没用到
		unsigned short Lin_SameAngleCount;//最开始的储存方案比较麻烦，后来改成现在的用校验位的方法，所以Lin_SameAngleCount没用到
		array<short>^ Lin_AngleWithValues;
               
                //这是新的储存方案，数据刷新以后，调用whu_UpdateAngleWithValues函数，将Lin_AngleWithValues的校验位设置为0xffff，表示需要储存 
		void whu_UpdateAngleWithValues(int CurrentAngle,array<short>^InputValues);

                //这是新的储存方案，将数据写入数据库以后，调用whu_ClearAngleWithValues函数，将Lin_AngleWithValues的校验位设置为0，表示已经储存
		void whu_ClearAngleWithValues();  

		//socket，接收服务器端发送过来的角度，如果使用旋转编码器，这个函数就用不到//
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
		/// Erforderliche Methode f黵 die Designerunterst黷zung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor ge鋘dert werden.
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
			this->label1->Text = L"最小显示温度:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(19, 99);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(89, 12);
			this->label2->TabIndex = 4;
			this->label2->Text = L"显示温度区间：";
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
			this->groupBox1->Text = L"画面调节";
			this->groupBox1->Enter += gcnew System::EventHandler(this, &FormMulti::groupBox1_Enter);
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(259, 135);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(53, 12);
			this->label12->TabIndex = 17;
			this->label12->Text = L"接收到..";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(38, 133);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(77, 12);
			this->label11->TabIndex = 16;
			this->label11->Text = L"本地IP地址：";
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
			this->groupBox2->Text = L"数据库配置";
			// 
			// button3
			// 
			this->button3->Enabled = false;
			this->button3->Location = System::Drawing::Point(286, 58);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(72, 39);
			this->button3->TabIndex = 13;
			this->button3->Text = L"断开";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &FormMulti::button3_Click_1);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(286, 15);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(72, 39);
			this->button1->TabIndex = 12;
			this->button1->Text = L"连接";
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
			this->label4->Text = L"数据库：";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(27, 30);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(53, 12);
			this->label3->TabIndex = 10;
			this->label3->Text = L"服务器：";
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
			this->label6->Text = L"65°C";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(320, 107);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(35, 12);
			this->label5->TabIndex = 6;
			this->label5->Text = L"20°C";
			// 
			// pictureBox1
			// 
			this->pictureBox1->ImageLocation = L"D:\\煤堆测温\\温度颜色调节.jpg";
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
			this->AngleLabel->Text = L"旋转角度：0度";
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
			this->SetButton->Text = L"设置";
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
			this->label7->Text = L"IPC通信未开启！";
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
			this->label8->Text = L"数据库未连接！";
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
					label7->Text = "IPC通信已开启！";
					//button2->Enabled = true;
					//Lin_OldAngle = Lin_CurrentAngle;
					//Lin_CurrentAngle = whu_GetCurrentAngle();//在其他的地方得到Lin_CurrentAngle的值了。
					if (Lin_OldAngle!=Lin_CurrentAngle)
					{
						AngleLabel->Text = String::Format("旋转角度：{0:##0.0}度",(double)Lin_CurrentAngle/AngleAccuracy);
						array<short>^ m_value = gcnew array<short>(Lin_AngleWithValues->Length/(AngleAccuracy*360)-2);
						int ValueSrc = FrameSize;
						for (int j=0;j<m_value->Length;j++,ValueSrc++)
						{
							m_value[j] = Values[ValueSrc];
						}
						whu_UpdateAngleWithValues(Lin_CurrentAngle,m_value); 
					}
					
				}else{
					label7->Text = "IPC通信未开启！";
					//button2->Enabled = false;
				}
				 /*if (Lin_BConnectToDB == true)
				 { 
					 label8->Text = "数据库已连接！";
				 }else{
					 label8->Text = "数据库未连接！";
				 } */
				///*此模块不需要*/
				// //得到所有热像仪的当前最高温度和平均温度//
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
					 //显示合成图像区域框的温度//
					 //if (whu_BMatchKeepRectangle)//绘制了矩形框
					 //{
						 //AverTempLabel->Show();
						 //this->MyChart->Series["区域温度"]->Points->AddXY(m_MatchSelectRectShowTime,whu_AllSelectMatchTempValues[0]);
						 //AverTempLabel->Text = String::Format("{0:##0.0}°C", whu_AllSelectMatchTempValues[0]); 
						 //m_MatchSelectRectShowTime++;
						 //if (m_MatchSelectRectShowTime>=360)
						 //{
							 //this->MyChart->Series["区域温度"]->Points->Clear();
							 //m_MatchSelectRectShowTime = 0;
						 //}
					 //} 
					// else
					// {
						// this->MyChart->Series["区域温度"]->Points->Clear();
						// m_MatchSelectRectShowTime = 0;
						// AverTempLabel->Hide();
						// AverTempLabel->Text = String::Format("°C"); 
					 //}

				 //}
				 
				

			 }
private: System::Void trackBar1_Scroll(System::Object^  sender, System::EventArgs^  e) {
				 //统一调节图像//
				 for (int i=0;i<IMAGERCOUNT;i++)
				 {
					 formsImager[i]->TempMinTrackBarValue = trackBar1->Value;			 
				 }

				 TempMinTrackBarValue = trackBar1->Value - 20;
				 label5->Text = String::Format("{0:##0}°C", trackBar1->Value-20);
				 label6->Text = String::Format("{0:##0}°C", trackBar1->Value + trackBar2->Value-20);

			 }
private: System::Void trackBar2_Scroll(System::Object^  sender, System::EventArgs^  e) {
			// for (int i=0;i<IMAGERCOUNT;i++)
			// {
				// formsImager[i]->TempRangTrackBarValue = trackBar2->Value;			 
			 //}
			 TempRangTrackBarValue = trackBar2->Value;
			 label6->Text = String::Format("{0:##0}°C", trackBar1->Value + trackBar2->Value);
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
					 //显示区域温度//
					 if (m_Count>=1)
					 {
						 m_TempValue = m_All/m_Count;
						 whu_AllSelectRectValues[0] = m_TempValue;
						 String ^StrRectTemp = String::Format("平均温度：{0:##0.0}°C", m_TempValue);
						 
						 e->Graphics->DrawString(StrRectTemp,mySmallFront,myBrush,whu_SelectRectangle->X,whu_SelectRectangle->Y-30);
						 //画出当前区域最高温度点//
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

						 String ^StrRectHighTemp = String::Format("区域最高温度：{0:##0.0}°C", RectHighTemp);
						 e->Graphics->DrawString(StrRectHighTemp,mySmallFront,myBrush,RectHighTempPoint.X,RectHighTempPoint.Y);

					 }
					
				 }


				 //温度最高点
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
				 String ^StrMaxTempValue = String::Format("当前最高温：{0:##0.0}°C",m_MaxTempValue);
				 int PosX = pictureBox->Width/30;
				 int PosY = pictureBox->Height/20;
				 e->Graphics->DrawString(StrMaxTempValue,myBigFront,myBrush,PosX,PosY);
				 //StrMaxTempValue = String::Format("高温点：{0:##0.0}°C",m_MaxTempValue);
				 //e->Graphics->DrawString(StrMaxTempValue,mySmallFront,myBrush,m_MaxTempValuePoint);
				 //显示鼠标点温度//
				 if (whu_BShowMouseTemp)
				 {
					 String ^StrTempValue = String::Format("{0:##0.0}°C",whu_MouseTempValue);
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
				 if (whu_BSHowRectangle&&!whu_BKeepRectangle)//获得鼠标选定区域// 
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
			//获得各个热像仪的图像,这里主要处理当前画面//
			 if (Connected)
			 {

				 
				 //将两个热像仪图片简单合到一起//
				 GetValuesData(Values,formsImager[0]->Values,formsImager[1]->Values);
				 
				 ////保存到数据库//
				 //array<short>^ m_SaveToDBValue = gcnew array<short>(LineCount);
				 //for (int i = (Values->Length)/2,j=0;i<(Values->Length)/2+LineCount;i++,j++)
				 //{
					// m_SaveToDBValue[j] = Values[i];
				 //}
				/* m_CurrentAngle = whu_GetCurrentAngle();
				 AngleLabel->Text = String::Format("旋转角度：{0:##0}度",m_CurrentAngle);
				 whu_SaveDataToDB(m_CurrentAngle,Values);*/
				 //whu_ReadDataFromDB(Values);
				 GetBitmap(m_BmpImage,Values);
				 pictureBox->Invalidate();
				 //显示最高温度//
				 //MaxTempLabel->Text = String::Format("{0:##0.0}°C",m_MaxTempValue);
				 //刷新鼠标点温度//
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
			 /*极坐标拼接合成图像处理,此模块不需要*/
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

				// //显示鼠标点的温度
				// if (whu_BMatchShowMouseTemp)
				// {
				//	 int pos = m_MatchMousePositionY*MatchWidth+m_MatchMousePositionX;
				//	 if (pos<MatchWidth*MatchHeight)
				//	 {
				//		 whu_MatchMouseTempValue = whu_AllMatchTempValues[pos];	 
				//	 }
				// }

				// //极坐标温度信息的获取//
				// for (int i=0;i<360;i++)
				// {
				//	 int VerifyPos = i*(1+1+LineCount);
				//	 if (whu_OutputPolarTemp[VerifyPos]!=0xffff)
				//	 {
				//		 whu_OutputPolarTemp[VerifyPos]=0xffff;//校验位说明

				//	 }else{
				//		 whu_OutputPolarTemp[VerifyPos+1] = i;//角度
				//		 for (int j=0;j<LineCount;j++)
				//		 {
				//			 int dst = j+i*whu_MatchValues->Length/360+2;
				//			 whu_OutputPolarTemp[VerifyPos+j+2] = (whu_MatchValues[dst]-1000)/10.0;//温度信息//
				//		 }

				//	 }
				// }
				// //360个角度的温度最高值显示//
				// this->MyChart->Series["每列最高温"]->Points->Clear();
				// for (int angle=0;angle<360;angle++)
				// {
				//	 int VerifyPos = angle*(1+1+LineCount);
				//	 if (whu_OutputPolarTemp[VerifyPos]==0xffff)
				//	 {
				//		 //int angle = whu_OutputPolarTemp[VerifyPos+1];//角度,
				//		 double maxtemp = 0;
				//		 for (int j=0;j<LineCount;j++)
				//		 {
				//			 if (whu_OutputPolarTemp[VerifyPos+j+2]>maxtemp)
				//			 {
				//				 maxtemp = whu_OutputPolarTemp[VerifyPos+j+2];//取得最高温
				//			 }
				//		 }
				//		 this->MyChart->Series["每列最高温"]->Points->AddXY(angle,maxtemp);
				//		 //MaxTempLabel->Text = String::Format("{0:##0.0}°C",maxtemp);

				//	 }
				//	 
				// }
			 //}
			 


		 }
private: System::Void FrmChild_PassDataBetweenForm(bool show)
		 {
			
		 }
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
			 //生成报表//
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
			 /*极坐标拼接合成图像处理,此模块不需要*/
			 //if (Connected)
			 //{
				// m_MatchBmpImage = whu_ResizeImage(m_MatchBmpImage,MatchPictureBox->Width,MatchPictureBox->Height);
				// e->Graphics->DrawImage( m_MatchBmpImage, 0, 0 );
				// //
				// if (whu_BMatchShowMouseTemp&&whu_MatchMouseTempValue!=-100)
				// {
				//	 String ^StrTempValue = String::Format("{0:##0.0}°C",whu_MatchMouseTempValue);
				//	 e->Graphics->DrawString(StrTempValue,myBigFront,myBrush,m_MousePositionX+8,m_MousePositionY+8);
				// }
				// //温度最高点,由于图形缩放了，因此需要转化下坐标//
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

				// String ^StrMaxTempValue = String::Format("煤场最高温：{0:##0.0}°C",m_MaxMatchTempValue);
				// int PosX = MatchPictureBox->Width/30;
				// int PosY = MatchPictureBox->Height/20;
				// e->Graphics->DrawString(StrMaxTempValue,myBigFront,myBrush,PosX,PosY);


				// //区域温度//
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
				//	 //显示区域温度//
				//	 if (m_Count>=1)
				//	 {
				//		 m_TempValue = m_All/m_Count;
				//		 whu_AllSelectMatchTempValues[0] = m_TempValue;
				//		 String ^RectTemp = String::Format("区域温度：{0:##0.0}°C", m_TempValue);
				//		 e->Graphics->DrawString(RectTemp,mySmallFront,myBrush,whu_MatchSelectRectangle->X,whu_MatchSelectRectangle->Y-30);
				//		 //画出当前区域最高温度点//
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

				//		 String ^StrRectHighTemp = String::Format("区域最高温度：{0:##0.0}°C", RectHighTemp);
				//		 e->Graphics->DrawString(StrRectHighTemp,mySmallFront,myBrush,RectHighTempPoint.X,RectHighTempPoint.Y);
				//	 
				//	 }
				//	 
				// }
				// //绘制角度的指示箭头//
				// double angleData = (m_CurrentAngle-m_RangeAngle/2)*Math::PI/180.0;
				// double RangeAngleData = m_RangeAngle*Math::PI/180.0;
				// double MyWidthIndex = MatchWidth/(double)MatchPictureBox->Width;
				// double MyHeightIndex = MatchHeight/(double)MatchPictureBox->Height;

				// Point m_StartPoint,m_EndPoint1,m_EndPoint2; 
				// m_StartPoint.X = MatchPictureBox->Width/2;
				// m_StartPoint.Y = MatchPictureBox->Height/2;
				// m_EndPoint1.X = (int)(((MatchWidth/2)*System::Math::Cos(angleData)+MatchWidth/2)/MyWidthIndex);//极坐标原点在矩形的中心//
				// m_EndPoint1.Y = (int)((-(MatchHeight/2)*System::Math::Sin(angleData)+MatchHeight/2)/MyHeightIndex);
				// m_EndPoint2.X = (int)(((MatchWidth/2)*System::Math::Cos(angleData+RangeAngleData)+MatchWidth/2)/MyWidthIndex);//极坐标原点在矩形的中心//
				// m_EndPoint2.Y = (int)((-(MatchHeight/2)*System::Math::Sin(angleData+RangeAngleData)+MatchHeight/2)/MyHeightIndex);	 
				// //e->Graphics->DrawEllipse(myWhitePen,m_CenterRect);
				// e->Graphics->DrawLine(myWhitePen,m_StartPoint,m_EndPoint1);
				// e->Graphics->DrawLine(myWhitePen,m_StartPoint,m_EndPoint2);

				// //显示方法2
				// //绘制角度的指示箭头//
				// //double angleData = (m_CurrentAngle)*Math::PI/180.0;
				// //double RangeAngleData = m_RangeAngle*Math::PI/180.0;
				// //double MyWidthIndex = MatchWidth/(double)MatchPictureBox->Width;
				// //double MyHeightIndex = MatchHeight/(double)MatchPictureBox->Height;

				// //Point m_StartPoint,m_EndPoint1; 
				// //m_StartPoint.X = MatchPictureBox->Width/2;
				// //m_StartPoint.Y = MatchPictureBox->Height/2;
				// //m_EndPoint1.X = (int)(((MatchWidth/2)*System::Math::Cos(angleData)+MatchWidth/2)/MyWidthIndex);//极坐标原点在矩形的中心//
				// //m_EndPoint1.Y = (int)((-(MatchHeight/2)*System::Math::Sin(angleData)+MatchHeight/2)/MyHeightIndex);
				// //e->Graphics->DrawLine(myWhitePen,m_StartPoint,m_EndPoint1);
	

			 //}

			 


		 }
private: System::Void MatchPictureBox_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs ^  e) 
		 {
			 /*极坐标拼接合成图像处理,此模块不需要*/
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
			//	 if (whu_BMatchSHowRectangle&&!whu_BMatchKeepRectangle)//获得鼠标选定区域// 
			//	 {
			//		 whu_MatchSelectRectangle = gcnew System::Drawing::Rectangle(whu_MatchSelectRectangle->Left,whu_MatchSelectRectangle->Top,e->X-whu_MatchSelectRectangle->X,e->Y-whu_MatchSelectRectangle->Y);
			//	 }

			//	 if (whu_BMatchSHowRectangle&&!whu_BMatchKeepRectangle)//获得鼠标选定区域// 
			//	 {
			//		 whu_MatchSelectRectangle = gcnew System::Drawing::Rectangle(whu_MatchSelectRectangle->Left,whu_MatchSelectRectangle->Top,e->X-whu_MatchSelectRectangle->X,e->Y-whu_MatchSelectRectangle->Y);
			//	 }


			//}


		 }
private: System::Void MatchPictureBox_MouseLeave(System::Object^  sender, System::EventArgs ^  e) 
		 {
			 /*极坐标拼接合成图像处理,此模块不需要*/
			 //whu_BMatchShowMouseTemp = false;
			 
		 }
private: System::Void MatchPictureBox_MouseDown(System::Object^ sender,System::Windows::Forms::MouseEventArgs ^  e){
			 /*极坐标拼接合成图像处理,此模块不需要*/
			 /*whu_MatchSelectRectangle = gcnew System::Drawing::Rectangle(e->X,e->Y,0,0);
			 whu_BMatchSHowRectangle = true;
			 whu_BMatchKeepRectangle = false;*/
			 
		 }
private: System::Void MatchPictureBox_MouseUp(System::Object^ sender,System::Windows::Forms::MouseEventArgs ^  e)
		 {
			 /*极坐标拼接合成图像处理,此模块不需要*/
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
			 //此函数为连接数据库//
			 Lin_DataSource = DataSourcetextBox->Text;
			 Lin_DataName = InitialCatalogtextBox->Text;
			 String^ strConn = "Data Source = " + Lin_DataSource
				 + ";Initial Catalog = " + Lin_DataName
				 + ";Integrated Security=True";
			 ConnSql = gcnew SqlConnection(strConn); //Sql链接类的实例化

			 try
			 {
				 ConnSql->Open();//打开数据库
				 if (ConnSql->State == ConnectionState::Open)
				 {
					 Lin_BConnectToDB = true;
					 button1->Enabled = false;
					 button3->Enabled = true;
					 label8->Text = "数据库已连接！";
				 }
			 }
			 catch (Exception ^sb)
			 {
				 MessageBox::Show("无法连接数据库！");
				 label8->Text = "数据库未连接！";
				 Lin_BConnectToDB = false;
			 }		 


		 }
private: System::Void MyTimer5Mins_Tick(System::Object^  sender, System::EventArgs^  e) {
			 if (Connected)
			 {  
				 if (Lin_BConnectToDB == true)
				 {
					whu_SaveDataToDB();
					//已经保存数据了，清理Lin_AngleWithValues,校验位清空,下次存储直接跳出//
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
			 //此函数为断开数据库连接//
			 if (Lin_BConnectToDB)
			 {
				 Lin_BConnectToDB = false;
				 ConnSql->Close();
				 button1->Enabled = true;
				 button3->Enabled = false;
				 label8->Text = "数据库未连接！";
				 
			 }

		 }
private: System::Void MyTimerDeleteDB_Tick(System::Object^  sender, System::EventArgs^  e) {
			 //if (Lin_BConnectToDB)
			 //{
				// DateTime ^now = DateTime::Now;
				// DateTime m_HistoryTime;
				// String ^strSQL = "SELECT time FROM  dbo.SourceData2 order by time ";//得到最旧的时间
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
				 //此函数为连接数据库//
				 String^ strConn = "Data Source = MICROSOF-8B4B5C;Initial Catalog=LinDataBase;Integrated Security=True";//SQL Server链接字符串
				 ConnSql = gcnew SqlConnection(strConn); //Sql链接类的实例化
				 try
				 {
					 ConnSql->Open();//打开数据库
					 if (ConnSql->State == ConnectionState::Open)
					 {
						 Lin_BConnectToDB = true;
						 button1->Enabled = false;
						 button3->Enabled = true;
						 label8->Text = "数据库已连接！";
						 
					 }
				 }catch (Exception ^sb)
				 {
					 label8->Text = "数据库未连接！";
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
				 //String ^strSQL = "delete dbo.SourceData2 where time < "+ m_strtest;//删除7天前的数据。//看这个7天是否是可调节的。---->>>>这样删除会出问题。会删除全部//
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
					//	 MessageBox::Show("超过3天了");
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
			 if (Lin_RecvStr == "开始")
			 {
				 Lin_BNetConnect = true;
			 }else if(Lin_RecvStr == "停止")
			 {
				 Lin_BNetConnect = false;
			 }
			 else
			 {
				 //说明接收到的是角度信息//
				 if (Lin_BNetConnect == true)
				 {
					 int m_angle  = System::Int32::Parse(Lin_RecvStr);
					 if (m_angle<360*AngleAccuracy&&m_angle>=0)
					 {
						 Lin_OldAngle = Lin_CurrentAngle;
						 Lin_CurrentAngle = m_angle;
						 AngleLabel->Text = String::Format("旋转角度：{0:##0.0}度",(double)Lin_CurrentAngle/AngleAccuracy);
					 }
				 }
			 }
		 }
};


}
