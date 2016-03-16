#include "idatasource.h"

QVector<float> IDataSource::getData() const
{
    return mData;
}

void IDataSource::setData(const QVector<float> &value)
{
    mData = value;
}
