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


    //combocreate->setEnabled(false);
    combotype=new QComboBox(this);
    combotype->addItem("Игровой ПК");
    combotype->addItem("ОФисный ПК");
    combotype->addItem("Среднебюджетный ПК");
    lbprice1=new QLabel("Минимум:");
    spinprice1=new QSpinBox(this);
    spinprice1->setMaximum(500000);
    lbprice2=new QLabel("Максимум:");
    spinprice2=new QSpinBox(this); //проверку только на цифры сделать
    spinprice2->setMaximum(500000);
    buttonstart=new QPushButton("Сгенерировать");
    connect(buttonstart,SIGNAL(clicked()),SLOT(generate()));
    buttonstart->setEnabled(false);
    settingsLayout->addWidget(buttonload);
    settingsLayout->addWidget(combotype);
    settingsLayout->addWidget(lbprice1,0,Qt::AlignRight);
    settingsLayout->addWidget(spinprice1);
    settingsLayout->addWidget(lbprice2,0,Qt::AlignRight);
    settingsLayout->addWidget(spinprice2);
    settingsLayout->addWidget(buttonstart);
    mainLayout->addLayout(settingsLayout);
    QHBoxLayout * barlayout=new QHBoxLayout;
    progbar=new QProgressBar(this);
    progbar->setMinimum(0);
    progbar->setMaximum(100);
    barlayout->addWidget(progbar);
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
    bInfo = new QPushButton("Информация");
    connect( bInfo, SIGNAL( clicked() ), SLOT( get_info() ) );
    //bInfo->setEnabled(false);
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
        arrlab.push_back(new QLabel(""));
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
    connect(infbn[0],SIGNAL(clicked()),this,SLOT(iConfProcessor()));
    connect(infbn[1],SIGNAL(clicked()),this,SLOT(iConfMotherBoard()));
    connect(infbn[2],SIGNAL(clicked()),this,SLOT(iConfGraphicCard()));
    connect(infbn[3],SIGNAL(clicked()),this,SLOT(iConfRAM()));
    connect(infbn[4],SIGNAL(clicked()),this,SLOT(iConfCooler()));
    //connect(infbn[5],SIGNAL(clicked()),this,SLOT(iConfHDD()));
    connect(infbn[6],SIGNAL(clicked()),this,SLOT(iConfSSD()));
    connect(infbn[7],SIGNAL(clicked()),this,SLOT(iConfPower()));
    connect(infbn[8],SIGNAL(clicked()),this,SLOT(iConfCase()));
    saveLay=new QHBoxLayout;
    pricelab=new QLabel("Общая цена:");
    priceline=new QLineEdit;
    priceline->setReadOnly(true); 
    QPushButton* savebn=new QPushButton("Сохранить сборку в txt");
    connect(savebn,SIGNAL(clicked()),this,SLOT(savetxt()));
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
    QMessageBox msg;
    msg.setText("Загрузка данных с e-katalog.ru занимает ≈ 25 минут\nЕсли по прошествии 8 минут прогресс не виден визуально,\n"
                "IP адрес заблокирован на время из-за множественных запросов.\n"
                "В таком случае используйте VPN.");
    msg.exec();
    //loader->ClearElArrays();
    for(int i=0;i<9;++i)// i<9!
    {
    loader->Parse1lvl(i,loader->Html,loader->vectorReg,loader->u2array,loader->pages[i]);
    }


   loader->RefPrepare(1);//для материнки
   loader->RefPrepare(4);//для кулера
   loader->RefPrepare(8);

 for(int k=0;k<9;++k) //=/!!!!!!!!!!!!!!!!
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
        progbar->setValue(10);
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
       progbar->setValue(20);
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
       progbar->setValue(40);
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
       progbar->setValue(50);
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
       progbar->setValue(60);
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
       progbar->setValue(70);
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
       progbar->setValue(80);
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
       progbar->setValue(90);
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
       progbar->setValue(100);
       break;
   }
  }
 }
 bSort->setEnabled(true);
 buttonstart->setEnabled(true);
 //bInfo->setEnabled(true);
 //сюда функцию для активации всех кнопок.
}
void ModelViewWidget::generate()
{

    loader->GenerateConfig(spinprice1->value(),spinprice2->value(),combotype->currentIndex());
    arrline[0]->setText(loader->config.processor.getName());
    arrline[1]->setText(loader->config.motherboard.getName());
    arrline[2]->setText(loader->config.graphicscard.getName());
    arrline[3]->setText(loader->config.ram.getName());
    arrline[4]->setText(loader->config.cooler.getName());
    arrline[5]->setText(loader->config.hdd.getName());
    arrline[6]->setText(loader->config.ssd.getName());
    arrline[7]->setText(loader->config.power.getName());
    arrline[8]->setText(loader->config.box.getName());
    priceline->setText(QString::number(loader->demand.Price));
}



