#include "mymodel.h"

MyModel::MyModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

QVariant MyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if( role != Qt::DisplayRole ) {
           return QVariant();
       }

       if( orientation == Qt::Vertical ) {
           return section;
       }

       switch( section ) {
       case NAME:
           return QString("Наименование");
       case PRICE:
           return QString( "Цена" );

       }
        return QVariant();
}

int MyModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED( parent )
      //return box.vec.size();
    return ptrsize;  //ihehfiahahfhafhaohaohfoahfoahf!

}

int MyModel::columnCount(const QModelIndex &parent) const
{

    Q_UNUSED( parent )
        return 2;

}

QVariant MyModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()||ptrsize<= index.row()) //jsdjgaqpdjadjwqdja!!!!!!
        return QVariant();

     if(role==Qt::DisplayRole)
     {
         switch(index.column())
         {
            case 0:
             return ptr[index.row()]->name;
            case 1:
             return ptr[index.row()]->price;
         }
     }
    return QVariant();
}


