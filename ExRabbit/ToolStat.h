#pragma once


// ToolStat 对话框

class ToolStat : public CDialogEx
{
	DECLARE_DYNAMIC(ToolStat)

public:
	ToolStat(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ToolStat();

// 对话框数据
	enum { IDD = IDD_TOOL_STAT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	typedef struct img_version_term {
		long ver;
		int count;
		CString foundInNPKname;
		CString imgPathName;
	}img_version_term;

	typedef struct frame_version_term {
		DWORD versString;		// IMGversion << 16 | PICinfo.format << 8 | PICinfo.comp e.g. "040E06"
		int count;
		CString foundInNPKname;
		CString foundInIMGname;
		int frameID;
	}frame_version_term;

	typedef union part_and_layer {
		struct {
			BYTE layer[3];
			BYTE part;
		};
		DWORD value;
	}part_and_layer;

	typedef struct pal_term {
		part_and_layer value;
		int count;
		CString disc;
		CString imgPathName;
	}pal_term;

	std::vector<img_version_term> imgVerQuery;
	std::vector<frame_version_term> frameVerQuery;
	std::vector<pal_term> palQuery;
	void updateImgBerQueryTable(const img_version_term &newTerm) {
		for(int i = 0; i < imgVerQuery.size(); i++) {
			if(imgVerQuery[i].ver == newTerm.ver) {
				imgVerQuery[i].count++;
				return;
			}
			if(imgVerQuery[i].ver > newTerm.ver) {
				imgVerQuery.insert(imgVerQuery.begin() + i, newTerm);
				return;
			}
		}
		imgVerQuery.push_back(newTerm);
	}
	void updateFrameVerQueryTable(const frame_version_term &newTerm) {
		if(frameVerQuery.size() == 0) {
			frameVerQuery.push_back(newTerm);
			return;
		}
		for(int i = 0; i < frameVerQuery.size(); i++) {
			if(frameVerQuery[i].versString == newTerm.versString) {
				frameVerQuery[i].count++;
				return;
			}
			if(frameVerQuery[i].versString > newTerm.versString) {
				frameVerQuery.insert(frameVerQuery.begin() + i, newTerm);
				return;
			}
		}
		frameVerQuery.push_back(newTerm);
	}
	void updatePalQueryTable(const pal_term &newTerm) {
		for(int i = 0; i < palQuery.size(); i++) {
			if(palQuery[i].value.value == newTerm.value.value) {
				palQuery[i].count++;
				return;
			}
			if(palQuery[i].value.value > newTerm.value.value) {
				palQuery.insert(palQuery.begin() + i, newTerm);
				return;
			}
		}
		palQuery.push_back(newTerm);
	}
	DeclareThreadFunc(ToolStat, Tool1, int);
	DeclareThreadFunc(ToolStat, Tool2, int);
	DeclareThreadFunc(ToolStat, Tool3, int);
public:
	afx_msg void OnBnClickedButtonSelect();
	afx_msg void OnBnClickedButtonTool1();
	afx_msg void OnBnClickedButtonTool2();
	afx_msg void OnBnClickedButtonTool3();
	virtual BOOL OnInitDialog();


};
