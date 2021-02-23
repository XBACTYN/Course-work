#ifndef TABFORM_H
#define TABFORM_H

#include <QWidget>
#include <QTableView>
#include <QLayout>
#include <QDebug>
#include <QLabel>
#include <QHeaderView>
#include "mymodel.h"
#include <dataloader.h>

namespace Ui {
class TabForm;
}

class TabForm : public QWidget
{
    Q_OBJECT

public:
    QTableView * listptr;
    MyModel * infomodel;
    explicit TabForm(QVector<Processor> & arr,QWidget *parent = nullptr);
    explicit TabForm(QVector<MotherBoard> & arr,QWidget *parent = nullptr);
    explicit TabForm(QVector<GraphicsCard> & arr,QWidget *parent = nullptr);
    explicit TabForm(QVector<RAM> & arr,QWidget *parent = nullptr);
    explicit TabForm(QVector<Cooler> & arr,QWidget *parent = nullptr);
    explicit TabForm(QVector<HDD> & arr,QWidget *parent = nullptr);
    explicit TabForm(QVector<SSD> & arr,QWidget *parent = nullptr);
    explicit TabForm(QVector<Power> & arr,QWidget *parent = nullptr);
    explicit TabForm(QVector<Case> & arr,QWidget *parent = nullptr);
    ~TabForm();

private:
    Ui::TabForm *ui;
};

#endif // TABFORM_H
