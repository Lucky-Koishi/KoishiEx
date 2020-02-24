#pragma once


// ModalSoundInsert 对话框

class ModalSoundInsert : public CDialogEx
{
	DECLARE_DYNAMIC(ModalSoundInsert)

public:
	ModalSoundInsert(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ModalSoundInsert();

// 对话框数据
	enum { IDD = IDD_MODAL_SOUND_INSERT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRadioOperate1();
	afx_msg void OnBnClickedRadioOperate2();
	afx_msg void OnBnClickedRadioOperate3();
	afx_msg void OnBnClickedRadioInput1();
	afx_msg void OnBnClickedRadioInput2();
	afx_msg void OnBnClickedRadioInput3();
	afx_msg void OnBnClickedRadioInput4();
	afx_msg void OnBnClickedRadioConflick1();
	afx_msg void OnBnClickedRadioConflick2();
	afx_msg void OnBnClickedRadioConflick3();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();

public:
	struct INPUT{
		bool firstInsert;
	}in;
	struct OUTPUT{
		int operate;
		int type;
		CString pathName;	//全路径名
		CString fileName;	//文本框
		int conflict;
	}out;
};
