#pragma once

namespace Common
{
	struct struStream
	{
		// 码流类型
		enum StreamType
		{
			AllStream				= 0,									// 全部
			MainStream				= 1,									// 主码流
			SubStream				= 2,								    // 辅码流
			ThirdStream				= 3,									// 三码流
			LocalSignalStream		= 5,									// 本地信号
		};
	};

	#define BASIC_IP_LEN							46			// 远端IP地址长度
	#define BASIC_USER_NAME_LEN						64          // 设备登陆用户名的长度
	#define BASIC_PASSWORD_LEN						64	        // 密码长度
	#define BASIC_CHL_ID_LEN						64			// 通道ID长度
	#define BASIC_DEV_ID_LEN						64			// 设备ID长度
	#define BASIC_MATRIXID_LEN						32			// 矩阵服务器id

}
