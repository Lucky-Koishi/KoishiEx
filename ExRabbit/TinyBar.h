#pragma once


// TinyBar 对话框

class TinyBar : public CDialogEx
{
	DECLARE_DYNAMIC(TinyBar)

public:
	TinyBar(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~TinyBar();

// 对话框数据
	enum { IDD = IDD_TINY_PROGRESSBAR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	void setMax(long value);
	void setPos(long value);
	void setInfo(CString info);
	void setInfo(CString info, long value);
	void show();
	void show(long value);
	void hide();
};
