#ifndef MYMODEL_H
#define MYMODEL_H
#include <QAbstractTableModel>
#include <testbox.h>

class MyModel : public QAbstractTableModel
{
    Q_OBJECT
    enum Column
    {
        NAME=0,PRICE
    };

public:
    TestBox box;
    explicit MyModel(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
};

#endif // MYMODEL_H
