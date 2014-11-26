#pragma once

#include "FormImager.h"
#include "SetForm.h"
#include "SetForm02.h"
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Threading;
using namespace System::Net::Sockets;
using namespace System::Net;
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
			if (Lin_Thread->IsAlive)
			{
				if (Lin_Thread->ThreadState == System::Threading::ThreadState::Suspended)
				{
					Lin_Thread->Resume();
					Lin_Thread->Abort();
				}
				else 
				{
					Lin_Thread->Abort();
				}
			}
		}

	private: System::Windows::Forms::Button^  SetButton;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::GroupBox^  groupBox4;
	private: System::Windows::Forms::PictureBox^  MatchPictureBox;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  MyChart;
	protected: 

	protected: 
private: System::Windows::Forms::Timer^  MyTimerReadDB;











































private: System::Windows::Forms::GroupBox^  groupBox6;
















private: System::Windows::Forms::Timer^  MyTimerSynDB;
private: System::IO::Ports::SerialPort^  serialPort1;
private: System::Windows::Forms::Button^  buttonStart;
private: System::Windows::Forms::Label^  label19;
private: System::Windows::Forms::Button^  button1;
private: System::Windows::Forms::Button^  button6;
private: System::Windows::Forms::Timer^  MyTimerSendAngle;


private: System::Windows::Forms::Button^  buttonSwitch;


		 //画面的显示及温度的处理【变量】//
		System::Drawing::Brush ^Lin_Brush;
		int FrameWidth ;
		int FrameHeight;
		int Lin_MousePositionX,Lin_MousePositionY;
		int MatchWidth;
		int MatchHeight;
		int Lin_InnerCircleR;
		int Lin_MatchMousePositionX,Lin_MatchMousePositionY;
		bool Lin_BMatchSHowRectangle;
		bool Lin_BMatchKeepRectangle;
		bool Lin_BMatchShowMouseTemp;
		double Lin_MatchMouseTempValue;
		array<Byte>^ rgbMatchValues;
		Point Lin_MaxMatchTempValuePoint;
		array<unsigned short>^ Lin_AngleWithValues;
		/*扫描完成以后，从左至右，从上往下，正序储存煤场的温度。数组大小：MatchWidth*MatchHeight*/
		array<double>^ whu_AllMatchTempValues;
		/*选定框的温度信息*/
		array<double>^ whu_AllSelectMatchTempValues;
		System::Drawing::Rectangle ^Lin_MatchSelectRectangle;
		/*扫描像素长度，值为两个热像仪图像的FrameWidth值*/
		int LineCount ;
		/*储存到数据库的长度，StoreLineCount = 1(校验位)+1（角度）+5（年月日时分）+ LineCount*/
		int StoreLineCount;
		/*扫描的精度,定为5，即以0.2°为一个步进*/
		int AngleAccuracy;
		short TempMinTrackBarValue;
		short TempRangTrackBarValue;

		int SetFormPos;//隐藏和显示设置//
		/*画笔及字体信息，以标注图形上的温度*/
		System::Drawing::Pen^ Lin_BlackPen;
		System::Drawing::Font^ Lin_BigFront;
		System::Drawing::Font^ Lin_SmallFront;
		System::Drawing::Pen^ Lin_WhitePen;
		System::Drawing::Pen^ Lin_BulePen;
		System::Drawing::Pen^ Lin_RedPen;
		double Lin_MaxMatchTempValue;
		double Lin_AverageTempValue;
		
		Bitmap^ Lin_MatchBmpImage;
		int Lin_CurrentAngle;
		bool Lin_BConnectedToLocalDB;
		bool Lin_BConnectedToRemoteDB;
		array<double>^ Lin_MouseClickHistoryTemp;
		SetForm ^Lin_SetForm;
private: System::Windows::Forms::Timer^  MyTimerSynData;


		public:
			int Lin_AlarmTemp;
		private:

		//画面的显示及温度的处理【函数】//
		
		/*将数据转化成RGB像素值，在whu_GetMatchingImg中调用了此函数*/
		void whu_GetRGBValue(short m_value ,Byte *m_RGBValue);
		
		/*得到拼接图片*/
		void whu_GetMatchingImg(Bitmap ^MatchBmp);
		
		/*缩放图片以适应窗口*/
		Bitmap^ whu_ResizeImage(Bitmap^ Bmp,int NewWidth,int NewHeight);


		//数据库的读操作【变量】//
		SqlConnection ^Lin_LocalConnSql;
		SqlConnection ^Lin_RemoteConnSql;
		String ^Lin_LocalDataSource;
		String ^Lin_LocalDataBaseName;
		String ^Lin_RemoteDataSource;
		String ^Lin_RemoteDataBaseName;
		String ^Lin_RemoteUserName;
		String ^Lin_RemoteUserPwd;
		ThreadStart ^Lin_ThreadStart;
		Thread ^Lin_Thread;
		array<unsigned short>^ Lin_HistoryAngleWithValues;

		//数据库的读操作【函数】//

		/*通过调用whu_ReadDataFromRemoteDB，更新实时温度流信息至Lin_AngleWithValues*/
		void whu_UpdataTempData();

		/*通过调用whu_ReadDataFromLocalDB，更新历史温度流信息至Lin_HistoryAngleWithValues*/
		void whu_GetHistoryTemp(int angle,int Pos,array<double>^ Temp,array<unsigned short>^ TempTime,unsigned int Num);


		/*从远程数据库获取实时数据，输入为角度，输出为StoreLineCount长度的short型数组*/
		bool whu_ReadDataFromRemoteDB(double angle,array<short>^DestData);
		/*从本地数据库获取历史数据，输入为角度，输出为StoreLineCount*Num长度的short型数组*/
		bool FormMulti::whu_ReadDataFromLocalDB(double angle,array<short>^DestData,int Num);


		bool whu_ConnectToLocalDB(String ^m_LocalDataSource,String ^m_LocalDataBaseName);
		bool whu_DisConnectToLocalDB();
		bool whu_ConnectToRemoteDB(String ^m_DataSource,String ^m_DataBaseName,String ^m_User,String ^m_Password);
		bool whu_DisConnectToRemoteDB();
		//SOCKET 远程控制部分
		Socket ^Lin_SendSocket;
		IPEndPoint ^Lin_iPEndPoint;
		bool Lin_BSendAngle;

		//设置
		SetForm02 ^m_SetForm;

