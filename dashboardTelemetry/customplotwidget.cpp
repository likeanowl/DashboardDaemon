#include "customplotwidget.h"
#include <QSizePolicy>

CustomPlotWidget::CustomPlotWidget(int axis, QString title, int timerInterval) :
    ISensorWidget(axis, title, timerInterval)
{
    connect(getPaintTimer(), &QTimer::timeout, this, &CustomPlotWidget::paintWidget);

    mLabelNumders = new QLabel("");
    mLabelNumders->setAlignment(Qt::AlignCenter);

    mPlot = new QCustomPlot();
    mPlot->setWindowTitle(title);
    getLayout()->addWidget(mPlot, 0,0,10,1);
    getLayout()->addWidget(mLabelNumders,10,0,1,1);
    setLayout(getLayout()); //hmmm..

    init();
}

void CustomPlotWidget::addGraph(int n, QColor color)
{
    mPlot->addGraph();
    mPlot->graph(2*n)->setPen(QPen(color));
    mPlot->addGraph();
    mPlot->graph(2*n+1)->setPen(QPen(color));
    mPlot->graph(2*n+1)->setLineStyle(QCPGraph::lsNone);
    mPlot->graph(2*n+1)->setScatterStyle(QCP::ssDisc);
}

void CustomPlotWidget::init()
{
    mPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    mPlot->xAxis->setDateTimeFormat("mm:ss");
    mPlot->xAxis->setAutoTickStep(false);
    mPlot->xAxis->setTickStep(1);
    mPlot->setupFullAxesBox();
//    make left and bottom axes transfer their ranges to right and top axes:
    connect(mPlot->xAxis, SIGNAL(rangeChanged(QCPRange)),
            mPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(mPlot->yAxis, SIGNAL(rangeChanged(QCPRange)),
            mPlot->yAxis2, SLOT(setRange(QCPRange)));

    for (int i = 0; i < getAxis(); i++)
    {
        addGraph(i, getColors()[i]);
    }

}

void CustomPlotWidget::paintWidget()
{
    QString buf;
    QVector<float> data = getData();
    buf.sprintf("%g %g %g", data.at(0), data.at(1), data.at(2));
    mLabelNumders->setText(buf);

    double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
    for (int n = 0; n < getAxis(); n++)
    {
        mPlot->graph(2*n)->addData(key, data[n]);
        mPlot->graph(2*n+1)->clearData();
        mPlot->graph(2*n+1)->addData(key, data[n]);
        mPlot->graph(2*n)->removeDataBefore(key - 5);
        mPlot->graph(2*n)->rescaleValueAxis(true);
        mPlot->xAxis->setRange(key + 0.2, 5, Qt::AlignRight);
        mPlot->replot();
    }

}
