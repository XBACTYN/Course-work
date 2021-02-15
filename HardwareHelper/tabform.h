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
    ~TabForm();

private:
    Ui::TabForm *ui;
};

#endif // TABFORM_H