private: System::Windows::Forms::Timer^  MyTimerGetImg;


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
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea2 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea3 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^  legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^  series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series3 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series4 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series5 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Title^  title1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Title());
			this->MyTimerGetImg = (gcnew System::Windows::Forms::Timer(this->components));
			this->SetButton = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->MatchPictureBox = (gcnew System::Windows::Forms::PictureBox());
			this->MyChart = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->MyTimerReadDB = (gcnew System::Windows::Forms::Timer(this->components));
			this->groupBox6 = (gcnew System::Windows::Forms::GroupBox());
			this->MyTimerSynDB = (gcnew System::Windows::Forms::Timer(this->components));
			this->serialPort1 = (gcnew System::IO::Ports::SerialPort(this->components));
			this->buttonStart = (gcnew System::Windows::Forms::Button());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->MyTimerSendAngle = (gcnew System::Windows::Forms::Timer(this->components));
			this->buttonSwitch = (gcnew System::Windows::Forms::Button());
			this->MyTimerSynData = (gcnew System::Windows::Forms::Timer(this->components));
			this->groupBox4->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->MatchPictureBox))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->MyChart))->BeginInit();
			this->groupBox6->SuspendLayout();
			this->SuspendLayout();
			// 
			// MyTimerGetImg
			// 
			this->MyTimerGetImg->Enabled = true;
			this->MyTimerGetImg->Interval = 500;
			this->MyTimerGetImg->Tick += gcnew System::EventHandler(this, &FormMulti::MyTimer200_Tick);
			// 
			// SetButton
			// 
			this->SetButton->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->SetButton->Cursor = System::Windows::Forms::Cursors::Hand;
			this->SetButton->Font = (gcnew System::Drawing::Font(L"SimSun", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->SetButton->Location = System::Drawing::Point(712, 529);
			this->SetButton->Name = L"SetButton";
			this->SetButton->Size = System::Drawing::Size(82, 45);
			this->SetButton->TabIndex = 16;
			this->SetButton->Text = L"设置";
			this->SetButton->UseVisualStyleBackColor = false;
			this->SetButton->Click += gcnew System::EventHandler(this, &FormMulti::SetButton_Click);
			// 
			// button2
			// 
			this->button2->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->button2->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button2->Font = (gcnew System::Drawing::Font(L"SimSun", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->button2->Location = System::Drawing::Point(894, 529);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(82, 45);
			this->button2->TabIndex = 17;
			this->button2->Text = L"退出";
			this->button2->UseVisualStyleBackColor = false;
			this->button2->Click += gcnew System::EventHandler(this, &FormMulti::button2_Click);
			// 
			// groupBox4
			// 
			this->groupBox4->BackColor = System::Drawing::Color::Transparent;
			this->groupBox4->Controls->Add(this->MatchPictureBox);
			this->groupBox4->Location = System::Drawing::Point(5, -4);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Size = System::Drawing::Size(615, 521);
			this->groupBox4->TabIndex = 24;
			this->groupBox4->TabStop = false;
			// 
			// MatchPictureBox
			// 
			this->MatchPictureBox->ImageLocation = L"";
			this->MatchPictureBox->InitialImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"MatchPictureBox.InitialImage")));
			this->MatchPictureBox->Location = System::Drawing::Point(2, 8);
			this->MatchPictureBox->Name = L"MatchPictureBox";
			this->MatchPictureBox->Size = System::Drawing::Size(611, 512);
			this->MatchPictureBox->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->MatchPictureBox->TabIndex = 24;
			this->MatchPictureBox->TabStop = false;
			this->MatchPictureBox->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &FormMulti::MatchPictureBox_Pain);
			this->MatchPictureBox->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &FormMulti::MatchPictureBox_MouseClick);
			this->MatchPictureBox->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &FormMulti::MatchPictureBox_MouseDown);
			this->MatchPictureBox->MouseLeave += gcnew System::EventHandler(this, &FormMulti::MatchPictureBox_MouseLeave);
			this->MatchPictureBox->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &FormMulti::MatchPictureBox_MouseMove);
			this->MatchPictureBox->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &FormMulti::MatchPictureBox_MouseUp);
			// 
			// MyChart
			// 
			this->MyChart->BackColor = System::Drawing::Color::Transparent;
			chartArea1->Area3DStyle->LightStyle = System::Windows::Forms::DataVisualization::Charting::LightStyle::None;
			chartArea1->AxisX->ArrowStyle = System::Windows::Forms::DataVisualization::Charting::AxisArrowStyle::Triangle;
			chartArea1->AxisX->InterlacedColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), 
				static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			chartArea1->AxisX->LabelStyle->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			chartArea1->AxisX->LineColor = System::Drawing::Color::Snow;
			chartArea1->AxisX->Maximum = 360;
			chartArea1->AxisX->Minimum = 0;
			chartArea1->AxisX->ScaleView->Size = 360;
			chartArea1->AxisX->TextOrientation = System::Windows::Forms::DataVisualization::Charting::TextOrientation::Horizontal;
			chartArea1->AxisX->TitleAlignment = System::Drawing::StringAlignment::Far;
			chartArea1->AxisX->TitleFont = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.5F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			chartArea1->AxisX2->Enabled = System::Windows::Forms::DataVisualization::Charting::AxisEnabled::False;
			chartArea1->AxisX2->IsLabelAutoFit = false;
			chartArea1->AxisX2->Maximum = 1;
			chartArea1->AxisX2->Minimum = 0;
			chartArea1->AxisY->ArrowStyle = System::Windows::Forms::DataVisualization::Charting::AxisArrowStyle::Triangle;
			chartArea1->AxisY->Crossing = 1.7976931348623157E+308;
			chartArea1->AxisY->Enabled = System::Windows::Forms::DataVisualization::Charting::AxisEnabled::True;
			chartArea1->AxisY->InterlacedColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), 
				static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			chartArea1->AxisY->Interval = 20;
			chartArea1->AxisY->IsInterlaced = true;
			chartArea1->AxisY->IsLabelAutoFit = false;
			chartArea1->AxisY->LabelStyle->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			chartArea1->AxisY->LineColor = System::Drawing::Color::Snow;
			chartArea1->AxisY->Maximum = 100;
			chartArea1->AxisY->MaximumAutoSize = 0;
			chartArea1->AxisY->Minimum = -20;
			chartArea1->AxisY->TextOrientation = System::Windows::Forms::DataVisualization::Charting::TextOrientation::Stacked;
			chartArea1->AxisY->Title = L"温度值°C";
			chartArea1->AxisY->TitleAlignment = System::Drawing::StringAlignment::Near;
			chartArea1->AxisY->TitleFont = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.5F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			chartArea1->AxisY2->Enabled = System::Windows::Forms::DataVisualization::Charting::AxisEnabled::False;
			chartArea1->AxisY2->LineWidth = 0;
			chartArea1->AxisY2->LogarithmBase = 15;
			chartArea1->AxisY2->Maximum = 1;
			chartArea1->AxisY2->Minimum = 0;
			chartArea1->AxisY2->TitleFont = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.5F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			chartArea1->BackColor = System::Drawing::Color::White;
			chartArea1->CursorX->IsUserEnabled = true;
			chartArea1->CursorX->Position = 0;
			chartArea1->InnerPlotPosition->Auto = false;
			chartArea1->InnerPlotPosition->Height = 45;
			chartArea1->InnerPlotPosition->Width = 80;
			chartArea1->InnerPlotPosition->X = 15;
			chartArea1->Name = L"ChartArea1";
			chartArea1->Position->Auto = false;
			chartArea1->Position->Height = 45;
			chartArea1->Position->Width = 70;
			chartArea1->Position->X = 10;
			chartArea1->Position->Y = 10;
			chartArea1->ShadowColor = System::Drawing::Color::Gray;
			chartArea1->ShadowOffset = 2;
			chartArea2->AxisX->ArrowStyle = System::Windows::Forms::DataVisualization::Charting::AxisArrowStyle::Triangle;
			chartArea2->AxisX->InterlacedColor = System::Drawing::Color::Honeydew;
			chartArea2->AxisX->Interval = 10;
			chartArea2->AxisX->LabelStyle->IntervalType = System::Windows::Forms::DataVisualization::Charting::DateTimeIntervalType::Minutes;
			chartArea2->AxisX->ScaleBreakStyle->StartFromZero = System::Windows::Forms::DataVisualization::Charting::StartFromZero::No;
			chartArea2->AxisX->ScaleView->SizeType = System::Windows::Forms::DataVisualization::Charting::DateTimeIntervalType::Minutes;
			chartArea2->AxisX->ScrollBar->BackColor = System::Drawing::Color::MintCream;
			chartArea2->AxisX->ScrollBar->ButtonColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), 
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(192)));
			chartArea2->AxisX->ScrollBar->LineColor = System::Drawing::Color::Black;
			chartArea2->AxisX->TextOrientation = System::Windows::Forms::DataVisualization::Charting::TextOrientation::Horizontal;
			chartArea2->AxisX->Title = L"时间";
			chartArea2->AxisY->ArrowStyle = System::Windows::Forms::DataVisualization::Charting::AxisArrowStyle::Triangle;
			chartArea2->AxisY->InterlacedColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), 
				static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			chartArea2->AxisY->IsInterlaced = true;
			chartArea2->AxisY->TextOrientation = System::Windows::Forms::DataVisualization::Charting::TextOrientation::Stacked;
			chartArea2->AxisY->Title = L"浓度ppm";
			chartArea2->AxisY->TitleAlignment = System::Drawing::StringAlignment::Far;
			chartArea2->AxisY->TitleFont = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.5F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			chartArea2->InnerPlotPosition->Auto = false;
			chartArea2->InnerPlotPosition->Height = 45;
			chartArea2->InnerPlotPosition->Width = 80;
			chartArea2->InnerPlotPosition->X = 15;
			chartArea2->Name = L"ChartArea2";
			chartArea2->Position->Auto = false;
			chartArea2->Position->Height = 45;
			chartArea2->Position->Width = 70;
			chartArea2->Position->X = 10;
			chartArea2->Position->Y = 40;
			chartArea3->AxisX->ArrowStyle = System::Windows::Forms::DataVisualization::Charting::AxisArrowStyle::Triangle;
			chartArea3->AxisX->InterlacedColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), 
				static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)));
			chartArea3->AxisX->IsInterlaced = true;
			chartArea3->AxisY->ArrowStyle = System::Windows::Forms::DataVisualization::Charting::AxisArrowStyle::Triangle;
			chartArea3->AxisY->TextOrientation = System::Windows::Forms::DataVisualization::Charting::TextOrientation::Stacked;
			chartArea3->AxisY->Title = L"浓度%";
			chartArea3->AxisY->TitleFont = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.5F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			chartArea3->InnerPlotPosition->Auto = false;
			chartArea3->InnerPlotPosition->Height = 45;
			chartArea3->InnerPlotPosition->Width = 80;
			chartArea3->InnerPlotPosition->X = 15;
			chartArea3->Name = L"ChartArea3";
			chartArea3->Position->Auto = false;
			chartArea3->Position->Height = 45;
			chartArea3->Position->Width = 70;
			chartArea3->Position->X = 10;
			chartArea3->Position->Y = 70;
			this->MyChart->ChartAreas->Add(chartArea1);
			this->MyChart->ChartAreas->Add(chartArea2);
			this->MyChart->ChartAreas->Add(chartArea3);
			legend1->BackColor = System::Drawing::Color::Transparent;
			legend1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			legend1->IsTextAutoFit = false;
			legend1->Name = L"Legend1";
			legend1->Position->Auto = false;
			legend1->Position->Height = 80;
			legend1->Position->Width = 25;
			legend1->Position->X = 75;
			legend1->Position->Y = 10;
			legend1->ShadowColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)), 
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->MyChart->Legends->Add(legend1);
			this->MyChart->Location = System::Drawing::Point(3, 16);
			this->MyChart->Name = L"MyChart";
			this->MyChart->RightToLeft = System::Windows::Forms::RightToLeft::No;
			series1->BorderWidth = 2;
			series1->ChartArea = L"ChartArea1";
			series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series1->Color = System::Drawing::Color::Red;
			series1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.5F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			series1->LabelBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(192)), 
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			series1->Legend = L"Legend1";
			series1->Name = L"每列最高温";
			series1->ToolTip = L"#VAL °C";
			series1->YValuesPerPoint = 2;
			series2->BorderWidth = 2;
			series2->ChartArea = L"ChartArea1";
			series2->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series2->Color = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)), 
				static_cast<System::Int32>(static_cast<System::Byte>(128)));
			series2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			series2->Legend = L"Legend1";
			series2->Name = L"报警温度";
			series3->ChartArea = L"ChartArea2";
			series3->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			series3->IsXValueIndexed = true;
			series3->Legend = L"Legend1";
			series3->Name = L"CO浓度";
			series3->XValueType = System::Windows::Forms::DataVisualization::Charting::ChartValueType::Time;
			series4->ChartArea = L"ChartArea3";
			series4->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series4->Color = System::Drawing::Color::Black;
			series4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			series4->Legend = L"Legend1";
			series4->Name = L"CH4浓度";
			series5->ChartArea = L"ChartArea1";
			series5->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series5->Color = System::Drawing::Color::Yellow;
			series5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			series5->Legend = L"Legend1";
			series5->Name = L"报警浓度";
			this->MyChart->Series->Add(series1);
			this->MyChart->Series->Add(series2);
			this->MyChart->Series->Add(series3);
			this->MyChart->Series->Add(series4);
			this->MyChart->Series->Add(series5);
			this->MyChart->Size = System::Drawing::Size(559, 499);
			this->MyChart->TabIndex = 0;
			this->MyChart->Text = L"chart1";
			title1->Alignment = System::Drawing::ContentAlignment::TopCenter;
			title1->BackColor = System::Drawing::Color::Transparent;
			title1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			title1->Name = L"Title1";
			title1->Text = L"监测图表";
			title1->ToolTip = L"显示扫描过的煤堆的最高温度";
			this->MyChart->Titles->Add(title1);
			// 
			// MyTimerReadDB
			// 
			this->MyTimerReadDB->Enabled = true;
			this->MyTimerReadDB->Interval = 60000;
			this->MyTimerReadDB->Tick += gcnew System::EventHandler(this, &FormMulti::MyTimerReadDB_Tick);
			// 
			// groupBox6
			// 
			this->groupBox6->BackColor = System::Drawing::Color::Transparent;
			this->groupBox6->Controls->Add(this->MyChart);
			this->groupBox6->Location = System::Drawing::Point(626, -4);
			this->groupBox6->Name = L"groupBox6";
			this->groupBox6->Size = System::Drawing::Size(562, 521);
			this->groupBox6->TabIndex = 26;
			this->groupBox6->TabStop = false;
			// 
			// MyTimerSynDB
			// 
			this->MyTimerSynDB->Interval = 10000;
			this->MyTimerSynDB->Tick += gcnew System::EventHandler(this, &FormMulti::MyTimerSynDB_Tick);
			// 
			// buttonStart
			// 
			this->buttonStart->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->buttonStart->Cursor = System::Windows::Forms::Cursors::Hand;
			this->buttonStart->Font = (gcnew System::Drawing::Font(L"SimSun", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->buttonStart->Location = System::Drawing::Point(12, 528);
			this->buttonStart->Name = L"buttonStart";
			this->buttonStart->Size = System::Drawing::Size(82, 43);
			this->buttonStart->TabIndex = 28;
			this->buttonStart->Text = L"开始";
			this->buttonStart->UseVisualStyleBackColor = false;
			this->buttonStart->Click += gcnew System::EventHandler(this, &FormMulti::buttonStart_Click);
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->Font = (gcnew System::Drawing::Font(L"SimSun", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->label19->Location = System::Drawing::Point(125, 541);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(159, 20);
			this->label19->TabIndex = 29;
			this->label19->Text = L"当前角度：0.0°";
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->button1->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button1->Enabled = false;
			this->button1->Font = (gcnew System::Drawing::Font(L"SimSun", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->button1->Location = System::Drawing::Point(375, 529);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(82, 45);
			this->button1->TabIndex = 31;
			this->button1->Text = L"加速";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &FormMulti::button1_Click_1);
			// 
			// button6
			// 
			this->button6->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->button6->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button6->Enabled = false;
			this->button6->Font = (gcnew System::Drawing::Font(L"SimSun", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->button6->Location = System::Drawing::Point(514, 529);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(82, 45);
			this->button6->TabIndex = 32;
			this->button6->Text = L"减速";
			this->button6->UseVisualStyleBackColor = false;
			this->button6->Click += gcnew System::EventHandler(this, &FormMulti::button6_Click);
			// 
			// MyTimerSendAngle
			// 
			this->MyTimerSendAngle->Enabled = true;
			this->MyTimerSendAngle->Interval = 1000;
			this->MyTimerSendAngle->Tick += gcnew System::EventHandler(this, &FormMulti::MyTimerSendAngle_Tick);
			// 
			// buttonSwitch
			// 
			this->buttonSwitch->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->buttonSwitch->Cursor = System::Windows::Forms::Cursors::Hand;
			this->buttonSwitch->Font = (gcnew System::Drawing::Font(L"SimSun", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->buttonSwitch->Location = System::Drawing::Point(1058, 523);
			this->buttonSwitch->Name = L"buttonSwitch";
			this->buttonSwitch->Size = System::Drawing::Size(119, 55);
			this->buttonSwitch->TabIndex = 35;
			this->buttonSwitch->Text = L"切换";
			this->buttonSwitch->UseVisualStyleBackColor = false;
			this->buttonSwitch->Click += gcnew System::EventHandler(this, &FormMulti::buttonSwitch_Click);
			// 
			// MyTimerSynData
			// 
			this->MyTimerSynData->Enabled = true;
			this->MyTimerSynData->Tick += gcnew System::EventHandler(this, &FormMulti::MyTimerSynData_Tick);
			// 
			// FormMulti
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"$this.BackgroundImage")));
			this->ClientSize = System::Drawing::Size(1194, 583);
			this->Controls->Add(this->buttonSwitch);
			this->Controls->Add(this->button6);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label19);
			this->Controls->Add(this->buttonStart);
			this->Controls->Add(this->groupBox6);
			this->Controls->Add(this->groupBox4);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->SetButton);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"FormMulti";
			this->Text = L"      ";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &FormMulti::FormMulti_FormClosing);
			this->Load += gcnew System::EventHandler(this, &FormMulti::FormMulti_Load);
			this->groupBox4->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->MatchPictureBox))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->MyChart))->EndInit();
			this->groupBox6->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void FormMulti_Load(System::Object^  sender, System::EventArgs^  e);
	private: System::Void FormMulti_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e);
	private: System::Void FormImager_OnResize(System::Object^  sender, System::EventArgs^  e);
	private: System::Void MyTimer1000_Tick(System::Object^  sender, System::EventArgs^  e)
			 {
				////显示合成图像区域框的温度//
				//if (Lin_BMatchKeepRectangle)//绘制了矩形框
				//{
				//	//AverTempLabel->Show();
				//	//this->MyChart->Series["区域温度"]->Points->AddXY(m_MatchSelectRectShowTime,whu_AllSelectMatchTempValues[0]);
				//	AverTempLabel->Text = String::Format("{0:##0.0}°C", whu_AllSelectMatchTempValues[0]); 
				//	m_MatchSelectRectShowTime++;
				//	if (m_MatchSelectRectShowTime>=360)
				//	{
				//		//this->MyChart->Series["区域温度"]->Points->Clear();
				//		m_MatchSelectRectShowTime = 0;
				//	}
				//} 
				//else
				//{
				//	//this->MyChart->Series["区域温度"]->Points->Clear();
				//	m_MatchSelectRectShowTime = 0;
				//	AverTempLabel->Hide();
				//	//whu_AllSelectMatchTempValues[0] = -20;
				//	//this->MyChart->Series["区域温度"]->Points->AddXY(trackBar3->Value,whu_AllSelectMatchTempValues[0]);
				//	AverTempLabel->Text = String::Format("°C"); 
				//}
			 }
