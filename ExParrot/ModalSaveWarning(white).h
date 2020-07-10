#pragma once


// ModalSaveWarning 对话框

class ModalSaveWarning : public CDialogEx
{
	DECLARE_DYNAMIC(ModalSaveWarning)

public:
	ModalSaveWarning(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ModalSaveWarning();

// 对话框数据
	enum { IDD = IDD_MODAL_SAVE_WARNING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	enum _alertType{
		MODIFIED_SND, MODIFIED_NPK, MODIFIED_SND_NPK
	}alertType;
	enum _returnType {
		RETURN_CANCEL, RETURN_NO_SAVE, RETURN_SAVE, RETURN_ALL_SAVE
	}returnType;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonSaveleft();
	afx_msg void OnBnClickedButtonSaveright();
	afx_msg void OnBnClickedButtonContinue();
	afx_msg void OnBnClickedButtonCancel();
};
