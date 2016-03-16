#pragma once
#include "widgetslib_global.h"
#include "isensorwidget.h"
#include <QTableWidget>
#include <QDateTime>

class WIDGETSLIBSHARED_EXPORT TableWidget : public ISensorWidget
{
public:
    TableWidget(int axis, QString title, int timerInterval);

public slots:
    void paintWidget();
    void init();

private:
    static const int mMaxOfRows;

    int mRowToWriteData;
    QTableWidget *mTable;
};