private: System::Void MyTimer200_Tick(System::Object^  sender, System::EventArgs^  e) {
				whu_GetMatchingImg(Lin_MatchBmpImage);
				MatchPictureBox->Invalidate();
				//显示鼠标点的温度
				if (Lin_BMatchShowMouseTemp)
				{
					int pos = Lin_MatchMousePositionY*MatchWidth+Lin_MatchMousePositionX;
					if (pos<MatchWidth*MatchHeight)
					{
						Lin_MatchMouseTempValue = whu_AllMatchTempValues[pos];	 
					}
				}
				this->MyChart->Series["每列最高温"]->Points->Clear();
				for (int angle=0;angle<360;angle++)
				{
					int VerifyPos = angle*AngleAccuracy*(1+1+5+LineCount);
					if (Lin_AngleWithValues[VerifyPos]==0xffff)
					{
						//int angle = whu_OutputPolarTemp[VerifyPos+1];//角度,
						unsigned short m_MaxValue = 0;
						double maxtemp = 0;
						for (int j=0;j<LineCount;j++)
						{
							if (Lin_AngleWithValues[VerifyPos+j+2+5]>m_MaxValue)
							{
								m_MaxValue = Lin_AngleWithValues[VerifyPos+j+2+5];//取得最高温
							}
						}
						double m_MaxTemp = (m_MaxValue-1000)/10.0;
						this->MyChart->Series["每列最高温"]->Points->AddXY(angle,m_MaxTemp);
					}	 
				}
			 


		 }
