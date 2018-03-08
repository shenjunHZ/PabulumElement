#include "LocalIniFile/LocalIniFile.h"
#include "Tools/Dir.h"
#include "LocalIniFile/qinifile.h"

using namespace DSGUI;

namespace mainApp
{
	QVariant CLocalIniFile::ReadValue(const QString &strSecName, const QString &strKey, const QString& qstrFilename)
	{
		QIniFile LocalIniFile(DSDir::GetCurrentPath() + QString("/") + qstrFilename);
		return LocalIniFile.ReadValue(strSecName, strKey);
	}

	void CLocalIniFile::WriteValue(const QString &strSecName, const QString &strKey, QVariant qvValue, const QString& qstrFilename)
	{
		QIniFile LocalIniFile(DSDir::GetCurrentPath()+ QString("/") + qstrFilename);
		LocalIniFile.WriteValue(strSecName, strKey, qvValue);
	}

}