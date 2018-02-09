#ifndef __DSPLUGINAPI_LANGUAGEDEF_H__
#define __DSPLUGINAPI_LANGUAGEDEF_H__

namespace DSPluginAPI
{
	typedef struct struLanguageData
	{
		enum Language
		{
			English = 0,	//Ӣ��
			Chinese,		//����
			Japanese,		//����
			German,			//����
			French,			//����
			Italian,		//�������
			Korean,			//������
			Russian,		//����
			Portugal,		//��������
			Spanish,		//��������
			Arabic,			//��������
			Finland,		//������
			Netherlands,	//������
			Sweden,			//�����
			Greek,			//ϣ����
			India,			//ӡ����
			Thailand,		//̩��
			Philippines,	//���ɱ���
			Poland,			//������
			Denmark,		//������
			Belarusian,		//�׶���˹��
			Turkish,		//��������
		};
	}struLanguageData_t;
}

#endif // __DSPLUGINAPI_LANGUAGEDEF_H__
