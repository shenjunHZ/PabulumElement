/*
 *@file   ComGUIDef.h
 *@brief  
 * 
 *@author 
 *@date   2014-05-22
 *
 */

#ifndef __DSGUI_COMGUIDEF_H
#define __DSGUI_COMGUIDEF_H

#include <QVariant>

namespace DSGUI
{
    typedef struct struTreeViewData
    {
        /** @enum  DSItemDataRole 
          * @brief 视图中用于标记数据的关键值
          * @brief 视图中的关键值不可重复，定义需做管理
          */ 
        enum DSItemDataRole
        {
            //////////////////////////////////////////////////////////////////////////
            InvalidRole     = Qt::UserRole + 98,
            MinUserRole     = Qt::UserRole + 99,                  // 最小值，不可定义比这更小的关键值

            // 基础关键值
            DecorationRole = Qt::UserRole + 100,  
            DisplayRole    = Qt::UserRole + 101,
            CheckStateRole = Qt::UserRole + 102,
            ItemFlagRole   = Qt::UserRole + 103,
            //BackgroundColorRole,

            // 标题视图
            HeaderViewDefautWidthRole    = Qt::UserRole + 110, // 默认初始化宽度
            HeaderViewCheckableRole      = Qt::UserRole + 111, // 勾选是否可用
            HeaderViewMaxCheckedRole     = Qt::UserRole + 112, // 最大可勾选数

            // 视图中控件
            ComboBoxRole           = Qt::UserRole + 120,  // 是否显示下拉框,索引中存在此key值即可
            ComboBoxDataRole       = Qt::UserRole + 121,  // 下拉框数据，数据格式QVector<QVariantMap>，容器大小为下拉列表数
                                                          // typedef QMap<QString, QVariant> QVariantMap; 索引中的关键值以字符串形式存储
                                                          // 下拉用户自定义数据使用Qt::UserRole关键值
            ComboBoxIndexRole      = Qt::UserRole + 122,  // 下拉索引

            DateTimeEditRole       = Qt::UserRole + 130,   // 传入当前日历QDateTime
            //DateEditRole           = Qt::UserRole + 131,
            DisplayFormatRole      = Qt::UserRole + 135,   // 日历格式 yyyy/M/d H:mm:ss
            

            //////////////////////////////////////////////////////////////////////////
            PixmapAlignmentRole     = Qt::UserRole + 170,     // 设置图标排列方式，靠左 居中 靠右

            // 依次绘制图片
            Pixmap1Role           = Qt::UserRole + 180, // DSGUI::ItemPixmapValue方式批量传入图片
            Pixmap2Role           = Qt::UserRole + 181,
            Pixmap3Role           = Qt::UserRole + 182,

			//选中状态下的替换图片(对应PixmapRole)
			PixmapChecked1Role    = Qt::UserRole + 190, 
			PixmapChecked2Role    = Qt::UserRole + 191,
			PixmapChecked3Role	  = Qt::UserRole + 192,

			//编辑状态下的替换图片(对应PixmapRole)
			PixmapEdit1Role        = Qt::UserRole + 200, 
			PixmapEdit2Role        = Qt::UserRole + 201,
			PixmapEdit3Role		   = Qt::UserRole + 202,
        
            // 图标ToolTip
            Pixmap1ToolRole      = Qt::UserRole + 210,
            Pixmap2ToolRole      = Qt::UserRole + 211,
            Pixmap3ToolRole      = Qt::UserRole + 212,

            MouseCursorShapeRole        = Qt::UserRole + 220, // 设置鼠标悬浮状态

            //////////////////////////////////////////////////////////////////////////
            
            ReservedRole    = Qt::UserRole + 500,             // 内部开发，在此之上定义关键值
            MaxUserRole     = Qt::UserRole + 800              // 外部开发，在此之上定义关键值
        }; 

    }TreeViewData;


    struct ItemPixmapValue
    {
    public:
        enum StateFlag 
        {
            State_Default,   // 默认状态
            State_Hover,     // 鼠标掠过状态
            State_Pressed,   // 鼠标按下状态
            State_Disabled,  // 不可用状态
        };

