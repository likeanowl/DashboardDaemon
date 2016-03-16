#include "progressbarwidget.h"
#include "math.h"

ProgressBarWidget::ProgressBarWidget(QString title, int timerInterval) :
    ISensorWidget(1, title, timerInterval)
{
    connect(getPaintTimer(), &QTimer::timeout, this, &ProgressBarWidget::paintWidget);
    mProgressBar = new QProgressBar();

    init();

    getLayout()->addWidget(mProgressBar);
    setLayout(getLayout());
}


void ProgressBarWidget::init()
{
//    this->setInterval(60);
    mProgressBar->setTextVisible(true);
    mProgressBar->setStyleSheet("QProgressBar { border: 2px solid grey; border-radius: 5px; text-align: center; } QProgressBar::chunk { background-color: #C0C0C0;width: 20px;}");
    mProgressBar->setOrientation(Qt::Horizontal);
    mProgressBar->setRange(0,100);
}

void ProgressBarWidget::paintWidget()
{
    mProgressBar->setValue(floor(getData().at(0)));
}
