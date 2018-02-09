#ifndef __DSPLUGINAPI_LANGUAGEDEF_H__
#define __DSPLUGINAPI_LANGUAGEDEF_H__

namespace DSPluginAPI
{
	typedef struct struLanguageData
	{
		enum Language
		{
			English = 0,	//Ó¢ÎÄ
			Chinese,		//ÖĞÎÄ
			Japanese,		//ÈÕÓï
			German,			//µÂÓï
			French,			//·¨Óï
			Italian,		//Òâ´óÀûÓï
			Korean,			//³¯ÏÊÓï
			Russian,		//¶íÓï
			Portugal,		//ÆÏÌÑÑÀÓï
			Spanish,		//Î÷°àÑÀÓï
			Arabic,			//°¢À­²®Óï
			Finland,		//·ÒÀ¼Óï
			Netherlands,	//ºÉÀ¼Óï
			Sweden,			//ÈğµäÓï
			Greek,			//Ï£À°Óï
			India,			//Ó¡¶ÈÓï
			Thailand,		//Ì©Óï
			Philippines,	//·ÆÂÉ±öÓï
			Poland,			//²¨À¼Óï
			Denmark,		//µ¤ÂóÓï
			Belarusian,		//°×¶íÂŞË¹Óï
			Turkish,		//ÍÁ¶úÆäÓï
		};
	}struLanguageData_t;
}

#endif // __DSPLUGINAPI_LANGUAGEDEF_H__
