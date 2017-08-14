
// TTPDFDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "TTPDFApp.h"
#include "TTPDFDlg.h"
#include "afxdialogex.h"
#include <boost/thread.hpp>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// TTPDFDlg ��ȭ ����



TTPDFDlg::TTPDFDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TOASTPDF_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void TTPDFDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS1, _progressCtrl);

	DDX_Control(pDX, IDC_STATIC_STATUS, _statusStatic);
	DDX_Control(pDX, IDC_STATIC_DOC_NAME, _docFilenameStatic);
	DDX_Control(pDX, IDC_STATIC_PDF_NAME, _pdFilenameStatic);
	DDX_Control(pDX, IDC_STATIC_PDF_FOLDER, _pdfFolderStatic);
}

BEGIN_MESSAGE_MAP(TTPDFDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OPEN, &TTPDFDlg::OnBnClickedOpen)
	ON_BN_CLICKED(IDCANCEL, &TTPDFDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// TTPDFDlg �޽��� ó����

BOOL TTPDFDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	
	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void TTPDFDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void TTPDFDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR TTPDFDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void TTPDFDlg::OnBnClickedOpen()
{
	// TODO: Add your control notification handler code here
	ShellExecute(NULL, NULL, _output.c_str(), NULL, NULL, SW_NORMAL);
	CDialogEx::OnOK();
}

void TTPDFDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	thePDFWorker.stop();
	CDialogEx::OnCancel();
}

// �ݹ� �Լ���
void TTPDFDlg::start(const string& docFilename, const string& pdfFilename, const string& pdfFolder, int totalpage) {
	TTPDFDlg *pPDFDlg = ((TTPDFDlg *)theApp.m_pMainWnd);
	pPDFDlg->_statusStatic.SetWindowText("PDF ��ȯ �غ� �� ...");
	pPDFDlg->_docFilenameStatic.SetWindowText(string("���� �̸�: " + docFilename).c_str());
	pPDFDlg->_pdFilenameStatic.SetWindowText(string("PDF �̸�: " + pdfFilename).c_str());
	pPDFDlg->_pdfFolderStatic.SetWindowText(string("PDF ����: " + pdfFolder).c_str());
	pPDFDlg->_progressCtrl.SetRange32(0, totalpage);
	pPDFDlg->_progressCtrl.SetPos(0);
}

void TTPDFDlg::workStatus(const string& status) {
	TTPDFDlg *pPDFDlg = ((TTPDFDlg *)theApp.m_pMainWnd);
	pPDFDlg->_statusStatic.SetWindowText(status.c_str());
}
void TTPDFDlg::progress(int page, int totalpage) {
	TTPDFDlg *pPDFDlg = ((TTPDFDlg *)theApp.m_pMainWnd);
	CString text;

	text.Format(_T("PDF ��ȯ �� ... (%d/%d)"), page, totalpage);
	pPDFDlg->_statusStatic.SetWindowText(text);
	pPDFDlg->_progressCtrl.SetPos(page);
}
void TTPDFDlg::finish() {
	TTPDFDlg *pPDFDlg = ((TTPDFDlg *)theApp.m_pMainWnd);
	pPDFDlg->_statusStatic.SetWindowText("PDF ��ȯ�� �Ϸ�Ǿ����ϴ�.");
	pPDFDlg->GetDlgItem(IDC_OPEN)->EnableWindow(TRUE);
}

void TTPDFDlg::ps2pdf(const string &input, const string &output) {
	
	_output = output;
	boost::thread pdfWorkerThread([&input, &output]() {
		boost::this_thread::sleep(boost::posix_time::milliseconds(100));
		thePDFWorker.setCallbacks(TTPDFDlg::start, TTPDFDlg::workStatus, TTPDFDlg::progress, TTPDFDlg::finish);
		thePDFWorker.ps2pdf(input, output);
	});
}
