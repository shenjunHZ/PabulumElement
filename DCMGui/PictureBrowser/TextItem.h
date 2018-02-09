#ifndef _DSGUI_TEXTITEM_H
#define _DSGUI_TEXTITEM_H

#include "DSGuiGlobal.h"
#include <QGraphicsTextItem>
#include <QGraphicsSimpleTextItem>

namespace DSGUI
{
    // 文字元素
	class DS_GUI_EXPORT DSSimpleTextItem : public QGraphicsSimpleTextItem
	{
	public:
		// 构造
        DSSimpleTextItem(const QString& strText, QGraphicsItem* pParent = NULL);

    public:
        // 设置矩形，本身矩形大小
        void SetRect(const QRectF& rtItem);
    public:
        // 设置文字画笔
        void SetTextPen(const QPen& penText);
        // 设置文字排列方式
        void SetAlignment(Qt::Alignment enumAlignment);
        // 设置背景色
        void SetBackgroundColor(const QColor& colorBg);

    protected:
        // 绘图
        virtual void paint(QPainter *pPainter, const QStyleOptionGraphicsItem *option, QWidget *pWidget);

        // 可用区域
        virtual QRectF boundingRect() const;

    private:
        QRectF m_rtItem; // 文字矩形
        QColor m_colorBg; // 背景色
        Qt::Alignment m_enumAlignment; // 文字排列方式
	};

    /*@cn:    DSComplexTextItem
     *@brief: 复杂文字元素
     *        主要实现了link鼠标状态改变
     *        链接使用setHtml，格式如下：
     *        QString("<a href=\"file:///%1\" style='color: rgb(255, 255, 255);'>%1</a>").arg("Program Files");
     *        QString("<a href=\"%1\">%1</a>").arg("Program Files");
     */
    class DS_GUI_EXPORT DSComplexTextItem : public QGraphicsTextItem
    {
        Q_OBJECT
    public:
        // 构造
        DSComplexTextItem(QGraphicsItem* pParent = NULL);

    private slots:
        // 处理鼠标状态
        void OnLinkHovered(const QString& strUrl);
    };
}

#endif
