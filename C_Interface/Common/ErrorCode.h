#ifndef __COMMON_ERRORCODE_H__
#define __COMMON_ERRORCODE_H__

// 通用错误[-99，0]
#define	DCM_RET_SUCCESS						0				// 返回成功
#define	DCM_UNKNOWN_ERROR			        -1		        // 未知错误
#define	DCM_FUNCTION_CALL_ERROR			    -2		        // 内部函数调用错误
#define	DCM_INVAILD_PARAM					-3			    // 无效参数

// 数据库
#define DCM_OPEN_DB_FAILED                  -10             // 打开数据库失败
#define DCM_CLOSE_DB_FAILED				    -11		        // 关闭数据库失败

// ErrorAnalyser
#define DCM_ERROR_QUERY_FAILED			    -15		        // 查询错误码失败

// Rest 错误码[-119, -100]
#define DCM_REST_INIT_FAILED                -100			// Rest初始化失败
#define DCM_REST_REQUEST_TIMEOUT            -101			// Rest请求超时，此错误码保持跟Rest内部一致
#define DCM_USER_TOKEN_INVALID				-102			// 无效的用户token

// 登陆[-149, -130]

// 预览[-299, -200]
#define DCM_PREVIEW_OPEN_SOUND_FAILED		-200			// 预览打开声音失败
#define DCM_PREVIEW_TALKING_WITH_OTHER		-201			// 打开声音失败，正在与其他设备对讲


// 回放[-399, -300]
#define DCM_INVAILD_SS						-300			//无可用的ss服务
#define DCM_CAPTURE_FRAME_INFO_FAILED		-301			//抓取回放快照失败

// RRSPSDK 错误码[-499, -400]
#define DCM_RTSP_UDP_LISTEN_FAILED          -400			// UDP监听失败
#define DCM_RTSP_CONNECT_SERVER_FAILED		-401			// 连接服务失败
#define DCM_RTSP_SENDDATA_FAILED			-402			// 数据发送失败
#define DCM_RTSP_COMMAND_CANCELED			-403			// 命令已被取消
#define DCM_RTSP_PORT_PARSE_FAILED		    -404			// 端口解析失败

// 云台[-599, -500]
#define DCM_PTZ_CAMERA_OCCUPY				-500			// 摄像头被其他用户锁定
#define DCM_PTZ_OCCUPY_BY_OTHER_USER		-501			// 被其他用户占用
#define DCM_PTZ_SERVEROFFLINE				-502			// REST服务离线

// FTP[-699, -600]
#define DCM_FTP_ERROR_UNKNOW					-601
#define DCM_FTPCURL_ERROR						-602			// 调用curl返回错误
#define DCM_FTPCURL_LOCALFILE_NOT_OPEN			-603			// 调用curl返回未找到本地文件
#define DCM_FTPCURL_LOCALFILE_NOT_READ			-604			// 调用curl返回打开本地文件出错
#define DCM_FTPCURL_FTPFILE_ERROR				-605			// 调用curl返回操作远程文件出错
#define DCM_FTPCURL_FREE_ERROR					-606			// 调用curl返回释放出错

// 对讲[-799, -700]
#define DCM_TALK_PARAM_UNMATCH				-701			// 对讲参数不匹配

#define DCM_QUERYREC_FAILED					-107302			//查询录像失败
#define DCM_QUERYREC_NORECORD               -107303           //查询录像无录像
#define DCM_QUERYREC_SUBSSCRIBER_NONE       -107304           //查询订阅者不存在 
#define DCM_QUERYREC_RET_DEV_DISCONNECT     -107305           //查询返回 设备离线
#define DCM_QUERYREC_RET_SENFAILED          -107306           //查询 发送信息失败
#define DCM_QUERYREC_RET_TIMEOUT            -107307           //查询录像 查询超时
#define DCM_QUERYREC_RET_BUSY               -107308           //查询录像 查询繁忙

#define DCM_QUERYTAG_FAILED                 -107309           //查询录像标签失败
#define DCM_QUERYTAG_NOTAG                  -107310           //查询录像标签0条
#define DCM_QUERYTAG_TOOQUICK				-107311			//查询录像标签速度过快

#define DCM_QUERYLOCK_FAILED				-107312			//查询录像锁定失败
#define DCM_QUERYLOCK_NOLOCK				-107313			//查询录像锁定0条
#define DCM_QUERYLOCK_BUSY					-107314			//查询录像锁定 查询繁忙

#define DCM_DOWNLOAD_WRITTENFAIL			-107315			//下载写文件失败



#endif // __COMMON_ERRORCODE_H__
