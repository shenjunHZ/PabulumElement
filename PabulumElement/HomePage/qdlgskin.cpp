
#include "HomePage/qdlgskin.h"

#include <QtGui/QPainter>
#include <QtGui/QPaintEvent>
#include <QtWidgets/QDesktopWidget>
#include <QtWidgets/QApplication>
#include <QtGui/QBitmap>

namespace mainApp
{

QList<_ImageInfo> g_lstLoadedPixmap;

QSize QDlgSkin::StringToSize(QString tar)
{
    QSize ret(0,0);
    if(! tar.isEmpty())
    {
        QString val = tar.trimmed();
        QStringList lstVal = val.split(",");
        if(lstVal.count() == 2)
        {
            val = lstVal.at(0);
            ret.setWidth(val.toInt());
            val = lstVal.at(1);
            ret.setHeight(val.toInt());
        }
    }
    return ret;
}

QDlgSkin::QDlgSkin(QWidget *parent) :
    QDialog(parent)
{
    m_lblTitle = NULL;
    m_bIsLeftBtnClicked = false;
    m_bIsMax = false;
    setWndMoveable(this, false);
    setWindowFlags(Qt::FramelessWindowHint);
}

QDlgSkin::~QDlgSkin()
{
    QList<_ImageInfo>::Iterator itor  = g_lstLoadedPixmap.begin();
    while(itor != g_lstLoadedPixmap.end())
    {
        _ImageInfo & GetInfo = *itor;
        if(GetInfo.pImgSrc != NULL && GetInfo.pImgSrc == m_SkinSettings.m_pixNormal)
        {
            if(--GetInfo.usedTotal == 0)
            {
                delete GetInfo.pImgSrc;
                itor = g_lstLoadedPixmap.erase(itor);
                continue;
            }
        }
        itor++;
    }
    if(m_lblTitle)
    {
        delete m_lblTitle;
        m_lblTitle = NULL;
    }
}

void QDlgSkin::InitSkinSetting(const char *format, const QString &strBmpNormal,
                               const QString & strMainDlgSize, const QString &strMinDlgSize)
{
    if( ! strMainDlgSize.isEmpty())
    {
        m_SkinSettings.m_dlgSize = StringToSize(strMainDlgSize);
    }
    // 窗口大小最小值
    if( ! strMinDlgSize.isEmpty())
    {
        m_SkinSettings.m_dlgMinSize = StringToSize(strMinDlgSize);
    }
    else
    {
        m_SkinSettings.m_dlgMinSize  = m_SkinSettings.m_dlgSize;
    }

    LoadBkImage(strBmpNormal, m_SkinSettings.m_pixNormal, format);
}

bool QDlgSkin::LoadBkImage(const QString &strImgPath, QPixmap *&_out, const char *format)
{
    if(strImgPath.isEmpty() ) {
        _out = NULL;
        return false;
    }

    QList<_ImageInfo>::Iterator itor  = g_lstLoadedPixmap.begin();
    while(itor != g_lstLoadedPixmap.end())
    {
        _ImageInfo & GetInfo = *itor;
        if(GetInfo.strImgPath ==strImgPath )
        {
            _out = GetInfo.pImgSrc;
            GetInfo.usedTotal ++;
            return true;
        }
        itor++;
    }

    _ImageInfo ImgHistory;
    QPixmap *newPic = new QPixmap();
    if(newPic->load( strImgPath, format ) == true)
    {
        _out = newPic;
        ImgHistory.strImgPath = strImgPath;
        ImgHistory.pImgSrc = newPic;
        ImgHistory.usedTotal = 1;
        g_lstLoadedPixmap.push_back(ImgHistory);
        return  true;
    }
    else
    {
        delete newPic;
        _out = NULL;
        return false;
    }
}

/*
    在窗体大小改变事件里把背景图先画好
  */
void QDlgSkin::resizeEvent(QResizeEvent *)
{
    // 原始图片必要性检查
    if( m_SkinSettings.m_pixNormal == NULL || m_SkinSettings.m_pixNormal->isNull() )
       return;

    const QSize dlgNowSize = this->size();

    if( dlgNowSize.width() > m_SkinSettings.m_pixNormal->width()
        || dlgNowSize.height() > m_SkinSettings.m_pixNormal->height() )
    {
        // 设置参数,根据参数来扩充图片
        _wantExtendImgInfo _input;
        _input.pImgSrc = m_SkinSettings.m_pixNormal;
        _input.extendSize = dlgNowSize;
        setExtendPicOrigin(_input.imgOrigin);
        doPaintExtendImag( _input, m_ImgBkgrnd);
    }
    else if(dlgNowSize ==m_SkinSettings.m_pixNormal->size())
    {
        // 大小一致就用原始背景图片
        m_ImgBkgrnd = *m_SkinSettings.m_pixNormal;
    }
    else
    {
        // 这里之所以要用到COPY函数是因为有的窗口要显示图像的一部分
        m_ImgBkgrnd = m_SkinSettings.m_pixNormal->copy( QRect(QPoint(0,0), dlgNowSize) );
    }
    if(m_lblTitle)
    {
        SetWinTitle(m_lblTitle->text());
    }
}

void QDlgSkin::paintEvent(QPaintEvent *event)
{
    if( m_ImgBkgrnd.isNull() )
    {
        return  QDialog::paintEvent(event);
    }
    else
    {
        QPainter painter(this);
        painter.drawPixmap(rect(),m_ImgBkgrnd);
    }
}

void QDlgSkin::SetWinTitle(const QString &title)
{
    int fontW = this->fontMetrics().width(title) + 1;
    int fontH =  this->fontMetrics().height() + 1;

    QRect fontRec = QRect((this->width() - fontW)/2, 8,  fontW+1, fontH+1);

    if(m_lblTitle == NULL)
    {
        m_lblTitle = CreateLabel(this, fontRec, title, Qt::black);
    }
    else
    {
        m_lblTitle->setText(title);
        m_lblTitle->setGeometry(fontRec);
    }
}

/*
    创建label
*/
QLabel * QDlgSkin::CreateLabel(QWidget*parent, const QRect& lblRec, const QString& lblText,
                               const QColor& txtColor ,  const QColor& bgColor )
{
    QLabel * lbl = new QLabel(parent);
    lbl->setGeometry(lblRec);
    lbl->setText(lblText);

    QPalette pal;
    if(txtColor.isValid())
    {
        pal.setColor(QPalette::WindowText, txtColor);
    }
    if(bgColor.isValid())
    {
        pal.setColor(QPalette::Background, bgColor);
        lbl->setAutoFillBackground(true);
    }
    lbl->setPalette(pal);
    return lbl;
}

/*
  切割窗口四角
 */
void QDlgSkin::setRoundMask(int xRnd, int yRnd)
{
    QPainterPath path;
    path.addRoundRect(rect(),xRnd,yRnd);
    QPolygon polygon= path.toFillPolygon().toPolygon();
    QRegion region(polygon);
    setMask(region);
}

/*
    设置可否窗口移动
 */
void QDlgSkin::setWndMoveable(QDlgSkin* pTarget , bool bCanMove)
{
    m_bCanWndMove = bCanMove;
    m_moveTarget = pTarget;
}

void QDlgSkin::mousePressEvent( QMouseEvent * event )
{
    if((event->button() & Qt::LeftButton) == Qt::LeftButton)
    {
        if( m_bCanWndMove && (m_moveTarget && ! m_moveTarget->_IsMaximized()) )
        {
            m_bIsLeftBtnClicked = true;
            m_movePoint = event->globalPos() - m_moveTarget->pos();
        }
    }
}

void QDlgSkin::mouseReleaseEvent( QMouseEvent *)
{
    m_bIsLeftBtnClicked = false;
}

void QDlgSkin::mouseMoveEvent( QMouseEvent *event )
{
    // move windows
    QDesktopWidget wgtDesk;
    QRect  avilableRect = wgtDesk.availableGeometry();
    if(!avilableRect.contains(event->globalPos()))
        return;
    if( m_bIsLeftBtnClicked && m_bCanWndMove && (m_moveTarget && ! m_moveTarget->_IsMaximized()) )
    {
        QPoint movedRange(event->globalPos() - m_movePoint);
        QPoint prevPoit = m_moveTarget->pos();
        int x = abs(movedRange.x() - prevPoit.x());
        int y = abs(movedRange.y() - prevPoit.y());
        if(x > 8 || y > 8)
        {
            m_moveTarget->move(movedRange);
        }
    }
}

void QDlgSkin::OnSwitchSize()
{
    fnSwitchWndSize();
}

/*
    切换窗口大小
 */
void QDlgSkin::fnSwitchWndSize()
{
    if(m_bIsMax)
    {
        _SwitchNormal();
    }
    else
    {
        _SwitchMaximized();
    }
}

void QDlgSkin::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
    {
        return;
    }
}

