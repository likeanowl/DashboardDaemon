#pragma once

#include "idatasource.h"
#include <QVector>

class ElementaryDataSource : public IDataSource
{
public:
    ElementaryDataSource();

public:
    void updateData(QVector<float> submittedData);
};

