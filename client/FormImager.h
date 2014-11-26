#pragma once

#include "IPCSample.h"
#include "IPC2.h"


namespace IPCSample 
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Zusammenfassung f黵 FormImager
	///
	/// Warnung: Wenn Sie den Namen dieser Klasse 鋘dern, m黶sen Sie auch
	///          die Ressourcendateiname-Eigenschaft f黵 das Tool zur Kompilierung verwalteter Ressourcen 鋘dern,
	///          das allen RESX-Dateien zugewiesen ist, von denen diese Klasse abh鋘gt.
	///          Anderenfalls k鰊nen die Designer nicht korrekt mit den lokalisierten Ressourcen
	///          arbeiten, die diesem Formular zugewiesen sind.
	/// </summary>

	public ref class FormImager : public System::Windows::Forms::Form
	{
	//public class PassDataWinFormEventArgs:EventArgs
	//	{
	//		public PassDataWinFormEventArgs()
	//		{
	//			//
	//		}
	//		public PassDataWinFormEventArgs(bool m_show)
	//		{
	//			this->show = m_show;
	//		}
	//		bool show;


	//	};
	public:	FormImager(HWND hostHandle, IPC^ Ipc, int imagerIndex, String ^instanceName);

	private: System::Windows::Forms::GroupBox^  groupBoxVideo;
	private: System::Windows::Forms::GroupBox^  groupBoxMeasureAreas;
	private: System::Windows::Forms::TextBox^  textBoxInstanceName;
	private: System::Windows::Forms::Label^  labelInstanceName;
	private: System::Windows::Forms::Button^  buttonKill;
	private: System::Windows::Forms::Button^  buttonFlagRenew;
	private: System::Windows::Forms::ProgressBar^  progressBarInit;


	private: System::Windows::Forms::Panel^  panelImager;






	private: System::Windows::Forms::Label^  MousePointTempLabe;
	private: System::Windows::Forms::Label^  RectTempLabel;


	private: System::ComponentModel::BackgroundWorker^  backgroundWorker1;


	private: System::Windows::Forms::Label^  label1;















	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		~FormImager();
		//void GetBitmap(Bitmap^ Bmp, array<short>^values);
		void GetBitmap_Limits(array<short>^Values, short *min, short *max);

		short FrameWidth, FrameHeight, FrameDepth;
		double FrameRatio;
		int FrameSize;
		IPC^ ipc;
		
		int FrameCounter0, FrameCounter1, LastFrameCounter, FC0, FC1;
		System::DateTime LastFrameTime;
		System::Collections::ArrayList^ List;
		
		Device Dev;
		
		bool AppendLog;
		int ImagerIndex;

		array<Byte>^rgbValues;
		//array<short>^Values;
		array<double>^ whu_AllTemValues;
		
		Point m_MaxTempValuePoint;
		bool whu_BShowMousePositionTemp; 
		bool whu_BSHowRectangle;
		bool whu_BKeepRectangle;
		System::Drawing::Pen^ myPen;
		System::Drawing::Pen^ myPen2;
		System::Drawing::Rectangle ^whu_SelectRectangle;
		System::Drawing::Brush ^myBrush;
		int MainTimerDivider;
		bool Painted;
		USHORT MeasureAreaCount;
		Drawing::Size Margin;

		IPC::delOnServerStopped^		onServerStopped;
		IPC::delOnFrameInit^			onFrameInit;
		IPC::delOnNewFrameEx^			onNewFrameEx;
		IPC::delOnInitCompleted^		onInitCompleted;
		IPC::delOnConfigChanged^		onConfigChanged;

		//define by shelmylin//

		short TempTrackBarValue;



	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::PictureBox^  pictureBox;
	private: System::Windows::Forms::Timer^  timer2;
	private: System::ComponentModel::IContainer^  components;
	private:
	public: double m_MaxTempValue;
			bool ipcInitialized;
			bool Connected;
			short TempMinTrackBarValue;
			short TempRangTrackBarValue;
			double m_AverageTempValue;
			Bitmap^ bmp;
			void GetBitmap(Bitmap^ Bmp, array<short>^values);
			array<short>^Values;
			void SaveImage();
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>
	public :
		delegate void PassDataBetweenFormHandler(bool show);
	public :
		event PassDataBetweenFormHandler ^PassDataBetweenForm;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode f黵 die Designerunterst黷zung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor ge鋘dert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(FormImager::typeid));
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->pictureBox = (gcnew System::Windows::Forms::PictureBox());
			this->timer2 = (gcnew System::Windows::Forms::Timer(this->components));
			this->buttonFlagRenew = (gcnew System::Windows::Forms::Button());
			this->groupBoxVideo = (gcnew System::Windows::Forms::GroupBox());
			this->groupBoxMeasureAreas = (gcnew System::Windows::Forms::GroupBox());
			this->textBoxInstanceName = (gcnew System::Windows::Forms::TextBox());
			this->labelInstanceName = (gcnew System::Windows::Forms::Label());
			this->buttonKill = (gcnew System::Windows::Forms::Button());
			this->progressBarInit = (gcnew System::Windows::Forms::ProgressBar());
			this->panelImager = (gcnew System::Windows::Forms::Panel());
			this->RectTempLabel = (gcnew System::Windows::Forms::Label());
			this->MousePointTempLabe = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox))->BeginInit();
			this->groupBoxVideo->SuspendLayout();
			this->panelImager->SuspendLayout();
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &FormImager::timer1_Tick);
			// 
			// pictureBox
			// 
			this->pictureBox->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pictureBox->Location = System::Drawing::Point(3, 17);
			this->pictureBox->Name = L"pictureBox";
			this->pictureBox->Size = System::Drawing::Size(194, 109);
			this->pictureBox->TabIndex = 8;
			this->pictureBox->TabStop = false;
			this->pictureBox->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &FormImager::pictureBox_Paint);
			this->pictureBox->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &FormImager::pictureBox_MouseClick);
			this->pictureBox->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &FormImager::pictureBox_MouseDown);
			this->pictureBox->MouseLeave += gcnew System::EventHandler(this, &FormImager::pictureBox_MouseLeave);
			this->pictureBox->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &FormImager::pictureBox_MouseMove);
			this->pictureBox->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &FormImager::pictureBox_MouseUp);
			// 
			// timer2
			// 
			this->timer2->Enabled = true;
			this->timer2->Interval = 1000;
			this->timer2->Tick += gcnew System::EventHandler(this, &FormImager::timer2_Tick);
			// 
			// buttonFlagRenew
			// 
			this->buttonFlagRenew->Location = System::Drawing::Point(213, 238);
			this->buttonFlagRenew->Name = L"buttonFlagRenew";
			this->buttonFlagRenew->Size = System::Drawing::Size(73, 21);
			this->buttonFlagRenew->TabIndex = 35;
			this->buttonFlagRenew->Text = L"Flag";
			this->buttonFlagRenew->UseVisualStyleBackColor = true;
			this->buttonFlagRenew->Visible = false;
			this->buttonFlagRenew->Click += gcnew System::EventHandler(this, &FormImager::buttonFlagRenew_Click);
			// 
			// groupBoxVideo
			// 
			this->groupBoxVideo->Controls->Add(this->pictureBox);
			this->groupBoxVideo->Location = System::Drawing::Point(15, 32);
			this->groupBoxVideo->Name = L"groupBoxVideo";
			this->groupBoxVideo->Size = System::Drawing::Size(200, 129);
			this->groupBoxVideo->TabIndex = 66;
			this->groupBoxVideo->TabStop = false;
			// 
			// groupBoxMeasureAreas
			// 
			this->groupBoxMeasureAreas->Location = System::Drawing::Point(15, 303);
			this->groupBoxMeasureAreas->Name = L"groupBoxMeasureAreas";
			this->groupBoxMeasureAreas->Size = System::Drawing::Size(116, 28);
			this->groupBoxMeasureAreas->TabIndex = 67;
			this->groupBoxMeasureAreas->TabStop = false;
			this->groupBoxMeasureAreas->Text = L" 当前最高温度";
			// 
			// textBoxInstanceName
			// 
			this->textBoxInstanceName->Location = System::Drawing::Point(116, 183);
			this->textBoxInstanceName->Name = L"textBoxInstanceName";
			this->textBoxInstanceName->Size = System::Drawing::Size(168, 21);
			this->textBoxInstanceName->TabIndex = 71;
			this->textBoxInstanceName->Visible = false;
			this->textBoxInstanceName->TextChanged += gcnew System::EventHandler(this, &FormImager::textBoxInstanceName_TextChanged);
			// 
			// labelInstanceName
			// 
			this->labelInstanceName->AutoSize = true;
			this->labelInstanceName->Location = System::Drawing::Point(12, 189);
			this->labelInstanceName->Name = L"labelInstanceName";
			this->labelInstanceName->Size = System::Drawing::Size(89, 12);
			this->labelInstanceName->TabIndex = 70;
			this->labelInstanceName->Text = L"Instance name:";
			this->labelInstanceName->Visible = false;
			// 
			// buttonKill
			// 
			this->buttonKill->Location = System::Drawing::Point(172, 207);
			this->buttonKill->Name = L"buttonKill";
			this->buttonKill->Size = System::Drawing::Size(93, 25);
			this->buttonKill->TabIndex = 72;
			this->buttonKill->Text = L"Close Host-Appl.";
			this->buttonKill->UseVisualStyleBackColor = true;
			this->buttonKill->Visible = false;
			this->buttonKill->Click += gcnew System::EventHandler(this, &FormImager::buttonKill_Click);
			// 
			// progressBarInit
			// 
			this->progressBarInit->Location = System::Drawing::Point(93, 6);
			this->progressBarInit->Name = L"progressBarInit";
			this->progressBarInit->Size = System::Drawing::Size(172, 21);
			this->progressBarInit->TabIndex = 74;
			this->progressBarInit->Visible = false;
			// 
			// panelImager
			// 
			this->panelImager->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panelImager->Controls->Add(this->RectTempLabel);
			this->panelImager->Controls->Add(this->MousePointTempLabe);
			this->panelImager->Controls->Add(this->labelInstanceName);
			this->panelImager->Controls->Add(this->buttonFlagRenew);
			this->panelImager->Controls->Add(this->label1);
			this->panelImager->Controls->Add(this->progressBarInit);
			this->panelImager->Controls->Add(this->groupBoxVideo);
			this->panelImager->Controls->Add(this->buttonKill);
			this->panelImager->Controls->Add(this->groupBoxMeasureAreas);
			this->panelImager->Controls->Add(this->textBoxInstanceName);
			this->panelImager->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panelImager->Location = System::Drawing::Point(0, 0);
			this->panelImager->Name = L"panelImager";
			this->panelImager->Size = System::Drawing::Size(312, 382);
			this->panelImager->TabIndex = 83;
			this->panelImager->Visible = false;
			// 
			// RectTempLabel
			// 
			this->RectTempLabel->AutoSize = true;
			this->RectTempLabel->BackColor = System::Drawing::Color::Transparent;
			this->RectTempLabel->Location = System::Drawing::Point(221, 105);
			this->RectTempLabel->Name = L"RectTempLabel";
			this->RectTempLabel->Size = System::Drawing::Size(65, 12);
			this->RectTempLabel->TabIndex = 88;
			this->RectTempLabel->Text = L"矩形框温度";
			this->RectTempLabel->Visible = false;
			// 
			// MousePointTempLabe
			// 
			this->MousePointTempLabe->AutoSize = true;
			this->MousePointTempLabe->BackColor = System::Drawing::Color::Transparent;
			this->MousePointTempLabe->Location = System::Drawing::Point(221, 81);
			this->MousePointTempLabe->Name = L"MousePointTempLabe";
			this->MousePointTempLabe->Size = System::Drawing::Size(65, 12);
			this->MousePointTempLabe->TabIndex = 87;
			this->MousePointTempLabe->Text = L"鼠标点温度";
			this->MousePointTempLabe->Visible = false;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(19, 15);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(23, 12);
			this->label1->TabIndex = 0;
			this->label1->Text = L"---";
			// 
			// FormImager
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(312, 382);
			this->Controls->Add(this->panelImager);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"FormImager";
			this->Text = L"FormImager";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &FormImager::FormImager_FormClosing);
			this->Load += gcnew System::EventHandler(this, &FormImager::FormImager_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox))->EndInit();
			this->groupBoxVideo->ResumeLayout(false);
			this->panelImager->ResumeLayout(false);
			this->panelImager->PerformLayout();
			this->ResumeLayout(false);

		} 
