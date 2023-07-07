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
	//m_db.Connect();

	bool bRet = m_db_pro.connect("127.0.0.1", "postgres");

	DBResult result =m_db_pro.execute("select * from PLCaddress");

	int a = 10;

	//ReadPLC();
	//WritePLC();
	//int nBlockSize = 20;
	//short* pPlcData = new short[nBlockSize];
	//memset(pPlcData, 0, sizeof(short) * nBlockSize);

	//int nSttIdx = 0;
	//int nIdxBit = 0;
	//int nSize = 1;
	//CString strType = "int";
	//CString strValue = "1234";
	//DecodingPlcData(pPlcData, nSttIdx, nIdxBit, nSize, strType, strValue);
	////WriteBlock_short("D1000", nSize, pPlcData);
	////memset(pPlcData, 0, sizeof(short) * nBlockSize);

	//CString strType2 = "bit";
	//CString strValue2 = "True";
	//nIdxBit = 4;
	//nSttIdx = 1;
	//nSize = 1;
	//DecodingPlcData(pPlcData, nSttIdx, nIdxBit, nSize, strType2, strValue2);
	////WriteBlock_short("D1001", nSize, pPlcData);
	////memset(pPlcData, 0, sizeof(short) * nBlockSize);

	//CString strType3 = "int";
	//CString strValue3 = "80000";
	//nSttIdx = 2;
	//nSize = 2;
	//DecodingPlcData(pPlcData, nSttIdx, nIdxBit, nSize, strType3, strValue3);
	////WriteBlock_short("D1005", nSize, pPlcData);
	////memset(pPlcData, 0, sizeof(short) * nBlockSize);

	//CString strType4 = "string";
	//CString strValue4 = "ABCDE";
	//nSize = 10;
	//nSttIdx = 10;
	//DecodingPlcData(pPlcData, nSttIdx, nIdxBit, nSize, strType4, strValue4);
	//WriteBlock_short("D1000", nBlockSize, pPlcData);

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
		std::string strSyncType = vt_address_data[i].cSyncType;
		if (strSyncType != "read") {
			continue;
		}
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
			int nIdxBit = vt_sch_data[j].idxbit;
			int nSize = vt_sch_data[j].size;
			std::string strKeyName = vt_sch_data[j].keyname;
			CString strType = vt_sch_data[j].cDataTypeDB;

			std::string strVal = ParsePlcData(pPlcData, nSttIdx, nIdxBit, nSize, strType);

			map_data.insert({ strKeyName, strVal });

			//키를 확인하여 원래 

		}
	
		delete[] pPlcData;
	}
	
	//정보는 가져왔는데 어떤방식으로 데이터를 만들어서 클라이언트들한테 보낼까?
	//1. 구조체 만들어서 넣는다
	//2. 
	//map_data
}

void CPlcManager::WritePLC()
{
	std::vector<st_plc_address> vt_address_data = GetPlcAddressFromDB(); //db에 있는 Plc 어드레스 정보를 읽는다

	int nSize = vt_address_data.size();

	for (int i = 0; i < nSize; i++) {
		std::string strSyncType = vt_address_data[i].cSyncType;
		if (strSyncType != "write") {
			continue;
		}

		int nBlockID = vt_address_data[i].blockID;
		int nBlockSize = vt_address_data[i].blockSize;
		CString strAddress = vt_address_data[i].cAddress;

		//힙 할당
		short* pPlcData = new short[nBlockSize];
		memset(pPlcData, 0, sizeof(short) * nBlockSize);

		std::vector<st_plc_read_sch> vt_sch_data = GetSchFromDB(nBlockID); //plc block 데이터 명세 정보 가져옴

		int nSizeSch = vt_sch_data.size();

		for (int j = 0; j < nSizeSch; j++) {
			int nSttIdx = vt_sch_data[j].idxstt;
			int nIdxBit = vt_sch_data[j].idxbit;
			int nSize = vt_sch_data[j].size;
			std::string strKeyName = vt_sch_data[j].keyname;
			CString strType = vt_sch_data[j].cDataTypeDB;

			//키에 해당하는 값을 가져온다.
			//std::string strValue = GetValue("키값");

			//타입을 보고 맞는 걸로 변환
			//DecodingPlcData(pPlcData, nSttIdx, nIdxBit, nSize, strType, strValue);
			
		}

		delete[] pPlcData;
	}
}

void  CPlcManager::DecodingPlcData(short* pPlcData, int nIdxStt, int nIdxBit, int nSize, CString strType, CString _strValue)
{
	std::string strValue = _strValue;
	if (strType == "string") {
		GetShortDataFromString(_strValue, &pPlcData[nIdxStt], 10);
	}
	else if (strType == "int") {
		CString strData;

		if (nSize == 2) {	//2word 처리
			long lValueSrc = std::stoi(strValue);
			short* pShort = (short*)&lValueSrc;
			
			pPlcData[nIdxStt] = pShort[0] & 0xFFFF;
			pPlcData[nIdxStt + 1] = pShort[1] & 0xFFFF;
		}
		else {
			pPlcData[nIdxStt] = std::stoi(strValue);
		}
	}
	else if (strType == "bit") {
		if (strValue == "True") {
			short sValue = (0x01 << nIdxBit);
			pPlcData[nIdxStt] = sValue;
		}
		else {
			short sValue = (0x00 << nIdxBit);
			pPlcData[nIdxStt] = sValue;
		}
	}
}



std::string  CPlcManager::ParsePlcData(short* pPlcData, int nIdxStt, int nIdxBit, int nSize, CString strType)
{
	std::string strRet;

	if (strType == "string") {
		CString strData = GetStringDataFromShort(&pPlcData[nIdxStt], nSize);
		strRet = strData;
	}
	else if (strType == "int") {
		CString strData;

		if (nSize == 2) {	//2word 처리
			long lValue = 0;
			short* pShort = (short*)&lValue;
			pShort[0] = pPlcData[nIdxStt] & 0xFFFF;
			pShort[1] = pPlcData[nIdxStt + 1] & 0xFFFF;
			strData.Format("%d", lValue);
		}
		else {
			strData.Format("%d", pPlcData[nIdxStt]);
		}
		
		strRet = strData;
	}
	else if (strType == "bit") {
		bool bValue = pPlcData[nIdxStt] & (0x01 << nIdxBit);

		if (bValue == true) {
			strRet = "TRUE";
		}
		else {
			strRet = "FALSE";
		}
	}

	return strRet;

}



CString CPlcManager::GetStringDataFromShort(short* pData, int nSize)
{
	int nSizeWithNull = (nSize * 2) + 1;
	char* cData = new char[nSizeWithNull];
	memset(cData, NULL, sizeof(char) * nSizeWithNull);

	for (int i = 0; i < nSize; i++) {
		cData[i * 2 + 0] = pData[i] >> 8;
		cData[i * 2 + 1] = pData[i] & 0xFF; 
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