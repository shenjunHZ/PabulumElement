#ifndef QDLGSKIN_H
#define QDLGSKIN_H

#include <QtWidgets//QDialog>
#include <QtWidgets/QLabel>
#include <QtGui/QMouseEvent>
#include <QtCore/QTimer>
#include <QtGui/QBitmap>

typedef struct 
{
    QSize extendSize;
    QPoint imgOrigin;
    const QPixmap *pImgSrc;
}_wantExtendImgInfo;

struct _dlgSkinSetting
{
    _dlgSkinSetting()
    {
        m_pixNormal = 0;
    }
    QPixmap *m_pixNormal;
    QSize m_dlgSize;
    QSize m_dlgMinSize;
};

typedef struct
{
    QPixmap *pImgSrc;
    QString strImgPath;
    int usedTotal;
}_ImageInfo;

namespace mainApp
{

class QDlgSkin : public QDialog
{
    Q_OBJECT
public:
    explicit QDlgSkin(QWidget *parent = 0);
    virtual ~QDlgSkin();

    void SetWinTitle(const QString &title);
    void _SwitchMaximized();
    void _SwitchNormal();
    void _Show();
    bool _IsMaximized() {return m_bIsMax==true;}
    QSize StringToSize(QString);
    _dlgSkinSetting m_SkinSettings;

    void InitSkinSetting(const char *format, const QString &strBmpNormal
        , const QString &strMainDlgSize="", const QString &strMinDlgSize = "");

    // 拉伸图片(不适用于条纹或有规律背景图)
    static void doPaintExtendImag(const  _wantExtendImgInfo &target, QPixmap &pixmap);
    //  1张图片根据5个坐标抠图

    static QLabel* CreateLabel(QWidget*parent, const QRect&,const QString &, const QColor& txtColor=Qt::black ,  const QColor& bgColor="");
    QPixmap m_ImgBkgrnd;

protected:
    bool LoadBkImage(const QString &, QPixmap *&, const char *format = 0);
    void GetCenterPosition(QPoint &pos);
    QSize GetWndRealSize();

    // 切割窗口四角
    void setRoundMask(int xRnd, int yRnd);
    // 设置可否窗口移动
    void setWndMoveable(QDlgSkin*, bool);
    virtual void paintEvent(QPaintEvent *);
    virtual void resizeEvent(QResizeEvent *);
    virtual void mousePressEvent( QMouseEvent * event );
    virtual void mouseReleaseEvent( QMouseEvent * event );
    virtual void mouseMoveEvent(QMouseEvent *event );

    // 切换窗口大小
    virtual void fnSwitchWndSize();
    virtual void keyPressEvent(QKeyEvent *event);
    bool m_bIsMax;
    QLabel *m_lblTitle;

    // 设置欲拉伸图片的原点坐标
    virtual void setExtendPicOrigin(QPoint &);

private:
    bool m_bCanWndMove;
    QPoint m_movePoint;
    QPoint m_lastWndPostion;
    QDlgSkin *m_moveTarget;
    bool m_bIsLeftBtnClicked;

protected slots:
    void OnSwitchSize();
};

}
#endif // QDLGSKIN_H
