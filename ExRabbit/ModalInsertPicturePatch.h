#pragma once


// ModalInsertPicturePatch 对话框

class ModalInsertPicturePatch : public CDialogEx
{
	DECLARE_DYNAMIC(ModalInsertPicturePatch)

public:
	ModalInsertPicturePatch(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ModalInsertPicturePatch();

// 对话框数据
	enum { IDD = IDD_MODAL_INSERT_PICTURE_PATCH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedRadioOperate1();
	afx_msg void OnBnClickedRadioOperate2();
	afx_msg void OnBnClickedRadioFormat1();
	afx_msg void OnBnClickedRadioFormat2();
	afx_msg void OnBnClickedRadioFormat3();
	afx_msg void OnBnClickedRadioFormat4();
	afx_msg void OnBnClickedRadioMethod1();
	afx_msg void OnBnClickedRadioMethod2();
	afx_msg void OnBnClickedOk();

public:
	//传入
	struct INPUT{
		IMGversion version;
		int maxPICcount;
	}in;
	//传出
	struct OUTPUT{
		int operate;		//选择项1-2
		bool holdCoordinate;//operate=2时， 是否保留原坐标
		int outputFormat;	//选择项1-4
		CString filePath;	//PNG时为所在资源文件夹名，IMG时为IMG文件名
		int PNGcount;		//资源为PNG时，提取出PNG个数，数值上等于的最大帧号加1（因为包含0）
		int inputFormat;	//1.PNG 2.IMG
	}out;
};
