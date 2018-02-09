/**
* Copyright (c) 2012
* All rights reserved.
*
* 文件名称：DCMDefine.h
* 文件标识：
* 摘　　要：DCM的通用定义
*
* 当前版本：1.0 
* 原作者　：jl
* 完成日期：2012年12月24日 
* 修订记录：
*/

#ifndef INCLUDE_DCMDEFINE_H
#define INCLUDE_DCMDEFINE_H

#include "ClientPluginAPI/TypeDef.h"
#include <vector>
#include <map>
#include <iostream>
#include <string>

//DCM命名空间
#ifndef BEGIN_NAMESPACE_DCM 
#define BEGIN_NAMESPACE_DCM namespace DCM {
#endif

#ifndef END_NAMESPACE_DCM 
#define END_NAMESPACE_DCM }
#endif

#ifdef WIN32
#define  dcmRect RECT
#define  dcmLong LONG
#define  dcmDWORD DWORD
#define  dcmHDC HDC
#else
struct dcmRect
{
	long    left;
	long    top;
	long    right;
	long    bottom;
};

#define __stdcall
#define dcmLong int
#define dcmDWORD unsigned int
#define dcmHDC void*


#endif

#define MAX_SPLIT_SIZE				8
#define MAX_SPLIT_WND_COUNT			(MAX_SPLIT_SIZE * MAX_SPLIT_SIZE)

namespace DCM
{
	typedef struct tagCustomWnd{

		tagCustomWnd(void){}
		tagCustomWnd(bool bEnable, int nCombine, int x1, int y1, int x2, int y2)
			: bEnable(bEnable)
			, nCombine(nCombine)
			, x1(x1)
			, y1(y1)
			, x2(x2)
			, y2(y2)
		{

		}

		bool operator!=(const tagCustomWnd& src)
		{
			if(bEnable != src.bEnable)return true;
			if(nCombine != src.nCombine)return true;
			if(x1 != src.x1)return true;
			if(y1 != src.y1)return true;
			if(x2 != src.x2)return true;
			if(y2 != src.y2)return true;

			return false;
		}

		tagCustomWnd& operator=(const tagCustomWnd& other)
		{
			bEnable = other.bEnable;
			nCombine = other.nCombine;
			x1 = other.x1;
			y1 = other.y1;
			x2 = other.x2;
			y2 = other.y2;

			return *this;
		}

		bool bEnable;
		int nCombine;
		int x1;
		int y1;
		int x2;
		int y2;
	}SmartWnd_CustomWnd_t;