#pragma endregion
protected: 
	void AppInit(void);
	void AppExit(void);
	void InitIPC(void);
	void ReleaseIPC(void) ;
	HRESULT MainTimer100ms(void);
	HRESULT MainTimer1000ms(void);
	void GetSoftwareInfo(void);
	void GetDeviceInfo(void);
	void GetDeviceSetup(void);
	void RenewFlag(void);
	void Init(int frameWidth, int frameHeight, int frameDepth); 
	void InitMeasureAreas(void);
	void UpdateSize(void);

	void whu_GetRGBValue(short m_value ,Byte *m_RGBValue);

	HRESULT NewFrame(short *ImgBuf, int frameCounter); 

	HRESULT OnServerStopped(int reason);
	HRESULT OnFrameInit(int frameWidth, int frameHeight, int frameDepth);
	HRESULT OnNewFrameEx(void * pBuffer, FrameMetadata *pMetadata);
	HRESULT OnNewFrame(char * pBuffer, int frameCounter);
	HRESULT OnInitCompleted(void);
	HRESULT OnConfigChanged(long reserved);

private: System::Void FormImager_Load(System::Object^  sender, System::EventArgs^  e) {AppInit(); } 
private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e)
		 {
			MainTimerDivider++;
			MainTimer100ms();
			if(!(MainTimerDivider%20)) MainTimer1000ms();
		 }
