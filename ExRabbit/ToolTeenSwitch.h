#pragma once


// ToolTeenSwitch 对话框

class ToolTeenSwitch : public CDialogEx
{
	DECLARE_DYNAMIC(ToolTeenSwitch)

public:
	ToolTeenSwitch(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ToolTeenSwitch();

// 对话框数据
	enum { IDD = IDD_TOOL_TEEN_SWITCH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	virtual BOOL OnInitDialog();

public:
	CString infoString;
	std::vector<CString> loadKeyWordFile();
	void showKeyWordFile();
	void addInfo(const CString &rString);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnBnClickedButton4();

public:
	DeclareThreadFunc(ToolTeenSwitch, Make18plus, INT);
	DeclareThreadFunc(ToolTeenSwitch, Make18plus1, std::vector<CString>);
	static CString addPrefix(CString ori, CString prf) {
		return prf + ori;
	}
	static CString addSuffix(CString ori, CString suf) {
		CString noExt = ori.Left(ori.GetLength() - 4);
		return noExt + suf + L".img";
	}
	afx_msg void OnDropFiles(HDROP hDropInfo);
};