/*
    设置欲拉伸图片的原点坐标
 */
void QDlgSkin::setExtendPicOrigin(QPoint &point)
{
    point.setX(m_SkinSettings.m_pixNormal->width()/2);
    point.setY(m_SkinSettings.m_pixNormal->height()/2);
}

/*
    拉伸图片(不适用于条纹或有规律背景图)
 */
void  QDlgSkin::doPaintExtendImag(const _wantExtendImgInfo &target, QPixmap &pixmap)
{
    int imgRemnantW = 0;
    int imgRemnantH = 0;
    int rightX = 0;
    int underY = 0;

    QPainter Painter;
    const QPixmap * pGetImgSrc = target.pImgSrc;
    QSize newDlgSize = target.extendSize;
    QPoint imgOrigin = target.imgOrigin;

    pixmap = QPixmap(newDlgSize);
    pixmap.fill(Qt::transparent);
    Painter.begin(&pixmap);

    //left upper
    Painter.drawPixmap(0,0,imgOrigin.x(),imgOrigin.y(),
                       pGetImgSrc->copy(QRect(0,0,imgOrigin.x(),imgOrigin.y())));
    //right upper
    imgRemnantW = pGetImgSrc->width() - imgOrigin.x();
    rightX = newDlgSize.width() - imgRemnantW;
    Painter.drawPixmap(rightX, 0, imgRemnantW, imgOrigin.y(),
                       pGetImgSrc->copy(QRect(imgOrigin.x(),0,imgRemnantW,imgOrigin.y())));
    // left under
    imgRemnantH = pGetImgSrc->height() - imgOrigin.y();
    underY = newDlgSize.height() - imgRemnantH;
    Painter.drawPixmap(0,underY,imgOrigin.x(),imgRemnantH,
                       pGetImgSrc->copy(QRect(0,imgOrigin.y(),imgOrigin.x(),imgRemnantH)));
    // right under
    Painter.drawPixmap(rightX,underY,imgRemnantW,imgRemnantH,
                       pGetImgSrc->copy(QRect(imgOrigin.x(),imgOrigin.y(),imgRemnantW,imgRemnantH)));

    //fill upper
    QPixmap pixFill = pGetImgSrc->copy(QRect(imgOrigin.x(),0,1,imgOrigin.y()));
    for(int i=imgOrigin.x(); i<=rightX; i++)
    {
        Painter.drawPixmap(i,0,1,imgOrigin.y(), pixFill);
    }

    //fill under
    pixFill = pGetImgSrc->copy(QRect(imgOrigin.x(),imgOrigin.y(),1,imgRemnantH));
    for(int i = imgOrigin.x(); i< rightX; i++)
    {
        Painter.drawPixmap(i,underY, 1, imgRemnantH, pixFill);
    }

    // left center
    pixFill = pGetImgSrc->copy(QRect(0,imgOrigin.y(),imgOrigin.x(),1));
    for(int i = imgOrigin.y(); i< underY; i++)
    {
        Painter.drawPixmap(0,i, imgOrigin.x(), 1, pixFill);
    }

    // right center
    pixFill = pGetImgSrc->copy(QRect(imgOrigin.x(),imgOrigin.y(),imgRemnantW,1));
    for(int i = imgOrigin.y(); i< underY; i++)
    {
        Painter.drawPixmap(rightX,i, imgRemnantW, 1, pixFill);
    }

    // center
    if(rightX-imgOrigin.x()>0 && underY-imgOrigin.y()>0)
    {
        pixFill = pGetImgSrc->copy(QRect(imgOrigin.x(),imgOrigin.y(),1,1));
        QRect recObj = QRect(imgOrigin.x(),imgOrigin.y(), rightX-imgOrigin.x(),underY-imgOrigin.y());
        Painter.fillRect(recObj, pixFill);
    }

    Painter.end();
}

