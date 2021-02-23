#include "infoform.h"
#include "ui_infoform.h"

InfoForm::InfoForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InfoForm)
{
    ui->setupUi(this);
}

InfoForm::InfoForm(QVector<QString>names,QVector<QString>values,QWidget *parent):
    QWidget(parent),
    ui(new Ui::InfoForm)
{
    mainlay=new QHBoxLayout;
    table=new QTableWidget();
    table->setColumnCount(2);
    table->setRowCount(names.size());
    for(int i=0;i<table->rowCount();++i)
    {
        table->setItem(i,0,new QTableWidgetItem (names[i]));
    }
    for(int i=0;i<table->rowCount();++i)
    {
         table->setItem(i,1,new QTableWidgetItem (values[i]));
    }
    table->setHorizontalHeaderItem(0,new QTableWidgetItem("Характеристика"));
    table->setHorizontalHeaderItem(1,new QTableWidgetItem("Значение"));
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    mainlay->addWidget(table);
     setLayout(mainlay);
     resize( 500, 600 );
}
InfoForm::~InfoForm()
{
    delete mainlay;
    delete table;
    delete ui;
}

