/*
@function    element table
@author  sj
@data    2018-1-25
@version 1.0
*/
#pragma once

#include <QtWidgets/QWidget>
#include <QtGui/QStandardItem>

#include "HomePage/ViewDefine.h"

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
        void getElementListData(std::vector<nutrientContentTable>& contentTable, float& eachPer);

    protected:
        void resizeEvent(QResizeEvent *event);
        QString calculateConstituentValue(QString& strElement, float& fConstituent, bool bAddUnit = false);
        QString calculateNRVReferenceValue(QString& strElement, float& fConstituent);

    private:
        void initUI();
        void connectSgn();
        float calculateElementReference(float& fConstituent, QList<float>& listRatio);
        void refreshHeaderData();
        void addElementToList(QList<QString> listElement, QList<float> listConstituent, 
            QList<float> listConstituentHundred, float& eachPer);
        void calculateEnergy();
        void changeConstituentToHundredEachPer(const QList<float>& listConstituent, QList<float>& listConstituentHundred);
        void calculateUnitAndNRV(const QList<QString>& listElement, const QList<float>& m_listConstituentHundred);
        float roundingOffValue(const float& fvalue);

    private:
        Ui::ElementListWidget* m_pUi;
        QString m_strValue;
        QStandardItemModel*	   m_model;

        QList<QString> m_listElement;   // protein axunge
        QList<QString> m_listUnit;
        QList<QString> m_listNRV;
        QList<float> m_listConstituent;
        QList<float> m_listConstituentHundred;
        float m_eachPer = 0.0;

        RecipeReferenceTargetTable targetTable;
        NRVReferenceValueTable valueTable;
    };
}