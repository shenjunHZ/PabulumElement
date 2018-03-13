#include "HomePage/QPanelButton.h"
#include "AppCommon/commonControl.h"

#include <QtGui/QPainter>
#include <QtWidgets/qdrawutil.h>
#include <QtWidgets/QStyleOptionButton>
#include <QtWidgets/QStyle>

static const int MARGIN = 5;

QPanelButton::QPanelButton(QWidget *parent,QString text)
    : QPushButton(parent)
{
    m_text = text;
    m_btnState = Btn_Normal;
    m_pmNormal       =  QPixmap(commonSpace::GetSkinPath("HomePage/toolbar/") + "btn-n.png");
    m_pmHover        =  QPixmap(commonSpace::GetSkinPath("HomePage/toolbar/") + "btn-h.png");
    m_pmPressed      =  QPixmap(commonSpace::GetSkinPath("HomePage/toolbar/") + "btn-p.png");
    m_pmHoverNoFocus =  QPixmap(commonSpace::GetSkinPath("HomePage/toolbar/") + "light.png");
    setStyleSheet("QPanelButton {font-size: 14px;}");
    ensurePolished();
    m_ibtnWidth = 18*2+this->fontMetrics().width(text)+2*MARGIN;
    setFixedWidth(m_ibtnWidth);
    setFlat(true);
}


QPanelButton::~QPanelButton()
{

}

void QPanelButton::setText(const QString &text)
{
    m_text = text;
}

bool QPanelButton::load(const QPixmap& pixNormal)
{
    m_pixNormal = pixNormal;
    return true;
}

QPixmap QPanelButton::GetPixmap()
{
    return m_pixNormal;
}

QString QPanelButton::GetText()
{
    return m_text;
}

void QPanelButton::SetHighLight(bool enable)
{
    if(enable)
    {
        m_btnState |= Btn_Select;
        update();
    }
    else
    {
        if (m_btnState & Btn_Select)
        {
            m_btnState ^= Btn_Select;
        }
        update();
    }
}

void QPanelButton::paintEvent(QPaintEvent* e)
{
    QPushButton::paintEvent(e);
    QPainter painter(this);
    //PaintMenuBtn(painter);
}

void QPanelButton::enterEvent(QEvent* e)
{
    QPushButton::enterEvent(e);

    QStyleOptionButton option;
    initStyleOption(&option);
    if(option.state & QStyle::State_MouseOver)
    {
        m_btnState |= Btn_Hover;
        emit sgnEnter();
    }
}

void QPanelButton::leaveEvent(QEvent* e)
{
    QPushButton::leaveEvent(e);

    if(m_btnState & Btn_Hover)
    {
        m_btnState ^= Btn_Hover;
    }
    if (m_btnState & Btn_Pressed)
    {
        m_btnState ^= Btn_Pressed;
    }
    emit sgnLeave();
}

void QPanelButton::mousePressEvent(QMouseEvent *e)
{
    if((e->button() &Qt::RightButton) == Qt::RightButton)
    {
        emit sgnRightClicked(e);
    }
    else
    {
        m_btnState |= Btn_Pressed;
        emit sgnLeftClicked(e);
    }

    QPushButton::mousePressEvent(e);
}

void QPanelButton::mouseReleaseEvent(QMouseEvent *e)
{
    emit sgnReleased();

    if (m_btnState & Btn_Pressed)
    {
        m_btnState ^= Btn_Pressed;
    }

    QPushButton::mouseReleaseEvent(e);
}

void QPanelButton::mouseMoveEvent(QMouseEvent *e)
{
    if((e->buttons() & Qt::LeftButton) == Qt::LeftButton)
    {
        emit sgnMove(e);
    }
    return QPushButton::mouseMoveEvent(e);
}


