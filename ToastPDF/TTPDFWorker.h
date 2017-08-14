#pragma once
#include <string>
#include <boost/function.hpp>
#include <boost/process.hpp>

using namespace std;
using namespace boost::process;

typedef boost::function<void(const string& docFilename, const string& pdfFilename, const string& pdfFolder, int totalpage)> t_start_callback;
typedef boost::function<void(const string& status)> t_work_status_callback;
typedef boost::function<void (int page, int totalpage)> t_progress_callback;
typedef boost::function<void()> t_finish_callback;

class TTPDFWorker
{
public:
	TTPDFWorker();
	~TTPDFWorker();
	
	// ǥ���Է� ��Ʈ���� Postcript�� ����(Silent ���)
	bool stdin2ps(const string& ps);

	// Postscript�� PDF�� ����
	void ps2pdf(const string& input, const string& output);

	// ��ȯ ����, ����, ���� �ݹ� �Լ� ���
	void setCallbacks(
		t_start_callback start = t_start_callback(),
		t_work_status_callback status = t_work_status_callback(),
		t_progress_callback progress = t_progress_callback(),
		t_finish_callback finish = t_finish_callback()
	);

	// ��ȯ ����
	void stop();

protected:
	
	// Postscript�κ��� ��ü ���������� ����
	int _getPageCount(const string& input);

protected:
	static t_start_callback _start_callback;
	static t_work_status_callback _status_callback;
	static t_progress_callback _progress_callback;
	static t_finish_callback _finish_callback;
	

	child *_process;

	bool _canceled;
};

