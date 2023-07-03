#include "stdafx.h"
#include "PlcManager.h"


CPlcManager::CPlcManager()
{
}


CPlcManager::~CPlcManager()
{
}

BOOL CPlcManager::PlcOpen(int nLogicalStationNumber)
{
	BOOL bConnection = FALSE;

	long	lRet;

	m_ActEasyIF.SetActLogicalStationNumber(nLogicalStationNumber);	// Exec set-property method 
	lRet = m_ActEasyIF.Open();	// Open method exec
							
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
	lRet = m_ActEasyIF.Close();

}

BOOL CPlcManager::ReadBlock_short(CString strAddress, int nSize, short* sValue)
{
	BOOL bret = FALSE;

	m_ActEasyIF.ReadDeviceBlock2(strAddress, nSize, sValue);

	return bret;
}

BOOL CPlcManager::ReadBlock_long(CString strAddress, int nSize, long* lValue)
{
	BOOL bret = FALSE;

	m_ActEasyIF.ReadDeviceBlock(strAddress, nSize, lValue);

	return bret;
}

BOOL CPlcManager::WriteBlock_short(CString strAddress, int nSize, short* sValue)
{
	BOOL bret = FALSE;

	m_ActEasyIF.WriteDeviceBlock2(strAddress, nSize, sValue);

	return bret;
}

BOOL CPlcManager::WriteBlock_long(CString strAddress, int nSize, long* lValue)
{
	BOOL bret = FALSE;

	m_ActEasyIF.WriteDeviceBlock(strAddress, nSize, lValue);

	return bret;
}
