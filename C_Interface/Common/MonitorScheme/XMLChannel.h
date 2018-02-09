
#ifndef XML_CHANNEL_H
#define XML_CHANNEL_H
#include "Common/CommonGlobal.h"
#include "MonitorScheme/XMLMonitorDefine.h"
#include "AX_API/platform.h"
#include <string.h>

#ifdef WIN32
#pragma warning(disable : 4996)
#endif

class COMMON_EXPORT XMLChannel
{
public:
	XMLChannel(void);
	~XMLChannel(void);

	XMLChannel* clone(void);

public:
	//uint32	_id;			//摄像头ID
	char		_id[DEVICE_ID_LEN];		//因IPC的ID是字符串，所以改成字符串，gaowei 08-11-22
	int			_subStream;		//码流类型
	uint32		_timeSpan;		//停留时间
	int			_presetPos;		//预置位
	char		_devId[DEVICE_ID_LEN];		//设备ID
	int			_channelNo;		//通道号
	int			_devType;		//设备类型
	char		_osdText[256];  //叠加信息
	char        _devInfo[256];  //设备附加信息
	int         _rotateDegree;//旋转角度，0为不旋转 //DSS_C
	int         _nodeType;      //channel type add by fengjian 2012.8.14
};

class SearchChannelByID
{
public:
	SearchChannelByID(const char* id)
	{
		strncpy(_id, id, sizeof(_id));
	}
	~SearchChannelByID(void){}

	bool operator()(XMLChannel* channel)
	{
		return 0 == strcmp(_id, channel->_id);
	}

protected:
	SearchChannelByID()
	{// for flexelint Info(1712)
		_id[0] = '\0';
	}

private:
	char _id[DEVICE_ID_LEN];
};

#include <list>
typedef std::list<XMLChannel*> IChannelList;
typedef IChannelList::iterator IChannelEntry;

#endif
