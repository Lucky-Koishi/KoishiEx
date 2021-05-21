#pragma once


// ModalInsertTexture 对话框

class ModalInsertTexture : public CDialogEx
{
	DECLARE_DYNAMIC(ModalInsertTexture)

public:
	ModalInsertTexture(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ModalInsertTexture();

// 对话框数据
	enum { IDD = IDD_MODAL_INSERT_TEXTURE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

public:
	//传入
	struct INPUT{
		bool firstInsert;
		TEXinfo ti;
		int maxTEXcount;
	}in;
	//传出
	struct OUTPUT{
		void *context;
		int operate;		//选择项1-4
		bool adjustTexID;	//调整纹理集引用帧的引用纹理集编号
		int outputFormat;	//选择项1-4
		CString fileName;	//资源文件名
		int inputFormat;	//0.空 1.PNG 2.DDS
	}out;
	afx_msg void OnBnClickedRadioOperate1();
	afx_msg void OnBnClickedRadioOperate2();
	afx_msg void OnBnClickedRadioOperate3();
	afx_msg void OnBnClickedRadioOperate4();
	afx_msg void OnBnClickedRadioFormat1();
	afx_msg void OnBnClickedRadioFormat2();
	afx_msg void OnBnClickedRadioFormat3();
	afx_msg void OnBnClickedRadioFormat4();
	afx_msg void OnBnClickedButtonResource();
	afx_msg void OnBnClickedOk();

	void updateRadio();
};
