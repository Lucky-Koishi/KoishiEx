#pragma once


// ModalAddMark 对话框

class ModalAddMark : public CDialogEx
{
	DECLARE_DYNAMIC(ModalAddMark)

public:
	ModalAddMark(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ModalAddMark();

// 对话框数据
	enum { IDD = IDD_MODAL_ADD_MARK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	struct IN{
		IMGversion version;
		colorList list;
	}in;
	struct OUTPUT{
		int target;
		int operate;
		int xDelta;
		int yDelta;
		CString text;
		int useColorID;
		color useColor;
	}out;
	afx_msg void OnBnClickedRadioTarget1();
	afx_msg void OnBnClickedRadioTarget2();
	afx_msg void OnBnClickedRadioTarget3();
	afx_msg void OnBnClickedRadioOperate1();
	afx_msg void OnBnClickedRadioOperate2();
	afx_msg void OnBnClickedRadioOperate3();
	afx_msg void OnBnClickedRadioOperate4();
	afx_msg void OnBnClickedRadioOperate5();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonColor();
};
