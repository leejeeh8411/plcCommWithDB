#pragma once

//���δ��̾�α׿��� ocx �߰��� �� �����Ǵ� ���Ϸ� ���ٰ�
#include "actutltype1.h"

//#include <fstream>
//#include <sstream>
#include <map>
#include "PocoDB.h"
//#include "nlohmann\json.hpp"

//const auto JSON_INDENT = 2;

//using json = nlohmann::json;

class CPlcManager
{
public:
	CPlcManager();
	~CPlcManager();

	//ocx ���� �߰��� �� �ʱ�ȭ �� ������ �Ѱ��ٰ�
	CActutltype1*	m_plcIF;

	CPocoDB m_db;

	void SetOCXCtrl(CActutltype1* pPlcCtrl);
	BOOL PlcOpen(int nLogicalStationNumber);
	void PlcClose();
	BOOL m_bPlcConnection;
	int m_nPlcStationNum;
	BOOL ReadBlock_short(CString strAddress, int nSize, short* sValue);
	BOOL ReadBlock_long(CString strAddress, int nSize, long* lValue);
	BOOL WriteBlock_short(CString strAddress, int nSize, short* sValue);
	BOOL WriteBlock_long(CString strAddress, int nSize, long* lValue);

	void CPlcManager::ReadPLC();
	void CPlcManager::WritePLC();
	std::vector<st_plc_read_sch> CPlcManager::GetSchFromDB(int nBlockID);
	std::vector<st_plc_address> CPlcManager::GetPlcAddressFromDB();
	std::string CPlcManager::ParsePlcData(short* pPlcData, int nIdxStt, int nIdxBit, int nSize, CString strType);
	void  CPlcManager::DecodingPlcData(short* pPlcData, int nIdxStt, int nIdxBit, int nSize, CString strType, CString _strValue);

	CString CPlcManager::GetStringDataFromShort(short* pData, int nSize);
	void CPlcManager::GetShortDataFromString(CString strData, short* pData, int nSize);

	//std::string CPlcManager::getTypeOfValue(json value);
};

