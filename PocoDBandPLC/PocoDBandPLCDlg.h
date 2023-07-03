
// PocoDBandPLCDlg.h : 헤더 파일
//

#pragma once

#include "PocoDB.h"
#include <vector>

// CPocoDBandPLCDlg 대화 상자
class CPocoDBandPLCDlg : public CDialogEx
{
// 생성입니다.
public:
	CPocoDBandPLCDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

	CPocoDB m_db;

	bool CPocoDBandPLCDlg::ConnectDB();
	void CPocoDBandPLCDlg::SelectDB();

	void CPocoDBandPLCDlg::ReadPlc();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_POCODBANDPLC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
