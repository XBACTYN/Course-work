#include "modelviewwidget.h"

ModelViewWidget::ModelViewWidget( QWidget* parent ) : QWidget( parent ) //конструктор для виджета и окна
{
    loader=new DataLoader;

    tabIndex=0;
    QVBoxLayout* mainLayout = new QVBoxLayout;
    setLayout( mainLayout );

    QHBoxLayout * settingsLayout=new QHBoxLayout;
    buttonload=new QPushButton("Загрузка данных");
    connect(buttonload,SIGNAL(clicked()),SLOT (load_data()));

    combocreate=new QComboBox(this);
    combocreate->addItem("Авто режим");
    combocreate->addItem("Ручной режим");
    connect(combocreate, SIGNAL(activated(int)), SLOT(available_to_create(int)));

    //combocreate->setEnabled(false);
    combotype=new QComboBox(this);
    combotype->addItem("Игровой ПК");
    combotype->addItem("ОФисный ПК");
    combotype->addItem("Среднебюджетный ПК");
    lbprice=new QLabel("Сумма (max 500 000):");
    spinprice=new QSpinBox(this); //проверку только на цифры сделать
    spinprice->setMaximum(500000);
    buttonstart=new QPushButton("Сгенерировать");
    settingsLayout->addWidget(buttonload);
    settingsLayout->addWidget(combocreate);
    settingsLayout->addWidget(combotype);
    settingsLayout->addWidget(lbprice,0,Qt::AlignRight);
    settingsLayout->addWidget(spinprice);
    settingsLayout->addWidget(buttonstart);
    mainLayout->addLayout(settingsLayout);
    QHBoxLayout * barlayout=new QHBoxLayout;
    QProgressBar *progbar=new QProgressBar(this);
    QLabel * progress=new QLabel("0 %");
    barlayout->addWidget(progbar);
    barlayout->addWidget(progress);
    mainLayout->addLayout(barlayout);

    QHBoxLayout *horLay=new QHBoxLayout;

    tabw=new QTabWidget(this);
    tabw->addTab(new TabForm(),"CPU");
    tabw->addTab(new TabForm(),"MB");
    tabw->addTab(new TabForm(),"GCard");
    tabw->addTab(new TabForm(),"RAM");
    tabw->addTab(new TabForm(),"AcCooler");
    tabw->addTab(new TabForm(),"HDD");
    tabw->addTab(new TabForm(),"SSD");
    tabw->addTab(new TabForm(),"Power");
    tabw->addTab(new TabForm(),"Case");
    connect(tabw,SIGNAL(tabBarClicked(int)),SLOT(tab_clicked(int)));
    horLay->addWidget((tabw));
    //mainLayout->addWidget(tabw);//в другой layoutf

    QVBoxLayout* panelLayout = new QVBoxLayout;
    QPushButton* bSort = new QPushButton("Сортировать");
    //connect
    panelLayout->addWidget(bSort);
    QRadioButton *rbCheap=new QRadioButton;
    rbCheap->setText("Сначала дешевые");
    //connect
    panelLayout->addWidget(rbCheap);
    QRadioButton *rbExpens=new QRadioButton;
    rbExpens->setText("Сначала дорогие");
    //connect
    panelLayout->addWidget(rbExpens);
    QPushButton* bAdd = new QPushButton("Добавить");
   // connect( bAdd, SIGNAL( clicked() ), SLOT( on_clicked() ) );
    panelLayout->addWidget( bAdd );
    QPushButton* bInfo = new QPushButton("Информация");
    connect( bInfo, SIGNAL( clicked() ), SLOT( get_info() ) );
    panelLayout->addWidget( bInfo,0,Qt::AlignTop );
   /* QPushButton* bCompare = new QPushButton("Сравнить");
   //connect( bCompare, SIGNAL( clicked() ), SLOT( //on_clicked() ) );
    panelLayout->addWidget( bCompare,0,Qt::AlignTop );
    */
    horLay->addLayout(panelLayout);

    groupLay=new QVBoxLayout;
    //arrlab=new QLabel;
    QLabel* titleconfig=new QLabel("Моя конфигурация");
    titleconfig->setStyleSheet(QString("font-size: %1px").arg(32));
    groupLay->addWidget(titleconfig,0,Qt::AlignTop|Qt::AlignCenter);

    for(int i=0;i<9;++i)
    {
        //qDebug()<<i;
        arrlab.push_back(new QLabel("Пусто"));
        arrline.push_back(new QLineEdit);
        arrline[i]->setReadOnly(true);
        arrbn.push_back(new QPushButton);
        arrbn[i]->setText("Удалить");
        infbn.push_back(new QPushButton);
        infbn[i]->setMaximumWidth(20);
        infbn[i]->setText("i");
        arrlay.push_back(new QHBoxLayout);
        arrlay[i]->addWidget(arrlab[i]);
        arrlay[i]->addWidget(arrline[i]);
        arrlay[i]->addWidget(infbn[i]);
        arrlay[i]->addWidget(arrbn[i]);
        groupLay->addWidget(new QLabel(confNames[i]),0,Qt::AlignCenter);
        groupLay->addLayout(arrlay[i]);
    }
    QPushButton* save=new QPushButton("Сохранить в txt");
    groupLay->addWidget(save,10,Qt::AlignCenter|Qt::AlignTop);
    horLay->addLayout(groupLay);

    mainLayout->addLayout(horLay);


    resize( 1200, 800 );

}