private: System::Void FrmChild_PassDataBetweenForm(bool show)
		 {
			 bool sb = show;
		 }
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
			////label13->Text = "读取数据....";
			//ButtonRefresh->Enabled = false;
			//array<short>^ m_DestData = gcnew array<short>(LineCount+1+1);
			//for (int i=0;i<360*AngleAccuracy;i++)
			//{
			//	double m_angle = i/(double)AngleAccuracy;
			//	if (Lin_BConnectedToLocalDB)
			//	{
			//		if (whu_ReadDataFromDB(m_angle,m_DestData))
			//		{
			//			int pos = i*(1+1+LineCount);
			//			System::Buffer::BlockCopy(m_DestData,0,Lin_AngleWithValues,pos*sizeof(short),m_DestData->Length*sizeof(short));
			//		}
			//		
			//		
			//	}
			//	
			//}
			////label13->Text = "读取完成....";
			//ButtonRefresh->Enabled = true;//上面的程序需要1分钟才能跑完，需要使用多线程分别刷新。

			/* if (Lin_Thread->ThreadState == System::Threading::ThreadState::Unstarted)
			 {
				 Lin_Thread->Start();
			 }else if(Lin_Thread->ThreadState == System::Threading::ThreadState::Running){
				 Lin_Thread->Suspend();
			 }else if(Lin_Thread->ThreadState == System::Threading::ThreadState::Suspended){
				 Lin_Thread->Resume();
			 }*/

		  }
