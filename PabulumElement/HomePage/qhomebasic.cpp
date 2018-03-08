#include "HomePage/qhomebasic.h"
#include "AppCommon/commonControl.h"
#include "AppCommon/ClientApp.h"

QHomeBasic::QHomeBasic(QWidget *parent)
	: QHomePanel(parent)
{
	this->setObjectName("QHomeBasic");
	SET_MODULE_STYLE_BY_PATH("HomePage");
}

QHomeBasic::~QHomeBasic()
{

}

void QHomeBasic::AddButtons()
{
	for(int id = GetTabCount() - 1; id >= 0; id--)
	{
		this->RemoveTab(id);
	}

	for (QVector<PanelBtnInfoEx_t>::iterator it = m_vecBtnInfo.begin(); it != m_vecBtnInfo.end(); it++)
	{
		PanelBtnInfoList& lsPanelBtnInfo = it->lsPanelBtnInfo;
		if (lsPanelBtnInfo.size() == 1)
		{
			// non group label
			PanelBtnInfo_t& struPanelBtnInfo = *lsPanelBtnInfo.begin();

			if (struPanelBtnInfo.bRight )
			{
				QString strID = struPanelBtnInfo.strPluginID;

				this->AddTab(struPanelBtnInfo.pBtn->GetPixmap(), struPanelBtnInfo.pBtn->GetText(), strID);
			}
		}
		else
		{
			// group label
			QList<DSGUI::TabGroup_t> lsTabGroup;

			DSGUI::TabGroup_t struTabGroup;
			PanelBtnInfoList& lsPanelBtnInfo = it->lsPanelBtnInfo;
			for (PanelBtnInfoList::iterator iter = lsPanelBtnInfo.begin(); iter != lsPanelBtnInfo.end(); iter++)
			{
				PanelBtnInfo_t& struPanelBtnInfo = *iter;
				if (struPanelBtnInfo.bRight && struPanelBtnInfo.nType == HomeBasic)
				{
					QString strID = struPanelBtnInfo.strPluginID;

					struTabGroup.iconTab = struPanelBtnInfo.pBtn->GetPixmap();
					struTabGroup.strName = struPanelBtnInfo.pBtn->GetText();
					struTabGroup.strPluginID = strID;
					lsTabGroup.push_back(struTabGroup);
				}
			}

			if (lsTabGroup.size() != 0)
			{
				this->AddTabGroup(lsTabGroup, it->strGroupName);
			}
		}
	}
}

int	QHomeBasic::ClickBtn(QString strWidgetID)
{
	bool bFind = false;
	for (QVector<PanelBtnInfoEx_t>::iterator it = m_vecBtnInfo.begin(); it != m_vecBtnInfo.end(); it++)
	{
		PanelBtnInfoList& lsPanelBtnInfo = it->lsPanelBtnInfo;
		for (PanelBtnInfoList::iterator iter = lsPanelBtnInfo.begin(); iter != lsPanelBtnInfo.end(); iter++)
		{
			PanelBtnInfo_t& struPanelBtnInfo = *iter;
			//QVector<std::string> vsWidgetID = struPanelBtnInfo.vecWidgetID;

			{
				if (struPanelBtnInfo.vecWidgetID == strWidgetID.toStdString())
				{
					LaunchPlugin(struPanelBtnInfo);
					return 0;
				}
			}
		}
	}

	return 0;
}

QList<DSGUI::TabPanel_t> QHomeBasic::GetPanelBtnList()
{
	return this->GetAllTabPluginID();
}
