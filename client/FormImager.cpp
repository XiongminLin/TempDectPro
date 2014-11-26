#include "stdafx.h"
#include "time.h"
#include "FormImager.h"


namespace IPCSample {

unsigned char clip(int val) { return (val <= 255) ? ((val > 0) ? val : 0) : 255; };

FormImager::FormImager(HWND hostHandle, IPC^ Ipc, int imagerIndex, String ^instanceName)
{
	InitializeComponent();
	ImagerIndex = imagerIndex;
	ipc = Ipc;
	TopLevel = false;
	FrameWidth = 0;
	FrameHeight = 0;
	FrameDepth = 0;
	bmp = gcnew Bitmap( 100 , 100 , System::Drawing::Imaging::PixelFormat::Format24bppRgb );
	ipcInitialized = false;
	Connected = false;
	Painted = false;
	MeasureAreaCount = 0;
	Margin = groupBoxVideo->Size - pictureBox->Size;
	FC0 = FC1 = 0;
	AppendLog = false;
	List = gcnew System::Collections::ArrayList(100);
	textBoxInstanceName->Text = instanceName;
}

FormImager::~FormImager()
{
	if (components)
		delete components;
}

void FormImager::AppInit(void)
{
	Init(160, 120, 2);
}

System::Void FormImager::textBoxInstanceName_TextChanged(System::Object^  sender, System::EventArgs^  e)
{
	ReleaseIPC();
}

void FormImager::InitIPC(void) 
{
	 if(ipc && !ipcInitialized)
	 {
		HRESULT hr = ipc->Init(ImagerIndex, textBoxInstanceName->Text);
		
		if(FAILED(hr))
 			ipcInitialized = false;
		else
		{
			onServerStopped = gcnew IPC::delOnServerStopped(this, &FormImager::OnServerStopped );
			ipc->SetCallback_OnServerStopped(ImagerIndex, onServerStopped);

			onFrameInit = gcnew IPC::delOnFrameInit(this, &FormImager::OnFrameInit );
			ipc->SetCallback_OnFrameInit(ImagerIndex, onFrameInit);

			onNewFrameEx = gcnew IPC::delOnNewFrameEx(this, &FormImager::OnNewFrameEx );
			ipc->SetCallback_OnNewFrameEx(ImagerIndex, onNewFrameEx);

			onConfigChanged = gcnew IPC::delOnConfigChanged(this, &FormImager::OnConfigChanged );
			ipc->SetCallback_OnConfigChanged(ImagerIndex, onConfigChanged);

			onInitCompleted = gcnew IPC::delOnInitCompleted(this, &FormImager::OnInitCompleted );
			ipc->SetCallback_OnInitCompleted(ImagerIndex, onInitCompleted);

			hr = ipc->Run(ImagerIndex);
			ipcInitialized = SUCCEEDED(hr);
			LastFrameTime = DateTime::Now;
			FC0 = FC1 = 0; 
		}
		label1->Text = hr ? "NOT CONNECTED" : "OK";

	 }
}

void FormImager::ReleaseIPC(void) 
{
	Connected = false;
	if(ipc && ipcInitialized)
	{
		ipc->Release(ImagerIndex);
		ipcInitialized = false;
	}
}

void FormImager::AppExit(void)
{
	ReleaseIPC();
}

void FormImager::GetBitmap(Bitmap^ Bmp, array<short>^values)
{
	int stride_diff;
	// Lock the bitmap's bits.  
	System::Drawing::Rectangle rect = System::Drawing::Rectangle(0, 0, Bmp->Width, Bmp->Height);
	Imaging::BitmapData^ bmpData = Bmp->LockBits( rect, Imaging::ImageLockMode::ReadWrite, Bmp->PixelFormat );
	stride_diff = bmpData->Stride - FrameWidth*3;

	//
	//rgbValues = System.Text.Encoding.Default.GetBytes( values );
	//
	// Get the address of the first line.
	IntPtr ptr = bmpData->Scan0;

	short mn, mx;
	GetBitmap_Limits(values, &mn, &mx);
	double Fact = 255.0 / (mx - mn);
	m_MaxTempValue = (double)((values[0]-1000)/10.0);
	for ( int dst=0, src=0, y=0; y < FrameHeight; y++, dst += stride_diff) 
		for ( int x=0; x < FrameWidth; x++, src++, dst+=3 )
		{
			//获取温度信息
			whu_AllTemValues[src] = (double)((values[src]-1000)/10.0);
			//获取最高温度信息//
			if (whu_AllTemValues[src]>m_MaxTempValue)
			{ 
				m_MaxTempValue = whu_AllTemValues[src];
				m_MaxTempValuePoint.X = x;
				m_MaxTempValuePoint.Y = y;
			}
			short m_Temp = (values[src]-1000)/10;
			short m_NewValue = 1024*(m_Temp-TempMinTrackBarValue)/TempRangTrackBarValue;
			Byte m_RGBValue[3];
			whu_GetRGBValue(m_NewValue,m_RGBValue);
			rgbValues[dst] = m_RGBValue[0];//b
			rgbValues[dst+1] = m_RGBValue[1];//g
			rgbValues[dst+2] = m_RGBValue[2];//r

		}
	// Copy the RGB values back to the bitmap
	System::Runtime::InteropServices::Marshal::Copy( rgbValues, 0, ptr, rgbValues->Length );

	// Unlock the bits.
	Bmp->UnlockBits( bmpData );
	//计算平均温度//
	double m_data = 0;
	for (int i=0;i<FrameSize;i++)
	{
		m_data = m_data + whu_AllTemValues[i];
	}
	m_AverageTempValue = m_data/FrameSize;
	
}

void FormImager::whu_GetRGBValue(short value ,Byte *m_RGBValue)
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

void FormImager::GetBitmap_Limits(array<short>^Values, short *min, short *max)
{
	int y;
	double Sum, Mean, Variance;
	if(!Values) return;

	Sum = 0;
	for (y=0; y < FrameSize; y++ ) 
		Sum += Values[y];
	Mean = (double)Sum / FrameSize;
	Sum = 0;
	for (y=0; y < FrameSize; y++ ) 
		Sum += (Mean - Values[y]) * (Mean - Values[y]);
	Variance = Sum / FrameSize;
	Variance = Math::Sqrt(Variance);
	Variance *= 3;  // 3 Sigma
	*min = short(Mean - Variance);
	*max = short(Mean + Variance);
}


HRESULT FormImager::MainTimer100ms(void)
{
	Painted = false;
	if(Connected && progressBarInit->Visible)
	{
		int i = ipc->GetInitCounter(ImagerIndex);
		progressBarInit->Value = progressBarInit->Maximum - i;
		progressBarInit->Visible = (i != 0);
	}
    return S_OK;
}

HRESULT FormImager::MainTimer1000ms(void)
{
	double Mean = 0, x, last=0;
	IEnumerator^ Enum = List->GetEnumerator();
	while ( Enum->MoveNext() )
	{
		x = safe_cast<double>(Enum->Current);
		last = x;
		Mean += x;
	}
	Mean /= List->Count;
	Enum->Reset();
	while ( Enum->MoveNext() )
		x = Mean - safe_cast<double>(Enum->Current);
	List->Clear();

	//labelFramerate->Text = String::Format(L"{0:0.0}Hz", 1000.0 / Mean);//111

	if(Connected)
	{
		for(int i=0; i < groupBoxMeasureAreas->Controls->Count; i++)
			((Label^)groupBoxMeasureAreas->Controls->default[i])->Text
				= String::Format(" {0:##0.0}度", ipc->GetTempMeasureArea(ImagerIndex, i));
	}
	return S_OK;
}


void FormImager::GetSoftwareInfo(void)
{
	Dev.SoftInfo.Application	= gcnew IPCSample::Version(ipc->GetVersionApplication(ImagerIndex));
	Dev.SoftInfo.CD_DLL			= gcnew IPCSample::Version(ipc->GetVersionCD_DLL(ImagerIndex));
	Dev.SoftInfo.HID_DLL		= gcnew IPCSample::Version(ipc->GetVersionHID_DLL(ImagerIndex)); 
	Dev.SoftInfo.IPC_DLL		= gcnew IPCSample::Version(ipc->GetVersionIPC_DLL(ImagerIndex));
}

void FormImager::GetDeviceInfo(void)
{
	Dev.Info.HW_Model			= ipc->GetHardware_Model(ImagerIndex);
	Dev.Info.HW_Spec			= ipc->GetHardware_Spec(ImagerIndex);
	Dev.Info.SerialNumber		= ipc->GetSerialNumber(ImagerIndex);
	Dev.Info.SerialNumberULIS	= ipc->GetSerialNumber(ImagerIndex);
	Dev.Info.FW_MSP				= ipc->GetFirmware_MSP(ImagerIndex);
	Dev.Info.FW_Cypress			= ipc->GetFirmware_Cypress(ImagerIndex);
	Dev.Info.PID				= ipc->GetPID(ImagerIndex);
	Dev.Info.VID				= ipc->GetVID(ImagerIndex);
	Dev.Info.OpticsFOV			= ipc->GetOpticsFOV(ImagerIndex, ipc->GetOpticsIndex(ImagerIndex));
	Dev.Info.TempMinRange		= ipc->GetTempMinRange(ImagerIndex, ipc->GetTempRangeIndex(ImagerIndex));
	Dev.Info.TempMaxRange		= ipc->GetTempMaxRange(ImagerIndex, ipc->GetTempRangeIndex(ImagerIndex));
}
void FormImager::GetDeviceSetup(void)
{
	MeasureAreaCount = ipc->GetMeasureAreaCount(ImagerIndex);
}
void FormImager::RenewFlag(void)  
{
	ipc->RenewFlag(ImagerIndex);
}

void FormImager::Init(int frameWidth, int frameHeight, int frameDepth)
{
	FrameWidth = frameWidth;
	FrameHeight = frameHeight;
	FrameSize = FrameWidth * FrameHeight;
	FrameRatio = (double)FrameWidth /  (double)FrameHeight;
	FrameDepth = frameDepth;
	FrameCounter1 = LastFrameCounter = FC0 = FC1 =0;
	timer1->Enabled = true;
	bmp = gcnew Bitmap( FrameWidth , FrameHeight , System::Drawing::Imaging::PixelFormat::Format24bppRgb );
	System::Drawing::Rectangle rect = System::Drawing::Rectangle(0, 0, bmp->Width, bmp->Height);
	Imaging::BitmapData^ bmpData = bmp->LockBits( rect, Imaging::ImageLockMode::ReadWrite, bmp->PixelFormat );
	int stride = bmpData->Stride;
	bmp->UnlockBits( bmpData );
	rgbValues = gcnew array<Byte>(stride * FrameHeight);
	Values = gcnew array<short>(FrameSize);
	whu_AllTemValues = gcnew array<double>(FrameSize);

	groupBoxVideo->Size = Drawing::Size(FrameWidth, FrameHeight) + Margin;
	groupBoxMeasureAreas->Location = Drawing::Point(groupBoxMeasureAreas->Left, groupBoxVideo->Bottom + 10);
	whu_BShowMousePositionTemp = true;//是否显示鼠标点温度
	whu_BSHowRectangle = false;
	whu_BKeepRectangle = false;
	myPen = gcnew System::Drawing::Pen(System::Drawing::Color::Black);//矩形框颜色
	myPen2 = gcnew System::Drawing::Pen(System::Drawing::Color::White);//矩形框颜色
	myBrush = gcnew SolidBrush(System::Drawing::Color::Black);//平均区域温度颜色
	whu_SelectRectangle = gcnew System::Drawing::Rectangle(0,0,0,0);//选择的区域
	m_MaxTempValuePoint.X = 0;
	m_MaxTempValuePoint.Y = 0;
	m_MaxTempValue = -99;
	m_AverageTempValue = -99;
	UpdateSize();
}

void FormImager::InitMeasureAreas(void)
{
	if(MeasureAreaCount != groupBoxMeasureAreas->Controls->Count)
	{
		groupBoxMeasureAreas->SuspendLayout();
		groupBoxMeasureAreas->Controls->Clear();

		for(int i=0; i < MeasureAreaCount; i++)
		{
			Label^ lbl = gcnew Label();
			lbl->AutoSize = true;
			lbl->Location = System::Drawing::Point(10, i*15 + 16);
			lbl->Name = L"labelMeasureArea" + i.ToString();
			lbl->Text = "";
			groupBoxMeasureAreas->Controls->Add(lbl);
		}

		groupBoxMeasureAreas->Size = Drawing::Size(groupBoxMeasureAreas->Size.Width, MeasureAreaCount * 15 + 20);
		groupBoxMeasureAreas->ResumeLayout();
		UpdateSize();
	}
}

void FormImager::UpdateSize(void)
{
	int right = max(max(groupBoxVideo->Right, groupBoxMeasureAreas->Right), buttonFlagRenew->Right);
	int bottom = groupBoxMeasureAreas->Bottom;

	ClientSize = Drawing::Size(right + 10, bottom + 10);
}

HRESULT FormImager::OnServerStopped(int reason)
{
	ReleaseIPC();
	return 0;
}

HRESULT FormImager::OnFrameInit(int frameWidth, int frameHeight, int frameDepth)
{
	Init(frameWidth, frameHeight, frameDepth);
	return 0;
} 

// will work with Imager.exe release > 2.0 only:
HRESULT FormImager::OnNewFrameEx(void * pBuffer, FrameMetadata *pMetadata)
{
	//labelFrameCounter->Text = "Frame counter HW/SW: " + pMetadata->CounterHW.ToString() + "/" + pMetadata->Counter.ToString();
	//labelPIF->Text = "PIF digital/analog: " 
	//	+ ((pMetadata->PIFin >> 15) == 0).ToString() + "/"
	//	+ (pMetadata->PIFin & 0x3FF).ToString();
	return NewFrame((short*)pBuffer, pMetadata->Counter);
}

HRESULT FormImager::OnNewFrame(char * pBuffer, int frameCounter)
{
	return NewFrame((short*)pBuffer, frameCounter);
}

HRESULT FormImager::NewFrame(short *ImgBuf, int frameCounter)
{
	DateTime time = DateTime::Now;
	TimeSpan ts = time - LastFrameTime;
	List->Add(ts.TotalMilliseconds);
	LastFrameTime = time;

	FrameCounter0 = frameCounter;
	FrameCounter1++;

	for ( int x = 0; x < FrameSize; x++ ) Values[x] = ImgBuf[x];

	//if(!Painted)
	//{
		//GetBitmap(bmp, Values);
		//pictureBox->Invalidate();
		//Painted = true;
		//PassDataBetweenForm(true);
	//}

	return 0;
}

HRESULT FormImager::OnInitCompleted(void)
{
	progressBarInit->Maximum = ipc->GetInitCounter(ImagerIndex);
	progressBarInit->Value = 0;
	//progressBarInit->Visible = true;
	GetSoftwareInfo();
	GetDeviceInfo(); 
	GetDeviceSetup(); 
	InitMeasureAreas();
	//labelFW->Text = String::Format("FW: {0}", Dev.Info.FW_Cypress);
	label1->Text = L"已连接至设备 #" + Dev.Info.SerialNumber.ToString();
	Connected = true;
	return S_OK;
}

HRESULT FormImager::OnConfigChanged(long reserved)
{
	GetDeviceInfo(); 
	GetDeviceSetup(); 
	InitMeasureAreas();
	return S_OK;
}
void FormImager::SaveImage()
{
	ipc->FileSnapshot(0);
}


}
