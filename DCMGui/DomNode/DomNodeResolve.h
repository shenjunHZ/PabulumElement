#ifndef __DSGUI_DOMNODERESOLVE_H
#define __DSGUI_DOMNODERESOLVE_H

#include "DSGuiGlobal.h"
#include <QtXml/QDomDocument>

namespace DSGUI
{
	/** @class DSDomNodeResolve
	  * @brief 基于Qt的QDomNode类解析xml
	  */
	class DS_GUI_EXPORT DSDomNodeResolve
	{
	public:
		// 构造
		DSDomNodeResolve();
		// 析够
		~DSDomNodeResolve();

	public:
		//////////////////////////////////////////////////////////////////////////
		// 读取部分
        //////////////////////////////////////////////////////////////////////////
		// 读取XML文件
		bool LoadXML(const QString& strFileName);
        // 加载字符
        bool LoadContent(const QByteArray& byteArrayText);
		// 获得子节点数量
		int GetChildNodeCount() const;
		// 获取子节点
		DSDomNodeResolve GetChild(int iIndex) const;
		// 通过节点名获取子节点
		DSDomNodeResolve FindChildByNodeName(const QString& strNodeName) const;
		// 获取节点名称
		QString GetNodeName() const;
        // 获取节点值
        bool GetNodeValue(QString& strNodeValue) const;
        QString GetNodeValue() const;
		// 通过标签名获取值，若获取不到，返回参数2
		QString GetAttribute(const QString& strTagValue, const QString& strDefValue = QString()) const;
		
	public:
		//////////////////////////////////////////////////////////////////////////
		// 保存xml部分
		//////////////////////////////////////////////////////////////////////////
		// 保存文件
		bool SaveXML(const QString& strFileName);
        // 保存为QByteArray
        QByteArray SaveAsByteArray() const; 
		// 创建根节点
		bool CreateRootNode(const QString& strName);
		// 添加为子节点
		DSDomNodeResolve CreateChildNode(const QString& strNodeName);
		// 设置当前节点值
		bool SetNodeValue(const QString& strValue);
		// 设置当前节点名以及值
		bool SetAttribute(const QString& strTagValue, const QString& strValue);
		//删除子节点
		bool RemoveChildNode(int iIndex);
	
	private:
		QDomElement m_domElement;
        QDomDocument m_pDomDocument;
	};
}

#endif
