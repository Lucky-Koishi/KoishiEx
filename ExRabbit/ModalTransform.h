#pragma once
#include "TinyBar.h"

// ModalTransform �Ի���

class ModalTransform : public CDialogEx
{
	DECLARE_DYNAMIC(ModalTransform)

public:
	ModalTransform(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ModalTransform();

// �Ի�������
	enum { IDD = IDD_MODAL_IMAGE_TRASFORM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	struct INPUT{
		IMGobject *contextIO;
		colorList contextColorList;
		long currentFrame;
		long currentPalette;
	}in;
	TinyBar bar;
	struct OUTPUT{
		int target;
		IMGversion version;
		colorFormat outputFormat;
		bool useNewPalette;
		bool makeTexture;
		colorTable useColorPalette;
	}out;
	int currentPaletteID;

	void updateRadio();
	void updatePaletteList();
	void updatePalette();
	afx_msg void OnBnClickedRadioOperate1();
	afx_msg void OnBnClickedRadioOperate2();
	afx_msg void OnBnClickedRadioOperate3();
	afx_msg void OnBnClickedRadioType1();
	afx_msg void OnBnClickedRadioType2();
	afx_msg void OnBnClickedRadioType3();
	afx_msg void OnBnClickedRadioType4();
	afx_msg void OnBnClickedRadioFormat1();
	afx_msg void OnBnClickedRadioFormat2();
	afx_msg void OnBnClickedRadioFormat3();
	afx_msg void OnBnClickedRadioFormat4();
	afx_msg void OnBnClickedRadioFormat5();
	afx_msg void OnBnClickedButtonGetPalette();
	afx_msg void OnLbnSelchangeListPalette();
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRadioUseNewPalette();
	afx_msg void OnBnClickedRadioUseOldPalette();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedCheckUseTexture();
	afx_msg void OnMenuIndexingCurrent();
	afx_msg void OnMenuIndexingBase();
	afx_msg void OnMenuIndexing16();
	afx_msg void OnMenuIndexing64();
	afx_msg void OnMenuIndexing256();
	afx_msg void OnMenuIndexingBaseOnFrame();
	afx_msg void OnMenuIndexingBaseOnImage();
	afx_msg void OnMenuIndexingImportPhotoshop();
	afx_msg void OnMenuIndexingImportRabbit();

	static UINT pickColorFrame(void*context);
	static UINT pickColorImage(void*context);
};