void QPanelButton::PaintMenuBtn(QPainter& painter)
{
    PaintBottonRect(painter);
    PaintMenuWord(painter);
}
void QPanelButton::PaintBottonRect(QPainter& painter)
{
    const QRect tmpRect = rect().adjusted(MARGIN,11,-MARGIN,-11);
    const QMargins tmpMargin = QMargins(6,6,6,6);
    if ((m_btnState & Btn_Select) && (m_btnState & Btn_Pressed))
    {
        qDrawBorderPixmap(&painter,tmpRect,tmpMargin,m_pmPressed);
    }
    else if ((m_btnState & Btn_Select) && (m_btnState & Btn_Hover))
    {
        qDrawBorderPixmap(&painter,tmpRect,tmpMargin,m_pmHover);
    }
    else if(m_btnState & Btn_Hover)
    {
        qDrawBorderPixmap(&painter,tmpRect,tmpMargin,m_pmHoverNoFocus);
    }
    else if(m_btnState & Btn_Select)
    {
        qDrawBorderPixmap(&painter,tmpRect,tmpMargin,m_pmNormal);
    }
}

void QPanelButton::PaintMenuWord(QPainter& painter)
{
    QString title(m_text);
    if (title.isEmpty())
    {
        return;
    }

    QColor txtColor;
    QFont font = painter.font();

    if ((m_btnState & Btn_Select) && (m_btnState & Btn_Pressed))
    {
        txtColor = m_selPressedFontColor;
        font.setBold(true);
    }
    else if((m_btnState & Btn_Select) && (m_btnState & Btn_Hover))
    {
        txtColor = m_selHoverFontColor;
        font.setBold(true);
    }
    else if(m_btnState & Btn_Hover)
    {
        txtColor = m_normalHoverFontColor;
        font.setBold(true);
    }
    else if(m_btnState & Btn_Select)
    {
        txtColor = m_selFontColor;
        font.setBold(true);
    }
    else
    {
        txtColor = m_normalFontColor;
        font.setBold(false);
    }

    painter.setFont(font);
    painter.setPen(txtColor);

    // 字体长度,高度
    QTextOption opt;
    QRect fontRect = rect().adjusted(MARGIN,0,-MARGIN,0);
    opt.setAlignment(Qt::AlignCenter);
    opt.setWrapMode(QTextOption::NoWrap);
    bool bLeft = false;

    if ((m_btnState & Btn_Select) && (m_btnState & Btn_Pressed))
    {
        bLeft = true;
    }
    else if(m_btnState & Btn_Hover)
    {
        bLeft = true;
    }

    if(parentWidget())
    {
        QVariant prop = parentWidget()->property("ItemCloseable");
        if(prop.isValid() && prop.canConvert<bool>())
        {
            bool bCloseable = prop.toBool();
            if(!bCloseable)
            {
                bLeft = false;
            }
        }
    }
    if (bLeft)
    {
        fontRect.adjust(16,0,-20,0);
    }
    else
    {
        fontRect.adjust(18,0,-18,0);
    }
    title = this->fontMetrics().elidedText(title, Qt::ElideRight, fontRect.width());
    painter.drawText(fontRect,title,opt);
}

void QPanelButton::mouseDoubleClickEvent( QMouseEvent* event )
{
    if ( (event->button()&Qt::LeftButton) != Qt::LeftButton)
    {
        return;
    }

    emit sgnDbClicked();
}

int QPanelButton::Margin() const
{
    return MARGIN;
}

void QPanelButton::setNormalFontColor( const QColor& color )
{
    m_normalFontColor = color;
}

QColor QPanelButton::normalFontColor() const
{
    return m_normalFontColor;
}

void QPanelButton::setSelectPressedFontColor(const QColor& color)
{
    m_selPressedFontColor = color;
}

QColor QPanelButton::selectPressedFontColor() const
{
    return m_selPressedFontColor;
}

void QPanelButton::setSelectHoverFontColor(const QColor& color)
{
    m_selHoverFontColor = color;
}

QColor QPanelButton::selectHoverFontColor() const
{
    return m_selHoverFontColor;
}

void QPanelButton::setSelectFontColor(const QColor& color)
{
    m_selFontColor = color;
}

QColor QPanelButton::selectFontColor() const
{
    return m_selFontColor;
}

void QPanelButton::setNormalHoverFontColor(const QColor& color)
{
    m_normalHoverFontColor = color;
}

QColor QPanelButton::normalHoverFontColor() const
{
    return m_normalHoverFontColor;
}