private: System::Void SetButton_Click(System::Object^  sender, System::EventArgs^  e) {


			 m_SetForm->Show();
			 static bool show = true;
			 //if (show == false)
			 //{
				// m_SetForm->Hide();
				// ClientSize = Drawing::Size(SetFormPos, SetgroupBox->Top);
				// show = true;
			 //}else{
				// //ClientSize = Drawing::Size(SetFormPos, SetgroupBox->Bottom+10);
				// show = false;
				// m_SetForm->Show();
				// 
			 //}

			 
			 


		 }
private: System::Void groupBox2_Enter(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void label9_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void SetgroupBox_Enter(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void trackBar3_Scroll(System::Object^  sender, System::EventArgs^  e) {
			//m_CurrentAngle  =  trackBar3->Value;
			//AngleLabel->Text = String::Format({0#00.0})
		 }
private: System::Void ContactButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 
		 }
private: System::Void MatchPictureBox_Pain(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) 
		 {  
			if (Lin_BConnectedToRemoteDB)
			{
				Lin_MatchBmpImage = whu_ResizeImage(Lin_MatchBmpImage,MatchPictureBox->Width,MatchPictureBox->Height);
				e->Graphics->DrawImage( Lin_MatchBmpImage, 0, 0 );
				//m_MatchBmpImage->Bitmap
				//
				if (Lin_BMatchShowMouseTemp&&Lin_MatchMouseTempValue!=-100)
				{
					String ^StrTempValue = String::Format("{0:##0.0}°C",Lin_MatchMouseTempValue);
					e->Graphics->DrawString(StrTempValue,Lin_BigFront,Lin_Brush,Lin_MousePositionX+8,Lin_MousePositionY+8);
				}
				//温度最高点,由于图形缩放了，因此需要转化下坐标//
				Lin_MaxMatchTempValuePoint.X =  Lin_MaxMatchTempValuePoint.X*MatchPictureBox->Width/(double)MatchWidth;
				Lin_MaxMatchTempValuePoint.Y =  Lin_MaxMatchTempValuePoint.Y*MatchPictureBox->Height/(double)MatchHeight;
				System::Drawing::Rectangle ^m_Rect = gcnew System::Drawing::Rectangle(Lin_MaxMatchTempValuePoint.X-8,Lin_MaxMatchTempValuePoint.Y-8,16,16);
				Point StartPoint1,StartPoint2,EndPoint1,EndPoint2;
				StartPoint1.X = Lin_MaxMatchTempValuePoint.X-30;
				StartPoint1.Y = Lin_MaxMatchTempValuePoint.Y;
				EndPoint1.X = Lin_MaxMatchTempValuePoint.X+30;
				EndPoint1.Y = Lin_MaxMatchTempValuePoint.Y;
				StartPoint2.X = Lin_MaxMatchTempValuePoint.X;
				StartPoint2.Y = Lin_MaxMatchTempValuePoint.Y-30;
				EndPoint2.X = Lin_MaxMatchTempValuePoint.X;
				EndPoint2.Y = Lin_MaxMatchTempValuePoint.Y+30;			 
				e->Graphics->DrawEllipse(Lin_RedPen,*m_Rect);
				e->Graphics->DrawLine(Lin_RedPen,StartPoint1,EndPoint1);
				e->Graphics->DrawLine(Lin_RedPen,StartPoint2,EndPoint2);

				String ^StrMaxTempValue = String::Format("煤场最高温：{0:##0.0}°C",Lin_MaxMatchTempValue);
				int PosX = MatchPictureBox->Width/30;
				int PosY = MatchPictureBox->Height/20;
				e->Graphics->DrawString(StrMaxTempValue,Lin_BigFront,Lin_Brush,PosX,PosY);


				//区域温度//
				e->Graphics->DrawRectangle(Lin_WhitePen,*Lin_MatchSelectRectangle);
				if (Lin_BMatchKeepRectangle&&(Lin_MatchSelectRectangle->Left != Lin_MatchSelectRectangle->Right)&&(Lin_MatchSelectRectangle->Top!=Lin_MatchSelectRectangle->Bottom))
				{
					double m_TempValue = 0;
					double m_All = 0;
					int m_Count = 0;
					Point RectHighTempPoint;
					double RectHighTemp = 0;
					double MyWidthIndex = MatchWidth/(double)MatchPictureBox->Width;
					double MyHeightIndex = MatchHeight/(double)MatchPictureBox->Height;
					int iStart = Lin_MatchSelectRectangle->Top*MyHeightIndex;
					int iEnd = (Lin_MatchSelectRectangle->Height+Lin_MatchSelectRectangle->Top)*MyHeightIndex;
					int jStart = Lin_MatchSelectRectangle->Left*MyWidthIndex;
					int jEnd = (Lin_MatchSelectRectangle->Width+Lin_MatchSelectRectangle->Left)*MyWidthIndex;
					for (int i=iStart;i<iEnd;i++ )
					{
						for (int j=jStart;j<jEnd;j++)
						{
							int pos = i*MatchWidth + j;
							if (pos<MatchWidth*MatchHeight)
							{
								if(whu_AllMatchTempValues[pos]!=-100)
								{
									m_All = m_All + whu_AllMatchTempValues[pos];
									m_Count ++;
									if (whu_AllMatchTempValues[pos]>RectHighTemp)
									{
										RectHighTemp = whu_AllMatchTempValues[pos];
										RectHighTempPoint.X = j/MyWidthIndex;
										RectHighTempPoint.Y = i/MyHeightIndex;
									}
								}

							}

						} 
					}
					//显示区域温度//
					if (m_Count>=1)
					{
						m_TempValue = m_All/m_Count;
						whu_AllSelectMatchTempValues[0] = m_TempValue;
						String ^RectTemp = String::Format("区域温度：{0:##0.0}°C", m_TempValue);
 						e->Graphics->DrawString(RectTemp,Lin_SmallFront,Lin_Brush,Lin_MatchSelectRectangle->X,Lin_MatchSelectRectangle->Y-30);
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
						e->Graphics->DrawEllipse(Lin_RedPen,*m_MaxTempValuePointRect);
						e->Graphics->DrawLine(Lin_RedPen,StartPoint1,EndPoint1);
						e->Graphics->DrawLine(Lin_RedPen,StartPoint2,EndPoint2);

						String ^StrRectHighTemp = String::Format("区域最高温度：{0:##0.0}°C", RectHighTemp);
						e->Graphics->DrawString(StrRectHighTemp,Lin_SmallFront,Lin_Brush,RectHighTempPoint.X,RectHighTempPoint.Y);

					}

				}
			}
			


		 }
private: System::Void MatchPictureBox_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs ^  e) 
		 {
			 int Height = this->MatchPictureBox->Height;
			 int Width = this->MatchPictureBox->Width;
			 /*int Lin_MousePositionX,Lin_MousePositionY;*/
			 Lin_MousePositionX = e->X;
			 Lin_MousePositionY = e->Y;
			 Lin_MatchMousePositionX = Lin_MousePositionX*MatchWidth/MatchPictureBox->Width;
			 Lin_MatchMousePositionY = Lin_MousePositionY*MatchHeight/MatchPictureBox->Height;
			 if ((Lin_MousePositionX < Width)&&(Lin_MousePositionY<Height ))
			 {

				 int pos = Lin_MatchMousePositionY*MatchWidth+Lin_MatchMousePositionX;
				 if (pos<MatchWidth*MatchHeight)
				 {
					 Lin_MatchMouseTempValue = whu_AllMatchTempValues[pos];
					 Lin_BMatchShowMouseTemp = true; 		 
				 }
				 if (Lin_BMatchSHowRectangle&&!Lin_BMatchKeepRectangle)//获得鼠标选定区域// 
				 {
					 Lin_MatchSelectRectangle = gcnew System::Drawing::Rectangle(Lin_MatchSelectRectangle->Left,Lin_MatchSelectRectangle->Top,e->X-Lin_MatchSelectRectangle->X,e->Y-Lin_MatchSelectRectangle->Y);
				 }

				 if (Lin_BMatchSHowRectangle&&!Lin_BMatchKeepRectangle)//获得鼠标选定区域// 
				 {
					 Lin_MatchSelectRectangle = gcnew System::Drawing::Rectangle(Lin_MatchSelectRectangle->Left,Lin_MatchSelectRectangle->Top,e->X-Lin_MatchSelectRectangle->X,e->Y-Lin_MatchSelectRectangle->Y);
				 }


			}


		 }
