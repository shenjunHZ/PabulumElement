
#ifndef XML_MONITOR_DEFINE_H
#define XML_MONITOR_DEFINE_H

#define     DEVICE_ID_LEN           64

namespace XMLMonitor
{
	#define XML_TAG_SCHEME			"MonitorScheme"
	#define XML_TAG_PROJECTS		"Projects"
	#define XML_TAG_PROJECT			"Project"
	#define XML_TAG_ITASK			"ITask"
	#define XML_TAG_TASKS			"Tasks"
	#define XML_TAG_TASK			"Task"

	//add by weikaizhi
	#define XML_TAG_SPLIT			"Split"
	#define XML_TAG_SPLIT_WNDOW		"Wnd"
	//end

	#define XML_TAG_WINDOW			"Window"
	#define XML_TAG_CHANNEL			"Channel"
	#define XML_TAG_OSDTXT			"OsdTxt"

	#define XML_ATTR_NAME			"name"
	#define XML_ATTR_ID				"id"
	#define XML_ATTR_ID_CREATOR		"idCreator"
	#define XML_ATTR_BEGIN_TIME		"beginTime"
	#define XML_ATTR_END_TIME		"endTime"
	#define XML_ATTR_WINDOWS		"windows"
	#define XML_ATTR_RIGHT			"right"

	//add by weikaizhi
	#define XML_ATTR_ROW			"row"
	#define XML_ATTR_COL			"col"
	#define XML_ATTR_COUNT			"count"
	#define XML_ATTR_SPLIT_ID		"id"
	#define XML_ATTR_ENABLE			"enable"
	#define XML_ATTR_COMBINE		"combine"
	#define XML_ATTR_X1				"x1"
	#define XML_ATTR_Y1				"y1"
	#define XML_ATTR_X2				"x2"
	#define XML_ATTR_Y2				"y2"
	//end

	#define XML_ATTR_WND_NO			"wndNO"
	#define XML_ATTR_STREAM			"subStream"
	#define XML_ATTR_TIME_SPAN		"timeSpan"
	#define XML_ATTR_PRESET_POS		"presetPos"
	//DSS_C
	#define XML_ATTR_ROTATE_DEGREE "rotateDegree"
	//end
	#define XML_ATTR_DEVICE_ID		"deviceId"
	#define XML_ATTR_CHANNEL_NO		"no"
	#define XML_ATTR_DEV_TYPE		"devType"
	#define XML_ATTR_DEV_INFO       "devInfo"
    #define XML_ATTR_NODE_TYPE       "nodeType"//add by fengjian 2012.8.14

	#define XML_ATTR_ENABLE			"enable"
	#define XML_ATTR_POS_X			"posX"
	#define XML_ATTR_POS_Y			"posY"
	#define XML_ATTR_COLOR			"color"
	#define XML_ATTR_FONT			"font"
	#define XML_ATTR_FONT_SIZE		"fontSize"
	#define XML_ATTR_TEXT			"text"
	#define XML_ATTR_BOLD			"bold"
	#define XML_ATTR_TRANSPARENT	"transparent"
	#define XML_ATTR_BKCOLOR		"bkcolor"

 //add by fengjian 2012.9.1
	#define XML_ATTR_PRJOECTMODE	"mode"				//add by zhaojian 2010-05-10
	#define XML_ATTR_RUNTIME		"runtime"			//add by zhaojian 2010-05-10
//end
};

#endif
