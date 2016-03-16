#include "elementarydatasource.h"

ElementaryDataSource::ElementaryDataSource()
{

}

void ElementaryDataSource::updateData(QVector<float> submittedData)
{
    setData(submittedData);
    emit this->recieveNewData(submittedData);
}