private: System::Void MatchPictureBox_MouseLeave(System::Object^  sender, System::EventArgs ^  e) 
		 {
			 Lin_BMatchShowMouseTemp = false;
			 
		 }
private: System::Void MatchPictureBox_MouseDown(System::Object^ sender,System::Windows::Forms::MouseEventArgs ^  e){
			 Lin_MatchSelectRectangle = gcnew System::Drawing::Rectangle(e->X,e->Y,0,0);
			 Lin_BMatchSHowRectangle = true;
			 Lin_BMatchKeepRectangle = false;
			 
		 }
private: System::Void MatchPictureBox_MouseUp(System::Object^ sender,System::Windows::Forms::MouseEventArgs ^  e)
		 {
			 Lin_MatchSelectRectangle = gcnew System::Drawing::Rectangle(Lin_MatchSelectRectangle->Left,Lin_MatchSelectRectangle->Top,e->X-Lin_MatchSelectRectangle->Left,e->Y-Lin_MatchSelectRectangle->Top);
			 if ((Lin_MatchSelectRectangle->Left != Lin_MatchSelectRectangle->Right)&&(Lin_MatchSelectRectangle->Top!=Lin_MatchSelectRectangle->Bottom))
			 {
				 Lin_BMatchSHowRectangle = true;
				 Lin_BMatchKeepRectangle = true;
			 }



		 }
