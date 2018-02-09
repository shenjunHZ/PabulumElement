
#ifndef XML_WINDOW_H
#define XML_WINDOW_H

#include "Common/CommonGlobal.h"
#include "MonitorScheme/XMLChannel.h"

class COMMON_EXPORT XMLWindow
{
public:
	XMLWindow(int idx);
	~XMLWindow(void);

	int getIndex(void) { return _index; }
	void setIndex(int idx) { _index = idx; }

	XMLWindow* clone(void);

public:
	//允许同ID节点，故废止此二接口
	//bool isChannelExist(const char* id);
	//XMLChannel* getChannel(const char* id);

	XMLChannel* addChannel(const char* id, int subStream, uint32 timeSpan, uint32 presetPos,int rotateDegree=0,int nodeType=0);//modified by fengjian 2012.8.14
	int delChannel(const char* id);
	void clearChannels(void);
	int addChannel(XMLChannel* channel); //克隆时才用

	//这两个操作，实现对通道的遍历，firstChannel返回NULL，说明没有节点，nextChannel返回NULL，说明遍历结束
	XMLChannel* firstChannel(void);
	XMLChannel* nextChannel(void);

	//循环获得下一个通道，也就是说，如果当前通道是最后一个通道，那么下一个通道就是第一个，
	//ID为空时，默认返回首个；不为空时，ID无用，直接根据成员值,返回下一个节点  09-05-18 yulu
	XMLChannel* cycleNextChannel(const char* currId);
	
private:
	int				_index;	//窗口序号
	IChannelList	_channels;
	IChannelEntry	_current_chnl_entry;		//应用于first遍历
	IChannelEntry	_cycle_chnl_entry;			//应用于cycle查找  09-05-18
};

#endif