private: System::Void FormImager_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) { AppExit(); }
private: System::Void timer2_Tick(System::Object^  sender, System::EventArgs^  e)
		 {	
			 if (!ipcInitialized){ 
				 InitIPC();
			 }else{
				 //Graphics ^g = this->TempPictureBox->CreateGraphics();
				 //static int pos = 0;
				 //static int data[289];
				 //if (pos==289)
				 //{
					// pos = 0;
					// this->TempPictureBox->ImageLocation = L"D:\\3.bmp";

				 //}else
				 //{
					// data[pos] = (int)m_MaxTempValue;
					// pos++;
	
					// for (int i=0;i<pos;i++)
					// {
					//	 System::Drawing::Rectangle ^Rectangle = gcnew System::Drawing::Rectangle(i,data[i],1,1);
					//	 Point m_point1,m_point2;
					//	 m_point1.X = 0;
					//	 m_point1.Y = 0;
					//	 g->DrawRectangle(myPen2,*Rectangle);
					//	// g->DrawLine(myPen2,)
					// } 

				 //}

				 //this->chart1->DataSource = GetData.GetChartData();
				 //this->chart1->Series["ChartArea1"]->XValueMember ="home";
				// this->chart1->Series["ChartArea1"]->YValueMembers ="num1";
				 
				 //踢掉前面的数据//
				 ////假设使用的数据源是List<int>
				 //List<int> source = new List<int>();
				 //int maxCount = 100;

				 //private void AddItem(int value)
				 //{
					// if(source.Count>maxCount) source.RomoveAt(0);
					// source.Add(value);
				 //}

				 //this->chart1->Series->Points->AddY(20);
				// this->chart1->series1->Points->AddY(20);
				 //Series series = new Series("Spline");
				 //series.ChartType = SeriesChartType.Spline;
				 //series.BorderWidth = 3;
				 //series.ShadowOffset = 2;
				 //this->chart1->Series["最高温度"]->Points->AddY(m_MaxTempValue);
				 
			 }
			 
			 //
			

			 
		 }
		 