	typedef struct tagSplitInfo{

		bool operator==(const tagSplitInfo& src)
		{
			if(nRow != src.nRow)return false;
			if(nCol != src.nCol)return false;
			if(nSplitCount != src.nSplitCount)return false;

			int nCount = nRow * nCol;
			for (int i = 0; i < nCount; ++i)
			{
				if (stuWnds[i] != src.stuWnds[i])
				{
					return false;
				}
			}

			return true;
		}

		tagSplitInfo& operator=(const tagSplitInfo& other)
		{
			nRow = other.nRow;
			nCol = other.nCol;
			nSplitCount = other.nSplitCount;
			for (int i = 0; i < MAX_SPLIT_WND_COUNT; i++)
			{
				stuWnds[i] = other.stuWnds[i];
			}

			return *this;
		}

		int nRow;
		int nCol;
		int nSplitCount;
		SmartWnd_CustomWnd_t stuWnds[MAX_SPLIT_WND_COUNT];
		tagSplitInfo()
		{
			nRow = 0;
			nCol = 0;
			nSplitCount = 0;
		}

		void Reset()
		{
			nRow = 0;
			nCol = 0;
			nSplitCount = 0;
			for ( int i = 0; i < MAX_SPLIT_WND_COUNT; i++ )
			{
				stuWnds[i].bEnable = false;
				stuWnds[i].nCombine = 0;
				stuWnds[i].x1 = 0;
				stuWnds[i].x2 = 0;
				stuWnds[i].y1 = 0;
				stuWnds[i].y2 = 0;
			}
		}

		//////////////////////////////////////////////////////////////////////////
	private:
		int GetCustomWnds(int* outnRow, int* outnCol, std::vector<SmartWnd_CustomWnd_t>* outCustomWnds)
		{
			if (outnRow == NULL || outnCol == NULL || outCustomWnds == NULL)
			{
				return -1;
			}

			outCustomWnds->clear();

			*outnRow = this->nRow;
			*outnCol = this->nCol;

			int nCount = (*outnRow) * (*outnCol);
			for (int i=0; i<nCount; i++)
			{
				outCustomWnds->push_back(this->stuWnds[i]);
			}

			return 0;
		}
		int SaveCustomWnds(const int& newnRow, const int& newnCol, const std::vector<SmartWnd_CustomWnd_t>& vecCustomWnds)
		{
			if ((int)vecCustomWnds.size() < newnRow * newnCol)
				return -1;

			memset(this, 0, sizeof(tagSplitInfo));
			this->nRow = newnRow;
			this->nCol = newnCol;
			this->nSplitCount = 0;
			int nCount = newnRow * newnCol;
			for (int i=0; i<nCount; i++)
			{
				this->stuWnds[i] = vecCustomWnds[i];
				if (this->stuWnds[i].bEnable)
				{
					this->nSplitCount++;
				}
			}

			return 0;
		}
	public:
		void AddRow(void)
		{
			std::vector<SmartWnd_CustomWnd_t> vecCustomWnds;
			int tmpnRow;
			int tmpnCol;
			GetCustomWnds(&tmpnRow, &tmpnCol, &vecCustomWnds);

			if (tmpnRow == MAX_SPLIT_SIZE)
				return;

			int nCount = tmpnRow * tmpnCol;
			for (int i=0; i<tmpnCol; i++)
			{
				vecCustomWnds.push_back(SmartWnd_CustomWnd_t(true,nCount,i,tmpnRow,i+1,tmpnRow+1));
				nCount++;
			}
			tmpnRow++;


			SaveCustomWnds(tmpnRow, tmpnCol, vecCustomWnds);
		}

		void SubRow(void)
		{
			std::vector<SmartWnd_CustomWnd_t> vecCustomWnds;
			int tmpnRow;
			int tmpnCol;
			GetCustomWnds(&tmpnRow, &tmpnCol, &vecCustomWnds);

			if (tmpnRow == 1)
				return;

			std::vector<SmartWnd_CustomWnd_t>::iterator itWnd = vecCustomWnds.begin() + (tmpnRow - 1) * tmpnCol;
			while (itWnd != vecCustomWnds.end())
			{
				itWnd = vecCustomWnds.erase(itWnd);
			}

			tmpnRow--;
			for (int i=0; i<(int)vecCustomWnds.size(); i++)
			{
				SmartWnd_CustomWnd_t& wnd = vecCustomWnds[i];
				if (wnd.y2 > tmpnRow)
				{
					wnd.y2 = tmpnRow;
				}
			}

			SaveCustomWnds(tmpnRow, tmpnCol, vecCustomWnds);
		}
		void AddCol(void)
		{
			std::vector<SmartWnd_CustomWnd_t> vecCustomWnds;
			int tmpnRow;
			int tmpnCol;
			GetCustomWnds(&tmpnRow, &tmpnCol, &vecCustomWnds);

			if (tmpnCol == MAX_SPLIT_SIZE)
				return;

			for (int i=0; i<tmpnRow; i++)
			{
				vecCustomWnds.push_back(SmartWnd_CustomWnd_t());
			}

			// 移动窗口信息
			tmpnCol++;
			for (int i=(int)vecCustomWnds.size()-1; i>=tmpnCol-1; i--)
			{
				int y = i / tmpnCol;
				if ((i+1) % tmpnCol == 0)
				{
					vecCustomWnds[i] = SmartWnd_CustomWnd_t(true,i,tmpnCol-1,y,tmpnCol,y+1);
				}
				else
				{
					vecCustomWnds[i] = vecCustomWnds[i-y];
					vecCustomWnds[i].nCombine = i;
				}
			}

			// 重置nCombine
			for (int i=0; i<(int)vecCustomWnds.size(); i++)
			{
				for (int j=i+1; j<(int)vecCustomWnds.size(); j++)
				{
					SmartWnd_CustomWnd_t& src = vecCustomWnds[i];
					SmartWnd_CustomWnd_t& dst = vecCustomWnds[j];
					if (src.x1==dst.x1 && src.y1==dst.y1 && src.x2==dst.x2 && src.y2==dst.y2)
					{
						vecCustomWnds[j].nCombine = vecCustomWnds[i].nCombine;
					}
				}
			}

			SaveCustomWnds(tmpnRow, tmpnCol, vecCustomWnds);
		}

		void SubCol(void)
		{
			std::vector<SmartWnd_CustomWnd_t> vecCustomWnds;
			int tmpnRow;
			int tmpnCol;
			GetCustomWnds(&tmpnRow, &tmpnCol, &vecCustomWnds);

			if (tmpnCol == 1)
				return;

			// 移动窗口信息
			std::vector<SmartWnd_CustomWnd_t>::iterator itWnd = vecCustomWnds.begin() + tmpnCol-1;
			for (int i=tmpnCol-1; itWnd!=vecCustomWnds.end(); i++)
			{
				if (i >= (tmpnRow * (tmpnCol-1)))
				{
					itWnd = vecCustomWnds.erase(itWnd);
					continue;
				}

				int y = i / (tmpnCol - 1);
				vecCustomWnds[i] = vecCustomWnds[i+y];
				vecCustomWnds[i].nCombine = i;
				itWnd++;	
			}

			tmpnCol--;
			for (int i=0; i<(int)vecCustomWnds.size(); i++)
			{
				SmartWnd_CustomWnd_t& wnd = vecCustomWnds[i];
				if (wnd.x2 > tmpnCol)
				{
					wnd.x2 = tmpnCol;
				}
			}

			// 重置nCombine
			for (int i=0; i<(int)vecCustomWnds.size(); i++)
			{
				for (int j=i+1; j<(int)vecCustomWnds.size(); j++)
				{
					SmartWnd_CustomWnd_t& src = vecCustomWnds[i];
					SmartWnd_CustomWnd_t& dst = vecCustomWnds[j];
					if (src.x1==dst.x1 && src.y1==dst.y1 && src.x2==dst.x2 && src.y2==dst.y2)
					{
						vecCustomWnds[j].nCombine = vecCustomWnds[i].nCombine;
					}
				}
			}

			SaveCustomWnds(tmpnRow, tmpnCol, vecCustomWnds);
		}
		//////////////////////////////////////////////////////////////////////////
	}SmartWnd_SplitInfo_t;

