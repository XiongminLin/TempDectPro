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
			DayNum = 10;
			Lin_MouseClickHistoryTemp = gcnew array<double>(DayNum);
			HistoryTime = gcnew array<unsigned short>(DayNum*5);
			for (int i=0;i<DayNum;i++)
			{
				Lin_MouseClickHistoryTemp[i] = 0;
			}
			for (int i=0;i<DayNum*5;i++)
			{
				HistoryTime[i] = 0;
			}
			//int iSysMenu;
			//const int MF_BYCOMMAND = 0x400; //0x400-关闭
			//GetSystemMenu(this->Handle.ToInt32(),0);
			//return RemoveMenu(iSysMenu, 6, MF_BYCOMMAND);
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

	protected: 





















	private: System::Windows::Forms::Label^  label11;
	private: System::ComponentModel::IContainer^  components;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  chart1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>

	public:
		array<double>^ Lin_MouseClickHistoryTemp;
		array<unsigned short>^ HistoryTime;
		int DayNum;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea2 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^  legend2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^  series3 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series4 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->chart1))->BeginInit();
			this->SuspendLayout();
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->BackColor = System::Drawing::Color::White;
			this->label11->Location = System::Drawing::Point(305, 13);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(47, 12);
			this->label11->TabIndex = 6;
			this->label11->Text = L"label11";
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Tick += gcnew System::EventHandler(this, &SetForm::timer1_Tick);
			// 
			// chart1
			// 
			chartArea2->AxisY->Minimum = 0;
			chartArea2->Name = L"ChartArea1";
			this->chart1->ChartAreas->Add(chartArea2);
			legend2->Name = L"Legend1";
			this->chart1->Legends->Add(legend2);
			this->chart1->Location = System::Drawing::Point(12, 46);
			this->chart1->Name = L"chart1";
			series3->ChartArea = L"ChartArea1";
			series3->Legend = L"Legend1";
			series3->Name = L"温度";
			series4->BorderWidth = 2;
			series4->ChartArea = L"ChartArea1";
			series4->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series4->Color = System::Drawing::Color::Red;
			series4->Legend = L"Legend1";
			series4->MarkerBorderColor = System::Drawing::Color::White;
			series4->Name = L"警戒线";
			this->chart1->Series->Add(series3);
			this->chart1->Series->Add(series4);
			this->chart1->Size = System::Drawing::Size(442, 275);
			this->chart1->TabIndex = 7;
			this->chart1->Text = L"  ";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::SystemColors::ControlDark;
			this->label1->Font = (gcnew System::Drawing::Font(L"SimSun", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->label1->Location = System::Drawing::Point(2, 13);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(142, 19);
			this->label1->TabIndex = 8;
			this->label1->Text = L"历史温度图表：";
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"SimSun", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->button1->Location = System::Drawing::Point(483, 251);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 36);
			this->button1->TabIndex = 9;
			this->button1->Text = L"打印";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &SetForm::button1_Click_1);
			// 
			// button2
			// 
			this->button2->Font = (gcnew System::Drawing::Font(L"SimSun", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(134)));
			this->button2->Location = System::Drawing::Point(483, 302);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 36);
			this->button2->TabIndex = 10;
			this->button2->Text = L"退出";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &SetForm::button2_Click);
			// 
			// SetForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ControlDark;
			this->ClientSize = System::Drawing::Size(586, 366);
			this->ControlBox = false;
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->chart1);
			this->Controls->Add(this->label11);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Name = L"SetForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"历史温度查询";
			this->TransparencyKey = System::Drawing::Color::Black;
			this->Load += gcnew System::EventHandler(this, &SetForm::SetForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->chart1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void SetForm_Load(System::Object^  sender, System::EventArgs^  e) {
			 }
	private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
				 this->Close();
			 }
private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {

			  String ^HistoryTemp = String::Format("温度：{0:##0.0} {1:##0} {2:##0.0}，{3:##0.0}，{4:##0.0}，{5:##0.0}，{6:##0.0}，{7:##0.0}，{8:##0.0}，{9:##0.0} ",
				Lin_MouseClickHistoryTemp[0],Lin_MouseClickHistoryTemp[1],Lin_MouseClickHistoryTemp[2],Lin_MouseClickHistoryTemp[3],Lin_MouseClickHistoryTemp[4],
				 Lin_MouseClickHistoryTemp[5],Lin_MouseClickHistoryTemp[6],Lin_MouseClickHistoryTemp[7],Lin_MouseClickHistoryTemp[8],Lin_MouseClickHistoryTemp[9]);
				 //label11->Text = HistoryTemp;
				 String^ m_str = String::Format("从{0:##0}年{1:##0}月{2:##0}日{3:##0}时{4:##0}分 至 {5:##0}年{6:##0}月{7:##0}日{8:##0}时{9:##0}分",
													HistoryTime[45],HistoryTime[46],HistoryTime[47],HistoryTime[48],HistoryTime[49],HistoryTime[0],HistoryTime[1],HistoryTime[2],HistoryTime[3],HistoryTime[4]);
				 label1->Text = "历史温度图表：" + m_str;
				 //360个角度的温度最高值显示//
				 this->chart1->Series["温度"]->Points->Clear();
				 this->chart1->Series["警戒线"]->Points->Clear();
				 for (int i=9,j=0;i>=0;i--,j++)
				 {
					 this->chart1->Series["温度"]->Points->AddXY(j,Lin_MouseClickHistoryTemp[i]);
					 this->chart1->Series["警戒线"]->Points->AddXY(j,70);//警戒线还需传递参数过来
				 }

		 }
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
			 
		 }
private: System::Void button1_Click_1(System::Object^  sender, System::EventArgs^  e) {
			 
		 }
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
			this->Hide();
		 }
};
}
