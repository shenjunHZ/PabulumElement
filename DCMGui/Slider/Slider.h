/*
 *@file   Slider.h
 *@brief  
 * 
 *@author cc
 *@date   2014-06-30
 *
 */

#ifndef _DSGUI_SLIDER_H
#define _DSGUI_SLIDER_H

#include "DSGuiGlobal.h"
#include <QSlider>
#include "QLabel"

namespace DSGUI
{
	/**  类名：DSSlider
	  *  说明  滑动条
	 **/
	class DS_GUI_EXPORT DSSlider : public QSlider
	{
		Q_OBJECT

	public:
		// 构造
		explicit DSSlider(QWidget* pParent = NULL);
		explicit DSSlider(Qt::Orientation enumOrientation, QWidget* pParent = NULL);
		void SetUponShowType();


	protected:
// 		// 重载事件
// 		virtual void mousePressEvent(QMouseEvent* pEvent);
// 		virtual void mouseMoveEvent(QMouseEvent* pEvent);

	protected:
        // 根据滑条Orientation排列方式转换出对于的坐标值
		int GetPick(const QPoint& ptMouse) const;
        // 通过窗口坐标值转换出滑条值
		int PixelPosToRangeValue(int iPos) const;

		QLabel* m_pNumLab;
		QLabel* m_pHintNumUponLab;

		bool m_bShowHintUpon;

	private slots:
		void OnValueChanged(int changedValue);
	};
}

#endif
