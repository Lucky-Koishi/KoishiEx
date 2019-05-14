#pragma once


// ModalImageRemove 对话框

class ModalImageRemove : public CDialogEx
{
	DECLARE_DYNAMIC(ModalImageRemove)

public:
	ModalImageRemove(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ModalImageRemove();

// 对话框数据
	enum { IDD = IDD_MODAL_IMAGE_REMOVE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	struct OUTPUT{
		int operate;
	}out;
	afx_msg void OnBnClickedRadioOperate1();
	afx_msg void OnBnClickedRadioOperate2();
	afx_msg void OnBnClickedRadioOperate3();
	virtual BOOL OnInitDialog();
};
