#if !defined(AFX_ACTEASYIF_H__575A92CF_F819_4F44_869C_3D80B0C4BB42__INCLUDED_)
#define AFX_ACTEASYIF_H__575A92CF_F819_4F44_869C_3D80B0C4BB42__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//  Microsoft Visual C++ によって自動生成された IDispatch ラップ クラス

// メモ: このファイルの内容を編集しないでください。 このクラスが再度
//  Microsoft Visual C++ で生成された場合、変更を上書きします。

/////////////////////////////////////////////////////////////////////////////
// CActEasyIF ラップ クラス

class CActEasyIF : public CWnd
{
protected:
	DECLARE_DYNCREATE(CActEasyIF)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x5af69f12, 0xae9b, 0x11d3, { 0x83, 0xae, 0x0, 0xa0, 0x24, 0xbd, 0xbf, 0x2b } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName,
		LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect,
		CWnd* pParentWnd, UINT nID,
		CCreateContext* pContext = NULL)
	{ return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); }

    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect, CWnd* pParentWnd, UINT nID,
		CFile* pPersist = NULL, BOOL bStorage = FALSE,
		BSTR bstrLicKey = NULL)
	{ return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); }

// アトリビュート
public:

// オペレーション
public:
	long GetActLogicalStationNumber();
	void SetActLogicalStationNumber(long nNewValue);
	long Open();
	long Close();
	long GetCpuType(BSTR* szCpuName, long* lplCpuCode);
	long SetCpuStatus(long lOperation);
	long ReadDeviceBlock(LPCTSTR szDevice, long lSize, long* lplData);
	long WriteDeviceBlock(LPCTSTR szDevice, long lSize, long* lplData);
	long ReadDeviceRandom(LPCTSTR szDeviceList, long lSize, long* lplData);
	long WriteDeviceRandom(LPCTSTR szDeviceList, long lSize, long* lplData);
	long ReadBuffer(long lStartIO, long lAddress, long lSize, short* lpsData);
	long WriteBuffer(long lStartIO, long lAddress, long lSize, short* lpsData);
	long GetClockData(short* lpsYear, short* lpsMonth, short* lpsDay, short* lpsDayOfWeek, short* lpsHour, short* lpsMinute, short* lpsSecond);
	long SetClockData(short sYear, short sMonth, short sDay, short sDayOfWeek, short sHour, short sMinute, short sSecond);
	long SetDevice(LPCTSTR szDevice, long lData);
	long GetDevice(LPCTSTR szDevice, long* lplData);
	long CheckDeviceString(LPCTSTR szDevice, long lCheckType, long lSize, long* lplDeviceType, BSTR* lpszDeviceName, long* lplDeviceNumber, long* lplDeviceRadix);
	long EntryDeviceStatus(LPCTSTR szDeviceList, long lSize, long lMonitorCycle, long* lplData);
	long FreeDeviceStatus();
	CString GetActPassword();
	void SetActPassword(LPCTSTR lpszNewValue);
	long ReadDeviceBlock2(LPCTSTR szDevice, long lSize, short* lpsData);
	long WriteDeviceBlock2(LPCTSTR szDevice, long lSize, short* lpsData);
	long ReadDeviceRandom2(LPCTSTR szDevice, long lSize, short* lpsData);
	long WriteDeviceRandom2(LPCTSTR szDeviceList, long lSize, short* lpsData);
	long GetDevice2(LPCTSTR szDevice, short* lpsData);
	long SetDevice2(LPCTSTR szDevice, short sData);
	long Connect();
	long Disconnect();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_ACTEASYIF_H__575A92CF_F819_4F44_869C_3D80B0C4BB42__INCLUDED_)
