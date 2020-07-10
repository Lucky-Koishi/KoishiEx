#pragma once


// ModalAdvancedMix �Ի���

class ModalAdvancedMix : public CDialogEx
{
	DECLARE_DYNAMIC(ModalAdvancedMix)

public:
	ModalAdvancedMix(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ModalAdvancedMix();

// �Ի�������
	enum { IDD = IDD_MODAL_ADVANCED_MIXING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	CString enumStr1[6];
	CString enumStr2[9];
	int currentSelect;
	struct INPUT {
		std::vector<str> layerName;
	}in;
	struct OUTPUT{
		queue preprocessing;
		queue mixMethod;
	}out;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnCbnSelchangeComboPreprocess();
	afx_msg void OnCbnSelchangeComboMixMethod();
	afx_msg void OnLvnItemchangedListLayer(NMHDR *pNMHDR, LRESULT *pResult);
};
