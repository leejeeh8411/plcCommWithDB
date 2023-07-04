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

	//DB Ŀ�ؼ�
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
	//db�� �ִ� plc ��巹�� ������ �д´�
	std::vector<st_plc_address> vt_plcAddress;
	m_db.ReadPLCAddress(&vt_plcAddress);

	return vt_plcAddress;
}

//PLC�޾ƿ;��� ��ü read ������ ó���Ѵ�.
void CPlcManager::ReadPLC()
{
	//PLC read�����͸� ���������� ������ ����ü
	//PLC_READ_DATA
	std::map<string, string> map_data;

	std::vector<st_plc_address> vt_address_data = GetPlcAddressFromDB(); //db�� �ִ� Plc ��巹�� ������ �д´�

	int nSize = vt_address_data.size();

	for (int i = 0; i < nSize; i++) {
		int nBlockID = vt_address_data[i].blockID;
		int nBlockSize = vt_address_data[i].blockSize;
		CString strAddress = vt_address_data[i].cAddress;

		//�� �Ҵ�
		short* pPlcData = new short[nBlockSize];
		memset(pPlcData, 0, sizeof(short) * nBlockSize);
   
		ReadBlock_short(strAddress, nBlockSize, pPlcData); //������ �Ҵ��� Heap�����Ϳ� Size�� �����Ͽ� plc�κ��� data�� �޴´�

		std::vector<st_plc_read_sch> vt_sch_data = GetSchFromDB(nBlockID); //plc block ������ �� ���� ������

		int nSizeSch = vt_sch_data.size();

		for(int j = 0; j < nSizeSch; j++){
			int nSttIdx = vt_sch_data[j].idxstt;
			int nSize = vt_sch_data[j].size;
			ParsePlcData(pPlcData, nSttIdx, nSize, &map_data);	//�Ľ��ѵ�, �ش� keyname���� value�� ���� �����Ѵ�
		}
	
		delete[] pPlcData;
	}

	//������ü �б�
	/*ifstream file("d:\\read.json");
	std::string strJson;
	stringstream ss;
	ss << file.rdbuf();
	strJson = ss.str();


	//json �Ľ�
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

std::map<string, string> CPlcManager::ParsePlcData()
{

}

std::string CPlcManager::getTypeOfValue(json value) 
{
	if (value.is_array()) return "array";
	if (value.is_boolean()) return "boolean";
	if (value.is_null()) return "null";
	if (value.is_number_integer()) return "integer";
	if (value.is_number_float()) return "double";
	if (value.is_string()) return "string";
	if (value.is_object()) return "object";

	return "Unknown";
}