	typedef struct Change_WndInfo
	{
		bool						bSplitWnd;			//是否自定义分割  true则struWndSplitInfo有效  false则nWndCount有效
		DCM::SmartWnd_SplitInfo_t	struWndSplitInfo;	//自定义分割信息
		int							nWndCount;			//窗口数
	}Change_WndInfo_t;

	typedef struct WndChannel_Info
	{
		typedef enum
		{
			NODE_CHANNEL,										//通道节点
			NODE_EMAP,											//地图节点
		}Node_type_e;
		DSPluginAPI::Code codeChannel;							//通道ID
		int nStreamType;										//码流类型	
		int nNodeType;											//节点类型		值取为Node_type_e
		WndChannel_Info()
		{
			nStreamType = 0;
			nNodeType = NODE_CHANNEL;
		}
	}WndChannel_Info_t;

	typedef std::vector<WndChannel_Info_t>	VecWndChannel_Info;

	/*
		视图数据结构
		数据数据主要由GroupLogical和PreviewLogical使用
	*/
	typedef struct View_Node
	{
		DSPluginAPI::Code codeView;								//视图编号
		std::string strName;									//视图名称
		bool bSplitWnd;											//是否有自由分割窗口
		DCM::SmartWnd_SplitInfo_t struSplitWndInfo;				//窗口分割信息
		std::map<int, VecWndChannel_Info> mapWndChannelInfo;	//<窗口序号, 窗口绑定的通道信息>
	}View_Node_t;

	/*
		语音对讲参数
		涉及多个模块使用，定义放到公共头文件中
	*/
	typedef enum{
		Talk_Coding_Default =0,		//default
		Talk_Coding_PCM = 1,		//PCM
		Talk_Coding_G711a,			//G711a
		Talk_Coding_AMR,			//AMR
		Talk_Coding_G711u,			//G711u
		Talk_Coding_G726,			//G726
		Talk_Coding_AAC = 8,        //add by fengjian 2012.8.8
		Talk_Coding_G722 = 101,		//G722 海康设备使用
		Talk_Coding_G711_MU,		//G711 海康使用
	}Audio_Type_e;					//音频类型

	typedef enum
	{
		Talk_Audio_Bits_8  = 8,
		Talk_Audio_Bits_16 = 16,
	}Talk_Bits_e;					//位数

	typedef enum
	{
		Talk_Audio_Sam_8K  = 8000,
		Talk_Audio_Sam_16K = 16000,
		Talk_Audio_Sam_32K = 32000,
		Talk_Audio_Sam_48K = 48000,
		Talk_Audio_Sam_8192 = 8192,
	}Talk_Sample_Rate_e;			//精度

	//通道支持的功能(EncChannelInfo::m_strCameraFunction)
	typedef enum
	{
		CAM_FUN_NONE		= 0x00,	//无
		CAM_FUN_FISHEYE		= 0x01,	//鱼眼=>与cms定过协议
		CAM_FUN_EFOCUS		= 0x02,	//电动聚焦=>与cms定过协议
		CAM_FUN_FISHEYEEX	= 0x04,	//鱼眼，支持前端矫正
		CAM_FUN_PTZ			= 0x100000,//云台功能，该定义只是为了在客户端容易区分功能，判断过球机+云台权限后可赋该值
	}cam_fun_e;
}


#endif