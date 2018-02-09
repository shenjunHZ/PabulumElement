#ifndef __DSGUI_SWITCHBUTTON_H
#define __DSGUI_SWITCHBUTTON_H

#include "DSGuiGlobal.h"
#include <QWidget>
#include <QTimer>

namespace DSGUI
{
	/**  @class DSSwitchButton
	 *   @brief 开关按钮
	 */
	class DS_GUI_EXPORT DSSwitchButton : public QWidget
	{
		Q_OBJECT
		Q_PROPERTY(QColor normalOpenBgColor READ normalOpenColor WRITE SetNormalOpenColor)
		Q_PROPERTY(QColor disableOpenBgColor READ disableOpenColor WRITE SetDisableOpenColor)
		Q_PROPERTY(QColor normalCloseBgColor READ normalCloseColor WRITE SetNormalCloseColor)
		Q_PROPERTY(QColor disableCloseBgColor READ disableCloseColor WRITE SetDisableCloseColor)
		Q_PROPERTY(QColor thumbColor READ thumbColor WRITE SetThumbColor)
		Q_PROPERTY(QColor disableThumbColor READ disableThumbColor WRITE SetDisableThumbColor)
		Q_PROPERTY(qint16 outHeight16 READ outHeight16 WRITE SetUserDefinedOutHeight)
		Q_PROPERTY(qint16 inHeight16 READ InHeight16 WRITE SetUserDefinedInHeight)
		Q_PROPERTY(qint16 width16 READ width16 WRITE SetUserDefinedWidth)
		Q_PROPERTY(qint16 margin16 READ margin16 WRITE SetUserDefinedMargin)
		Q_PROPERTY(qreal radius READ radius WRITE SetRadius)

	public:
		explicit DSSwitchButton(QWidget *parent = 0);

		// 返回开关状态 - 打开：true 关闭：false
		bool isToggled() const;
		// 设置开关状态
		void setToggle(bool checked);

	protected:
		// 绘制开关
		void paintEvent(QPaintEvent *event) ;

		// 鼠标按下事件
		void mousePressEvent(QMouseEvent *event) ;

		// 鼠标释放事件 - 切换开关状态、发射toggled()信号
		void mouseReleaseEvent(QMouseEvent *event) ;

		// 大小改变事件
		void resizeEvent(QResizeEvent *event) ;

		// 缺省大小
		QSize sizeHint() const ;
		QSize minimumSizeHint() const ;

signals:
		// 状态改变时，发射信号
		void toggled(bool checked);

	private slots:
		// 状态切换时，用于产生滑动效果
		void onTimeout();

	private:
		bool		m_bChecked;				// 是否选中
		QTimer		m_timer;				// 定时器
		qreal		m_nX;					// x点坐标
		qreal		m_nY;					// y点坐标

	private /*property*/:
		QColor		m_noramlOpenBgClr;		// 正常打开背景色
		QColor		m_disableOpenBgClr;		// 禁用打开背景色
		QColor		m_normalCloseBgClr;		// 正常关闭背景色
		QColor		m_disableCloseBgClr;    // 禁用关闭背景色
		QColor		m_thumbColor;			// 拇指颜色
		QColor		m_disbaleThumbColor;	// 禁用拇指颜色
		qreal		m_radius;				// 圆角
		qint16		m_nOutHeight;			// 外圆高度
		qint16		m_nInHeight;			// 内圆高度
		qint16		m_nWidth;				// 宽度
		qint16		m_nMargin;				// 外边距
	private:
		inline QColor normalOpenColor()const
		{
			return m_noramlOpenBgClr;
		}
		inline void SetNormalOpenColor(QColor color)
		{
			m_noramlOpenBgClr = color;
		}
		inline QColor disableOpenColor()const
		{
			return m_disableOpenBgClr;
		}
		inline void SetDisableOpenColor(QColor color)
		{
			m_disableOpenBgClr = color;
		}
		inline QColor normalCloseColor()const
		{
			return m_normalCloseBgClr;
		}
		inline void SetNormalCloseColor(QColor color)
		{
			m_normalCloseBgClr = color;
		}
		inline QColor disableCloseColor()const
		{
			return m_disableCloseBgClr;
		}
		inline void SetDisableCloseColor(QColor color)
		{
			m_disableCloseBgClr = color;
		}
		inline QColor thumbColor()const
		{
			return m_thumbColor;
		}
		inline void SetThumbColor(QColor color)
		{
			m_thumbColor = color;
		}
		inline QColor disableThumbColor()const
		{
			return m_disbaleThumbColor;
		}
		inline void SetDisableThumbColor(QColor color)
		{
			m_disbaleThumbColor = color;
		}
		inline qreal radius()const
		{
			return m_radius;
		}
		inline void SetRadius(qreal r)
		{
			m_radius = r;
		}
		inline qint16 outHeight16()const
		{
			return m_nOutHeight;
		}
		inline void SetUserDefinedOutHeight(qint16 h)
		{
			m_nOutHeight = h;
		}
		inline qint16 InHeight16()const
		{
			return m_nInHeight;
		}
		inline void SetUserDefinedInHeight(qint16 h)
		{
			m_nInHeight = h;
		}
		inline qint16 width16()const
		{
			return m_nWidth;
		}
		inline void SetUserDefinedWidth(qint16 w)
		{
			m_nWidth= w;
		}
		inline qint16 margin16()const
		{
			return m_nMargin;
		}
		inline void SetUserDefinedMargin(qint16 m)
		{
			m_nMargin = m;
		}
	};
}

#endif // 
