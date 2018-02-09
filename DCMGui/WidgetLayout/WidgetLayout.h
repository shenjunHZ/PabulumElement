#ifndef __DSGUI_WIDGETLAYOUT_H
#define __DSGUI_WIDGETLAYOUT_H

#include "DomNode/DomNodeResolve.h"
#include "ComGuiDef.h"

#include <QWidget>
#include <QList>
#include <QGridLayout>

#define MAX_WNDSPLIT_COUT			12
#define MAX_SPLIT_SIZE				8
#define MAX_SPLIT_WND_COUNT			(MAX_SPLIT_SIZE * MAX_SPLIT_SIZE)
#define MAX_NODE_COUNT				100


namespace DSGUI
{
	class DSSingleWnd;

	typedef struct struSubWnd{
		int wndID;								// 子窗口的索引号
		int wndColumn;							// 行号
		int wndRow;
		int wndHStretch;						// 子窗口行比例值
		int wndVStretch;						// 子窗口列比例值
	}subWnd;

	typedef struct struNode{
		QString splitName;						// 分割类型名
		int typeIndex;							// 分割类型索引号
		int wndNum;								// 窗口分割数
		QString rowStretch;						// 列比例
		QString columnStretch;					// 行比例
		int wndRows;							// 行数，计算得到
		int wndColumns;							// 列数
		subWnd subWnds[MAX_SPLIT_WND_COUNT];	// 子窗口
	}wndNode;


	/** @class DSWidgetLayout
	  * @brief 窗口分割功能实现类
	  */
	class DSWidgetLayout
	{
	public:
		// 构造
		DSWidgetLayout(const QString& strXmlFile);
		// 析构
		~DSWidgetLayout();

	public:
		bool Init(QWidget* pParent, struLayoutData::LayoutType enumLayoutType = struLayoutData::D_2x2_4);
        bool UnInit();

    public:
		//bool ReLayout(LayoutType eunmType);
		// 计算窗口矩形位置
		QRect CalWndFrameRect(int iWndIndex, struLayoutData::LayoutType eunmType);

		struLayoutData::LayoutType GetLayoutType() const;

		int GetRows(struLayoutData::LayoutType eunmType) const;
		int GetColumns(struLayoutData::LayoutType eunmType) const;

		// 自定义分割布局保存
		// 增加布局类型
		bool AddLayoutInXml(const QString& strXmlFile, wndNode CustomNode);
		// 修改布局类型（覆盖）
		bool ModifyLayoutInXml(const QString& strXmlFile, wndNode CustomNode);

    /*public:
		void ShowMaximized(int iIndex);
		bool IsMaximized(int iIndex) const;
		void ShowNormal();*/

    public:
		//QWidget* GetWidget(int iIndex) const;
        //bool GetWidgets(QList<QWidget*>& listWidgets);

	private:
		// 提取Xml中的数据，保存到结点对应的结构体
		void getDataFromXml();

		// 获取某一分割类型在xml中的索引号
		int GetIndexOfXML(struLayoutData::LayoutType eunmType) const;

		// 改变子窗口的数目
		void ChangeSingleWndNum();



	private:
		QWidget*			m_pParent;							// 父窗口
		struLayoutData::LayoutType		m_enumlayoutType;					// 当前窗口分割类型
		int					m_iIndex;							// 当前窗口分割在xml中的索引号
		wndNode				m_struWndNodes[MAX_NODE_COUNT];		// 保存每种分割类型的参数
		wndNode				m_struCustomWndNodes;
		int					m_iNodeNum;							// 窗口布局的分割种类数目
		int					m_iCustomNodeNum;
		DSDomNodeResolve	m_dNode;							// 默认
		DSDomNodeResolve	m_dCustomNode;						// 自定义
		bool				m_bIsMaximized;						// 是否最大化
	};
}

#endif
