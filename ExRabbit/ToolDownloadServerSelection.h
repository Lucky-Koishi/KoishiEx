#pragma once


// ToolDownloadServerSelection 对话框

class ToolDownloadServerSelection : public CDialogEx
{
	DECLARE_DYNAMIC(ToolDownloadServerSelection)

public:
	ToolDownloadServerSelection(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ToolDownloadServerSelection();

// 对话框数据
	enum { IDD = IDD_TOOL_DOWNLOAD_SERVER_SELECTION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	SERVER_INFO serverInfo;
	std::vector<SERVER_REGION> list;
	std::vector<CRect> rcRegion;
	std::vector<CRect> rcRegionBack;
	std::vector<std::vector<CRect>> rcServer;
	std::vector<CRect> rcCtrl;
	CRect rcFull;
	void loadServerList();
	void defaultServerList();
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

private:
	BOOL firstDraw;
	void initLayout();
	void drawLayout();
	void addButton(CRect rc, image &im, color btnColor);
	void quickSetFont(CFont *ft, int size, CString fontName, BOOL isBold, BOOL isItalic, BOOL isUnderline);
	void drawText(CRect rc, CString myString, CFont *ft, COLORREF fontColor);
	CFont dataFont, *oldFont;
public:
	afx_msg void OnPaint();
};
