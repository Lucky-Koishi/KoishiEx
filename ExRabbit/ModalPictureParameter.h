#pragma once


// ModalPictureParameter 对话框

class ModalPictureParameter : public CDialogEx
{
	DECLARE_DYNAMIC(ModalPictureParameter)

public:
	ModalPictureParameter(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ModalPictureParameter();

// 对话框数据
	enum { IDD = IDD_MODAL_MODIFY_PICTURE_PARAMETER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	//输入
	struct INPUT{
		long curFH, curFW;
		long curBX, curBY;
	}in;
public:
	//输出
	struct OUTPUT{
		int target;
		int operate;
		bool enable[2];
		int para[2];
	}out;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRadioTarget1();
	afx_msg void OnBnClickedRadioTarget2();
	afx_msg void OnBnClickedRadioTarget3();
	afx_msg void OnBnClickedRadioOperate1();
	afx_msg void OnBnClickedRadioOperate2();
	afx_msg void OnBnClickedRadioOperate3();
	afx_msg void OnBnClickedOk();
};
