
#ifndef XML_ITEM_TASK_H
#define XML_ITEM_TASK_H
#include "Common/CommonGlobal.h"
#include "AX_API/platform.h"

class COMMON_EXPORT XMLItemTask
{
public:
	XMLItemTask(void);
	~XMLItemTask(void);

	XMLItemTask* clone(void);

public:
	uint32	_id;
	uint32	_beginTime;
	uint32	_endTime;
	uint32  _runTime;	// add by zhaojian 2010-05-11  add by fengjian 2012.9.1
};

class SearchItemTaskByID
{
public:
	SearchItemTaskByID(uint32 id, uint32 beginTime, uint32 runTime = 0)
		: _id(id)
		, _beginTime(beginTime)
        , _runTime(runTime)
	{

	}

	~SearchItemTaskByID(void){}

	bool operator()(XMLItemTask* item)
	{
		return (item->_id == _id) && (item->_beginTime == _beginTime) && (item->_runTime == _runTime);//modified by fengjian 2012.9.1
	}

protected:
	SearchItemTaskByID() : _id(0), _beginTime(0), _runTime(0)
	{// for flexelint Info(1712)
	}

private:
	uint32	_id;
	uint32  _beginTime;
	uint32	_runTime;// add by fengjian 2012.9.1
};

#include <list>
typedef std::list<XMLItemTask*> ITaskList;
typedef ITaskList::iterator ITaskEntry;

#endif