private: System::Void TempPictureBox_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) 
		 {
			
			
		 }
private: System::Void pictureBox_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) 
		 {  
			 
			 e->Graphics->DrawImage( bmp, 0, 0 );
			 //Brush ^m_brush = new SolidBrush(Color.Blue);
			/* System::Drawing::Pen^ myPen;
			 myPen = gcnew System::Drawing::Pen(System::Drawing::Color::Tomato);
			 System::Drawing::Rectangle ^myRectangle;
			 myRectangle = gcnew System::Drawing::Rectangle(20,20,20,20);*/
			 e->Graphics->DrawRectangle(myPen,*whu_SelectRectangle);
			 if (whu_BKeepRectangle&&(whu_SelectRectangle->Left != whu_SelectRectangle->Right)&&(whu_SelectRectangle->Top!=whu_SelectRectangle->Bottom))
			 {
				 double m_TempValue = 0;
				 double m_All = 0;
				 int m_Count = 0;
				 for (int i=whu_SelectRectangle->Top;i<whu_SelectRectangle->Height+whu_SelectRectangle->Top;i++ )
				 {
					 for (int j=whu_SelectRectangle->Left;j<whu_SelectRectangle->Width+whu_SelectRectangle->Left;j++)
					 {
						 int pos = i*FrameWidth + j;
						 m_All = m_All + whu_AllTemValues[pos];
						 m_Count ++;
					 } 
				 }
				 //m_TempValue = m_All/(whu_SelectRectangle->Height*whu_SelectRectangle->Width);
				 m_TempValue = m_All/m_Count;
				 String ^RectTemp = String::Format("平均温度：{0:##0.0}°C", m_TempValue);
				 RectTempLabel->Text = RectTemp;
				 Point picLocation = this->groupBoxVideo->Location;
				 RectTempLabel->Location = System::Drawing::Point(whu_SelectRectangle->Left+picLocation.X,whu_SelectRectangle->Top+picLocation.Y);
				 RectTempLabel->Show();
				  
				 //e->Graphics->DrawString(RectTemp,MousePointTempLabe->Font,myBrush,(int)(whu_SelectRectangle->Right-whu_SelectRectangle->Left)/2+whu_SelectRectangle->Left,(int)(whu_SelectRectangle->Bottom-whu_SelectRectangle->Top)/2+whu_SelectRectangle->Top);
			 }
			 
			 //温度最高点
			System::Drawing::Rectangle ^m_MaxTempValuePointRect = gcnew System::Drawing::Rectangle(m_MaxTempValuePoint.X,m_MaxTempValuePoint.Y,10,10);
			e->Graphics->DrawRectangle(myPen,*m_MaxTempValuePointRect);
			//校准
			//String ^maxtempposition = String::Format("最高温度坐标:X = {0:##0.0} Y = {1:##0.0}",m_MaxTempValuePoint.X,m_MaxTempValuePoint.Y);
			//HighTempPositionLabel->Text = maxtempposition;
			
		 }
