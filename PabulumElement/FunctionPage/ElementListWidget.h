/*
@function    element table
@author  sj
@data    2018-1-25
@version 1.0
*/
#pragma once

#include <QtWidgets/QWidget>
#include <QtGui/QStandardItem>

namespace Ui
{
    class ElementListWidget;
}

namespace mainApp
{
    class ElementListWidget : public QWidget
    {
        Q_OBJECT

    public:
        ElementListWidget(QWidget* pParent = nullptr);
        ~ElementListWidget();

        void createElementList(QList<QList<QString>>& listVar);
        void getElementListData(QList<QString>& listElement, QList<float>& listConstituent, float& eachPer);

    protected:
        void resizeEvent(QResizeEvent *event);

    private:
        void initUI();
        void connectSgn();
        float calculateElementReference(float& fConstituent, QList<float>& listRatio);
        void refreshHeaderData();
        void addElementToList(QList<QString>& listElement, QList<float>& listConstituent, float& eachPer);

    private:
        Ui::ElementListWidget* m_pUi;
        QString m_strValue;
        QStandardItemModel*	   m_model;

        QList<QString> m_listElement;   // protein axunge
        QList<float> m_listConstituent;
        float m_eachPer = 0.0;
    };
}