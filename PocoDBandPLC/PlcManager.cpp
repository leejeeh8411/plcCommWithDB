#include "stdafx.h"
#include "PlcManager.h"


CPlcManager::CPlcManager()
{
}


CPlcManager::~CPlcManager()
{
}

void CPlcManager::SetOCXCtrl(CActutltype1* pPlcCtrl)
{
	m_plcIF = pPlcCtrl;
}

BOOL CPlcManager::PlcOpen(int nLogicalStationNumber)
{
	BOOL bConnection = FALSE;

	long	lRet;

	m_plcIF->put_ActLogicalStationNumber(nLogicalStationNumber);
	lRet = m_plcIF->Open();

	if (lRet == 0) {
		bConnection = TRUE;
	}
	else {
		bConnection = FALSE;
	}

	//DB 커넥션
	m_db.Connect();

	ReadPLC();

	return bConnection;
}

void CPlcManager::PlcClose()
{
	m_bPlcConnection = FALSE;

	long lRet;
	lRet = m_plcIF->Close();

}

BOOL CPlcManager::ReadBlock_short(CString strAddress, int nSize, short* sValue)
{
	BOOL bret = FALSE;

	m_plcIF->ReadDeviceBlock2(strAddress, nSize, sValue);

	return bret;
}

BOOL CPlcManager::ReadBlock_long(CString strAddress, int nSize, long* lValue)
{
	BOOL bret = FALSE;

	m_plcIF->ReadDeviceBlock(strAddress, nSize, lValue);

	return bret;
}

BOOL CPlcManager::WriteBlock_short(CString strAddress, int nSize, short* sValue)
{
	BOOL bret = FALSE;

	m_plcIF->WriteDeviceBlock2(strAddress, nSize, sValue);

	return bret;
}

BOOL CPlcManager::WriteBlock_long(CString strAddress, int nSize, long* lValue)
{
	BOOL bret = FALSE;

	m_plcIF->WriteDeviceBlock(strAddress, nSize, lValue);

	return bret;
}

std::vector<st_plc_read_sch> CPlcManager::GetSchFromDB(int nBlockID)
{
	std::vector<st_plc_read_sch> vt_plcReadSch;

	m_db.ReadPLCSch(&vt_plcReadSch, nBlockID);

	return vt_plcReadSch;

}

std::vector<st_plc_address> CPlcManager::GetPlcAddressFromDB()
{
	//db에 있는 plc 어드레스 정보를 읽는다
	std::vector<st_plc_address> vt_plcAddress;
	m_db.ReadPLCAddress(&vt_plcAddress);

	return vt_plcAddress;
}

//PLC받아와야할 전체 read 정보를 처리한다.
void CPlcManager::ReadPLC()
{
	//PLC read데이터를 전반적으로 관리할 구조체
	//PLC_READ_DATA
	std::map<string, string> map_data;

	std::vector<st_plc_address> vt_address_data = GetPlcAddressFromDB(); //db에 있는 Plc 어드레스 정보를 읽는다

	int nSize = vt_address_data.size();

	for (int i = 0; i < nSize; i++) {
		int nBlockID = vt_address_data[i].blockID;
		int nBlockSize = vt_address_data[i].blockSize;
		CString strAddress = vt_address_data[i].cAddress;

		//힙 할당
		short* pPlcData = new short[nBlockSize];
		memset(pPlcData, 0, sizeof(short) * nBlockSize);
   
		ReadBlock_short(strAddress, nBlockSize, pPlcData); //힙영역 할당후 Heap포인터와 Size를 전달하여 plc로부터 data를 받는다

		std::vector<st_plc_read_sch> vt_sch_data = GetSchFromDB(nBlockID); //plc block 데이터 명세 정보 가져옴

		int nSizeSch = vt_sch_data.size();

		for(int j = 0; j < nSizeSch; j++){
			int nSttIdx = vt_sch_data[j].idxstt;
			int nSize = vt_sch_data[j].size;
			CString strKeyName = vt_sch_data[j].keyname;
			CString strType = vt_sch_data[j].cDataTypeDB;

			std::string strVal = ParsePlcData(pPlcData, nSttIdx, nSize, strType);
		}
	
		delete[] pPlcData;
	}

	//파일전체 읽기
	/*ifstream file("d:\\read.json");
	std::string strJson;
	stringstream ss;
	ss << file.rdbuf();
	strJson = ss.str();


	//json 파싱
	auto j = json::parse(strJson);

	for (json::iterator it = j.begin(); it != j.end(); ++it) {
		st_plc_address plc_address;

		std::string strKey = it.key();
		std::string strType = getTypeOfValue(it.value());
		auto value = it.value();

		if (strKey == "address") {

		}
		else if (strKey == "integer") {

		}
		else if (strKey == "double") {

		}
		else if (strKey == "string") {

		}

		int a = 10;

	}	*/
}

