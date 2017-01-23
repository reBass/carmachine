#include "bottomWidgets.h"
#include <QHBoxLayout>
#include <QTime>

#include <QMediaPlayer>
#include "global_value.h"

bottomWidgets::bottomWidgets(QWidget *parent) : baseWidget(parent)
{
    setStyleSheet("bottomWidgets{background:transparent;}");
    init();
    setMouseTracking(true);
    setFixedHeight(160);
}

void bottomWidgets::init()
{
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    QHBoxLayout *mainlyout=new QHBoxLayout;

    // first layout
    QHBoxLayout *layout1=new QHBoxLayout;

    m_btnnext=new flatButton(this);
    m_btnprevious=new flatButton(this);
    m_btnPlay=new flatButton(this);

    m_btnnext->setFixedSize(100,100);
    m_btnprevious->setFixedSize(100,100);
    m_btnPlay->setFixedSize(100,100);

    m_btnnext->setStyleSheet("QPushButton{border-image:url(:/image/music/btn_next (1).png);}"
                             "QPushButton::hover{border-image:url(:/image/music/btn_next (2).png);}"
                             "QPushButton::pressed{border-image:url(:/image/music/btn_next (3).png);}");
    m_btnprevious->setStyleSheet("QPushButton{border-image:url(:/image/music/btn_previous (1).png);}"
                                 "QPushButton::hover{border-image:url(:/image/music/btn_previous (2).png);}"
                                 "QPushButton::pressed{border-image:url(:/image/music/btn_previous (3).png);}");
    m_btnPlay->setStyleSheet("QPushButton{border-image:url(:/image/music/btn_play (1).png);}"
                             "QPushButton::hover{border-image:url(:/image/music/btn_play (2).png);}"
                             "QPushButton::pressed{border-image:url(:/image/music/btn_play (3).png);}");

    layout1->addWidget(m_btnprevious);
    layout1->addWidget(m_btnPlay);
    layout1->addWidget(m_btnnext);
    layout1->setSpacing(20);
    layout1->setContentsMargins(0,0,0,0);
    //////////////////////////////////////////////////////////////

    // second layput
    QVBoxLayout *layout2=new QVBoxLayout;

    m_positionWid = new musicPositionWidget(this);
    m_positionWid->m_mainslider->installEventFilter(this);


    QHBoxLayout *layout2_1=new QHBoxLayout;
    m_labnowPlayname=new TextMovingWidget(str_origin_move_songname,this);
    m_labnowPlayname->setMinimumWidth(250);
    m_labnowPlayname->setFixedHeight(25);
    m_labnowPlayname->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    m_labnowPlayname->setFont(QFont(Font_Family,Font_size_Normal+1,QFont::Normal));

    m_labposition=new QLabel("00:00/00:00",this);
    m_labposition->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    m_labposition->setFixedSize(170,25);
    m_labposition->setFont(QFont(Font_Family,Font_size_Normal+1,QFont::Normal));

    layout2_1->addWidget(m_labnowPlayname);
    layout2_1->addWidget(m_labposition);


    layout2->addSpacing(20);
    layout2->addLayout(layout2_1);
    layout2->addWidget(m_positionWid);
    layout2->setSpacing(0);
    layout2->setContentsMargins(0,0,0,10);
    /////////////////////////////////////////////

    // third layout
    QHBoxLayout *layout3=new QHBoxLayout;

    m_volwid=new volWidget(this);
    m_btnplaymode=new flatButton(this);


    //    m_volwid->setFixedSize(20,20);
    m_btnplaymode->setFixedSize(40,40);



    m_btnplaymode->setStyleSheet("QPushButton{border-image:url(:/image/music/btn_listrandom (1).png);}"
                                 "QPushButton::hover{border-image:url(:/image/music/btn_listrandom (2).png);}" );


    layout3->addWidget(m_btnplaymode);
    layout3->addWidget(m_volwid);
    layout3->setSpacing(18);
    layout3->setContentsMargins(0,0,0,0);

    ////////////////////////////////////////
    mainlyout->addSpacing(30);
    mainlyout->addLayout(layout1);
    mainlyout->addLayout(layout2);
    mainlyout->addSpacing(30);
    mainlyout->addLayout(layout3);
    mainlyout->addSpacing(50);
    mainlyout->setSpacing(30);
    mainlyout->setContentsMargins(20,10,20,10);
    setLayout(mainlyout);
}