/*
    最大化显示
  */
void QDlgSkin::_SwitchMaximized()
{
    // 保存最大化之前,当前窗口的位置
    if( m_lastWndPostion.isNull() )
    {
        GetCenterPosition(m_lastWndPostion);
    }
    else
    {
        m_lastWndPostion = this->pos();
    }

    m_bIsMax = true;

    // 设置窗口位置
    QSize dlgSize = GetWndRealSize();
    QRect deskTopRec = QApplication::desktop()->availableGeometry(this);
    if( dlgSize.width() >  deskTopRec.width() || dlgSize.height() > deskTopRec.height())
    {
        // 如果桌面比窗口允许的最小值还要小
        this->setGeometry(QRect(QPoint(deskTopRec.left(),deskTopRec.top()), dlgSize));
    }
    else
    {
        this->setGeometry(deskTopRec);
    }
    if(this->isHidden())
    {
        this->show();
    }
}

/*
    普通显示
*/
void QDlgSkin::_SwitchNormal()
{
    if(this->isHidden())
    {
        this->show();
    }
    if( m_lastWndPostion.isNull() )
    {
        GetCenterPosition(m_lastWndPostion);
    }
    m_bIsMax = false;
    this->setGeometry(QRect(m_lastWndPostion, GetWndRealSize()));
}