private: System::Void pictureBox_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs ^  e) 
		 {
			 int Height = this->pictureBox->Height;
			 int Width = this->pictureBox->Width;
			 int m_MousePositionX,m_MousePositionY;
			 if ((e->X < Width)&&(e->Y<Height ))
			 {
				 MousePointTempLabe->Show();
				 m_MousePositionX = e->X;
				 m_MousePositionY = e->Y;
				 int pos = m_MousePositionY*FrameWidth+m_MousePositionX;
				 if (pos<FrameSize&&m_MousePositionX<FrameWidth&&m_MousePositionY<FrameHeight&&whu_BShowMousePositionTemp)
				 {
					 double m_TempValue = whu_AllTemValues[pos];
					 this->MousePointTempLabe->Text = String::Format("{0:##0.0}°C",m_TempValue);
					 
					 //移动温度信息至鼠标点//
					 Point picLocation = this->groupBoxVideo->Location;
					 //this->MousePointTempLabe->Location = System::Drawing::Point(m_MousePositionX , m_MousePositionY );
					 this->MousePointTempLabe->Location = System::Drawing::Point(m_MousePositionX + picLocation.X, m_MousePositionY + picLocation.Y);
					
				 }
				 if (whu_BSHowRectangle&&!whu_BKeepRectangle)//获得鼠标选定区域// 
				 {
					 whu_SelectRectangle = gcnew System::Drawing::Rectangle(whu_SelectRectangle->Left,whu_SelectRectangle->Top,e->X-whu_SelectRectangle->X,e->Y-whu_SelectRectangle->Y);
				 }

			 }

			 
		 }
private: System::Void pictureBox_MouseLeave(System::Object^  sender, System::EventArgs ^  e) 
		 {
			 MousePointTempLabe->Hide();
			 RectTempLabel->Hide();
		 }
private: System::Void pictureBox_MouseDown(System::Object^ sender,System::Windows::Forms::MouseEventArgs ^  e){
			 whu_SelectRectangle = gcnew System::Drawing::Rectangle(e->X,e->Y,0,0);
			 whu_BSHowRectangle = true;
			 whu_BKeepRectangle = false;
			 RectTempLabel->Hide();
		 }
private: System::Void pictureBox_MouseUp(System::Object^ sender,System::Windows::Forms::MouseEventArgs ^  e)
		 {
			 whu_SelectRectangle = gcnew System::Drawing::Rectangle(whu_SelectRectangle->Left,whu_SelectRectangle->Top,e->X-whu_SelectRectangle->Left,e->Y-whu_SelectRectangle->Top);
			 //if ((whu_SelectRectangle->Left != whu_SelectRectangle->Right)&&(whu_SelectRectangle->Top!=whu_SelectRectangle->Bottom))
			 //{
				 whu_BSHowRectangle = true;
				 whu_BKeepRectangle = true;
			 //}
			 
		 }
private: System::Void pictureBox_MouseClick(System::Object ^sender,System::Windows::Forms::MouseEventArgs ^  e)
		 {
			 //whu_BSHowRectangle = false;
		 }
private: System::Void buttonFlagRenew_Click(System::Object^  sender, System::EventArgs^  e) { RenewFlag();	 }
private: System::Void buttonInit_Click(System::Object^  sender, System::EventArgs^  e){};
 
private: System::Void textBoxInstanceName_TextChanged(System::Object^  sender, System::EventArgs^  e) ;
private: System::Void buttonKill_Click(System::Object^  sender, System::EventArgs^  e) { if(ipc) ipc->CloseApplication(ImagerIndex); };
private: System::Void checkBoxBuffered_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {	ReleaseIPC(); };

};

} 