private: System::Void MatchPictureBox_MouseClick(System::Object ^sender,System::Windows::Forms::MouseEventArgs ^  e)
		 {
			 //whu_BSHowRectangle = false;
			 //MessageBox::Show("没事点什么鼠标?");
			 //定位鼠标点//
			 int Height = this->MatchPictureBox->Height;//512
			 int Width = this->MatchPictureBox->Width;//611
			 short CircleCenterXY = MatchWidth/2;
			 /*int Lin_MousePositionX,Lin_MousePositionY;*/
			 Lin_MousePositionX = e->X;
			 Lin_MousePositionY = e->Y;
			 Lin_MatchMousePositionX = Lin_MousePositionX*MatchWidth/MatchPictureBox->Width;
			 Lin_MatchMousePositionY = Lin_MousePositionY*MatchHeight/MatchPictureBox->Height;
			 if ((Lin_MousePositionX < Width)&&(Lin_MousePositionY<Height ))
			 {
				 int R =System::Math::Sqrt((Lin_MatchMousePositionX -CircleCenterXY)*(Lin_MatchMousePositionX -CircleCenterXY)+ 
					     (Lin_MatchMousePositionY -CircleCenterXY)*(Lin_MatchMousePositionY -CircleCenterXY));
				 
				 double MyAngle = System::Math::Atan((CircleCenterXY-Lin_MatchMousePositionY)/(double)(Lin_MatchMousePositionX-CircleCenterXY));
				 MyAngle = MyAngle*180/3.1415;
				 if (Lin_MatchMousePositionX <= CircleCenterXY)
				 {
					 MyAngle+=180;
				 }
				 if (MyAngle<0)
				 {
					 MyAngle+=360;
				 }
				 if (MyAngle>=360)
				 {
					 MyAngle-=360;
				 }
				 
				 int Pos = R - Lin_InnerCircleR;

				 if (Pos>=0&&Pos<=LineCount)
				 {
					 array<unsigned short>^ HistoryTime = gcnew array<unsigned short>(10*5);
					  whu_GetHistoryTemp(MyAngle,Pos,Lin_MouseClickHistoryTemp,HistoryTime,10);//根据弧度和弧长，得到历史温度//

				 /* String ^HistoryTemp = String::Format("角度：{0:##0.0} 弧度：{1:##0} 温度：{2:##0.0}，{3:##0.0}，{4:##0.0}，{5:##0.0}，{6:##0.0}，{7:##0.0}，{8:##0.0}，{9:##0.0}，{10:##0.0}，{11:##0.0} ",
				 MyAngle,R,Lin_MouseClickHistoryTemp[0],Lin_MouseClickHistoryTemp[1],Lin_MouseClickHistoryTemp[2],Lin_MouseClickHistoryTemp[3],Lin_MouseClickHistoryTemp[4],
				 Lin_MouseClickHistoryTemp[5],Lin_MouseClickHistoryTemp[6],Lin_MouseClickHistoryTemp[7],Lin_MouseClickHistoryTemp[8],Lin_MouseClickHistoryTemp[9]);*/
				 String ^HistoryTemp = String::Format("角度：{0:##0.0} 弧度：{1:##0} 温度：{2:##0.0}，{3:##0.0}，{4:##0.0}，{5:##0.0}，{6:##0.0} ",
					 MyAngle,R,Lin_MouseClickHistoryTemp[0],Lin_MouseClickHistoryTemp[1],Lin_MouseClickHistoryTemp[2],Lin_MouseClickHistoryTemp[3],Lin_MouseClickHistoryTemp[4]);
				 //label20->Text = HistoryTemp;
				 Lin_SetForm->Show();
				 Lin_SetForm->TopMost = true;
				 Lin_SetForm->Location = System::Drawing::Point(Lin_MousePositionX,Lin_MousePositionY);
				 for (int i = 0;i<10;i++)
				 {
					 Lin_SetForm->Lin_MouseClickHistoryTemp[i] = Lin_MouseClickHistoryTemp[i];
					 for (int j=0;j<5;j++)
					 {
						 Lin_SetForm->HistoryTime[i*5+j] = HistoryTime[i*5+j];
					 }
					 
				 }
				 }else{

					 Lin_SetForm->Hide();
				 }
				/* int pos = Lin_MatchMousePositionY*MatchWidth+Lin_MatchMousePositionX;*/


			 }

			


		 }

