#include "isensorwidget.h"

ISensorWidget::ISensorWidget(int axis, QString title, int timerInterval, QWidget *parent) :
    QWidget(parent),
    mData(axis),
    mTitle(title),
    mAxis(axis),
    mTimerInterval(timerInterval)
{
    this->setStyleSheet("background-color: white");
    mData.fill(0.0);
    mColors << QColor("red") << QColor("blue") << QColor("green");
    mPaintTimer = new QTimer(this);
    mLayout = new QGridLayout;
    mTitleLabel = new QLabel(title);
    mTitleLabel->setAlignment(Qt::AlignCenter);

    mPaintTimer->setInterval(timerInterval);
}

QVector<QColor> ISensorWidget::getColors() const
{
    return mColors;
}

void ISensorWidget::setColors(const QVector<QColor> &value)
{
    mColors = value;
}

QGridLayout *ISensorWidget::getLayout() const
{
    return mLayout;
}

void ISensorWidget::setMLayout(QGridLayout *value)
{
    mLayout = value;
}

QLabel *ISensorWidget::getTitleLabel() const
{
    return mTitleLabel;
}

void ISensorWidget::setTitleLabel(QLabel *value)
{
    mTitleLabel = value;
}

QMenu *ISensorWidget::getWidgetMenu() const
{
    return mWidgetMenu;
}

void ISensorWidget::setWidgetMenu(QMenu *value)
{
    mWidgetMenu = value;
}

QTimer *ISensorWidget::getPaintTimer() const
{
    return mPaintTimer;
}

void ISensorWidget::setPaintTimer(QTimer *value)
{
    mPaintTimer = value;
}

QString ISensorWidget::getTitle() const
{
    return mTitle;
}

void ISensorWidget::setTitle(const QString &value)
{
    mTitle = value;
}

int ISensorWidget::getAxis() const
{
    return mAxis;
}

void ISensorWidget::setAxis(int value)
{
    mAxis = value;
}

int ISensorWidget::getTimerInterval() const
{
    return mTimerInterval;
}

void ISensorWidget::setTimerInterval(int value)
{
    mTimerInterval = value;
}

void ISensorWidget::startPaint()
{
    mPaintTimer->start(mTimerInterval);
}

void ISensorWidget::stopPaint()
{
    mPaintTimer->stop();
}

void ISensorWidget::setInterval(int interval)
{
    mTimerInterval = interval;
}
QVector<float> ISensorWidget::getData() const
{
    return mData;
}

void ISensorWidget::setData(const QVector<float> &data)
{
    mData = data;
}


void ISensorWidget::updateData(QVector<float> updates)
{
    int n = updates.size();
    n = n >= mAxis ? mAxis : n;
    for (int i = 0; i < n; i++)
    {
        mData[i] = updates.at(i);
    }
}

void ISensorWidget::subscribeWidgetToDataSource(IDataSource *dataSource)
{
    connect(dataSource, &IDataSource::recieveNewData, this, &ISensorWidget::updateData);
}

void ISensorWidget::unscribeWidgetFromDataSource(IDataSource *dataSource)
{
    disconnect(dataSource, &IDataSource::recieveNewData, this, &ISensorWidget::updateData);
}
