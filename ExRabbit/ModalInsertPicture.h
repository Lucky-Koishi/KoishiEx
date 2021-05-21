#pragma once


// ModalInsertPicture 对话框

class ModalInsertPicture : public CDialogEx
{
	DECLARE_DYNAMIC(ModalInsertPicture)

public:
	ModalInsertPicture(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ModalInsertPicture();

// 对话框数据
	enum { IDD = IDD_MODAL_INSERT_PICTURE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	//传入
	struct INPUT{
		bool firstInsert;
		IMGversion version;
		PICinfo pi;
		int maxPICcount;
		int maxTEXcount;
	}in;
	//传出
	struct OUTPUT{
		void *context;
		int operate;		//选择项1-5
		int type;			//选择项1-3
		int outputFormat;	//选择项1-4
		CString fileName;	//资源文件名
		int inputFormat;	//0.空 1.PNG 2.DDS
		int para[10];		//其余参数
	}out;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRadioOperate1();
	afx_msg void OnBnClickedRadioOperate2();
	afx_msg void OnBnClickedRadioOperate3();
	afx_msg void OnBnClickedRadioOperate4();
	afx_msg void OnBnClickedRadioOperate5();
	afx_msg void OnBnClickedRadioType1();
	afx_msg void OnBnClickedRadioType2();
	afx_msg void OnBnClickedRadioType3();
	afx_msg void OnBnClickedRadioFormat1();
	afx_msg void OnBnClickedRadioFormat2();
	afx_msg void OnBnClickedRadioFormat3();
	afx_msg void OnBnClickedRadioFormat4();
	afx_msg void OnBnClickedButtonResource();
	afx_msg void OnBnClickedOk();
};