void bottomWidgets::setRandomStyle()
{
    m_btnplaymode->setStyleSheet("QPushButton{border-image:url(:/image/music/btn_listrandom (1).png);}"
                                 "QPushButton:hover{border-image:url(:/image/music/btn_listrandom (2).png);}");
}

void bottomWidgets::setInOrderStyle()
{
    m_btnplaymode->setStyleSheet("QPushButton{border-image:url(:/image/music/btn_listcircle (1).png);}"
                                 "QPushButton:hover{border-image:url(:/image/music/btn_listcircle (2).png);}");
}

void bottomWidgets::setOneCycleStyle()
{
    m_btnplaymode->setStyleSheet("QPushButton{border-image:url(:/image/music/btn_listscircle_single (1).png);}"
                                 "QPushButton:hover{border-image:url(:/image/music/btn_listscircle_single (2).png);}");
}

void bottomWidgets::setPlayModeBtnStyle(PlayMode mode)
{
    if(mode==PlayMode::playInOrder)
    {
        setInOrderStyle();
    }
    else if(mode==PlayMode::playRandom)
    {
        setRandomStyle();
    }
    else if(mode==PlayMode::playOneCircle)
    {
        setOneCycleStyle();
    }
    else
    {
        setInOrderStyle();
    }
}

void bottomWidgets::setPauseStyle()
{
    m_btnPlay->setStyleSheet("QPushButton{border-image:url(:/image/music/btn_pause (1).png);}"
                             "QPushButton::hover{border-image:url(:/image/music/btn_pause (2).png);}"
                             "QPushButton::pressed{border-image:url(:/image/music/btn_pause (3).png);}");
    m_labnowPlayname->setText(m_labnowPlayname->Text().remove("缓冲中---->> "));

}

void bottomWidgets::setPlayStyle()
{
    m_btnPlay->setStyleSheet("QPushButton{border-image:url(:/image/music/btn_play (1).png);}"
                             "QPushButton::hover{border-image:url(:/image/music/btn_play (2).png);}"
                             "QPushButton::pressed{border-image:url(:/image/music/btn_play (3).png);}");
    m_labnowPlayname->setText(m_labnowPlayname->Text().remove("缓冲中---->> "));
}

void bottomWidgets::setBufferStaus()
{
    if(!m_labnowPlayname->Text().contains(QString("缓冲中---->> ")))
        m_labnowPlayname->setText(QString("缓冲中---->> ")+m_labnowPlayname->Text());
}

void bottomWidgets::setCurrentSongName(const QString& str)
{
    m_labnowPlayname->setText(str);
}

void bottomWidgets::setPositionLabel(const QString &str)
{
    m_labposition->setText(str);
}

bool bottomWidgets::eventFilter(QObject *obj, QEvent *event)
{
    if(obj==m_positionWid->m_mainslider)
    {
        if (event->type()==QEvent::MouseButtonPress){
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            if (mouseEvent->button() == Qt::LeftButton)	{
                int dur = m_positionWid->m_mainslider->maximum() - m_positionWid->m_mainslider->minimum();
                int pos = m_positionWid->m_mainslider->minimum() + dur * ((double)mouseEvent->x() /m_positionWid->m_mainslider->width());
                if(pos != m_positionWid->m_mainslider->sliderPosition()){
                    m_positionWid->m_mainslider->setValue(pos);
                    m_mainWid->getPlayer()->setPosition(pos);
                }
            }
        }
    }
    return QObject::eventFilter(obj,event);
}

void bottomWidgets::mouseMoveEvent(QMouseEvent *e)
{
    baseWidget::mouseMoveEvent(e);
}

