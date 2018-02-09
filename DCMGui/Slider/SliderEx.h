#ifndef DSSliderEx_H
#define DSSliderEx_H

#include "Slider.h"
#include "DSGuiGlobal.h"

namespace DSGUI
{
	class DS_GUI_EXPORT DSSliderEx : public DSSlider
	{
		Q_OBJECT
			Q_PROPERTY(bool handleHover READ handleHover WRITE setHandleHover)
	public:
		DSSliderEx(QWidget *parent = NULL);
		~DSSliderEx();

	public:
		bool handleHover(){return m_bHandleHover;}
		void setHandleHover(bool bHover){m_bHandleHover = bHover;}

	protected:
		virtual void mousePressEvent(QMouseEvent* pEvent);

		virtual void mouseReleaseEvent(QMouseEvent *pEvent);

		virtual void mouseMoveEvent(QMouseEvent* pEvent);

	private:
		bool m_bHandleHover;
		bool m_bPress;

	};
}
#endif // DSSliderEx_H
