/*
 *@file   PixmapBrowser.h
 *@brief  图片浏览器
 * 
 *@author cc
 *@date   2014-06-21
 *
 */

#ifndef _DSGUI_PIXMAPBROWSER_H
#define _DSGUI_PIXMAPBROWSER_H

#include "DSGuiGlobal.h"
#include <QtWidgets/QGraphicsView>

namespace DSGUI
{
    class DSGraphicsLayout;
    class DS_GUI_EXPORT DSPictureBrowser : public QGraphicsView
    {
        Q_OBJECT

    public:
        // 构造
        DSPictureBrowser(QWidget* pParent = NULL);

    public:
        // 设置布局
        void SetGraphicsLayout(DSGraphicsLayout* pLayout);
        // 获取布局
        DSGraphicsLayout* GetGraphicsLayout() const;

    public:
        //void SetCurrentIndex(int iIndex);
        //int GetCurrentIndex() const;

    Q_SIGNALS:
        // 选中改变，如果没有选中，发送NULL
        void SignalCurrentChanged(QGraphicsItem* pItem);
        // 双击信号
        void SignalClickedItem(QGraphicsItem* pItem);
        // 双击信号
        void SignalDoubleClickedItem(QGraphicsItem* pItem);
        // 单击信号
        void SignalPressItem(QGraphicsItem* pItem);

    protected:
        // 大小改变事件
        virtual void resizeEvent(QResizeEvent* pResizeEvent);
        // 鼠标单击事件
        virtual void mouseReleaseEvent(QMouseEvent* pMouseEvent);
        // 鼠标双击事件
        virtual void mouseDoubleClickEvent(QMouseEvent* pMouseEvent);
        // 鼠标单击事件
        virtual void mousePressEvent(QMouseEvent* pMouseEvent);
    private slots:
        // 选中改变
        void OnSelectionChanged();

    private:
        DSGraphicsLayout* m_pGraphicsItemLayout; // 场景布局
    };
}

#endif //_DSGUI_LISTVIEW_H
