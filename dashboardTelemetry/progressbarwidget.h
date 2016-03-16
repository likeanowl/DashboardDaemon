#pragma once
#include "widgetslib_global.h"
#include "isensorwidget.h"
#include <QProgressBar>
#include <QLabel>

class WIDGETSLIBSHARED_EXPORT ProgressBarWidget : public ISensorWidget
{
public:
    ProgressBarWidget(QString title, int timerInterval);

public slots:
    void paintWidget();
    void init();

private:
    QProgressBar* mProgressBar;
    QLabel* mLabelNumders;

};
