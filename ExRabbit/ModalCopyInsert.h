#pragma once


// ModalCopyInsert 对话框

class ModalCopyInsert : public CDialogEx
{
	DECLARE_DYNAMIC(ModalCopyInsert)

public:
	ModalCopyInsert(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ModalCopyInsert();

// 对话框数据
	enum { IDD = IDD_MODAL_IMAGE_INSERT_COPY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRadioOperate1();
	afx_msg void OnBnClickedRadioOperate2();
	afx_msg void OnBnClickedRadioInput1();
	afx_msg void OnBnClickedRadioInput2();

public:
	struct INPUT{
		CString pathName;
	}in;
	struct OUTPUT{
		int operate;
		int type;
		CString pathName;
	}out;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
