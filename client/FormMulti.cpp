#include "stdafx.h"
#include "FormMulti.h"



namespace IPCSample {
FormMulti::FormMulti(HWND hostHandle)
{
	InitializeComponent();
	formsImager = gcnew array<FormImager^>(IMAGERCOUNT);
	
	ipc = gcnew IPC(IMAGERCOUNT);
	m_MaxTempValue = -99;
	m_AlarmTemp = 70;
	this->SuspendLayout();
	
	for(int i=0; i<IMAGERCOUNT; i++)
	{
		//formsImager[i] = gcnew FormImager(hostHandle, ipc, i, "Instance " + (i+1).ToString());
		formsImager[i] = gcnew FormImager(hostHandle, ipc, i, "camera"+(i+1).ToString());//这里修改name以初始化IPC
		formsImager[i]->Location = Drawing::Point(i*300+5, 5);
		formsImager[i]->Name = "FormImager" + (i+1).ToString();
		formsImager[i]->Visible = true;
		formsImager[i]->Resize += gcnew System::EventHandler(this, &FormMulti::FormImager_OnResize);
		Controls->Add(formsImager[i]);
		//formsImager[i]->PassDataBetweenForm += gcnew FormImager->PassDataBetweenFormHandler(true);//????有问题！！！我想实现，子窗口有新图像，通知父窗口更新//
		//上面的问题不知道怎么解决，但图片刷新问题已经解决好,忘记把timer开启了!!!//
	}
	this->ResumeLayout();
	this->PerformLayout();
	TempMinTrackBarValue = trackBar1->Value - 20;
	TempRangTrackBarValue = trackBar2->Value;
	myBlackPen = gcnew System::Drawing::Pen(System::Drawing::Color::Black);//矩形框颜色
	myWhitePen = gcnew System::Drawing::Pen(System::Drawing::Color::White);//矩形框颜色
	myBulePen = gcnew System::Drawing::Pen(System::Drawing::Color::Blue);//矩形框颜色
	myRedPen = gcnew System::Drawing::Pen(System::Drawing::Color::Red);//矩形框颜色
	myBrush = gcnew SolidBrush(System::Drawing::Color::White);//平均区域温度颜色
	myBigFront = gcnew System::Drawing::Font("宋体",18);
	mySmallFront = gcnew System::Drawing::Font("宋体",14);
	SetFormPos = this->Width-15;
	ClientSize = Drawing::Size(SetFormPos, SetgroupBox->Top);
	Connected = false;
	/*当前画面的温度处理初始化*/

	m_SetForm = gcnew SetForm;//暂时没用到
	for (int i=0;i<IMAGERCOUNT;i++)
	{
		formsImager[i]->TempMinTrackBarValue = trackBar1->Value;
		formsImager[i]->TempRangTrackBarValue = trackBar2->Value;
	}
	FrameWidth = 0x17e;
	FrameHeight = 0x120;
	FrameSize = FrameWidth*FrameHeight;
	TwoFrameWidth = FrameWidth*2;  //两个Imager图像合在一起，高度不变，但是宽度变为两倍.
	m_BmpImage = gcnew Bitmap( TwoFrameWidth , FrameHeight , System::Drawing::Imaging::PixelFormat::Format24bppRgb );
	System::Drawing::Rectangle rect = System::Drawing::Rectangle(0, 0, m_BmpImage->Width, m_BmpImage->Height);
	Imaging::BitmapData^ bmpData = m_BmpImage->LockBits( rect, Imaging::ImageLockMode::ReadWrite, m_BmpImage->PixelFormat );
	int stride = bmpData->Stride;
	int stride_diff = bmpData->Stride - TwoFrameWidth*3;
	m_BmpImage->UnlockBits( bmpData );
	rgbValues = gcnew array<Byte>(stride * FrameHeight);
	Values = gcnew array<short>(FrameSize*2);//两张图片//
	whu_AllTemValues = gcnew array<double>(FrameSize*2);
	whu_AllSelectRectValues = gcnew array<double>(100);
	whu_BSHowRectangle = false;
	whu_BKeepRectangle = false;
	whu_BShowMouseTemp = false;
	whu_MouseTempValue = 0;
	whu_SelectRectangle = gcnew System::Drawing::Rectangle(0,0,0,0);//选择的区域
	whu_MatchSelectRectangle = gcnew System::Drawing::Rectangle(0,0,0,0);//选择的区域
	m_MaxTempValuePoint.X = 0;
	m_MaxTempValuePoint.Y = 0;

////////////////////////////由于采集端不需要显示整个煤堆的数据,因此带Match字眼的变量或是函数都用不到///////////////////////////////////

	/* 整个煤堆的温度处理初始化*/

	LineCount = FrameWidth*2;
	InnerCircleR = 256;
	MatchWidth = LineCount*2+InnerCircleR*2;
	MatchHeight = LineCount*2+InnerCircleR*2;//正方形的图片//
	AngleAccuracy = 5;
	int AngleCount = 360*AngleAccuracy;
	Lin_RangeAngle = 48*AngleAccuracy;//热像仪能显示的最宽视角//62*49°
	Lin_CurrentAngle = 0*AngleAccuracy;
	Lin_OldAngle = Lin_CurrentAngle;
	whu_AllAngles = gcnew array<double>(AngleCount);//360显示的信息太少了，约为原来的1/8//
	whu_MatchValues = gcnew array<double>((1+1+LineCount)*AngleCount);//合成的图像所需的信息//
	
	whu_OutputPolarTemp = gcnew array<double>((1+1+LineCount)*360);//1校验位0xffff，1角度，FrameWidth温度//
	for (int i=0;i<360;i++)
	{
		int VerifyPos = i*(1+1+LineCount);
		whu_OutputPolarTemp[VerifyPos] = 0xffff;
		whu_OutputPolarTemp[VerifyPos+1] = i;
	}
	//m_MatchBmpImage为合成的图像，长和宽均为0x17e*4,因为一个角度对应的温度信息长度即直径为0x17e*2//
	m_MatchBmpImage = gcnew Bitmap(MatchWidth,MatchWidth,System::Drawing::Imaging::PixelFormat::Format24bppRgb);
	System::Drawing::Rectangle rect2 = System::Drawing::Rectangle(0, 0, m_MatchBmpImage->Width, m_MatchBmpImage->Height);
	Imaging::BitmapData^ bmpData2 = m_MatchBmpImage->LockBits( rect2, Imaging::ImageLockMode::ReadWrite, m_MatchBmpImage->PixelFormat );
	int stride2 = bmpData2->Stride;
	int stride_diff2 = bmpData2->Stride - MatchWidth*3;
	m_MatchBmpImage->UnlockBits( bmpData2 );
	rgbMatchValues = gcnew array<Byte>(stride2 * MatchWidth);
	whu_AllMatchTempValues = gcnew array<double>(MatchWidth*MatchHeight);
	whu_AllSelectMatchTempValues = gcnew array<double>(100);//支持查看100个区域的温度信息//
	for (int i=0;i<whu_AllMatchTempValues->Length;i++)
	{
		whu_AllMatchTempValues[i] = -100;
	}
	m_MaxMatchTempValuePoint.X = 0;
	m_MaxMatchTempValuePoint.Y = 0;
	m_MatchSelectRectShowTime = 0;
	//////报警温度的显示/////
	//for (int i=0;i<360;i++)
	//{
	 //this->MyChart->Series["报警温度"]->Points->AddXY(i,m_AlarmTemp);
	//}
	

	//String^ strConn = "Data Source = SHELMYLIN-PC;Initial Catalog=LinDataBase;Integrated Security=True";//SQL Server链接字符串
	//ConnSql = gcnew SqlConnection(strConn); //Sql链接类的实例化
	//ConnSql->Open();//打开数据库
	/*Lin_DataSource = "SHELMYLIN-PC";
	Lin_DataName = "LinDataBase";
	DataSourcetextBox->Text = Lin_DataSource;
	InitialCatalogtextBox->Text =Lin_DataName;*/

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	Lin_BConnectToDB = false;
	Lin_BMoving = false;
	Lin_BMoveDone = false;
	Lin_BDBSaveDone = false;
	Lin_MoveTimeInterval = 0;
	Lin_AngleInterval = 14.3; //此值和InnerCircleR有关系
	Lin_AngleWithValues = gcnew array<short>((1+1+LineCount)*AngleCount);
	Lin_SameAngleCount = 0;

	//此函数为连接数据库//
	Lin_DataSource = DataSourcetextBox->Text;
	Lin_DataName = InitialCatalogtextBox->Text;
	String^ strConn = "Data Source = " + Lin_DataSource
		+ ";Initial Catalog = " + Lin_DataName
		+ ";Integrated Security=True";
	//String^ strConn = "Data Source = MICROSOF-8B4B5C;Initial Catalog=LinDataBase;Integrated Security=True";//SQL Server链接字符串
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
		//MessageBox::Show("无法连接数据库！");
		label8->Text = "数据库未连接！";
		Lin_BConnectToDB = false;
	}	