    public:
        inline ItemPixmapValue()
        {

        }

    public:
        void AddValue(StateFlag enumStateFlag, QVariant vtValue)
        {
            mapValues[enumStateFlag] = vtValue;
        }

        QVariant GetValue(StateFlag enumStateFlag) const
        {
            if (mapValues.contains(enumStateFlag))
            {
                return mapValues.value(enumStateFlag);
            }

            return QVariant();
        }

        QMap<StateFlag, QVariant> mapValues;
    };

    typedef struct struLayoutData
    {
        enum LayoutType
        {
            // 默认布局
            D_1x1_1		    = 1,
            D_2x2_4		    = 4,
            D_3x3_6		    = 6,
            D_3x3_8		    = 8,
            D_3x3_9		    = 9,	
            D_4x4_13		= 13,
            D_4x4_16		= 16,
            D_5x5_20		= 20,
            D_5x5_25		= 25,
            D_6x6_36		= 36,
			D_6x6_64		= 64,

            // 自定义布局

        };

    }LayoutData;

    /** 结构体：StructScaleRect
     *  说明：  矩形比例
     **/
    typedef struct StructScaleRect 
    {
        double dLeftScale;
        double dTopScale;
        double dRightScale;
        double dBottomScale;

        StructScaleRect() 
            : dLeftScale(0.0),
            dTopScale(0.0),
            dRightScale(0.0),
            dBottomScale(0.0)
        {

        }

        StructScaleRect(double dLeftScaleIn, double dTopScaleIn, double dRightScaleIn, double dBottomScaleIn) 
            : dLeftScale(dLeftScaleIn),
            dTopScale(dTopScaleIn),
            dRightScale(dRightScaleIn),
            dBottomScale(dBottomScaleIn)
        {

        }

        StructScaleRect(const StructScaleRect& struScale) 
            : dLeftScale(struScale.dLeftScale),
            dTopScale(struScale.dTopScale),
            dRightScale(struScale.dRightScale),
            dBottomScale(struScale.dBottomScale)
        {

        }

        // 等号操作，只匹配窗口相同即可
        inline bool operator == (const StructScaleRect& struOther) const
        {
            return struOther.dLeftScale == dLeftScale && struOther.dTopScale == dTopScale
                && struOther.dRightScale == dRightScale && struOther.dBottomScale == dBottomScale;
        }

    }ScaleRectData;

	typedef struct struPTZData
	{
		enum PTZBtnType
		{
			Direction_Up,					// 八方向
			Direction_Down,
			Direction_Left,
			Direction_Right,
			Direction_LeftUp,
			Direction_LeftDown,
			Direction_RightUp,
			Direction_RightDown,

			Direction_3DSiteOn,				// 三维定位
			Direction_3DSiteOff,

			Zoom_Inc,
			Zoom_Dec,
			Foucus_Inc,
			Foucus_Dec,
			Aperture_Inc,
			Aperture_Dec,

			Menu_Up,			  // 云台菜单
			Menu_Down,
			Menu_Left,
			Menu_Right,
			Menu_Enter,
			Menu_Open,
			Menu_Close,
			
			PresetPosition,       // 预置点定位
			AddPreset,			  // 添加预置点
			DeletePreset,		  // 删除预置点

			AutoRotate_On,		  // 水平旋转
			AutoRotate_Off,

			Scan_LeftBoundarySet,    // 线性扫描
			Scan_RightBoundarySet,
			Scan_On,
			Scan_Off,

			Pattern_Set_Start,    // 巡迹
			Pattern_Set_Stop,
			Pattern_On,
			Pattern_Off,

			Asstst_On,			  // 辅助命令
			Asstst_Off,			
		};
	}PTZBtnData;

    typedef QMap<int, QVariant> DSVariantMap;
}

Q_DECLARE_METATYPE(DSGUI::ItemPixmapValue)
Q_DECLARE_METATYPE(DSGUI::StructScaleRect)

Q_DECLARE_METATYPE(QList<DSGUI::DSVariantMap>)
#endif 
