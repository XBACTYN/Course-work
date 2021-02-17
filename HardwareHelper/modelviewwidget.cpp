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
    connect(buttonstart,SIGNAL(clicked()),SLOT(generate()));
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
    connect(tabw,SIGNAL(tabBarClicked(int)),SLOT(tab_clicked(int)));
    horLay->addWidget((tabw));
    //mainLayout->addWidget(tabw);//в другой layoutf

    QVBoxLayout* panelLayout = new QVBoxLayout;
    bSort = new QPushButton("Сортировать");
    connect(bSort,SIGNAL(clicked()),SLOT(sort_all()));
    bSort->setEnabled(false);
    panelLayout->addWidget(bSort);
    bycheap=true;
    rbCheap=new QRadioButton;
    rbCheap->setText("Сначала дешевые");
    connect(rbCheap, SIGNAL(toggled(bool)), this, SLOT(radio1_toggled(bool)));
    panelLayout->addWidget(rbCheap);
    rbExpens=new QRadioButton;
    rbExpens->setText("Сначала дорогие");
    connect(rbExpens, SIGNAL(toggled(bool)), this, SLOT(radio2_toggled(bool)));
    panelLayout->addWidget(rbExpens);
    QPushButton* bAdd = new QPushButton("Добавить");

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
    saveLay=new QHBoxLayout;
    QLabel*pricelab=new QLabel("Общая цена:");
    QLineEdit* priceline=new QLineEdit;
    priceline->setReadOnly(true);
    priceline->setMaxLength(5);
    QPushButton* savebn=new QPushButton("Сохранить сборку в txt");
    saveLay->addWidget(pricelab);
    saveLay->addWidget(priceline);
    saveLay->addWidget(savebn,10,Qt::AlignRight);
    groupLay->addLayout(saveLay);
    saveLay->setContentsMargins(0,0,0,80);
    horLay->addLayout(groupLay);

    mainLayout->addLayout(horLay);

    resize( 1200, 800 );

}

ModelViewWidget::~ModelViewWidget()
{
    qDebug()<<"DESTRUCTOR MODELVIEW";
    delete tabw;
}




