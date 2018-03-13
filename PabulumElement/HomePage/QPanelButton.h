#ifndef QPANELBUTTON_H
#define QPANELBUTTON_H

#include <QPushButton>
#include <QtWidgets/QWidget>
#include <QtGui/QMouseEvent>

enum
{
	Btn_Normal		= 1,		//普通状态
	Btn_Pressed		= 2,		//按下、选择状态
	Btn_Hover		= 4,		//Hover状态
	Btn_Select		= 8,		//选择状态
};

class QPanelButton : public QPushButton
{
	Q_OBJECT
	Q_PROPERTY(QColor selectPressedFontColor READ selectPressedFontColor WRITE setSelectPressedFontColor)
	Q_PROPERTY(QColor selectHoverFontColor READ selectHoverFontColor WRITE setSelectHoverFontColor)
	Q_PROPERTY(QColor selectFontColor READ selectFontColor WRITE setSelectFontColor)
	Q_PROPERTY(QColor normalHoverFontColor READ normalHoverFontColor WRITE setNormalHoverFontColor)
	Q_PROPERTY(QColor normalFontColor READ normalFontColor WRITE setNormalFontColor)

public:
	QPanelButton(QWidget* parent = 0, QString text="", bool bPaint = true);
	~QPanelButton();
	
	void setText(const QString &text);
	bool load(const QPixmap& pixNormal);
	QPixmap GetPixmap();
	QString GetText();

	void SetHighLight(bool enable);
	int  GetBtnWidth(){return m_ibtnWidth;};
	int  Margin()const;

protected:
	virtual void paintEvent(QPaintEvent* e);
	virtual void enterEvent(QEvent* e);
	virtual void leaveEvent(QEvent* e);
	virtual void mousePressEvent(QMouseEvent *e);
	virtual void mouseReleaseEvent(QMouseEvent *e);
	virtual void mouseMoveEvent(QMouseEvent *e);
	virtual void mouseDoubleClickEvent(QMouseEvent *event);

signals:
	void sgnEnter();
	void sgnLeave();
	void sgnRightClicked(QMouseEvent *event);
	void sgnLeftClicked(QMouseEvent *event);
	void sgnReleased();
	void sgnMove(QMouseEvent *event);
	void sgnDbClicked();

private:
	void PaintMenuBtn(QPainter& painter);
	void PaintMenuWord(QPainter& painter);
	void PaintBottonRect(QPainter& painter);

	void setNormalFontColor(const QColor& color);
	QColor normalFontColor() const;
	void setSelectPressedFontColor(const QColor& color);
	QColor selectPressedFontColor() const;
	void setSelectHoverFontColor(const QColor& color);
	QColor selectHoverFontColor() const;
	void setSelectFontColor(const QColor& color);
	QColor selectFontColor() const;
	void setNormalHoverFontColor(const QColor& color);
	QColor normalHoverFontColor() const;

private:
	int				m_ibtnWidth;  //增加每一个btn的宽度，在构造的时候算好，Additem的时候用
	QPixmap			m_pixNormal;
	QString			m_text;
	int				m_btnState;
	QPixmap			m_pmNormal;
	QPixmap			m_pmHover;
	QPixmap			m_pmHoverNoFocus;
	QPixmap			m_pmPressed;

	QColor			m_normalFontColor;
	QColor			m_selPressedFontColor;
	QColor			m_selHoverFontColor;
	QColor			m_selFontColor;
	QColor			m_normalHoverFontColor;
    bool            m_bPaint;
};

#endif // QPANELBUTTON_H
