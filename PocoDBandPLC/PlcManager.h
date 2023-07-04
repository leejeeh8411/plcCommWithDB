#pragma once

#include "actutltype1.h"

class CPlcManager
{
public:
	CPlcManager();
	~CPlcManager();

	CActutltype1*	m_plcIF;

	void SetOCXCtrl(CActutltype1* pPlcCtrl);
	BOOL PlcOpen(int nLogicalStationNumber);
	void PlcClose();
	BOOL m_bPlcConnection;
	int m_nPlcStationNum;
	BOOL ReadBlock_short(CString strAddress, int nSize, short* sValue);
	BOOL ReadBlock_long(CString strAddress, int nSize, long* lValue);
	BOOL WriteBlock_short(CString strAddress, int nSize, short* sValue);
	BOOL WriteBlock_long(CString strAddress, int nSize, long* lValue);
};