void ModelViewWidget::load_data()
{ buttonload->setEnabled(false);
    //loader->ClearElArrays();
    for(int i=0;i<3;++i)// i<9!
    {
    loader->Parse1lvl(i,loader->Html,loader->vectorReg,loader->u2array,loader->pages[i]);
    }


   loader->RefPrepare(1);//для материнки
   loader->RefPrepare(4);//для кулера
   loader->RefPrepare(8);

 for(int k=0;k<3;++k) //=/!!!!!!!!!!!!!!!!
 {
   switch (k)
  {
    case 0:
   {
        for(int p=0;p<loader->u2arrayI[k];++p)
            {
                loader->DownloadPage(loader->Html,loader->u2array[k][p]);
                loader->Regex2lvl(k,loader->Html,loader->vectorReg2,loader->tempdata);
                if(loader->tempdata[0]!="")
                loader->arrProcessors.push_back(Processor(loader->tempdata));
               }
        tabw->addTab(new TabForm(loader->arrProcessors),"CPU");
        break;
   }
   case 1:
   {
       for(int p=0;p<loader->u2arrayI[k];++p)
           {
               loader->DownloadPage(loader->Html,loader->u2array[k][p]);
               loader->Regex2lvl(k,loader->Html,loader->vectorReg2,loader->tempdata);
               if(loader->tempdata[0]!="")
                loader->arrMotherboards.push_back(MotherBoard(loader->tempdata));
              }
       tabw->addTab(new TabForm(loader->arrMotherboards),"Mother");
       break;
   }
   case 2:
   {
       for(int p=0;p<loader->u2arrayI[k];++p)
           {
               loader->DownloadPage(loader->Html,loader->u2array[k][p]);
               loader->Regex2lvl(k,loader->Html,loader->vectorReg2,loader->tempdata);
               if(loader->tempdata[0]!="")
                loader->arrGraphicsCards.push_back(GraphicsCard(loader->tempdata));
              }
       tabw->addTab(new TabForm(loader->arrGraphicsCards),"Graphics");
       break;
   }
   case 3:
   {
       for(int p=0;p<loader->u2arrayI[k];++p)
           {
               loader->DownloadPage(loader->Html,loader->u2array[k][p]);
               loader->Regex2lvl(k,loader->Html,loader->vectorReg2,loader->tempdata);
               if(loader->tempdata[0]!="")
                loader->arrRAMs.push_back(RAM(loader->tempdata));
              }
       tabw->addTab(new TabForm(loader->arrRAMs),"RAM");
       break;
   }
   case 4:
   {
       for(int p=0;p<loader->u2arrayI[k];++p)
           {
               loader->DownloadPage(loader->Html,loader->u2array[k][p]);
               loader->Regex2lvl(k,loader->Html,loader->vectorReg2,loader->tempdata);
               if(loader->tempdata[0]!="")
                loader->arrCoolers.push_back(Cooler(loader->tempdata));
              }
       tabw->addTab(new TabForm(loader->arrCoolers),"Cooler");
       break;
   }
   case 5:
   {
       for(int p=0;p<loader->u2arrayI[k];++p)
           {
               loader->DownloadPage(loader->Html,loader->u2array[k][p]);
               loader->Regex2lvl(k,loader->Html,loader->vectorReg2,loader->tempdata);
               if(loader->tempdata[0]!="")
                loader->arrHDDs.push_back(HDD(loader->tempdata));
              }
       tabw->addTab(new TabForm(loader->arrHDDs),"HDD");
       break;
   }
   case 6:
   {
       for(int p=0;p<loader->u2arrayI[k];++p)
           {
               loader->DownloadPage(loader->Html,loader->u2array[k][p]);
               loader->Regex2lvl(k,loader->Html,loader->vectorReg2,loader->tempdata);
               if(loader->tempdata[0]!="")
                loader->arrSSDs.push_back(SSD(loader->tempdata));
              }
       tabw->addTab(new TabForm(loader->arrSSDs),"SSD");
       break;
   }
   case 7:
   {
       for(int p=0;p<loader->u2arrayI[k];++p)
           {
               loader->DownloadPage(loader->Html,loader->u2array[k][p]);
               loader->Regex2lvl(k,loader->Html,loader->vectorReg2,loader->tempdata);
               if(loader->tempdata[0]!="")
                loader->arrPowers.push_back(Power(loader->tempdata));
              }
       tabw->addTab(new TabForm(loader->arrPowers),"Power");
       break;
   }
   case 8:
   {
       for(int p=0;p<loader->u2arrayI[k];++p)
           {
               loader->DownloadPage(loader->Html,loader->u2array[k][p]);
               loader->Regex2lvl(k,loader->Html,loader->vectorReg2,loader->tempdata);
               if(loader->tempdata[0]!="")
                loader->arrCases.push_back(Case(loader->tempdata));
              }
       tabw->addTab(new TabForm(loader->arrCases),"Case");
       break;
   }
  }
 }
 bSort->setEnabled(true);
 //сюда функцию для активации всех кнопок.
}
void ModelViewWidget::generate()
{
    for(int i=0;i<3;++i)
        arrline[i]->setText("");
    loader->GenerateConfig(0,spinprice->value());
    arrline[0]->setText(loader->config.processor.getName());
    arrline[1]->setText(loader->config.motherboard.getName());
    arrline[2]->setText(loader->config.graphicscard.getName());
    //ifbn[0]
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
{   qDebug()<<"in get_info()";
    TabForm * form=NULL;
    form=(TabForm*)tabw->widget(tabIndex);
        if(form->listptr->selectionModel()->hasSelection())
            {
            const QModelIndex index = form->listptr->selectionModel()->currentIndex();
            //qDebug()<<form->infomodel->ptr[index.row()]->GetNames();
            //qDebug()<<form->infomodel->ptr[index.row()]->GetValues();
            InfoForm *f=new InfoForm(form->infomodel->ptr[index.row()]->GetNames(),form->infomodel->ptr[index.row()]->GetValues());
            qDebug("dw");
            f->show();
        }
}

void ModelViewWidget::radio1_toggled(bool value)
{
    if (!value) return;
    bycheap=true;
}

void ModelViewWidget::radio2_toggled(bool value)
{
    if (!value) return;
    bycheap=false;
}


void ModelViewWidget::sort_all()
{
    if(bycheap)
    {
        qDebug()<<"sort from cheapest to expensive";
        loader->SortFromCheapest();
    }
    else
    {
        qDebug()<<"sort from expensiest to cheap";
        loader->SortFromMostExpensive();
    }
}