private: System::Void MyTimerReadDB_Tick(System::Object^  sender, System::EventArgs^  e) {
			 //array<short>^ m_DestData = gcnew array<short>(LineCount+1+1);
			 //for (int i=0;i<360*AngleAccuracy;i++)
			 //{
				// double m_angle = i/(double)AngleAccuracy;
				// if (Lin_BConnectedToLocalDB)
				// {
				//	 if (whu_ReadDataFromDB(m_angle,m_DestData))
				//	 {
				//		 int pos = i*(1+1+LineCount);
				//		 System::Buffer::BlockCopy(m_DestData,0,Lin_AngleWithValues,pos*sizeof(short),m_DestData->Length*sizeof(short));
				//	 }
				//	 //刚开始，未连接数据库，读取频率设置为100ms，等连上数据库时，先把读取数据，再把频率设置为60000.这样保证点击连接按钮，能马上得到数据//
				//	 MyTimerReadDB->Interval = 60000;
				// }

				// 
			 //}
	

		 }
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
			 if (Lin_BConnectedToLocalDB)
			 {
				 Lin_LocalConnSql->Close();//关闭数据库
			 }
			 if (Lin_BConnectedToRemoteDB)
			 {
				 Lin_RemoteConnSql->Close();
			 }
			 this->Close();
		 }
private: System::Void MyTimerSynDB_Tick(System::Object^  sender, System::EventArgs^  e) {

		 }
private: System::Void buttonStart_Click(System::Object^  sender, System::EventArgs^  e) {
			 Lin_CurrentAngle = 0;
			 String ^ip = m_SetForm->Lin_IP;
			 int port = 1110; 
			 Lin_SendSocket = gcnew Socket(AddressFamily::InterNetwork, SocketType::Dgram, ProtocolType::Udp);
			 Lin_iPEndPoint = gcnew IPEndPoint(IPAddress::Parse(ip->ToString()), port);
			 Lin_BSendAngle = false;

			 if (buttonStart->Text == "停止")
			 {
				 buttonStart->Text = "开始";
				 String ^msg = "停止";	 
				 Encoding ^m_Encoding = Encoding::Unicode;
				 Lin_SendSocket->SendTo(m_Encoding->GetBytes(msg), Lin_iPEndPoint);
				 Lin_BSendAngle = false;
				 button1->Enabled = false;
				 button6->Enabled = false;
			 }else if (buttonStart->Text == "开始")
			 {
				 buttonStart->Text = "停止";
				 String ^msg = "开始";	 
				 Encoding ^m_Encoding = Encoding::Unicode;
				 Lin_SendSocket->SendTo(m_Encoding->GetBytes(msg), Lin_iPEndPoint);
				 Lin_BSendAngle = true;
				 button1->Enabled = true;
				 button6->Enabled = true;
			 }
			 

			 
		 }
private: System::Void button1_Click_1(System::Object^  sender, System::EventArgs^  e) {
			 MyTimerSendAngle->Interval -=200;
			 if (MyTimerSendAngle->Interval<400)
			 {
				 button1->Enabled = false;
			 }
			 
		 }
private: System::Void button6_Click(System::Object^  sender, System::EventArgs^  e) {

			MyTimerSendAngle->Interval +=200;
			button1->Enabled = true;

		 }
private: System::Void MyTimerSendAngle_Tick(System::Object^  sender, System::EventArgs^  e) {
			if (Lin_BSendAngle)
			{
				
				label19->Text = String::Format("当前角度为：{0:##0.0}°",Lin_CurrentAngle/(double)AngleAccuracy);
				String ^msg = String::Format("{0:##0}",Lin_CurrentAngle);
				int m_angle  = System::Int32::Parse(msg);
				Encoding ^m_Encoding = Encoding::Unicode;
				Lin_SendSocket->SendTo(m_Encoding->GetBytes(msg), Lin_iPEndPoint);

				if (Lin_CurrentAngle < 360*AngleAccuracy)
				{
					Lin_CurrentAngle++;
				}else
				{
					Lin_CurrentAngle = 0;
				}
			}
			

		 }
private: System::Void buttonSwitch_Click(System::Object^  sender, System::EventArgs^  e) {
			
		 }
private: System::Void MyTimerSynData_Tick(System::Object^  sender, System::EventArgs^  e) {

			 //这个计时器主要是为了父窗口和设置子窗口之间的通信
			 TempMinTrackBarValue = m_SetForm->TempMinTrackBarValue;
			 TempRangTrackBarValue = m_SetForm->TempRangTrackBarValue;
			 if (m_SetForm->Lin_Saved)
			 {
				 m_SetForm->Lin_Saved = false;
				 if ((Lin_LocalDataSource != m_SetForm->Lin_LocalDataSource)|(Lin_LocalDataBaseName !=m_SetForm->Lin_LocalDataBaseName)|!Lin_BConnectedToLocalDB)
				 {
					 Lin_LocalDataSource = m_SetForm->Lin_LocalDataSource;
					 Lin_LocalDataBaseName = m_SetForm->Lin_LocalDataBaseName;
					 //开始重新连接本地数据库
					whu_DisConnectToLocalDB();
					whu_ConnectToLocalDB(Lin_LocalDataSource,Lin_LocalDataBaseName); 
				 }
				 if ((Lin_RemoteDataSource != m_SetForm->Lin_RemoteDataSource)|
					 (Lin_RemoteDataBaseName != m_SetForm->Lin_RemoteDataBaseName)|
					 (Lin_RemoteUserName != m_SetForm->Lin_RemoteUserName)|
					 (Lin_RemoteUserPwd != m_SetForm->Lin_RemoteUserPwd)|!Lin_BConnectedToRemoteDB)
				 {
					 Lin_RemoteDataSource = m_SetForm->Lin_RemoteDataSource;
					 Lin_RemoteDataBaseName = m_SetForm->Lin_RemoteDataBaseName;
					 Lin_RemoteUserName = m_SetForm->Lin_RemoteUserName;
					 Lin_RemoteUserPwd = m_SetForm->Lin_RemoteUserPwd;
					 whu_DisConnectToRemoteDB();
					 whu_ConnectToRemoteDB(Lin_RemoteDataSource,Lin_RemoteDataBaseName,Lin_RemoteUserName,Lin_RemoteUserPwd);
					 //开始重新连接远程数据库
				 }
				 
			 }
		 }
};


}
