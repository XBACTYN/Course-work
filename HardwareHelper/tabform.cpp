#include "tabform.h"
#include "ui_tabform.h"

TabForm::TabForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TabForm)
{
    ui->setupUi(this);

    listptr=new QTableView;
    infomodel=new MyModel;
    infomodel->box.Randomize();
    listptr->setModel( infomodel );
    QVBoxLayout* mainLay = new QVBoxLayout;
    setLayout( mainLay );
    listptr->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    mainLay->addWidget(listptr);
}

TabForm::~TabForm()
{
    delete ui;
}
