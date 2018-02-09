
#ifndef XML_TASK_H
#define XML_TASK_H

#ifdef WIN32
#pragma warning(disable : 4996)
#endif

#include "Common/CommonGlobal.h"
#include "MonitorScheme/XMLWindow.h"
#include "MonitorScheme/XMLSplit.h"

#define MAX_WINDOWS		256

/*
* 对窗口的遍历，应该根据窗口数进行循环
*/

class COMMON_EXPORT XMLTask
{
public:
	XMLTask(uint32 id, const char* name, int wndCount, const char *desc = "", int taskRight = 0);
	~XMLTask(void);

	uint32 getId(void) { return _id; }
	void setId(uint32 id) { _id = id; }

	int copy(XMLTask* srcTask);
	XMLTask* clone(void);

public:
	XMLWindow* getWindow(int idx);
	int createWindows(int count);
	int changeWindows(int count);
	int addWindow(XMLWindow* window); //克隆时才用到
	void clearWindows(void);

	XMLSplit* createSplit(int row,int col,int count);
	XMLSplit* getSplit() { return _split; }
	void clearSplit(void);

public:
	char		_name[64];
	int			_wndCount;
	char		_desc[256];
	int			_right;
private:
	uint32		_id;
	XMLWindow*  _windows[MAX_WINDOWS];
	XMLSplit* _split;
};

class SearchTaskByName
{
public:
	SearchTaskByName(const char* name)
	{
		strcpy(_name, name);
	}
	~SearchTaskByName(void){}

	bool operator()(XMLTask* task)
	{
		return strcmp(task->_name, _name) == 0;
	}

private:
	char		_name[64];
};

class SearchTaskByID
{
public:
	SearchTaskByID(uint32 id) 
	: _id(id)
	{
	}

	~SearchTaskByID(void) {}

	bool operator()(XMLTask* task)
	{
		return _id == task->getId();
	}

private:
	uint32		_id;
};

#include <list>
typedef std::list<XMLTask*> TaskList;
typedef TaskList::iterator TaskEntry;

#endif
