/*
 *@file   MessageBox.h
 *@brief  
 * 
 *@author wp
 *@date   2014-07-015
 *
 */

#ifndef __DSGUI_MESSAGEBOX_H
#define __DSGUI_MESSAGEBOX_H

#include "DSGuiGlobal.h"
#include "Dialog/Dialog.h"

class QAbstractButton;
class QDialogButtonBox;

namespace DSGUI
{
    class DSMessageBoxPrivate;
    class DSPushButton;
    /**	@class DSMessageBox
     *	@brief 信息提示框
     */
    class DS_GUI_EXPORT DSMessageBox : public DSDialog
    {
        Q_OBJECT
        Q_PROPERTY(QPixmap pixWarningImage READ GetWarningImage WRITE SetWarningImage)

    public:
         /*@enum:  DialogFlag
         *@brief: 用于设置图标
         *
         */
        enum Icon
        {
            NoIcon = 0,
            Information = 1,
            //Warning = 2,
            //Critical = 3,
            //Question = 4
        };

         /*@enum:  DialogFlag
         *@brief: 用于定制信息框按键
         *
         */
        enum StandardButton 
        {
            NoButton           = 0x00000000,
            Ok                 = 0x00000400,
            Cancel             = 0x00002000,
            Yes                = 0x00004000,
            No                 = 0x00010000,
            Close              = 0x00200000,
        };
        Q_DECLARE_FLAGS(StandardButtons, StandardButton)

    public:
         // 构造函数
        DSMessageBox(QWidget* pParent = NULL);
         // 构造函数，参数1配置图标，参数2设置标题，参数3设置消息内容，参数4配置按键
         //参数6设置配置关闭，最小化和最大化是否显示
        DSMessageBox(Icon enumIcon, const QString& strTitle, const QString& strMsg,
            StandardButtons enumButtons = NoButton, QWidget* pParent = NULL, DialogFlags enumDialogFlag = DSDialog::CloseButtonHint);

        ~DSMessageBox();

    public:
        // 信息框，参数2设置标题，参数3设置消息内容，参数4配置按键
        static StandardButton ShowInformation(QWidget* pParent, const QString& strTitle,
            const QString& strMsg, StandardButtons enumButtons);

        // 设置信息框文本内容
        void SetMsgText(QString strMsgText);

        // 获取用户点击的按钮
        StandardButton GetClickBtn();


    private:
        QScopedPointer<DSMessageBoxPrivate> d_ptr;

        // 设置图片
        void SetWarningImage(const QPixmap& pixBorderImage);
        // 获取图片
        QPixmap GetWarningImage() const;
    private:
        Q_PRIVATE_SLOT(d_func(), void OnButtonOkClicked())
        Q_PRIVATE_SLOT(d_func(), void OnButtonYesClicked())
        Q_PRIVATE_SLOT(d_func(), void OnButtonCancelClicked())
        Q_PRIVATE_SLOT(d_func(), void OnButtonNoClicked())
        Q_PRIVATE_SLOT(d_func(), void OnButtonCancelClicked())
        Q_DISABLE_COPY(DSMessageBox)
        Q_DECLARE_PRIVATE(DSMessageBox)
    };
}

Q_DECLARE_OPERATORS_FOR_FLAGS(DSGUI::DSMessageBox::StandardButtons)
#endif