void ModelViewWidget::tab_clicked(int index)
{
    qDebug()<<"tab_clicked";
    tabIndex=index;

}

void ModelViewWidget::get_info()
{
    TabForm * form=NULL;
    form=(TabForm*)tabw->widget(tabIndex);
        if(form->listptr->selectionModel()->hasSelection())
            {
            const QModelIndex index = form->listptr->selectionModel()->currentIndex();
            InfoForm *f=new InfoForm(form->infomodel->ptr[index.row()]->GetNames(),form->infomodel->ptr[index.row()]->GetValues());
            f->setAttribute(Qt::WA_DeleteOnClose, true);
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
void ModelViewWidget::savetxt()
{
    qDebug()<<"Попытка сохранить";
    QFile file("configFile.txt");
    QTextStream stream(&file);
   if(file.open(QIODevice::WriteOnly|QIODevice::Text))
   {
       stream<<QString::fromUtf8("Процессор\n")<<loader->config.processor.getName()<<"\n"<<loader->config.processor.getUrl().toString();
       stream<<QString::fromUtf8("\n\nМатеринская плата\n")<<loader->config.motherboard.getName()<<"\n"<<loader->config.motherboard.getUrl().toString();
       stream<<QString::fromUtf8("\n\nВидеокарта\n")<<loader->config.graphicscard.getName()<<"\n"<<loader->config.graphicscard.getUrl().toString();
       stream<<QString::fromUtf8("\n\nОперативная память\n")<<loader->config.ram.getName()<<"\n"<<loader->config.ram.getUrl().toString();
       stream<<QString::fromUtf8("\n\nКулер\n")<<loader->config.cooler.getName()<<"\n"<<loader->config.cooler.getUrl().toString();
       stream<<QString::fromUtf8("\n\nЖесткий диск\n")<<loader->config.hdd.getName()<<"\n"<<loader->config.hdd.getUrl().toString();
       stream<<QString::fromUtf8("\n\nТвердотельный накопитель\n")<<loader->config.ssd.getName()<<"\n"<<loader->config.ssd.getUrl().toString();
       stream<<QString::fromUtf8("\n\nБлок питания\n")<<loader->config.power.getName()<<"\n"<<loader->config.power.getUrl().toString();
       stream<<QString::fromUtf8("\n\nКорпус\n")<<loader->config.box.getName()<<"\n"<<loader->config.box.getUrl().toString();
       file.close();
   }
   else qWarning("Could not open file");
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

void ModelViewWidget::iConfProcessor()
{
    InfoForm * f=new InfoForm(loader->config.processor.GetNames(),loader->config.processor.GetValues());
    f->show();
}
void ModelViewWidget::iConfMotherBoard()
{
    InfoForm * f=new InfoForm(loader->config.motherboard.GetNames(),loader->config.motherboard.GetValues());
    f->show();
}
void ModelViewWidget::iConfGraphicCard()
{
    InfoForm * f=new InfoForm(loader->config.graphicscard.GetNames(),loader->config.graphicscard.GetValues());
    f->show();
}
void ModelViewWidget::iConfRAM()
{
    InfoForm * f=new InfoForm(loader->config.ram.GetNames(),loader->config.ram.GetValues());
    f->show();
}
void ModelViewWidget::iConfCooler()
{
    InfoForm * f=new InfoForm(loader->config.cooler.GetNames(),loader->config.cooler.GetValues());
    f->show();
}
void ModelViewWidget::iConfSSD()
{
    InfoForm * f=new InfoForm(loader->config.ssd.GetNames(),loader->config.ssd.GetValues());
    f->show();
}
void ModelViewWidget::iConfPower()
{
    InfoForm * f=new InfoForm(loader->config.power.GetNames(),loader->config.power.GetValues());
    f->show();
}
void ModelViewWidget::iConfCase()
{
    InfoForm * f=new InfoForm(loader->config.box.GetNames(),loader->config.box.GetValues());
    f->show();
}
