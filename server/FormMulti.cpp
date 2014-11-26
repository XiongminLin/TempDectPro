#include "stdafx.h"
#include "FormMulti.h"



namespace IPCSample {

FormMulti::FormMulti(HWND hostHandle)
{
	InitializeComponent();
	//formsImager = gcnew array<FormImager^>(IMAGERCOUNT);
	
	//ipc = gcnew IPC(IMAGERCOUNT);
	Lin_AlarmTemp = 70;
	this->SuspendLayout();
	this->ResumeLayout();
	this->PerformLayout();
	TempMinTrackBarValue = 20;
	TempRangTrackBarValue = 20;
	Lin_BlackPen = gcnew System::Drawing::Pen(System::Drawing::Color::Black);//矩形框颜色
	Lin_WhitePen = gcnew System::Drawing::Pen(System::Drawing::Color::White);//矩形框颜色
	Lin_BulePen = gcnew System::Drawing::Pen(System::Drawing::Color::Blue);//矩形框颜色
	Lin_RedPen = gcnew System::Drawing::Pen(System::Drawing::Color::Red);//矩形框颜色
	Lin_Brush = gcnew SolidBrush(System::Drawing::Color::White);//平均区域温度颜色
	Lin_BigFront = gcnew System::Drawing::Font("宋体",18);
	Lin_SmallFront = gcnew System::Drawing::Font("宋体",14);
	SetFormPos = this->Width-15;
	//ClientSize = Drawing::Size(SetFormPos, SetgroupBox->Top);
	FrameWidth = 0x17e;
	FrameHeight = 0x120;
	Lin_MatchSelectRectangle = gcnew System::Drawing::Rectangle(0,0,0,0);//选择的区域
	/* 整个煤堆的温度处理初始化*/
	LineCount = FrameWidth*2;//0x17e是一台热像仪红外图像的
	Lin_InnerCircleR = 200;
	MatchWidth = LineCount*2+Lin_InnerCircleR*2;
	MatchHeight = LineCount*2+Lin_InnerCircleR*2;//正方形的图片//
	AngleAccuracy = 5;
	int AngleCount = 360*AngleAccuracy;
	Lin_AngleWithValues = gcnew array<unsigned short>((1+1+5+LineCount)*AngleCount);//合成的图像所需的信息//
	Lin_HistoryAngleWithValues = gcnew array<unsigned short>((1+1+5+LineCount)*AngleCount*10);
	for (int i = 0;i<(1+1+5+LineCount)*AngleCount*10;i+=(1+1+5+LineCount))
	{
		Lin_HistoryAngleWithValues[i] = 0xee;
	}
	Lin_MatchBmpImage = gcnew Bitmap(MatchWidth,MatchWidth,System::Drawing::Imaging::PixelFormat::Format24bppRgb);
	System::Drawing::Rectangle rect2 = System::Drawing::Rectangle(0, 0, Lin_MatchBmpImage->Width, Lin_MatchBmpImage->Height);
	Imaging::BitmapData^ bmpData2 = Lin_MatchBmpImage->LockBits( rect2, Imaging::ImageLockMode::ReadWrite, Lin_MatchBmpImage->PixelFormat );
	int stride2 = bmpData2->Stride;
	int stride_diff2 = bmpData2->Stride - MatchWidth*3;
	Lin_MatchBmpImage->UnlockBits( bmpData2 );
	rgbMatchValues = gcnew array<Byte>(stride2 * MatchWidth);
	whu_AllMatchTempValues = gcnew array<double>(MatchWidth*MatchHeight);
	whu_AllSelectMatchTempValues = gcnew array<double>(100);//支持查看100个区域的温度信息//
	for (int i=0;i<whu_AllMatchTempValues->Length;i++)
	{
		whu_AllMatchTempValues[i] = -100;
	}
	Lin_MouseClickHistoryTemp = gcnew array<double>(10);
	for (int i = 0;i<10;i++)
	{
		Lin_MouseClickHistoryTemp[i] = 0;
	}
	Lin_SetForm = gcnew SetForm();
	m_SetForm = gcnew SetForm02();
	m_SetForm->Owner = this;
	Lin_MaxMatchTempValuePoint.X = 0;
	Lin_MaxMatchTempValuePoint.Y = 0;
	//m_MatchSelectRectShowTime = 0;
	//////报警温度的显示/////
	for (int i=0;i<360;i++)
	{
	 this->MyChart->Series["报警温度"]->Points->AddXY(i,Lin_AlarmTemp);
	 this->MyChart->Series["报警浓度"]->Points->AddXY(i,Lin_AlarmTemp);
	}
	//数据库相关部分
	Lin_BConnectedToLocalDB = false;
	Lin_BConnectedToRemoteDB = false;
	//label15->Text = "本地数据库未连接!";
	Lin_ThreadStart = gcnew ThreadStart(this,&FormMulti::whu_UpdataTempData);
	Lin_Thread = gcnew Thread(Lin_ThreadStart);

	//socket
	//Lin_CurrentAngle = 0;
	//String ^ip = IpAddress->Text;
	//int port = 1110; 
	//Lin_SendSocket = gcnew Socket(AddressFamily::InterNetwork, SocketType::Dgram, ProtocolType::Udp);
	//iPEndPoint = gcnew IPEndPoint(IPAddress::Parse(ip->ToString()), port);
	//Lin_BSendAngle = false;

}


System::Void FormMulti::FormMulti_Load(System::Object^  sender, System::EventArgs^  e) 
{
	this->Text = this->Text + " (Rel. " + this->Version->ToString() + ")";
}

System::Void FormMulti::FormMulti_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) 
{
	// we explicitely delete to release resources:
	//for(int i=0; i<formsImager->Length; i++)
	//	delete formsImager[i];
	//delete ipc;
	if (Lin_BConnectedToLocalDB)
	{
		Lin_LocalConnSql->Close();//关闭数据库
		Lin_BConnectedToLocalDB = false;
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
//void FormMulti::GetBitmap(Bitmap^ Bmp, array<short>^values)
//{
//	int stride_diff;
//	// Lock the bitmap's bits.  
//	System::Drawing::Rectangle rect = System::Drawing::Rectangle(0, 0, Bmp->Width, Bmp->Height);
//	Imaging::BitmapData^ bmpData = Bmp->LockBits( rect, Imaging::ImageLockMode::ReadWrite, Bmp->PixelFormat );
//	stride_diff = bmpData->Stride - TwoFrameWidth*3;
//
//	// Get the address of the first line.
//	IntPtr ptr = bmpData->Scan0;
//	m_MaxTempValue = (double)((values[0]-1000)/10.0);
//	for ( int dst=0, src=0, y=0; y < FrameHeight; y++, dst += stride_diff) 
//		for ( int x=0; x < TwoFrameWidth; x++, src++, dst+=3 )
//		{
//			short m_Temp = (values[src]-1000)/10;
//			short m_NewValue = 1024*(m_Temp-TempMinTrackBarValue)/TempRangTrackBarValue;
//			Byte m_RGBValue[3];
//			whu_GetRGBValue(m_NewValue,m_RGBValue);
//			rgbValues[dst] = m_RGBValue[0];//b
//			rgbValues[dst+1] = m_RGBValue[1];//g
//			rgbValues[dst+2] = m_RGBValue[2];//r
//
//			//获取温度//
//			//获取温度信息
//			whu_AllTemValues[src] = (double)((values[src]-1000)/10.0);
//			//获取最高温度信息//
//			if (whu_AllTemValues[src]>m_MaxTempValue)
//			{ 
//				m_MaxTempValue = whu_AllTemValues[src];
//				m_MaxTempValuePoint.X = x;
//				m_MaxTempValuePoint.Y = y;
//			}
//
//		}
//		// Copy the RGB values back to the bitmap
//		System::Runtime::InteropServices::Marshal::Copy( rgbValues, 0, ptr, rgbValues->Length );
//
//		// Unlock the bits.
//		Bmp->UnlockBits( bmpData );
//
//}
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

void FormMulti::whu_GetMatchingImg(Bitmap ^MatchBmp)
{
	short CircleCenterXY = MatchWidth/2;
	int ValueCount =1+1+LineCount+5;
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
		if (Lin_AngleWithValues[VerifyPos] == 0xffff)
		{
			double angleData = (Lin_AngleWithValues[VerifyPos+1]/(double)AngleAccuracy)*Math::PI/180.0;
			for (int i=0;i<LineCount;i++)
			{
				Xpos = (int)((i+Lin_InnerCircleR)*System::Math::Cos(angleData)+CircleCenterXY);//极坐标原点在矩形的中心//
				YPos = (int)(-(i+Lin_InnerCircleR)*System::Math::Sin(angleData)+CircleCenterXY);
				if (Xpos<MatchWidth&&YPos<MatchHeight)
				{
					DstValuePos = YPos*MatchWidth+Xpos;
					SrcValuePos = VerifyPos+2+5+i;
					OutputValues[DstValuePos] = Lin_AngleWithValues[SrcValuePos];
					whu_AllMatchTempValues[DstValuePos] = (Lin_AngleWithValues[SrcValuePos]-1000)/10.0;//得到煤场温度//
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
	Lin_MaxMatchTempValue = -100;
	for ( int dst=0, src=0, y=0; y < MatchHeight; y++, dst += stride_diff) 
		for ( int x=0; x < MatchWidth; x++, src++, dst+=3 )
		{
			double temp = (OutputValues[src]-1000)/10.0;
			short m_Temp = (short)temp;
			if (temp>Lin_MaxMatchTempValue)
			{
				Lin_MaxMatchTempValue = temp;
				Lin_MaxMatchTempValuePoint.X = x;
				Lin_MaxMatchTempValuePoint.Y = y;
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



	///*说明：InputValues数组的格式是：382个温度信息值，共360*5小组*/
	///*说明：MatchBmp是拼接好的图像*/
	////
	//short CircleCenterXY = MatchWidth/2;
	//int ValueCount = InputValues->Length/(360*AngleAccuracy);//
	//array<short> ^OutputValues = gcnew array<short>(MatchWidth*MatchHeight);
	//int Xpos = 0;
	//int YPos = 0;
	//int SrcValuePos=0;
	//int DstValuePos = 0;
	////
	//int AngleCount = 360*AngleAccuracy;
	//for (int anglePos = 0;anglePos<AngleCount;anglePos++)
	//{
	//	int VerifyPos = anglePos*ValueCount;
	//	if (InputValues[VerifyPos] == 0xffff)
	//	{
	//		double angleData = InputValues[VerifyPos+1]*Math::PI/180.0;
	//		for (int i=0;i<ValueCount-2;i++)
	//		{
	//			Xpos = (int)((i+Lin_InnerCircleR)*System::Math::Cos(angleData)+CircleCenterXY);//极坐标原点在矩形的中心//
	//			YPos = (int)(-(i+Lin_InnerCircleR)*System::Math::Sin(angleData)+CircleCenterXY);
	//			if (Xpos<MatchWidth&&YPos<MatchHeight)
	//			{
	//				DstValuePos = YPos*MatchWidth+Xpos;
	//				SrcValuePos = VerifyPos+2+i;
	//				OutputValues[DstValuePos] = InputValues[SrcValuePos];
	//				whu_AllMatchTempValues[DstValuePos] = (InputValues[SrcValuePos]-1000)/10.0;//得到煤场温度//
	//			}
	//		}
	//	}

	//}

	//int len = OutputValues->Length;
	////再拼接成图像//
	//int stride_diff;
	//// Lock the bitmap's bits.  
	//System::Drawing::Rectangle rect = System::Drawing::Rectangle(0, 0, MatchBmp->Width, MatchBmp->Height);
	//Imaging::BitmapData^ bmpData = MatchBmp->LockBits( rect, Imaging::ImageLockMode::ReadWrite, MatchBmp->PixelFormat );
	//stride_diff = bmpData->Stride - MatchWidth*3;

	//// Get the address of the first line.
	//IntPtr ptr = bmpData->Scan0;
	//Lin_MaxMatchTempValue = -100;
	//for ( int dst=0, src=0, y=0; y < MatchHeight; y++, dst += stride_diff) 
	//	for ( int x=0; x < MatchWidth; x++, src++, dst+=3 )
	//	{
	//		double temp = (OutputValues[src]-1000)/10.0;
	//		short m_Temp = (short)temp;
	//		if (temp>Lin_MaxMatchTempValue)
	//		{
	//			Lin_MaxMatchTempValue = temp;
	//			Lin_MaxMatchTempValuePoint.X = x;
	//			Lin_MaxMatchTempValuePoint.Y = y;
	//		}

	//		short m_NewValue = 1024*(m_Temp-TempMinTrackBarValue)/TempRangTrackBarValue;
	//		Byte m_RGBValue[3];
	//		whu_GetRGBValue(m_NewValue,m_RGBValue);
	//		rgbMatchValues[dst] = m_RGBValue[0];//b
	//		rgbMatchValues[dst+1] = m_RGBValue[1];//g
	//		rgbMatchValues[dst+2] = m_RGBValue[2];//r

	//	}
	//	// Copy the RGB values back to the bitmap
	//	System::Runtime::InteropServices::Marshal::Copy( rgbMatchValues, 0, ptr, rgbMatchValues->Length );

	//	// Unlock the bits.
	//	MatchBmp->UnlockBits( bmpData );

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

bool FormMulti::whu_ReadDataFromRemoteDB(double angle,array<short>^DestData)
{
	bool m_BRead = false; 
	String ^m_AngleStr = String::Format("{0:##0.0}",angle);
	//SELECT top 1 [Temperature] FROM dbo.SourceData2 where angle = 0.2 order by time desc
	//String ^strSQL = "SELECT  [Temperature] FROM dbo.SourceData2 where angle = " + m_AngleStr;
	String ^strSQL = "SELECT top 1 [Temperature] FROM dbo.SourceData2 where angle = " + m_AngleStr + "order by time desc";//得到最新的数据desc
	array<byte>^ m_byte = gcnew array<byte>(DestData->Length*sizeof(short));
	SqlCommand ^cmd = gcnew SqlCommand();
	//cmd->Connection = Lin_LocalConnSql;
	cmd->Connection = Lin_RemoteConnSql;
	cmd->CommandText = strSQL;
	SqlDataReader ^sdr = cmd->ExecuteReader();
	while(sdr->Read())
	{
		sdr->GetBytes(0,0,m_byte,0,m_byte->Length);
		System::Buffer::BlockCopy(m_byte,0,DestData,0,m_byte->Length);
		m_BRead = true;
	}
	sdr->Close();
	return m_BRead;
}

bool FormMulti::whu_ReadDataFromLocalDB(double angle,array<short>^DestData,int Num)
{
	bool m_BRead = false; 
	if (Lin_BConnectedToLocalDB)
	{
		
		String ^m_AngleStr = String::Format("{0:##0.0}",angle);
		if (Num>0&&Num<=100)
		{
			String ^m_NumStr = String::Format("{0:##0}",Num);
			String ^strSQL = "SELECT top "+ m_NumStr +" [Temperature] FROM dbo.SourceData2 where angle = " + m_AngleStr + " order by time desc";//得到最新的数据desc
			array<byte>^ m_byte = gcnew array<byte>((LineCount+1+1+5)*sizeof(short));//校验+角度+年+月+日+时+分
			SqlCommand ^cmd = gcnew SqlCommand();
			cmd->Connection = Lin_LocalConnSql;
			//cmd->Connection = Lin_RemoteConnSql;
			cmd->CommandText = strSQL;
			SqlDataReader ^sdr = cmd->ExecuteReader();
			int ReadNum = 0;
			while(sdr->Read())
			{
				sdr->GetBytes(0,0,m_byte,0,m_byte->Length);
				//System::Buffer::BlockCopy(m_byte,0,DestData,0,m_byte->Length);
				System::Buffer::BlockCopy(m_byte,0,DestData,ReadNum*m_byte->Length,m_byte->Length);
				ReadNum++;
				m_BRead = true;
			}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
			sdr->Close();

		}
		else{
			MessageBox::Show("历史记录查询天数应在1和100之间");
		}
	}
	return m_BRead;
}

bool FormMulti::whu_ConnectToLocalDB(String ^m_LocalDataSource,String ^m_LocalDataBaseName)
{
	if (Lin_BConnectedToLocalDB == false)
	{

		//String^ strConn = "Data Source = " + Lin_DataSource + ";Initial Catalog=" + Lin_DataBaseName + ";Integrated Security=True";//SQL Server链接字符串
		String^ strConn = "Data Source = " + m_LocalDataSource + ";Initial Catalog=" + m_LocalDataBaseName + ";uid = sa;pwd = 123456";//SQL Server链接字符串
		Lin_LocalConnSql = gcnew SqlConnection(strConn); //Sql链接类的实例化
		try
		{
			Lin_LocalConnSql->Open();//打开数据库
			if (Lin_LocalConnSql->State == ConnectionState::Open)
			{
				Lin_BConnectedToLocalDB = true;
				//buttonDisConnectToDB->Enabled =true;
				//buttonConnectToDB->Enabled = false;
				//label15->Text = "本地数据库已连接!!";

				int ReadNum = 10;
				array<short>^ m_DestData = gcnew array<short>((LineCount+1+1+5)*ReadNum);//校验位+角度+年+月+日+时+分
				for (int i=0;i<360*AngleAccuracy;i++)
				{
					double m_angle = i/(double)AngleAccuracy;
					if (Lin_BConnectedToLocalDB)
					{
						if (whu_ReadDataFromLocalDB(m_angle,m_DestData,ReadNum))
						{
							int pos = i*(1+1+5+LineCount)*ReadNum;
							System::Buffer::BlockCopy(m_DestData,0,Lin_HistoryAngleWithValues,pos*sizeof(short),m_DestData->Length*sizeof(short));
						}
					}
				}
			}
		}
		catch (Exception ^m_Exceptin)
		{

			MessageBox::Show(m_Exceptin->Message);
		}		 
	}
	return true;
}
bool FormMulti::whu_ConnectToRemoteDB(String ^m_DataSource,String ^m_DataBaseName,String ^m_User,String ^m_Password)
{
	if (Lin_BConnectedToRemoteDB == false)
	{
		//String ^m_DataSource = textBoxRemoteDataSource->Text;
		//String ^m_DataBaseName = textBoxRemoteDataBase->Text;
		//String ^m_User = textBoxUser->Text;
		//String ^m_Password = textBoxPWD->Text;
		String^ strConn = "Data Source = " + m_DataSource + ";Initial Catalog=" + m_DataBaseName + ";uid = "+ m_User + ";pwd = "+m_Password;//SQL Server链接字符串
		Lin_RemoteConnSql = gcnew SqlConnection(strConn); //Sql链接类的实例化
		try
		{
			Lin_RemoteConnSql->Open();//打开数据库
			if (Lin_RemoteConnSql->State == ConnectionState::Open)
			{
				Lin_BConnectedToRemoteDB = true;
				//buttonConnectToRemoteDB->Enabled =false;
				//buttonDisConnectToRemoteDB->Enabled = true;
				//label18->Text = "远程数据库已连接!";
				if (Lin_Thread->ThreadState == System::Threading::ThreadState::Unstarted)
				{
					Lin_Thread->Start(); 
				}else if(Lin_Thread->ThreadState == System::Threading::ThreadState::Suspended){
					Lin_Thread->Resume();
				}
			}
		}
		catch (Exception ^m_Exceptin)
		{
			MessageBox::Show("无法连接远程数据库，请检查数据库名称或账号密码");

		}		 

	}

	return true;
}
bool FormMulti::whu_DisConnectToLocalDB()
{
	if (Lin_BConnectedToLocalDB)
	{
		Lin_LocalConnSql->Close();//关闭数据库
		Lin_BConnectedToLocalDB = false;
		//buttonDisConnectToDB->Enabled = false;
		//buttonConnectToDB->Enabled = true;
		//label15->Text = "本地数据库未连接!";

		if(Lin_Thread->ThreadState == System::Threading::ThreadState::Running)
		{
			Lin_Thread->Suspend();
		}
	}
	return true;
}
bool FormMulti::whu_DisConnectToRemoteDB()
{
	if (Lin_BConnectedToRemoteDB)
	{
		Lin_RemoteConnSql->Close();//关闭数据库
		Lin_BConnectedToRemoteDB = false;
		//buttonDisConnectToRemoteDB->Enabled = false;
		//buttonConnectToRemoteDB->Enabled = true;
		//label18->Text = "远程数据库未连接!";
	}
	return true;
}

void FormMulti::whu_UpdataTempData()
{
	while(true)
	{
		//ButtonRefresh->Enabled = false;
		array<short>^ m_DestData = gcnew array<short>(LineCount+1+1+5);
		for (int i=0;i<360*AngleAccuracy;i++)
		{
			double m_angle = i/(double)AngleAccuracy;
			if (Lin_BConnectedToRemoteDB)
			{
				if (whu_ReadDataFromRemoteDB(m_angle,m_DestData))
				{
					int pos = i*(1+1+5+LineCount);
					System::Buffer::BlockCopy(m_DestData,0,Lin_AngleWithValues,pos*sizeof(short),m_DestData->Length*sizeof(short));
				}
				Sleep(1);
			}

		}
		Sleep(1000);
	}
	
}
void FormMulti::whu_GetHistoryTemp(int angle,int Pos,array<double>^ Temp,array<unsigned short>^ TempTime,unsigned int Num)
{
	int Angle = (int)angle*AngleAccuracy;//得到定位点//
	for (int i = 0;i<Num;i++)
	{
		
		int VerifyPos = Angle*(LineCount+1+1+5)*Num + i*(LineCount+1+1+5);
		for (int j=0;j<5;j++)
		{
			TempTime[i*5+j] = Lin_HistoryAngleWithValues[VerifyPos+2+j];
		}
		unsigned short VerifyData = Lin_HistoryAngleWithValues[VerifyPos];
		unsigned short VerifyAngle = Lin_HistoryAngleWithValues[VerifyPos+1];
		unsigned short year = Lin_HistoryAngleWithValues[VerifyPos+2];
		unsigned short month = Lin_HistoryAngleWithValues[VerifyPos+3];
		unsigned short day = Lin_HistoryAngleWithValues[VerifyPos+4];
		unsigned short hour = Lin_HistoryAngleWithValues[VerifyPos+5];
		unsigned short minute = Lin_HistoryAngleWithValues[VerifyPos+6];
		if ( VerifyData== 0xffff &&VerifyAngle == Angle && Pos>=0 &&Pos<=LineCount)
		{
			int AnglePos = Angle*(LineCount+1+1+5)*Num + i*(LineCount+1+1+5) + Pos + 2 + 5;//先定大存储位置
			Temp[i] = (Lin_HistoryAngleWithValues[AnglePos]-1000)/10.0;
		}
		
	}
}
}
