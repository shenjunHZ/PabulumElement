/*
 *@file   Dialog.h
 *@brief  
 * 
 *@author cc
 *@date   2014-07-01
 *
 */

#ifndef _DSGUI_DIALOG_H
#define _DSGUI_DIALOG_H

#include "DSGuiGlobal.h"
#include <QDialog>

class QHBoxLayout;
class QToolButton;
class Ui_CDialogUI;

namespace DSGUI
{
    class DSDialogPrivate;
    /** @class DSDialog
     *  @brief 对话框
     */
    class DS_GUI_EXPORT DSDialog 
        : public QDialog
    {
        Q_OBJECT
        Q_ENUMS(DialogFlag)
        Q_PROPERTY(QPixmap pixBorderImage READ GetBorderImage WRITE SetBorderImage)
    public:
        /*@enum:  DialogFlag
         *@brief: 用于定制窗口控件
         *
         */
        enum DialogFlag
        {
            CloseButtonHint = 0x1,     // 关闭按钮显示
            MinimizeButtonHint = 0x2,  // 最小化按钮显示
            MaximizeButtonHint = 0x4,  // 最大化按钮显示
            MinMaxButtonsHint = MinimizeButtonHint | MaximizeButtonHint,   // 
        };
        Q_DECLARE_FLAGS(DialogFlags, DialogFlag)

    public:
        // 构造，参数2配置关闭，最小化和最大化是否显示，具体可用参数如下
        DSDialog(QWidget* pParent = NULL, DialogFlags enumDialogFlags = 0);
        ~DSDialog();

    public:
        // 设置标题文字
        void SetTitle(const QString& strTitle);
        // 获取标题文字
        QString GetTitle() const;
        // 设置标题显示方式
        void SetTitleAlignment(Qt::Alignment enumAlignment);
        // 在关闭按钮左侧添加控件
        void InsertTitleWidget(QWidget* pWidget, int iIndex = 0);
        // 双击标题可最大化和还原
        void SetOpenDoubleClickTitle(bool bOpen);
        //是否开启退出动效
        void SetCloseAnimaEnable(bool bOpen);

    public:
        // 添加中间的窗口
        void AddCentralWidget(QWidget* pWidget);
        // 获取中间的窗口
        QWidget* GetCentralWidget() const;
        // 隐藏窗口标题
        void SetTitleHide(bool bhide = true);

    public:
        // 是否打开 改变窗口大小
        void SetOpenChangeSize(bool bOpen);

    public Q_SLOTS:
        // 关闭按钮响应，重载此接口可过滤默认关闭按钮重载
        virtual void OnCloseBtmClicked();

    protected:
        // 处理圆角
        virtual void resizeEvent(QResizeEvent* pEvent);
        // 过滤键盘Key_Escape等事件
        virtual void keyPressEvent(QKeyEvent* pEvent);
        virtual void moveEvent(QMoveEvent *event);
        virtual void done(int);

    protected slots:
        // 切换最大按钮 最大化和还原 tooltip
        void OnTurnMaximizeButtonTip();

    private:
        // 设置图片
        void SetBorderImage(const QPixmap& pixBorderImage);
        // 获取图片
        QPixmap GetBorderImage() const;

    private:
        QScopedPointer<DSDialogPrivate> d_ptr;
        
    private:
        Q_DECLARE_PRIVATE(DSDialog)
        Q_DISABLE_COPY(DSDialog)
        Q_PRIVATE_SLOT(d_func(), void OnSizeStatusChanged())
        Q_PRIVATE_SLOT(d_func(), void OnDoneAnimaFinished())
    private:
        QScopedPointer<Ui_CDialogUI> m_ptDialogUI;
    };
}

Q_DECLARE_OPERATORS_FOR_FLAGS(DSGUI::DSDialog::DialogFlags)


#endif
