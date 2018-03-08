/*
 *@file   SearchEdit.h
 *@brief  
 * 
 *@author wrb
 *@date   2015-04-30
 *
 */

#ifndef __DSGUI_SEARCHEDIT_H
#define __DSGUI_SEARCHEDIT_H

#include "DSGuiGlobal.h"
#include <QWidget>

namespace Ui
{
    class DSSearchEdit;
}

namespace DSGUI
{
    class DSSearchEditPrivate;
    /** @class DSSearchEdit
     *  @brief ËÑË÷±à¼­
     */
    class DS_GUI_EXPORT DSSearchEdit : public QWidget
    {
        Q_OBJECT

    public:
        DSSearchEdit(QWidget *parent = 0);
        ~DSSearchEdit();

        void ClearTextContent();
        void SetFilterText(QString strText);

    protected:
        virtual void keyPressEvent(QKeyEvent* event);		// ¼üÅÌÊÂ¼þ
        virtual void resizeEvent(QResizeEvent* event);		

    signals:
        void SignalSearchBtnClicked(QString& strText);

    private:
        QScopedPointer<DSSearchEditPrivate> d_ptr;

    private:
        Q_DECLARE_PRIVATE(DSSearchEdit)
        Q_DISABLE_COPY(DSSearchEdit)
        Q_PRIVATE_SLOT(d_func(), void OnTextChanged(const QString& strText))
        Q_PRIVATE_SLOT(d_func(), void OnBtnClearClicked())
        Q_PRIVATE_SLOT(d_func(), void OnBtnSearchClicked())

    private:
        QScopedPointer<Ui::DSSearchEdit>	m_pUi;
    };
}

#endif // __DSGUI_SEARCHEDIT_H