ModelViewWidget::~ModelViewWidget()
{
    qDebug()<<"DESTRUCTOR MODELVIEW";
    delete tabw;
}

/*
void ModelViewWidget::selectionChangedSlot(const QItemSelection & , const QItemSelection & )
{
    const QModelIndex index = m_view->selectionModel()->currentIndex();
   // QString shit=m_model->box.vec[index.row()].second;
    //int number=m_model->box.vec[index.row()].b;
}
*/

void ModelViewWidget::load_data()
{
    for(int i=0;i<1;++i)// i<9!
    {
    loader->Parse1lvl(i,loader->Html,loader->vectorReg,loader->u2array,loader->pages[i]);
    }


   int k=0;
   loader->RefPrepare(1);//для материнки
   loader->RefPrepare(4);//для кулера
   loader->RefPrepare(8);
                //QUrl urltest("https://www.e-katalog.ru/ek-item.php?resolved_name_=AEROCOOL-BOLT&view_=tbl");
 //for(int k=0;k<9;++k)
 //{
  for(int p=0;p<loader->u2arrayI[k];++p) //switch(k) , конструкторы классов. 9 массивов в dataloader, ссылки Element * ptr= processor[2]
   {
   loader->DownloadPage(loader->Html,loader->u2array[k][p]);
   qDebug()<<loader->u2array[k][p];
                    //qDebug()<<loader.Html;
                 //loader.DownloadPage(loader.Html,urltest);
                 // qDebug()<<"\n\n"<<urltest;
   loader->Regex2lvl(k,loader->Html,loader->vectorReg2);
  }
 //}
}
void ModelViewWidget::on_clicked()
{

}

void ModelViewWidget::available_to_create(int idx)
{
    if(idx==1)
    {
        combotype->setEnabled(false);
        spinprice->setEnabled(false);
        buttonstart->setEnabled(false);
    }
    else
    {
        //удалить конфигурацию()
        combotype->setEnabled(true);
        spinprice->setEnabled(true);
        buttonstart->setEnabled(true);

    }

}

void ModelViewWidget::tab_clicked(int index)
{
    qDebug()<<"tab_clicked";
    tabIndex=index;

}

void ModelViewWidget::get_info()
{
    qDebug()<<tabIndex;
    TabForm * form=NULL;
    //QWidget * pWidget=tabw->widget(index);
    form=(TabForm*)tabw->widget(tabIndex);

        if(form->listptr->selectionModel()->hasSelection())
            {
            const QModelIndex index = form->listptr->selectionModel()->currentIndex();
            int field2=form->infomodel->box.vec[index.row()].price;
            int field3=form->infomodel->box.vec[index.row()].b;
            QMessageBox msg;
             msg.setText("Second field: "+QString::number(field2)+"\nThird field: "+QString::number(field3));
              msg.exec();
            }
}



