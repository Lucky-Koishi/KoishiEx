#pragma once


// ModalPictureStretch 对话框

class ModalPictureStretch : public CDialogEx
{
	DECLARE_DYNAMIC(ModalPictureStretch)

public:
	ModalPictureStretch(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ModalPictureStretch();

// 对话框数据
	enum { IDD = IDD_MODAL_PICTURE_STRETCH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	//输入
	struct __input {
		long imgX1, imgY1, imgX2, imgY2;
		long curX1, curX2, curY1, curY2;
	}in;
public:
	//输出
	enum __mode{
		PIXEL_MODE, RATIO_MODE
	};
	struct __output {
		enumSelectType target;
		__mode mode;
		BOOL enable[4];
		long para[4];
	}out;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRadioTarget1();
	afx_msg void OnBnClickedRadioTarget2();
	afx_msg void OnBnClickedRadioTarget3();
	afx_msg void OnBnClickedRadioOperate1();
	afx_msg void OnBnClickedRadioOperate2();


	afx_msg void OnBnClickedOk();
};
