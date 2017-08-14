
// TTPDF.cpp : ���� ���α׷��� ���� Ŭ���� ������ �����մϴ�.
//

#include "stdafx.h"
#include <boost/regex.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp> 
#include <boost/process.hpp>
#include <TlHelp32.h>
#include "TTPDFApp.h"
#include "TTPDFDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


using namespace boost::program_options;

pair<string, string> reg_foo(const string& s)
{
	if (s.find("-f") == 0) {
		if (s.substr(2, 3) == "no-")
			return make_pair(s.substr(5), string("false"));
		else
			return make_pair(s.substr(2), string("true"));
	}
	else {
		return make_pair(string(), string());
	}
}

// TTPDFApp

BEGIN_MESSAGE_MAP(TTPDFApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// TTPDFApp ����

TTPDFApp::TTPDFApp()
{
	// �ٽ� ���� ������ ����
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	// InitInstance�� ��� �߿��� �ʱ�ȭ �۾��� ��ġ�մϴ�.
}

// ������ TTPDFApp ��ü�Դϴ�.

TTPDFApp theApp;

//
TTPDFWorker thePDFWorker;

// TTPDFApp �ʱ�ȭ
BOOL TTPDFApp::InitInstance()
{
	// ���� ���α׷� �Ŵ��佺Ʈ�� ComCtl32.dll ���� 6 �̻��� ����Ͽ� ���־� ��Ÿ����
	// ����ϵ��� �����ϴ� ���, Windows XP �󿡼� �ݵ�� InitCommonControlsEx()�� �ʿ��մϴ�.
	// InitCommonControlsEx()�� ������� ������ â�� ���� �� �����ϴ�.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ���� ���α׷����� ����� ��� ���� ��Ʈ�� Ŭ������ �����ϵ���
	// �� �׸��� �����Ͻʽÿ�.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();
	
	AfxEnableControlContainer();

	// ��ȭ ���ڿ� �� Ʈ�� �� �Ǵ�
	// �� ��� �� ��Ʈ���� ���ԵǾ� �ִ� ��� �� �����ڸ� ����ϴ�.
	CShellManager *pShellManager = new CShellManager;

	// MFC ��Ʈ���� �׸��� ����ϱ� ���� "Windows ����" ���־� ������ Ȱ��ȭ
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// �Ķ���Ϳ� ���� ������ ó��
	options_description desc("Allowed options");
	desc.add_options()("action,a", value<string>(), "action : doc2pdf");
	desc.add_options()("input,i", value<string>(), "postscript file");
	desc.add_options()("output,o", value<string>(), "pdf file");
	desc.add_options()("silent,s", "silent");
	
	variables_map vm;
	store(command_line_parser(__argc, __argv).options(desc).extra_parser(reg_foo).run(), vm);

	if (vm.empty() || vm["action"].as<string>() != "doc2pdf") { // ����Ȯ�� �Ķ���Ͷ�� ����
		return FALSE;
	}

	if (vm["input"].empty()) { // �Է�����(Postscript)�� ����ִٸ�

		// 1) ����Ʈ��ũ��Ʈ ��� ���� ����
		string ps_path = TTUtil::getOutputPostscript();
		if (ps_path.empty()) {
			ps_path = TTUtil::currentPath() + "\\temp\\" + TTUtil::getRandomString() + ".ps";
		}

		// 2) ǥ���Է� ��Ʈ���� ����Ʈ��ũ��Ʈ�� ����
		if (!thePDFWorker.stdin2ps(ps_path)) {
			return FALSE;
		}
		
		// 3) Silent ��尡 �ƴ϶�� Postscript ���� ���� �� PDF ��ȯ ����
		if (!TTUtil::silent() && vm["silent"].empty()) {
			string args;
			args = "-a doc2pdf";
			args += " -i \"" + ps_path + "\"";

			ShellExecute(NULL, NULL, TTUtil::getModuleFileName().c_str(), args.c_str(), NULL, SW_NORMAL);
		}
		
		// 4) ���� ����
		TTUtil::reset();

		return FALSE;
	}
	
	// Postscript �Է�����
	string input = vm["input"].as<string>();

	// Silent ����̰� ������� ������ ������� �ʴٸ� Silent ���� ����
	if ((TTUtil::silent() || !vm["silent"].empty()) && !vm["output"].empty()) {
		thePDFWorker.ps2pdf(input, vm["output"].as<string>());
		return FALSE;
	}
	
	// �������� ��ȭ���ڷκ��� PDF �����θ� �����Ѵ�.
	string output = TTUtil::getOutputFromSaveDialog(m_hInstance);

	// PDF ���������� ����ִٸ�(����ڿ� ���� ���) ����
	if (output.empty()) {
		return FALSE;
	}

	// PDF ��ȯ ���̾�α� Ȱ��ȭ
	TTPDFDlg dlg;
	m_pMainWnd = &dlg;
	
	dlg.ps2pdf(input, output);

	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: ���⿡ [Ȯ��]�� Ŭ���Ͽ� ��ȭ ���ڰ� ������ �� ó����
		//  �ڵ带 ��ġ�մϴ�.
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: ���⿡ [���]�� Ŭ���Ͽ� ��ȭ ���ڰ� ������ �� ó����
		//  �ڵ带 ��ġ�մϴ�.
	}
	else if (nResponse == -1)
	{
		
	}

	// ������ ���� �� �����ڸ� �����մϴ�.
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

#ifndef _AFXDLL
	ControlBarCleanUp();
#endif

	// ��ȭ ���ڰ� �������Ƿ� ���� ���α׷��� �޽��� ������ �������� �ʰ�  ���� ���α׷��� ���� �� �ֵ��� FALSE��
	// ��ȯ�մϴ�.
	return FALSE;
}

