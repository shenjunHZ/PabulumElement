#ifndef VIEW_DEFINE_H
#define VIEW_DEFINE_H

#include "QPanelButton.h"
#include <QtWidgets/QWidget>
#include <QtGui/QIcon>

// button start position
#define BUTTON_BEGINX 100

// height for toolbar
#define TOOLBAR_HEIGHT 50
#define TOOLBAR_BORDER 0                          // button与顶的间距
#define TOOLBAR_BTN_HEIGHT (TOOLBAR_HEIGHT-2*TOOLBAR_BORDER)      // button高度

// add button
#define BTN_AddPAGE_WIDTH 24
#define BTN_AddPAGE_HEIGHT 24
#define TOOLBAR_BTN_MARGIN 350

//PannelItem
#define PANNELITEM_WIDTH 100
#define PANNELITEM_HEIGHT 115

#define PANNELITEM_HSPACEING 20
#define PANNELITEM_VSPACEING 5

#define PANNELBORDER_LEFT 35
#define PANNELBORDER_TOP 35
#define PANNELBORDER_RIGHT 35
#define PANNELBORDER_BOTTOM 35

#define WM_ASKQUIT 100
#define WM_TASKBAR_ANIMATION 101
#define WM_TASKBAR_INIT 102
#define  WM_VIDEO_REFRESH 103

//#define MAX_REAL_MONITOR_NUM	4
#define Q_DELETE(T)  if(T != NULL) {  delete T; T = NULL;}

    typedef enum
    {
        Recipe_View_Column_Num = 0,
        Recipe_View_Column_MaterialCode = 1,
        Recipe_View_Column_MaterialName = 2,
        Recipe_View_Column_MaterialCount = 3,
        Recipe_View_Column_MaterialPrice = 4,
    }RecipeViewColumn_e;

    enum
    {
        HomeBasic = 0,	
        HomeExtended = 1,	
    };

    typedef struct PanelBtnInfo
    {
        QPanelButton* pBtn;					
        QString strPluginID;			
        std::string vecWidgetID;	
        bool bRight;						
        int nType;
        QWidget* pWidget; // match function widget
        QIcon*   pIcon;   // match toolbar icon
    }PanelBtnInfo_t;

    typedef QList<PanelBtnInfo_t> PanelBtnInfoList;

    typedef struct PanelBtnInfoEx
    {
        QString strGroupName;
        PanelBtnInfoList lsPanelBtnInfo;

        PanelBtnInfoEx()
        {
            strGroupName = "";
            lsPanelBtnInfo.clear();
        }
    }PanelBtnInfoEx_t;

    typedef struct AbbreviationInfo
    {
        uint64_t    iPrimaryKey;
        std::string strAcronym;
        std::string strDefinition;

        AbbreviationInfo()
        {
            iPrimaryKey = 0;
            strAcronym = "";
            strDefinition = "";
        }
    }AbbreviationInfo_s;

#endif
