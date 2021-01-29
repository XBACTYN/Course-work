#include "dataloader.h"
DataLoader::DataLoader()
{
    uarray[0]=QUrl("https://www.e-katalog.ru/list/186/"); //проц
    uarray[1]=QUrl("https://www.e-katalog.ru/list/187/"); //мать
    uarray[2]=QUrl("https://www.e-katalog.ru/list/189/"); //видео
    uarray[3]=QUrl("https://www.e-katalog.ru/list/188/"); //оператива
    uarray[4]=QUrl("https://www.e-katalog.ru/list/303/pr-7151/");//кулер на процессор,т.к. OEM
    uarray[5]=QUrl("https://www.e-katalog.ru/ek-list.php?katalog_=190&presets_=3573,24728&page_="); //hdd////////////изменено.
    //нужна доп фильтрация для уменьшения выборки
    //https://www.e-katalog.ru/ek-list.php?katalog_=190&presets_=3573,24728&page_=5/ для 6 страницы
    uarray[6]=QUrl("https://www.e-katalog.ru/ek-list.php?katalog_=61&presets_=3680,32956&page_=");  //ssd
    uarray[7]=QUrl("https://www.e-katalog.ru/list/351/"); //блок питания
    //нужна доп фильтрация для уменьшения выборки
    uarray[8]=QUrl("https://www.e-katalog.ru/ek-list.php?katalog_=193&presets_=5469,5470,5473&page_="); //корпус

    vectorReg.push_back(QRegExp("<a href='/([\\w-]{5,}-OEM\\.htm)'"));//проц                                        [0]
    vectorReg.push_back(QRegExp("<a href='/([\\w-]{5,}\\.htm)'"));//мать  ВРОДЕ ФИЛЬТРЫ НА МАТЬ СТАВИТЬ СМЫСЛА НЕТ  [1]
    vectorReg.push_back(QRegExp("<a href='/([\\w-]{5,}\\.htm)'"));//видео И НА ВИДЕОКАРТЫ ТОЖЕ НЕ НАДО ФИЛЬТРОВ     [2]
    vectorReg.push_back(QRegExp("<a href='/(PATRIOT[\\w-]{5,}\\.htm)'"));//опера только от фирмы патриот            [3]
    vectorReg.push_back(QRegExp("<a href='/([\\w-]{5,}\\.htm)'"));//кулер на проц БЕЗ ФИЛЬРАЦИИ                     [4]
    vectorReg.push_back(QRegExp("<a href='/(SEAGATE[\\w-]{5,}\\.htm)'"));//hdd только от seagate                    [5]
    vectorReg.push_back(QRegExp("<a href='/(KINGSTON[\\w-]{5,}\\.htm)'"));//ssd только от kingston                  [6]
    vectorReg.push_back(QRegExp("<a href='/(AEROCOOL[\\w-]{5,}\\.htm)'"));//БП только от AEROCOOL                   [7]
    vectorReg.push_back(QRegExp("<a href='/(AEROCOOL[\\w-]{5,}\\.htm)'"));//корпус только от AEROCOOL               [8]
    //
    SetRegexProcessor();
    SetRegexMotherBoard();
    SetRegexGraphicsCard();
    /*
        "class=.op3.>(\\d{1,2}).nbsp.cores<.td>.*class=.op3.>(\\d{1,2}).nbsp.threads<.td>" - для извлечения количества потоков \\d
    */
    manager = new QNetworkAccessManager(this);
    for(int i=0;i<9;++i)
        u2arrayI[i]=0;
    for(int i=0;i<9;++i)
        pages[i]=3;
    pages[4]=2;
    pages[5]=1;
    pages[7]=2;
};
void DataLoader::SetRegexProcessor()
{
    vectorReg2.push_back(QRegExp("<div class=.op1-tt.>(.+)  <span class='item-conf-name ib nobr'>"
                                 "(.+ OEM)</span><.div><div class='m-c-f1'>"
                                 ".*class=.op3.><a href='.+'>(.+)</a></td>"
                                 ".*class=.op3.>(\\d{1,2}).nbsp.cores<.td>"
                                 ".*class=.op3.>(\\d{1,2}).nbsp.threads<.td>"
                                 ".*Тактовая <span class='nobr ib'>частота<.span><.span><.td><td width=.\\d\\d.. class=.op3.>(\\d.\\d).nbsp.ГГц"
                                 ".*Техпроцесс</span></span></td><td width=.\\d\\d.. class=.op3.>(\\d{1,2}).nbsp.нм</td>"
                                 ".*class=.op3.>(\\d{1,4}).nbsp.КБ</td>"
                                 ".*class=.op3.>(\\d{1,4}).nbsp.КБ</td>"
                                 ".*class=.op3.>(\\d{1,4}).nbsp.МБ</td>"
                                 ".*class=.op3.>(\\d{1,4}).nbsp.Вт</td>"
                                 ".*class=.op3.>(\\d{1,4}).nbsp.ГБ</td>"
                                 ".*class=.op3.>(\\d{1,4}).nbsp.МГц</td>"
                                 ".*class=.op3.>(\\d).nbsp.шт</td>"));
    fields[0]=14;
    //https://www.e-katalog.ru/AMD-2600X-OEM.htm
}
void DataLoader::RefMotherboardsPrepare()
{
    QRegExp cutter("https://www.e-katalog.ru/([\\w-]{5,})\\.htm");
    for(int j=0;j<u2arrayI[1];++j)
    {

        int lastPos = 0;
        while( ( lastPos = cutter.indexIn( u2array[1][j].toString(), lastPos ) ) != -1 )
        {
            lastPos += cutter.matchedLength();
            u2array[1][j]=QUrl("https://www.e-katalog.ru/ek-item.php?resolved_name_="+cutter.cap(1)+"&view_=tbl");
        }
        //qDebug()<<u2array[1][j];
    }

}
void DataLoader::SetRegexMotherBoard()
{
    vectorReg2.push_back(QRegExp("<div class=.op1-tt.>(.{5,40})</div>"
                                 ".*class=.op3.><a href='.{20,40}'>(.{3,15})</a></td></tr>"
                                 ".*class=.op3.><a href='.{20,40}'>(.{3,15})</a></td></tr>"
                                 ".*class=.op3.><a href='.{20,40}'>(\\d{1,2}).nbsp.слот"
                                 ".*class=.op3.>(.{3,7})</td></tr>"
                                 ".*class=.op3.>(\\d{3,5}).nbsp.МГц</td></tr>"
                                 ".*class=.op3.>(\\d{1,2}).nbsp.ГБ</td></tr>"
                                 ".*Аудиочип</span></span></td><td width=..... class=.op3.>(.{10,20})</td></tr>"
                                 ".*SATA3 .+</span></span></td><td width=..... class=.op3.>(\\d{1,2}).nbsp.шт</td></tr>"
                                 ".*M.2 .+</span></span></td><td width=..... class=.op3.>(\\d{1,2}).nbsp.шт</td></tr>"
                                 ".*Поддержка PCI .+</span></span></td><td width=..... class=.op3.>(\\d\\.\\d)</td></tr>"
                                 ".*USB.+2\\..+</span></span></td><td width=..... class=.op3.>(\\d{1,2}).nbsp.шт</td></tr>"
                                 ".*USB.+3\\..+</span></span></td><td width=..... class=.op3.>(\\d{1,2}).nbsp.шт</td></tr>"
                                 ".*Основной разъем .+</span></span></td><td width=..... class=.op3.>(\\d{1,2})-контактный</td></tr>"
                                 ".*процессора.+</td><td width=..... class=.op3.>(\\d{1,2})-контакт"));


    fields[1]=15;
}

