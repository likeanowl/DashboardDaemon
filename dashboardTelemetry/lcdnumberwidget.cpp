#include "lcdnumberwidget.h"

LCDNumberWidget::LCDNumberWidget(QString title, int timerInterval) :
    ISensorWidget(1, title, timerInterval)
{
    connect(getPaintTimer(), &QTimer::timeout, this, &LCDNumberWidget::paintWidget);
    LCDNumbers = new QLCDNumber();

    init();

    getLayout()->addWidget(LCDNumbers);
    setLayout(getLayout());
}


void LCDNumberWidget::init()
{
    LCDNumbers->setDigitCount(10);
}

void LCDNumberWidget::paintWidget()
{
    LCDNumbers->display(getData().at(0));
}
