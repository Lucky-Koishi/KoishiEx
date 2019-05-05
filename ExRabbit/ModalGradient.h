#pragma once


// ModalGradient 对话框

class ModalGradient : public CDialogEx
{
	DECLARE_DYNAMIC(ModalGradient)

public:
	ModalGradient(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ModalGradient();

// 对话框数据
	enum { IDD = IDD_MODAL_GRADIENT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	struct OUTPUT{
		int target;
		colorProperty useProperty;
		color keyColor1;
		color keyColor2;
		bool remainAlpha;
	}out;
	afx_msg void OnBnClickedRadioTarget1();
	afx_msg void OnBnClickedRadioTarget2();
	afx_msg void OnBnClickedRadioTarget3();
	afx_msg void OnBnClickedRadioOperate1();
	afx_msg void OnBnClickedRadioOperate2();
	afx_msg void OnBnClickedRadioOperate3();
	afx_msg void OnBnClickedRadioOperate4();
	afx_msg void OnBnClickedRadioOperate5();
	afx_msg void OnBnClickedButtonColor1();
	afx_msg void OnBnClickedButtonColor2();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	void drawScale();
	afx_msg void OnPaint();
	afx_msg void OnEnChangeEditKeyalpha1();
	afx_msg void OnEnChangeEditKeyalpha2();
};
