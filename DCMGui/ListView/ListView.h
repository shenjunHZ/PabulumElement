#ifndef _DSGUI_LISTVIEW_H
#define _DSGUI_LISTVIEW_H

#include <QtGui/QListView>

namespace DSGUI
{
	/**  类名：DSListView
	*    说明 树型列表控件
	**/
	class DSListView : public QListView
	{
		Q_OBJECT
	public:
		// 构造
		DSListView(QWidget* pParent = NULL);
	};
}

#endif //_DSGUI_LISTVIEW_H
