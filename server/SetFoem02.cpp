#include "SetForm02.h"
#include "FormMulti.h"
namespace IPCSample {
void SetForm02::InitializeValues()
{

	TempMinTrackBarValue = trackBar1->Value - 20;
	TempRangTrackBarValue = trackBar2->Value;
	Lin_LocalDataSource = textBoxDataSource->Text;
	Lin_LocalDataBaseName = textBoxInitialCatalog->Text;
	Lin_RemoteDataSource = textBoxRemoteDataSource->Text;
	Lin_RemoteDataBaseName = textBoxRemoteDataBase->Text;
	Lin_RemoteUserName = textBoxUser->Text;
	Lin_RemoteUserPwd = textBoxPWD->Text;
	Lin_Saved = false;
	Lin_IP = IpAddress->Text;
}

}
