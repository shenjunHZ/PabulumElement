#ifndef _DSGUI_BACKGROUNDITEM_H
#define _DSGUI_BACKGROUNDITEM_H

#include "DSGuiGlobal.h"
#include <QGraphicsRectItem>
#include <QPen>

namespace DSGUI
{
    // ±≥æ∞‘™Àÿ
	class DS_GUI_EXPORT DSBackgroundItem : public QGraphicsRectItem
	{
	public:
		// ππ‘Ï
        DSBackgroundItem(qreal x, qreal y, qreal w, qreal h, QGraphicsItem* pParent = NULL);

    public:
        // …Ë÷√ª≠± 
        void SetSelectedPen(const QPen& pen);
    public:
        // ªÊÕº
        virtual void paint(QPainter *pPainter, const QStyleOptionGraphicsItem *option, QWidget *pWidget = 0);

    private:
        QPen m_penSelected;
	};
}

#endif