void QDlgSkin::_Show()
{
    if( ! this->_IsMaximized())
    {
        // show center
        GetCenterPosition(m_lastWndPostion);
        this->setGeometry(QRect(m_lastWndPostion, GetWndRealSize()));
        m_bIsMax = false;
    }
    this->show();
}

void QDlgSkin::GetCenterPosition(QPoint &pos)
{
    QRect desktopRec = QApplication::desktop()->availableGeometry(this);
    QSize  dlgSize = GetWndRealSize();

    if( dlgSize.width() >  desktopRec.width() || dlgSize.height() > desktopRec.height())
    {
        // 如果桌面比窗口允许的最小值还要小
        pos.setX(desktopRec.left());
        pos.setY(desktopRec.top());
    }
    else
    {
        pos.setX( desktopRec.left() + ( desktopRec.width() - dlgSize.width() )/2 );
        pos.setY( desktopRec.top() +  ( desktopRec.height() - dlgSize.height() )/2);
    }
}

QSize QDlgSkin::GetWndRealSize()
{
    QRect desktopRec = QApplication::desktop()->availableGeometry(this);
    int wDesktop = desktopRec.width();
    int hDesktop = desktopRec.height();
    int wNormal = m_SkinSettings.m_dlgSize.width();
    int hNormal = m_SkinSettings.m_dlgSize.height();
    int wMini = m_SkinSettings.m_dlgMinSize.width();
    int hMini = m_SkinSettings.m_dlgMinSize.height();

    int w = (wNormal > wDesktop) ?  ( (wDesktop > wMini) ? wDesktop : wMini) : wNormal;
    int h = (hNormal > hDesktop) ?  ( (hDesktop > hMini) ? hDesktop : hMini) : hNormal;
    w = (w<=0) ? wDesktop : w;
    h = (h<=0) ? hDesktop : h;
    return QSize(w,h);
}

}
