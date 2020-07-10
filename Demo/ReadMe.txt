========================================================================
    控制台应用程序：Demo 项目概述
========================================================================

应用程序向导已为您创建了此 Demo 应用程序。

本文件概要介绍组成 Demo 应用程序的每个文件的内容。


Demo.vcxproj
    这是使用应用程序向导生成的 VC++ 项目的主项目文件，
    其中包含生成该文件的 Visual C++ 
    的版本信息，以及有关使用应用程序向导选择的平台、配置和项目功能的信息。

Demo.vcxproj.filters
    这是使用“应用程序向导”生成的 VC++ 项目筛选器文件。 
    它包含有关项目文件与筛选器之间的关联信息。 在 IDE 
    中，通过这种关联，在特定节点下以分组形式显示具有相似扩展名的文件。
    例如，“.cpp”文件与“源文件”筛选器关联。

Demo.cpp
    这是主应用程序源文件。

/////////////////////////////////////////////////////////////////////////////
其他标准文件：

StdAfx.h，StdAfx.cpp
    这些文件用于生成名为 Demo.pch 的预编译头 (PCH) 文件和
    名为 StdAfx.obj 的预编译类型文件。

/////////////////////////////////////////////////////////////////////////////
其他注释：

应用程序向导使用“TODO:”注释来指示应添加或自定义的源代码部分。

/////////////////////////////////////////////////////////////////////////////
void swap(int x, double in1, double in2, double in3, double in4, double &out1, double &out2, double &out3, double &out4){
#define XX(x0,i1,i2,i3,i4)	if(x0==x){out1=in##i1,out2=in##i2,out3=in##i3,out4=in##i4;}
	XX(0x00,1,2,3,4);
	XX(0x01,1,2,4,3);
	XX(0x02,1,3,2,4);
	XX(0x03,1,3,4,2);
	XX(0x04,1,4,2,3);
	XX(0x05,1,4,3,2);
	XX(0x06,2,1,3,4);
	XX(0x07,2,1,4,3);
	XX(0x08,2,3,1,4);
	XX(0x09,2,3,4,1);
	XX(0x0A,2,4,1,3);
	XX(0x0B,2,4,3,1);
	XX(0x0C,3,1,2,4);
	XX(0x0D,3,1,4,2);
	XX(0x0E,3,2,1,4);
	XX(0x0F,3,2,4,1);
	XX(0x10,3,4,1,2);
	XX(0x11,3,4,2,1);
	XX(0x12,4,1,2,3);
	XX(0x13,4,1,3,2);
	XX(0x14,4,2,1,3);
	XX(0x15,4,2,3,1);
	XX(0x16,4,3,1,2);
	XX(0x17,4,3,2,1);
#undef XX
}
// x:5
void oper(int x, double in1, double in2, double&out){
#define XX(x0,op)	if(x0==x){out=in1##op##in2;}
	XX(0x00, +);
	XX(0x01, -);
	XX(0x02, *);
	XX(0x03, /);
	XX(0x04, -in1+pow(in1,in2)+in2-);
#undef XX
}
str mm[14] = {"0","1","2","3","4","5","6","7","8","9","10","J","Q","K"};
str oo[5] = {"+","-","*","/","^"};
queue test(double para1, double para2, double para3, double para4){
	sequence s;
	std::vector<str> ss, s0,ss0;
	for(int i = 0;i<24;i++){
		register double p1,p2,p3,p4;
		swap(i,para1,para2,para3,para4,p1,p2,p3,p4);
		for(int j1 = 0;j1<5;j1++){
			for(int j2 = 0;j2<5;j2++){
				for(int j3 = 0;j3<5;j3++){
					double d1,d2,d3;
					oper(j1, p1, p2, d1);oper(j2, p3, p4, d2);oper(j3, d1, d2, d3);if(d3<LONG_MAX){s.push_back(d3);ss.push_back("("+mm[(int)p1]+oo[j1]+mm[(int)p2]+")"+oo[j3]+"("+mm[(int)p3]+oo[j2]+mm[(int)p4]+")");}
					oper(j1, p1, p2, d1);oper(j2, d1, p3, d2);oper(j3, d2, p4, d3);if(d3<LONG_MAX){s.push_back(d3);ss.push_back("(("+mm[(int)p1]+oo[j1]+mm[(int)p2]+")"+oo[j2]+mm[(int)p3]+")"+oo[j3]+mm[(int)p4]);}
					oper(j1, p2, p3, d1);oper(j2, p1, d1, d2);oper(j3, d2, p4, d3);if(d3<LONG_MAX){s.push_back(d3);ss.push_back("("+mm[(int)p1]+oo[j2]+"("+mm[(int)p2]+oo[j1]+mm[(int)p3]+"))"+oo[j3]+mm[(int)p4]);}
					oper(j1, p2, p3, d1);oper(j2, d1, p4, d2);oper(j3, p1, d2, d3);if(d3<LONG_MAX){s.push_back(d3);ss.push_back(mm[(int)p1]+oo[j3]+"(("+mm[(int)p2]+oo[j1]+mm[(int)p3]+")"+oo[j2]+mm[(int)p4]+")");}
					oper(j1, p3, p4, d1);oper(j2, p2, d1, d2);oper(j3, p1, d2, d3);if(d3<LONG_MAX){s.push_back(d3);ss.push_back(mm[(int)p1]+oo[j3]+"("+mm[(int)p2]+oo[j2]+"("+mm[(int)p3]+oo[j1]+mm[(int)p4]+"))");}
				}
			}
		}
	}
	queue q,q0;
	for(int i = 0;i<s.size();i++){
		double p0 = s[i];
		double p1 = ceil(s[i]);
		double p2 = floor(s[i]);
		int isInt = 0;
		if(abs(p0 - p2) < 0.00001){
			p0 = p2;
			isInt = 1;
		}
		if(abs(p0 - p1) < 0.00001){
			p0 = p1;
			isInt = 1;
		}
		if(p0 <= 0){
			isInt = 0;
		}
		if(isInt == 1){
			//是正整数
			q0.push_back((int)p0);
			s0.push_back(ss[i]);
		}
	}
	for(int i = 0;i<q0.size();i++){
		//寻找q里是否存在
		int found = 0;
		for(int j = 0;j<q.size();j++){
			if(q[j] == q0[i]){
				found = 1;
				break;
			}
		}
		
		if(!found){
			q.push_back(q0[i]);
			ss0.push_back(s0[i]);
		}
	}
	return q;
}