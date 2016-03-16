#pragma once
#include "widgetslib_global.h"
#include "isensorwidget.h"

#include <QLCDNumber>
class WIDGETSLIBSHARED_EXPORT LCDNumberWidget : public ISensorWidget
{
public:
    LCDNumberWidget(QString title, int timerInterval);

public slots:
    void paintWidget();
    void init();

private:
    QLCDNumber *LCDNumbers;

};