	//SOCKET
	Lin_BNetConnect = false;
	Lin_ThreadStart = gcnew ThreadStart(this,&FormMulti::whu_RecvData);
	Lin_RecvThread  = gcnew Thread(Lin_ThreadStart);
	Lin_RecvThread->IsBackground = true;
	Lin_RecvThread->Start();

	Lin_RecvStr = "停止";
	//Thread ^acceptThread = gcnew Thread(AcceptData);
	//acceptThread->IsBackground = true;
	//acceptThread->Start();

}


System::Void FormMulti::FormMulti_Load(System::Object^  sender, System::EventArgs^  e) 
{
	this->Text = this->Text + " (Rel. " + this->Version->ToString() + ")";
}

System::Void FormMulti::FormMulti_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) 
{
	// we explicitely delete to release resources:
	for(int i=0; i<formsImager->Length; i++)
		delete formsImager[i];
	delete ipc;
	if (Lin_BConnectToDB==true)
	{
		ConnSql->Close();//关闭数据库
	}
	
}

System::Void FormMulti::FormImager_OnResize(System::Object^  sender, System::EventArgs^  e)
{
	//this->SuspendLayout();

	//int maxb = 0;
	//for(int i=0; i<formsImager->Length; i++)
	//{
		//formsImager[i]->Location = Drawing::Point((!i) ? 5 : formsImager[i-1]->Right + 5, this->MyChart->Bottom+5);
		//maxb = max(maxb, formsImager[i]->Bottom);
	//}
	//ClientSize = Drawing::Size(formsImager[formsImager->Length-1]->Right + 5, maxb + 5);
	//this->ResumeLayout();
	//this->PerformLayout();
}
void FormMulti::GetBitmap(Bitmap^ Bmp, array<short>^values)
{
	int stride_diff;
	// Lock the bitmap's bits.  
	System::Drawing::Rectangle rect = System::Drawing::Rectangle(0, 0, Bmp->Width, Bmp->Height);
	Imaging::BitmapData^ bmpData = Bmp->LockBits( rect, Imaging::ImageLockMode::ReadWrite, Bmp->PixelFormat );
	stride_diff = bmpData->Stride - TwoFrameWidth*3;

	// Get the address of the first line.
	IntPtr ptr = bmpData->Scan0;
	m_MaxTempValue = (double)((values[0]-1000)/10.0);
	for ( int dst=0, src=0, y=0; y < FrameHeight; y++, dst += stride_diff) 
		for ( int x=0; x < TwoFrameWidth; x++, src++, dst+=3 )
		{
			short m_Temp = (values[src]-1000)/10;
			short m_NewValue = 1024*(m_Temp-TempMinTrackBarValue)/TempRangTrackBarValue;
			Byte m_RGBValue[3];
			whu_GetRGBValue(m_NewValue,m_RGBValue);
			rgbValues[dst] = m_RGBValue[0];//b
			rgbValues[dst+1] = m_RGBValue[1];//g
			rgbValues[dst+2] = m_RGBValue[2];//r

			//获取温度//
			//获取温度信息
			whu_AllTemValues[src] = (double)((values[src]-1000)/10.0);
			//获取最高温度信息//
			if (whu_AllTemValues[src]>m_MaxTempValue)
			{ 
				m_MaxTempValue = whu_AllTemValues[src];
				m_MaxTempValuePoint.X = x;
				m_MaxTempValuePoint.Y = y;
			}

		}
		// Copy the RGB values back to the bitmap
		System::Runtime::InteropServices::Marshal::Copy( rgbValues, 0, ptr, rgbValues->Length );

		// Unlock the bits.
		Bmp->UnlockBits( bmpData );

}
void FormMulti::whu_GetRGBValue(short value ,Byte *m_RGBValue)
{
	Byte r,g,b;
	short m_value = 1024 - value;//
	if(m_value<256)
	{
		b=255-m_value;
		r=g=255;
	}
	else if(m_value<512)
	{
		g=512-m_value;
		r=255;
		b=0;
	}
	else if(m_value<640)
	{
		b=m_value-512;
		r=255;
		g=0;
	}
	else if(m_value<896)
	{
		r=896-m_value;
		g=0;
		b=128;
	}
	else
	{
		b=1024-m_value;
		r=g=0;
	}

	m_RGBValue[0] = b;
	m_RGBValue[1] = g;
	m_RGBValue[2] = r;

}
void FormMulti::GetValuesData(array<short>^values0,array<short>^values1,array<short>^values2){
	if (Connected)
	{

			if (formsImager[0]->Connected)
			{
				int dst = FrameWidth;
				//int dst2 = FrameWidth;
				for (int i=0;i<FrameHeight;i++,dst+= FrameWidth)
				{
					for (int j=0;j<FrameWidth;j++,dst++)
					{
						int src = i*FrameWidth +j;
						if (src<FrameSize&&dst<FrameSize*2)
						{
							values0[dst] = formsImager[0]->Values[src];
						}

					}
				}

			}
			if (formsImager[1]->Connected)
			{
				//int dst1 = 0;
				int dst = 0;
				for (int i=0;i<FrameHeight;i++,dst+= FrameWidth)
				{
					for (int j=0;j<FrameWidth;j++,dst++)
					{
						int src = i*FrameWidth +j;
						if (src<FrameSize&&dst<FrameSize*2)
						{
							values0[dst] = formsImager[1]->Values[src];
						}

					}
				}

			}	

	}
	




}
void FormMulti::whu_GetMatchingImg(array<double>^InputValues,array<double>^InputAngle,Bitmap ^MatchBmp)
{
	///*说明：InputValues数组的格式是：382个温度信息值，共360*5小组*/
	///*说明：MatchBmp是拼接好的图像*/
	////
	//short CircleCenterXY = MatchWidth/2;
	//int ValueCount = InputValues->Length;//
	//int AngleCount = InputAngle->Length;//
	//array<short> ^OutputValues = gcnew array<short>(MatchWidth*MatchHeight);
	//int Xpos = 0;
	//int YPos = 0;
	//int SrcValuePos=0;
	//int DstValuePos = 0;
	////
	//if ((ValueCount/LineCount)==AngleCount)/*假如数据匹配正确的话//获取它的数据*/
	//{
	//	//先获取数据//
	//	for (int anglePos = 0;anglePos<AngleCount;anglePos++)
	//	{
	//		double angleData = InputAngle[anglePos]*Math::PI/180.0;
	//		for (int i=0;i<LineCount;i++,SrcValuePos++)
	//		{
	//			Xpos = (int)((i+InnerCircleR)*System::Math::Cos(angleData)+CircleCenterXY);//极坐标原点在矩形的中心//
	//			YPos = (int)(-(i+InnerCircleR)*System::Math::Sin(angleData)+CircleCenterXY);
	//			if (Xpos<MatchWidth&&YPos<MatchHeight)
	//			{
	//				DstValuePos = YPos*MatchWidth+Xpos;//又少乘了个2，太不严谨了！！//
	//				OutputValues[DstValuePos] = InputValues[SrcValuePos];
	//				whu_AllMatchTempValues[DstValuePos] = (InputValues[SrcValuePos]-1000)/10.0;//得到煤场温度//
	//			}
	//		}
	//	}
	//	int len = OutputValues->Length;//2334784 = 764*2*764*2//
	//	//再拼接成图像//
	//	int stride_diff;
	//	// Lock the bitmap's bits.  
	//	System::Drawing::Rectangle rect = System::Drawing::Rectangle(0, 0, MatchBmp->Width, MatchBmp->Height);
	//	Imaging::BitmapData^ bmpData = MatchBmp->LockBits( rect, Imaging::ImageLockMode::ReadWrite, MatchBmp->PixelFormat );
	//	stride_diff = bmpData->Stride - MatchWidth*3;

	//	// Get the address of the first line.
	//	IntPtr ptr = bmpData->Scan0;
	//	m_MaxMatchTempValue = -100;
	//	for ( int dst=0, src=0, y=0; y < MatchHeight; y++, dst += stride_diff) 
	//		for ( int x=0; x < MatchWidth; x++, src++, dst+=3 )
	//		{
	//			double temp = (OutputValues[src]-1000)/10.0;
	//			short m_Temp = (short)temp;
	//			if (temp>m_MaxMatchTempValue)
	//			{
	//				m_MaxMatchTempValue = temp;
	//				m_MaxMatchTempValuePoint.X = x;
	//				m_MaxMatchTempValuePoint.Y = y;
	//			}

	//			short m_NewValue = 1024*(m_Temp-TempMinTrackBarValue)/TempRangTrackBarValue;
	//			Byte m_RGBValue[3];
	//			whu_GetRGBValue(m_NewValue,m_RGBValue);
	//			rgbMatchValues[dst] = m_RGBValue[0];//b
	//			rgbMatchValues[dst+1] = m_RGBValue[1];//g
	//			rgbMatchValues[dst+2] = m_RGBValue[2];//r

	//		}
	//		// Copy the RGB values back to the bitmap
	//		System::Runtime::InteropServices::Marshal::Copy( rgbMatchValues, 0, ptr, rgbMatchValues->Length );

	//		// Unlock the bits.
	//		MatchBmp->UnlockBits( bmpData );



	//}
	/*说明：InputValues数组的格式是：382个温度信息值，共360*5小组*/
	/*说明：MatchBmp是拼接好的图像*/
	//
	short CircleCenterXY = MatchWidth/2;
	int ValueCount = InputValues->Length/(360*AngleAccuracy);//
	array<short> ^OutputValues = gcnew array<short>(MatchWidth*MatchHeight);
	int Xpos = 0;
	int YPos = 0;
	int SrcValuePos=0;
	int DstValuePos = 0;
	//
	int AngleCount = 360*AngleAccuracy;
	for (int anglePos = 0;anglePos<AngleCount;anglePos++)
	{
		int VerifyPos = anglePos*ValueCount;
		if (InputValues[VerifyPos] == 0xffff)
		{
			double angleData = InputValues[VerifyPos+1]*Math::PI/180.0;
			for (int i=0;i<ValueCount-2;i++)
			{
				Xpos = (int)((i+InnerCircleR)*System::Math::Cos(angleData)+CircleCenterXY);//极坐标原点在矩形的中心//
				YPos = (int)(-(i+InnerCircleR)*System::Math::Sin(angleData)+CircleCenterXY);
				if (Xpos<MatchWidth&&YPos<MatchHeight)
				{
					DstValuePos = YPos*MatchWidth+Xpos;
					SrcValuePos = VerifyPos+2+i;
					OutputValues[DstValuePos] = InputValues[SrcValuePos];
					whu_AllMatchTempValues[DstValuePos] = (InputValues[SrcValuePos]-1000)/10.0;//得到煤场温度//
				}
			}
		}

	}

	int len = OutputValues->Length;
	//再拼接成图像//
	int stride_diff;
	// Lock the bitmap's bits.  
	System::Drawing::Rectangle rect = System::Drawing::Rectangle(0, 0, MatchBmp->Width, MatchBmp->Height);
	Imaging::BitmapData^ bmpData = MatchBmp->LockBits( rect, Imaging::ImageLockMode::ReadWrite, MatchBmp->PixelFormat );
	stride_diff = bmpData->Stride - MatchWidth*3;

	// Get the address of the first line.
	IntPtr ptr = bmpData->Scan0;
	m_MaxMatchTempValue = -100;
	for ( int dst=0, src=0, y=0; y < MatchHeight; y++, dst += stride_diff) 
		for ( int x=0; x < MatchWidth; x++, src++, dst+=3 )
		{
			double temp = (OutputValues[src]-1000)/10.0;
			short m_Temp = (short)temp;
			if (temp>m_MaxMatchTempValue)
			{
				m_MaxMatchTempValue = temp;
				m_MaxMatchTempValuePoint.X = x;
				m_MaxMatchTempValuePoint.Y = y;
			}

			short m_NewValue = 1024*(m_Temp-TempMinTrackBarValue)/TempRangTrackBarValue;
			Byte m_RGBValue[3];
			whu_GetRGBValue(m_NewValue,m_RGBValue);
			rgbMatchValues[dst] = m_RGBValue[0];//b
			rgbMatchValues[dst+1] = m_RGBValue[1];//g
			rgbMatchValues[dst+2] = m_RGBValue[2];//r

		}
		// Copy the RGB values back to the bitmap
		System::Runtime::InteropServices::Marshal::Copy( rgbMatchValues, 0, ptr, rgbMatchValues->Length );

		// Unlock the bits.
		MatchBmp->UnlockBits( bmpData );

}
Bitmap^ FormMulti::whu_ResizeImage(Bitmap^ Bmp,int NewWidth,int NewHeight)
{

	Bitmap^ m_NewMatchBmpImage = gcnew Bitmap( MatchWidth , MatchHeight ,System::Drawing::Imaging::PixelFormat::Format24bppRgb );
	Graphics ^g = Graphics::FromImage(m_NewMatchBmpImage);
	//g->SetInterpolationMode(InterpolationModeHighQualityBicubic);
	System::Drawing::Rectangle OldRect = System::Drawing::Rectangle(0, 0, Bmp->Width, Bmp->Height);
	System::Drawing::Rectangle NewRect = System::Drawing::Rectangle(0, 0, NewWidth, NewHeight);
	g->DrawImage(Bmp,NewRect,OldRect,GraphicsUnit::Pixel);
	return m_NewMatchBmpImage;
}
Point FormMulti::whu_GetValuePositon(short pos,int width,int height)
{
	Point m_point;
	m_point.Y = pos/width;
	m_point.X = pos%width;
	return m_point;
}
void FormMulti::whu_UpdateAngleWithValues(int CurrentAngle,array<short>^InputValues)
{

	int DataLength = Lin_AngleWithValues->Length/(360*AngleAccuracy);
	if (CurrentAngle>=360*AngleAccuracy)
	{
		CurrentAngle -= 360*AngleAccuracy;
	}
	if (CurrentAngle<0)
	{
		CurrentAngle+=360*AngleAccuracy;
	}
	if (CurrentAngle<360*AngleAccuracy&&CurrentAngle>=0)
	{

		int Pos = CurrentAngle*DataLength ;
		//校验一下:
		if(InputValues->Length == DataLength-2)
		{
			short sbbbb = sizeof(short); //short最长是0xff
			Lin_AngleWithValues[Pos] = 0xffff;//说明已初始化
			Lin_AngleWithValues[Pos+1] = CurrentAngle;//角度
			for(int Dst=Pos+2,Src=0;Src<InputValues->Length;Dst++,Src++)
			{
				Lin_AngleWithValues[Dst] = InputValues[Src];//原始温度流
			}
		}
	}
}
void FormMulti::whu_AddMatchValue(double CurrentAngle,array<double>^ InputValue)
{
	int DataLength = whu_MatchValues->Length/(360*AngleAccuracy);
	if (CurrentAngle>=360)
	{
		CurrentAngle -=360;
	}
	if (CurrentAngle<0)
	{
		CurrentAngle+=360;
	}
	if (CurrentAngle<360&&CurrentAngle>=0)
	{
		int Pos = (int)CurrentAngle*AngleAccuracy* DataLength ;
		//校验一下:
		if(InputValue->Length == DataLength-2)
		{
			//从后往前来,数据后挪DataLength 位//
			for(int i=AngleAccuracy-1;i>0;i--)
			{
				for(int Dst=Pos+i*DataLength,Count_i=0;Count_i<DataLength;Dst++,Count_i++)
				{
					int Src = Dst-DataLength;
					double test01 = whu_MatchValues[Dst];
					double test02 = whu_MatchValues[Src];
					whu_MatchValues[Dst] = whu_MatchValues[Src];

				}
			}
			//赋值
			whu_MatchValues[Pos] = 0xffff;//说明已初始化
			whu_MatchValues[Pos+1] = CurrentAngle;//角度
			for(int Dst=Pos+2,Src=0;Src<InputValue->Length;Dst++,Src++)
			{
				whu_MatchValues[Dst] = InputValue[Src];//原始温度流
			}
		}
	}
	
}
double FormMulti::whu_GetCurrentAngle()
{
	double angle = Lin_CurrentAngle;
	angle = angle + Lin_MoveTimeInterval;
	if (angle<0)
	{
		angle+=360*AngleAccuracy;
	}
	if (angle>=360*AngleAccuracy)
	{
		angle-=360*AngleAccuracy;
	}
	return angle;
}
bool FormMulti::whu_SaveDataToDB()
{
	DateTime ^now = DateTime::Now;
	System::Windows::Forms::DateTimePicker^  dateTimePicker2 = gcnew System::Windows::Forms::DateTimePicker();
	String ^m_time = now->ToString("yyyy-MM-dd HH:mm:ss:fff");
	array<short> ^m_AngleWithValues = gcnew array<short>(LineCount+1+1+5);//添加年月日时分....
	for (int i=0;i<360*AngleAccuracy;i++)
	{
		int pos = i*(Lin_AngleWithValues->Length/(360*AngleAccuracy));
		short m_VerifyValue = 0xffff;
		if(Lin_AngleWithValues[pos]==m_VerifyValue)
		{
			//先存校验位0xffff，再存角度，再存时间//
			m_AngleWithValues[0] = Lin_AngleWithValues[pos];
			m_AngleWithValues[1] = Lin_AngleWithValues[pos+1];
			m_AngleWithValues[2] = now->Year;
			m_AngleWithValues[3] = now->Month;
			m_AngleWithValues[4] = now->Day;
			m_AngleWithValues[5] = now->Hour;
			m_AngleWithValues[6] = now->Minute;
			for (int j=7;j<m_AngleWithValues->Length;j++)
			{
				int m_Pos = pos+j-5;
				m_AngleWithValues[j] = Lin_AngleWithValues[m_Pos];
			}
			double My_Angle = ((double)Lin_AngleWithValues[pos+1])/(double)AngleAccuracy;
			//存入数据//
			String ^m_InsertImageSQL = "insert into dbo.SourceData2(time,angle,Temperature) values(@time,@angle,@Temperature)";
			SqlCommand ^CmdObj = gcnew SqlCommand(m_InsertImageSQL, ConnSql);
			//写入：
			CmdObj->Parameters->Add("@time",SqlDbType::DateTime);
			CmdObj->Parameters->Add("@angle", SqlDbType::Float );
			CmdObj->Parameters->Add("@Temperature", SqlDbType::Image);
			CmdObj->Parameters["@time"]->Value = now;
			CmdObj->Parameters["@angle"]->Value = My_Angle;
			array<Byte>^ m_ByteDestData = gcnew array<Byte>(sizeof(short)*(m_AngleWithValues->Length));
			System::Buffer::BlockCopy(m_AngleWithValues,0,m_ByteDestData,0,m_ByteDestData->Length);
			CmdObj->Parameters["@Temperature"]->Value = m_ByteDestData;
			CmdObj->ExecuteNonQuery();

		}

	}



	
	return true;
}
double FormMulti::whu_ReadDataFromDB(array<short>^ DestData)
{
	
	String ^strSQL = "SELECT TOP 1 [time],[angle],[Temperature] FROM dbo.SourceData2";
	SqlDataAdapter ^da = gcnew SqlDataAdapter(strSQL, ConnSql); //创建DataAdapter数据适配器实例
	da->Fill(dataSet1, "data_2014年02月20日");//使用DataAdapter的Fill方法(填充)，调用SELECT命令
	DataTable ^m_DataTable = dataSet1->Tables[0];
	////得到列名//
	int ColumeCount = m_DataTable->Columns->Count;
	String ^m_str = m_DataTable->Columns[0]->ColumnName;
	m_str = m_DataTable->Columns[1]->ColumnName;
	m_str = m_DataTable->Columns[2]->ColumnName;
	//得到行数据
	int RowCount = m_DataTable->Rows->Count;
	DataRow ^m_DataRow = m_DataTable->Rows[0];
	m_str =  m_DataRow->ItemArray[0]->ToString();
	m_str = m_DataRow->ItemArray[1]->ToString();
	m_str = m_DataRow->ItemArray[2]->ToString();

	array<byte>^ m_byte = gcnew array<byte>(m_str->Length*sizeof(char));
	System::Buffer::BlockCopy(m_str->ToCharArray(),0,m_byte,0,m_byte->Length);
	array<short>^ m_destvalue = gcnew array<short>(m_str->Length);
	System::Buffer::BlockCopy(m_byte,0,m_destvalue,0,m_destvalue->Length);
	return 0;
}
void FormMulti::whu_ClearAngleWithValues()
{
	for (int verifypos=0;verifypos<Lin_AngleWithValues->Length;verifypos+=(1+1+LineCount))
	{
		Lin_AngleWithValues[verifypos] = 0;
	}
}
void FormMulti::whu_RecvData()
{
	//String ^ip = IPAddress->Text;
	int port = 1110;
	connectionSocket = gcnew Socket(AddressFamily::InterNetwork,SocketType::Dgram,ProtocolType::Udp);
	//IPEndPoint ^iPEndPoint = gcnew IPEndPoint(IPAddress::Parse(ip->ToString()),Convert::ToInt32(port));
	IPEndPoint ^iPEndPoint = gcnew IPEndPoint(System::Net::IPAddress::Any,Convert::ToInt32(port));
	try
	{
		connectionSocket->Bind(iPEndPoint);
	}
	catch (Exception ^ e)
	{
		//MessageBox::Show("连接出错，请检查网络");
	}
	while(true)
	{
			array<Byte>^ RecvByte = gcnew array<Byte>(1000);		
			EndPoint ^iPEndPoint = gcnew IPEndPoint(System::Net::IPAddress::Any,1110);
			int rev = connectionSocket->ReceiveFrom(RecvByte,iPEndPoint);
			Encoding ^m_Encoding = Encoding::Unicode;
			Lin_RecvStr = m_Encoding->GetString(RecvByte,0,rev);
	}      
}
}
