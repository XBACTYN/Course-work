#include "tabform.h"
#include "ui_tabform.h"

TabForm::TabForm(QVector<Processor> & arr,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TabForm)
{
    ui->setupUi(this);

    listptr=new QTableView;
    infomodel=new MyModel;
    for(int i=0;i<arr.size();++i)
        infomodel->ptr.push_back(&arr[i]);
    infomodel->ptrsize=arr.size();
    listptr->setModel( infomodel );
    QVBoxLayout* mainLay = new QVBoxLayout;
    setLayout( mainLay );
    listptr->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    mainLay->addWidget(listptr);
}

TabForm::TabForm(QVector<MotherBoard> &arr, QWidget *parent): QWidget(parent),
    ui(new Ui::TabForm)
{
    ui->setupUi(this);

    listptr=new QTableView;
    infomodel=new MyModel;
    for(int i=0;i<arr.size();++i)
        infomodel->ptr.push_back(&arr[i]);
    infomodel->ptrsize=arr.size();
    listptr->setModel( infomodel );
    QVBoxLayout* mainLay = new QVBoxLayout;
    setLayout( mainLay );
    listptr->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    mainLay->addWidget(listptr);
}

TabForm::TabForm(QVector<GraphicsCard> &arr, QWidget *parent): QWidget(parent),
    ui(new Ui::TabForm)
{
    ui->setupUi(this);

    listptr=new QTableView;
    infomodel=new MyModel;
    for(int i=0;i<arr.size();++i)
        infomodel->ptr.push_back(&arr[i]);
    infomodel->ptrsize=arr.size();
    listptr->setModel( infomodel );
    QVBoxLayout* mainLay = new QVBoxLayout;
    setLayout( mainLay );
    listptr->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    mainLay->addWidget(listptr);
}

TabForm::TabForm(QVector<RAM> &arr, QWidget *parent)
{

}

TabForm::TabForm(QVector<Cooler> &arr, QWidget *parent)
{

}

TabForm::TabForm(QVector<HDD> &arr, QWidget *parent)
{

}

TabForm::TabForm(QVector<SSD> &arr, QWidget *parent)
{

}

TabForm::TabForm(QVector<Power> &arr, QWidget *parent)
{

}

TabForm::TabForm(QVector<Case> &arr, QWidget *parent)
{

}

TabForm::~TabForm()
{
    delete ui;
}