std::string  CPlcManager::ParsePlcData(short* pPlcData, int nIdxStt, int nSize, CString strType)
{
	std::string strRet;

	if (strType == "string") {
		CString strData = GetStringDataFromShort(&pPlcData[nIdxStt], nSize);
		strRet = strData;
	}
	else if (strType == "int") {
		CString strData;
		strData.Format("%d", pPlcData[nIdxStt]);
		strRet = strData;
	}

	return strRet;

	//test
	//read
	/*int nSizeShort = 10;
	short* sValShort = new short[nSizeShort];
	memset(sValShort, 0, sizeof(short) * nSizeShort);

	std::string strPlcAddtrss = "D1000";
	ReadBlock_short(strPlcAddtrss.c_str(), nSizeShort, sValShort);*/


	/*int nSizeLong = 1;
	long* sValLong = new long[nSizeLong];
	memset(sValLong, 0, sizeof(short) * nSizeLong);

	ReadBlock_long(strPlcAddtrss.c_str(), nSizeLong, sValLong);
	*/

	//CString strData = GetStringDataFromShort(sValShort, nSizeShort);

	//delete[] sValShort;
	//delete[] sValLong;

	//write
	/*int nSizeWrite = 10;
	short* sVal_write = new short[nSizeWrite];
	memset(sVal_write, NULL, sizeof(short) * nSizeWrite);

	TRACE("shortSize=%d \n", sizeof(short));

	CString strDataWrite = "ABCD";

	GetShortDataFromString(strDataWrite, sVal_write, 10);*/
}



CString CPlcManager::GetStringDataFromShort(short* pData, int nSize)
{
	int nSizeWithNull = (nSize * 2) + 1;
	char* cData = new char[nSizeWithNull];
	memset(cData, NULL, sizeof(char) * nSizeWithNull);

	for (int i = 0; i < nSize; i++) {
		cData[i * 2 + 0] = pData[i] & 0xFF;
		cData[i * 2 + 1] = pData[i] >> 8;
	}

	CString retString;
	retString.Format("%s", cData);

	delete[] cData;

	return retString;
}

void CPlcManager::GetShortDataFromString(CString strData, short* pData, int nSize)
{
	int nStrLength = strData.GetLength();

	char* ptrChar = (char*)pData;	//첫번째 주소

	for (int i = 0; i < nStrLength; i++) {
		if (i >= nSize) {
			break;
		}
		char cData = strData.GetAt(i);
		ptrChar[i] = cData;
	}
}



//std::string CPlcManager::getTypeOfValue(json value) 
//{
//	if (value.is_array()) return "array";
//	if (value.is_boolean()) return "boolean";
//	if (value.is_null()) return "null";
//	if (value.is_number_integer()) return "integer";
//	if (value.is_number_float()) return "double";
//	if (value.is_string()) return "string";
//	if (value.is_object()) return "object";
//
//	return "Unknown";
//}