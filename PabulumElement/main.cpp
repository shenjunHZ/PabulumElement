/*
@tool    use for calculte pabulum element
@author  sj
@data    2018-1-22
@version 1.0
*/
#include "Tools/Dir.h"
#include "Tools/File.h"
#include "AppCommon/ClientApp.h"
#include "Common/GlobalDataCenter/GlobalDataCenter.h"
#include "MessageNotify/MessageNotify.h"
#include "MessageBox/MessageBox.h"
#include "DSGuiGlobalData.h"
#include "AppCommon/commonControl.h"
#include "version.h"

#include <QtWidgets/QApplication>
#include <QtCore/QTextCodec>
#include <QtCore/QDir>
#include <QtCore/QTime>
#include <QtCore/QFile>
#include <QtGui/QIcon>
#include <QtGui/QFont>
#include <QtCore/QTranslator>

void SetTranslator(const QString strPath);
void SearchQmFile(const QString & strPath);

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    // 解决库路径问题
    QTextCodec *xcodec = QTextCodec::codecForLocale();
    QString exeDir = xcodec->toUnicode(QByteArray(argv[0]));
    QString BKE_CURRENT_DIR = QFileInfo(exeDir).path();
    BKE_CURRENT_DIR.replace("//", "/");
    QStringList  libpath;

    libpath << BKE_CURRENT_DIR + QString::fromLocal8Bit("/plugins/platforms");
    libpath << BKE_CURRENT_DIR << BKE_CURRENT_DIR + QString::fromLocal8Bit("/plugins/imageformats");
    libpath << BKE_CURRENT_DIR + QString::fromLocal8Bit("/plugins");
    libpath << QApplication::libraryPaths();
    QApplication::setLibraryPaths(libpath);

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    // set current path for this application /* D:/Code/AbbreviationApplication/bin */
    QString strCurPath = QCoreApplication::applicationDirPath();
    QDir::setCurrent(strCurPath);
    DSGUI::DSDir::SetCurrentPath(strCurPath); // 封装库

                                              // set window interface
    app.setWindowIcon(QIcon("./Pabulum.ico"));

    // global common component
    Common::CGlobalDataCenter::GetInstance().SetCurrentDirPath_UTF8(strCurPath.toUtf8().data());
    Common::CGlobalDataCenter::GetInstance().SetCurrentDirPath(strCurPath.toLocal8Bit().data());

    // to do log
    QTime curTime = QTime::currentTime();
    char scLogName[25] = { 0 };
    sprintf_s(scLogName, sizeof(scLogName), "log\\%02d-%02d-%02d", curTime.hour(), curTime.minute(), curTime.second());

    // app set
    QString strAppName = "Pabulum Element";
    QString strAppVer = "";
    QString strWindowTitle = strAppName + strAppVer;
    app.setOrganizationName(strAppName);
    app.setApplicationName(strWindowTitle);

    // to do international
    QString strNotifyQmPath = QCoreApplication::applicationDirPath().append("/Language/Language_en/DSMessageNotify_en.qm");
    QString strLang("English");

    SearchQmFile(DSGUI::DSDir::GetCurrentPath() + "/Language/Language_zh/");
    strNotifyQmPath = QCoreApplication::applicationDirPath().append("/Language/Language_zh/DSMessageNotify_zh.qm");

    // set font
    QFont chnFont("Microsoft YaHei");
    chnFont.setPixelSize(14);
    QFont enFont("Arial");
    enFont.setPixelSize(14);
    app.setFont(chnFont);

    // set notify
    DSGUI::DSMessageNotify::Instance().SetParam(QStringList() << strNotifyQmPath, QStringList() << DSGUI::GetSkinVersion(), strLang);
    DSGUI::DSMessageNotify::Instance().StartMessageProcess();
    DSGUI::DSMessageNotify::Instance().SetMessageNotifyTitle(QObject::tr("Notify"));

    // load style
    QString strStyle = "";
    QFile fpStyle(commonSpace::GetSkinPath("public", "style.qss"));
    if (fpStyle.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        strStyle = fpStyle.readAll();
        fpStyle.close();
    }
    QString strCSSFilePath = commonSpace::GetSkinPath("") + QString("/DSGUI/CSS/");
    QStringList strList;
    strList.push_back("*.CSS");
    QStringList strFileList = QDir(strCSSFilePath).entryList(strList, QDir::Files);
    qApp->setStyleSheet(strStyle + DSGUI::DSFile::ReadAll(strFileList, strCSSFilePath));

    // to do uniqueness
    if (theApp.isRunning())
    {
        DSGUI::DSMessageBox::ShowInformation(NULL, QObject::tr("Notice"), QObject::tr("Application had runned!"), DSGUI::DSMessageBox::Ok);
        return 0;
    }

    if (theApp.initInstance())
    {
        //mainApp::InitAppWidget w;
        //w.show();
        app.exec();
    }
    theApp.releaseShareMemory();

    return theApp.exitInstance();
}

void SetTranslator(const QString strPath)
{
    if (strPath.isEmpty())
    {
        return;
    }
    QTranslator * pTrans = new QTranslator();
    if (pTrans->load(strPath))	
    {
        QApplication::installTranslator(pTrans);
    }
    else
    {
        delete pTrans;
        pTrans = NULL;
    }
}

void SearchQmFile(const QString & strPath)
{
    QDir dir(strPath);
    if (!dir.exists())
    {
        return;
    }
    dir.setFilter(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
    dir.setSorting(QDir::DirsFirst);	
                                        
    QFileInfoList list = dir.entryInfoList();
    if (list.size() < 1)
    {
        return;
    }
    int i = 0;
    do
    {
        QFileInfo fileInfo = list.at(i);
        QString tt = fileInfo.fileName();
        // 如果是文件夹
        bool bisDir = fileInfo.isDir();
        if (bisDir)
        {
            SearchQmFile(fileInfo.filePath());
        }
        else
        {
            bool bQm = fileInfo.fileName().endsWith(".qm");
            SetTranslator(fileInfo.filePath());
        }
        i++;
    } while (i < list.size());
}