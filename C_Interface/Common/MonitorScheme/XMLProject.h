
#ifndef XML_PROJECT_H
#define XML_PROJECT_H

#include "Common/CommonGlobal.h"
#include "AX_API/platform.h"
#include "MonitorScheme/XMLItemTask.h"
#include <string.h>

#ifdef WIN32
#pragma warning(disable : 4996)
#endif

class COMMON_EXPORT XMLProject
{
public:
	XMLProject(const char* name);
	~XMLProject(void);

public:
	bool isTaskItemExist(uint32 taskId, uint32 beginTime);
	XMLItemTask* getTaskItem(uint32 taskId, uint32 beginTime);

	//调用addTaskItem之前必须调用isTaskItemExist确保task未添加过
	//modified by fengjian 2012.9.1
	//XMLItemTask* addTaskItem(uint32 taskId, uint32 beginTime, uint32 endTime);
	XMLItemTask* addTaskItem(uint32 taskId, uint32 beginTime, uint32 endTime, uint32 runTime = 0 );
	//modified end 
	int delTaskItem(uint32 taskId); //删除所有该ID的任务子项
	int delTaskItem(uint32 taskId, uint32 beginTime); //因为允许一个任务添加两次，所以增加时间来确定唯一性，gaowei 09-04-06
	void clearTaskItems(void);

	//这两个操作，实现对通道的遍历，firstChannel返回NULL，说明没有节点，nextChannel返回NULL，说明遍历结束
	XMLItemTask* firstTaskItem(void);
	XMLItemTask* nextTaskItem(void);

public:
	int copy(XMLProject* srcProj);
	XMLProject* clone(void);

public:
	char		_name[64];
	int32		_mode;			//计划模式	add by zhaojian 2010-05-10 add by fengjian 2012.9.1
private:
	ITaskList	_tasks;
	ITaskEntry	_current_task_entry;
};

class SearchProjectByName
{
public:
	SearchProjectByName(const char* name)
	{
		strcpy(_name, name);
	}
	~SearchProjectByName(void){}

	bool operator()(XMLProject* project)
	{
		return strcmp(project->_name, _name) == 0;
	}

private:
	char	_name[64];
};

#include <list>
typedef std::list<XMLProject*> ProjectList;
typedef ProjectList::iterator ProjectEntry;

#endif
