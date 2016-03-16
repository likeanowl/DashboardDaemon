#include "tablewidget.h"

TableWidget::TableWidget(int axis, QString title, int timerInterval) :
    ISensorWidget(axis, title, timerInterval)
{
    connect(getPaintTimer(), &QTimer::timeout, this, &TableWidget::paintWidget);
    mTable = new QTableWidget();
    mRowToWriteData = 0;

    init();

    mTable->setWindowTitle(title);
    getLayout()->addWidget(mTable);
    setLayout(getLayout());
}

void TableWidget::init()
{
//    this->setInterval(5);

    mTable->setRowCount(1);
    mTable->setColumnCount(getAxis() + 1);

    QStringList nameOfColumns;
    nameOfColumns.append("time");
    for (int i = 0; i != getAxis(); ++i) {
        nameOfColumns.append(QString::number(i+1)+" value");
    }

    mTable->setHorizontalHeaderLabels(nameOfColumns);
}

void TableWidget::paintWidget()
{
    int currentNumOfRows = mTable->rowCount();
    if (currentNumOfRows < mMaxOfRows) {
        mTable->insertRow(currentNumOfRows);
    }

    QString currentTime = QTime::currentTime().toString();
    QTableWidgetItem *firstItem = new QTableWidgetItem(currentTime);
    firstItem->setFlags(firstItem->flags() ^ Qt::ItemIsEditable);
    mTable->setItem(mRowToWriteData, 0, firstItem);
    for (int i = 1; i != getAxis() + 1; ++i) {
        QTableWidgetItem *newItem = new QTableWidgetItem(QString::number(getData().at(i - 1)));
        newItem->setFlags(newItem->flags() ^ Qt::ItemIsEditable);
        mTable->setItem(mRowToWriteData, i, newItem);
    }

    if (mRowToWriteData == mMaxOfRows - 1) {
        mRowToWriteData = 0;
    } else {
        ++mRowToWriteData;
    }
}

const int TableWidget::mMaxOfRows = 10;
