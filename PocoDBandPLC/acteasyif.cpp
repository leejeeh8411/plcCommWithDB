// Microsoft Visual C++ �Ŏ����������ꂽ IDispatch ���b�v �N���X

// ����: ���̃t?�C���̓��e��ҏW���Ȃ��ł��������B ���̃N���X���ēx
//  Microsoft Visual C++ �Ő������ꂽ�ꍇ�A�ύX���㏑�����܂��B


#include "stdafx.h"
#include "acteasyif.h"

/////////////////////////////////////////////////////////////////////////////
// CActEasyIF

IMPLEMENT_DYNCREATE(CActEasyIF, CWnd)

/////////////////////////////////////////////////////////////////////////////
// CActEasyIF �v���p�e�B

/////////////////////////////////////////////////////////////////////////////
// CActEasyIF �I�y��?�V����

long CActEasyIF::GetActLogicalStationNumber()
{
	long result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CActEasyIF::SetActLogicalStationNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CActEasyIF::Open()
{
	long result;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CActEasyIF::Close()
{
	long result;
	InvokeHelper(0x3, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CActEasyIF::GetCpuType(BSTR* szCpuName, long* lplCpuCode)
{
	long result;
	static BYTE parms[] =
		VTS_PBSTR VTS_PI4;
	InvokeHelper(0x4, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		szCpuName, lplCpuCode);
	return result;
}

long CActEasyIF::SetCpuStatus(long lOperation)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x5, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		lOperation);
	return result;
}

long CActEasyIF::ReadDeviceBlock(LPCTSTR szDevice, long lSize, long* lplData)
{
	long result;
	static BYTE parms[] =
		VTS_BSTR VTS_I4 VTS_PI4;
	InvokeHelper(0x6, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		szDevice, lSize, lplData);
	return result;
}

long CActEasyIF::ReadDeviceBlock2(LPCTSTR szDevice, long lSize, short* lpsData)
{
	long result;
	static BYTE parms[] =
		VTS_BSTR VTS_I4 VTS_PI2;
	InvokeHelper(0x15, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		szDevice, lSize, lpsData);
	return result;
}


long CActEasyIF::WriteDeviceBlock(LPCTSTR szDevice, long lSize, long* lplData)
{
	long result;
	static BYTE parms[] =
		VTS_BSTR VTS_I4 VTS_PI4;
	InvokeHelper(0x7, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		szDevice, lSize, lplData);
	return result;
}

long CActEasyIF::WriteDeviceBlock2(LPCTSTR szDevice, long lSize, short* lpsData)
{
	long result;
	static BYTE parms[] =
		VTS_BSTR VTS_I4 VTS_PI2;
	InvokeHelper(0x16, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		szDevice, lSize, lpsData);
	return result;
}

long CActEasyIF::ReadDeviceRandom(LPCTSTR szDeviceList, long lSize, long* lplData)
{
	long result;
	static BYTE parms[] =
		VTS_BSTR VTS_I4 VTS_PI4;
	InvokeHelper(0x8, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		szDeviceList, lSize, lplData);
	return result;
}

long CActEasyIF::WriteDeviceRandom(LPCTSTR szDeviceList, long lSize, long* lplData)
{
	long result;
	static BYTE parms[] =
		VTS_BSTR VTS_I4 VTS_PI4;
	InvokeHelper(0x9, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		szDeviceList, lSize, lplData);
	return result;
}

long CActEasyIF::ReadBuffer(long lStartIO, long lAddress, long lSize, short* lpsData)
{
	long result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4 VTS_PI2;
	InvokeHelper(0xa, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		lStartIO, lAddress, lSize, lpsData);
	return result;
}

long CActEasyIF::WriteBuffer(long lStartIO, long lAddress, long lSize, short* lpsData)
{
	long result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4 VTS_PI2;
	InvokeHelper(0xb, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		lStartIO, lAddress, lSize, lpsData);
	return result;
}

long CActEasyIF::GetClockData(short* lpsYear, short* lpsMonth, short* lpsDay, short* lpsDayOfWeek, short* lpsHour, short* lpsMinute, short* lpsSecond)
{
	long result;
	static BYTE parms[] =
		VTS_PI2 VTS_PI2 VTS_PI2 VTS_PI2 VTS_PI2 VTS_PI2 VTS_PI2;
	InvokeHelper(0xc, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		lpsYear, lpsMonth, lpsDay, lpsDayOfWeek, lpsHour, lpsMinute, lpsSecond);
	return result;
}

long CActEasyIF::SetClockData(short sYear, short sMonth, short sDay, short sDayOfWeek, short sHour, short sMinute, short sSecond)
{
	long result;
	static BYTE parms[] =
		VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_I2;
	InvokeHelper(0xd, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		sYear, sMonth, sDay, sDayOfWeek, sHour, sMinute, sSecond);
	return result;
}

long CActEasyIF::SetDevice(LPCTSTR szDevice, long lData)
{
	long result;
	static BYTE parms[] =
		VTS_BSTR VTS_I4;
	InvokeHelper(0xe, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		szDevice, lData);
	return result;
}

long CActEasyIF::GetDevice(LPCTSTR szDevice, long* lplData)
{
	long result;
	static BYTE parms[] =
		VTS_BSTR VTS_PI4;
	InvokeHelper(0xf, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		szDevice, lplData);
	return result;
}

long CActEasyIF::CheckDeviceString(LPCTSTR szDevice, long lCheckType, long lSize, long* lplDeviceType, BSTR* lpszDeviceName, long* lplDeviceNumber, long* lplDeviceRadix)
{
	long result;
	static BYTE parms[] =
		VTS_BSTR VTS_I4 VTS_I4 VTS_PI4 VTS_PBSTR VTS_PI4 VTS_PI4;
	InvokeHelper(0x10, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		szDevice, lCheckType, lSize, lplDeviceType, lpszDeviceName, lplDeviceNumber, lplDeviceRadix);
	return result;
}

long CActEasyIF::EntryDeviceStatus(LPCTSTR szDeviceList, long lSize, long lMonitorCycle, long* lplData)
{
	long result;
	static BYTE parms[] =
		VTS_BSTR VTS_I4 VTS_I4 VTS_PI4;
	InvokeHelper(0x11, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		szDeviceList, lSize, lMonitorCycle, lplData);
	return result;
}

long CActEasyIF::FreeDeviceStatus()
{
	long result;
	InvokeHelper(0x12, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

CString CActEasyIF::GetActPassword()
{
	CString result;
	InvokeHelper(0x14, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CActEasyIF::SetActPassword(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x14, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}




long CActEasyIF::ReadDeviceRandom2(LPCTSTR szDevice, long lSize, short* lpsData)
{
	long result;
	static BYTE parms[] =
		VTS_BSTR VTS_I4 VTS_PI2;
	InvokeHelper(0x17, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		szDevice, lSize, lpsData);
	return result;
}

long CActEasyIF::WriteDeviceRandom2(LPCTSTR szDeviceList, long lSize, short* lpsData)
{
	long result;
	static BYTE parms[] =
		VTS_BSTR VTS_I4 VTS_PI2;
	InvokeHelper(0x18, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		szDeviceList, lSize, lpsData);
	return result;
}

long CActEasyIF::GetDevice2(LPCTSTR szDevice, short* lpsData)
{
	long result;
	static BYTE parms[] =
		VTS_BSTR VTS_PI2;
	InvokeHelper(0x19, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		szDevice, lpsData);
	return result;
}

long CActEasyIF::SetDevice2(LPCTSTR szDevice, short sData)
{
	long result;
	static BYTE parms[] =
		VTS_BSTR VTS_I2;
	InvokeHelper(0x1a, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		szDevice, sData);
	return result;
}

long CActEasyIF::Connect()
{
	long result;
	InvokeHelper(0x1b, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CActEasyIF::Disconnect()
{
	long result;
	InvokeHelper(0x1c, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}
