#ifndef __COMMON_JSONPARSE_H
#define __COMMON_JSONPARSE_H

#include "jsondsl/json.h"
#include "libdsl/dslbase.h"
#include "Common/CommonGlobal.h"
#include <string>

namespace Common
{
	//½âÎöjson
	 COMMON_EXPORT std::string ParseJsonToString(const dsl::Json::Value& jsonValue, const std::string& strNode, const std::string& strDefaultValue = "");
	 COMMON_EXPORT unsigned int ParseJsonToUInt(const dsl::Json::Value& jsonValue, const std::string& strNode, unsigned int nDefaultValue = 0);
	 COMMON_EXPORT int ParseJsonToInt(const dsl::Json::Value& jsonValue, const std::string& strNode, int nDefaultValue = 0);
	 COMMON_EXPORT uint64_t ParseJsonToUInt64(const dsl::Json::Value& jsonValue, const std::string& strNode, uint64_t nDefaultValue = 0);
	 COMMON_EXPORT int64_t ParseJsonToInt64(const dsl::Json::Value& jsonValue, const std::string& strNode, int64_t nDefaultValue = 0);
	 COMMON_EXPORT bool ParseJsonToBool(const dsl::Json::Value& jsonValue, const std::string& strNode, bool bTrue = false);
	 COMMON_EXPORT float ParseJsonToFloat(const dsl::Json::Value& jsonValue, const std::string& strNode, float fDefaultValue = 0.0);
	 COMMON_EXPORT double ParseHsonToDouble(const dsl::Json::Value& jsonValue, const std::string& strNode, double dDefaultValue = 0.0);
}

#endif