void DataLoader::SetRegexGraphicsCard()
{
    vectorReg2.push_back(QRegExp("<div class=.op1-tt.>(.{5,40})</div>"
                                 ".*class=.op3.>PCI-E v(\\d\\.\\d)</td>"
                                 ".*class=.op3.>(\\d{1,2}).nbsp.ГБ</td>"
                                 ".*class=.op3.>(GDDR\\d)</td>"
                                 ".*class=.op3.>(\\d{2,3}).nbsp.бит</td>"
                                 ".*памяти.*class=.op3.>(\\d{3,6}).nbsp.МГц</td>"
                                 ".*разрешение.*class=.op3.>(\\d{4,6}x\\d{4,6}).nbsp.пикс</td>"
                                 ".*(?:DVI-D.*class=.op3.>(\\d).nbsp.шт</td>)?"
                                 ".*(?:HDMI.*class=.op3.>(\\d).nbsp.шт</td>)?"
                                 ".*мониторов.*class=.op3.>(\\d)</td>"
                                 ".*class=.op3.>(\\d{2,3}).nbsp.Вт</td>"));
    fields[2]=11;
}
 void DataLoader::DownloadPage(QString &Html,QUrl &url) //максимально 24 процессора на странице. потом /(n-1)/ к адресу страницы
{
    qDebug()<<"in DownloadPage()\n";
    QNetworkReply *response = manager->get(QNetworkRequest(url));
    QEventLoop event;
    connect(response,SIGNAL(finished()),&event,SLOT(quit()));
    event.exec();
    Html=response->readAll();

}

void DataLoader::Regex1lvl(int i,QString & Html,QVector<QRegExp>&vectorReg,QVector<QUrl> &tempVector)//максимально 24 процессора на странице. потом /(n-1)/ к адресу страницы
{
    qDebug()<<"in Regex1lvl()\n";
   // qDebug()<<vectorReg[i];
       int lastPos = 0;
       while( ( lastPos = vectorReg[i].indexIn( Html, lastPos ) ) != -1 )
       {
           lastPos += vectorReg[i].matchedLength();
          // qDebug() <<vectorReg[i].cap( 0 ) << ":" << vectorReg[i].cap( 1 )<<u2arrayI[i]<<"\n";
           tempVector.push_back(QUrl("https://www.e-katalog.ru/"+vectorReg[i].cap(1)));
           ++u2arrayI[i];
       }

}

void DataLoader::Parse1lvl(int i, QString &Html, QVector<QRegExp> &vectorReg, QVector<QVector<QUrl> > &u2array,int pages)
{
    qDebug()<<"in Parse1lvl()\n";
    DownloadPage(Html,uarray[i]);
    QVector<QUrl> tempVector;
    Regex1lvl(i,Html,vectorReg,tempVector);
    if(pages>1)
        for(int j=1;j<=pages-1;++j)
        {
            QUrl nextPage=QUrl(uarray[i].toString()+QString::number(j)+"/");
            qDebug()<<nextPage;
             Html="";
            DownloadPage(Html,nextPage);
            Regex1lvl(i,Html,vectorReg,tempVector);
        }
    u2array.push_back(tempVector);

}

void DataLoader::Regex2lvl(int i,QString & Html,QVector<QRegExp> &vectorReg2)
{
    //настроить на прием количества полей для каждого элемента
    qDebug()<<"in Regex2lvl()\n";
    qDebug()<<vectorReg2[i];
    int lastPos = 0;
    while( ( lastPos = vectorReg2[i].indexIn( Html, lastPos ) ) != -1 )
    {
        qDebug()<<"in while";
        lastPos += vectorReg2[i].matchedLength();

        for(int j=1;j<=fields[i];++j)
            qDebug()<<vectorReg2[i].cap(j);

    }
    qDebug()<<"end regex2lvl";
}

