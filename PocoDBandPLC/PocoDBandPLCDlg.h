
// PocoDBandPLCDlg.h : ��� ����
//

#pragma once


#include <vector>
#include "actutltype1.h"
#include "PlcManager.h"
//#include "UniQueue.h"

// CPocoDBandPLCDlg ��ȭ ����
class CPocoDBandPLCDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CPocoDBandPLCDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

	
	CPlcManager m_plcManager;
	


// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_POCODBANDPLC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	//CActeasyif1 m_plcCtrl;
	CActutltype1 m_plcCtrl2;
};
