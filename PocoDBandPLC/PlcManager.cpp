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


void CPlcManager::ReadPLC()
{
	//PLC read�����͸� ���������� ������ ����ü
	//PLC_READ_DATA

	//vector<����ü> vt_address_data = GetPlcAddressFromDB(); //db�� �ִ� Plc ��巹�� ������ �д´�

	//int nSize = vt_address_data.Size();

	/*for (int i = 0; i < nSize; i++) {
		int nBlockID = vt_address_data[i].blockID;
		int nBlockSize = vt_address_data[i].blockSize;
		CString strAddress = vt_address_data[i].cAddress;

		//�� �Ҵ�
		short* pPlcData = new short[nBlockSize];
		memset(pPlcData, 0, sizeof(short) * nBlockSize);

		ReadPlcData(strAddress, nBlockSize, pPlcData);   //������ �Ҵ��� Heap�����Ϳ� Size�� �����Ͽ� plc�κ��� data�� �޴´�

		vector<����ü> vt_sch_data = GetSchFromDB(nBlockID);

		int nSizeSch = vt_sch_data.size();

		for(int j = 0; j < nSizeSch; j++){
			ParsePlcData();
		}
	
		delete[] pPlcData;

	}*/

	
	
	
}