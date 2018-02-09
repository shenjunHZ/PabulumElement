/*
* Copyright (c) 
* All rights reserved.
*
* 文件名称：XMLMonitorScheme.h
* 文件标识：
* 摘　　要：
*

* 当前版本：1.0
* 原作者　：
* 完成日期：
* 修订记录：创建
*/
#ifndef XML_MONITOR_SCHEME_H
#define XML_MONITOR_SCHEME_H

#include "Common/CommonGlobal.h"
#include "MonitorScheme/XMLProject.h"
#include "MonitorScheme/XMLTask.h"
#include "MonitorScheme/XMLOsdTxt.h"
/*#include "tinyxml/tinyxml.h"*/
#include "pugixmldsl/pugiassist.h"

class COMMON_EXPORT XMLMonitorScheme
{
	typedef enum
	{
		PARSER_SUCCESS = 0,				// 解析保存成功
		PARSER_FAILED,					// 解析保存失败
		PARSER_NULL,					// 空节点
		PARSER_STATUS_ERROR,			// 状态错误
		PARSER_ATTRIBUTE_ERROR,			// 属性错误
		PARSER_OUTMEMORY,				// 缓存不够
	}EnumParserState;
public:
	XMLMonitorScheme(void);
	~XMLMonitorScheme(void);

	int loadFile(const char* filename);
	int saveFile(const char* filename);

	int formStream(const char* data);
	int toStream(char* buf, int buflen, int& len);

	const char* getErrorMsg(void) { return _errorMsg; }

public:
	bool isProjectExist(const char* name);
	XMLProject* getProject(const char* name);
	XMLProject* addProject(const char* name); //调用之前必须调用isProjectExist，确保名称的唯一性
	int delProject(const char* name);
	void clearProjects(void);
	int addProject(XMLProject* project);

	//这两个操作，实现对计划的遍历，firstProject返回NULL，说明没有节点，nextProject返回NULL，说明遍历结束
	XMLProject* firstProject(void);
	XMLProject* nextProject(void);

	bool isTaskExist(const char* name);
	XMLTask* getTask(const char* name);
	XMLTask* getTask(uint32 taskId); //从project中的到一个task ID，需要使用该接口得到task的信息
	XMLTask* addTask(const char* name, int windows,const char* desc = ""); //调用之前必须调用isTaskExist，确保名称的唯一性
	int delTask(const char* name);
	int delTask(uint32 taskId);
	void clearTasks(void); //清除了task之后，project也没有意义，所以调用的同时必须调用clearProjects
	int addTask(XMLTask* task); //克隆的时候才用

	//这两个操作，实现对任务的遍历，firstTask返回NULL，说明没有节点，nextTask返回NULL，说明遍历结束
	XMLTask* firstTask(void);
	XMLTask* nextTask(void);

	XMLOsdTxt& getOsdTxt(void) { return _osdTxt; }

protected:
// 	int parseXmlInside(TiXmlDocument& doc);
// 	int packetXmlInside(TiXmlDocument& doc);
	int parseXmlInside(CPugiXmlDocument& doc);
	int packetXmlInside(CPugiXmlDocument& doc);

	void delTaskInProjects(uint32 taskId);
	uint32 getTaskId(void) { return ++_taskId; }

private:
	ProjectList	 _projects;
	ProjectEntry _current_project_entry;
	TaskList	 _tasks;
	TaskEntry    _current_task_entry;

	uint32		 _taskId;			//自动递增task的id

	char		 _errorMsg[1024];

	XMLOsdTxt	 _osdTxt;
};

#endif
