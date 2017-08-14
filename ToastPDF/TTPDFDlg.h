
// TTPDFDlg.h : ��� ����
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"

using namespace std;

// TTPDFDlg ��ȭ ����
class TTPDFDlg : public CDialogEx
{
// �����Դϴ�.
public:
	TTPDFDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

	void ps2pdf(const string &input, const string &output);
	
// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TOASTPDF_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.

	static void start(const string& docFilename, const string& pdfFilename, const string& pdfFolder, int totalpage);
	static void workStatus(const string& status);
	static void progress(int page, int totalpage);
	static void finish();

// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	CProgressCtrl _progressCtrl;
	CStatic _statusStatic;
	CStatic _docFilenameStatic;
	CStatic _pdFilenameStatic;
	CStatic _pdfFolderStatic;
	string  _output;
public:
	afx_msg void OnBnClickedOpen();
	afx_msg void OnBnClickedCancel();
};
