/*
 *@file   DSPushButton.h
 *@brief  重载兼容MAC平台点击问题
 * 
 *@author cc
 *@date   2014-06-12
 *
 */

#ifndef _DSGUI_PUSHBUTTON_H
#define _DSGUI_PUSHBUTTON_H

#include "DSGuiGlobal.h"
#include <QPushButton>
#include <QStyle>
#include <QStyleOption>

namespace DSGUI
{
    /** @class DSPushButton
      * @brief 按钮
      * 
      */
    class DS_GUI_EXPORT DSPushButton : public QPushButton
    {
        Q_OBJECT
    public:
        //构造
        DSPushButton(QWidget* pParent = NULL);
        DSPushButton(const QString& strText, QWidget* pParent = NULL);
        DSPushButton(const QIcon& icnIcon, const QString& strText, QWidget* pParent = NULL);
        
    protected:
        // 初始化风格
        void initStyleOption(QStyleOptionButton* pOpt) const;
        // 绘图
        virtual void paintEvent(QPaintEvent* pPaintEvent);

    #ifdef Q_WS_MAC
        // 重载掉为了让MAC平台跟windows效果一致
        virtual bool hitButton(const QPoint& ptPos) const;
    #endif

    };
}

#endif
