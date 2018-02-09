/*
 *@file   CustomSplitter.h
 *@brief  
 * 
 *@author 28100
 *@date   2016-12-07
 *
 */

#ifndef _DSGUI_CUSTOMSPLITTER_H
#define _DSGUI_CUSTOMSPLITTER_H

#include "DSGuiGlobal.h"
#include "Splitter/Splitter.h"

namespace DSGUI
{

	class DSCustomSplitterPrivate;
	/**  类名：DSCustomSplitter
	  *  说明  特殊处理拆分器（默认不启用OpaqueResize, 拉动时分割线绘制虚线）
	 **/
	class DS_GUI_EXPORT DSCustomSplitter : public DSSplitter
	{
		Q_OBJECT
	
	public:
		DSCustomSplitter(QWidget *parent = 0);
		~DSCustomSplitter();

	public:
		void setRubberBand(int position);

	protected:
		// 重载事件
		virtual QSplitterHandle *createHandle();

		void childEvent(QChildEvent *c);

	private:
		QScopedPointer<DSCustomSplitterPrivate> d_ptr;

	private:
		Q_DISABLE_COPY(DSCustomSplitter)
		Q_DECLARE_PRIVATE(DSCustomSplitter)
		
	};
}

#endif // _DSGUI_CUSTOMSPLITTER_H
