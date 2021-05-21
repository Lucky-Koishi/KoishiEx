#pragma once


// ModalLoseBlackPicture 对话框

class ModalLoseBlackPicture : public CDialogEx
{
	DECLARE_DYNAMIC(ModalLoseBlackPicture)

public:
	ModalLoseBlackPicture(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ModalLoseBlackPicture();

// 对话框数据
	enum { IDD = IDD_MODAL_LOSEBLACK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	
	afx_msg void OnBnClickedRadioTarget1();
	afx_msg void OnBnClickedRadioTarget2();
	afx_msg void OnBnClickedRadioTarget3();

	//传出
	struct INPUT{
		IMGversion version;
	}in;
	struct OUTPUT{
		int target;		//选择项1-2
		int gamma;		//1.PNG 2.IMG
	}out;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
