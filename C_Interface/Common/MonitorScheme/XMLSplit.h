#pragma once
#ifndef XML_SPLIT_H
#define XML_SPLIT_H

#ifdef WIN32
#pragma warning(disable : 4996)
#endif

#include "Common/CommonGlobal.h"
#include <list>
#include "MonitorScheme/XMLSplitWindow.h"

#define MAX_WINDOWS 256

typedef std::list<XMLSplitWindow*> ISplitWindowList;
typedef ISplitWindowList::iterator ISplitWindowEntry;

/*
对窗口分割信息的遍历，根据窗口数循环
*/

class COMMON_EXPORT XMLSplit
{
public:
	XMLSplit(int row,int col,int count);
	~XMLSplit(void);

public:
	XMLSplitWindow* firstSplitWindow();
	XMLSplitWindow* nextSplitWindow();
	XMLSplitWindow* getSplitWindow(int iIndex);
	XMLSplit* clone();	
	void createSplitWindow();
	int getRow(void) { return _row; }
	int getCol(void) { return _col; }
	int getCount(void) { return _count; }
private:
	void clearSplitWindow();
	int addSplitWindow(XMLSplitWindow* splitWindow);


private:
	int _row;		//分割的行数
	int _col;		//分割的列数
	int _count;		//分割的窗口总数

private:
	ISplitWindowList _splitWindows;				//窗口列表
	ISplitWindowEntry _current_splitwnd_entry;	//指向窗口列表当前位置的迭代器
};
#else
#endif

