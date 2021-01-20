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

    vectorReg.push_back(QRegExp("<a href='/([\\w-]{5,}-OEM\\.htm)'"));//проц //полностью рабочая структура "<a href='(/[\\w-]{5,}\\.htm)'"
    vectorReg.push_back(QRegExp("<a href='/([\\w-]{5,}\\.htm)'"));//мать  ВРОДЕ ФИЛЬТРЫ НА МАТЬ СТАВИТЬ СМЫСЛА НЕТ
    vectorReg.push_back(QRegExp("<a href='/([\\w-]{5,}\\.htm)'"));//видео И НА ВИДЕОКАРТЫ ТОЖЕ НЕ НАДО ФИЛЬТРОВ
    vectorReg.push_back(QRegExp("<a href='/(PATRIOT[\\w-]{5,}\\.htm)'"));//опера только от фирмы патриот
    vectorReg.push_back(QRegExp("<a href='/([\\w-]{5,}\\.htm)'"));//кулер на проц БЕЗ ФИЛЬРАЦИИ
    vectorReg.push_back(QRegExp("<a href='/(SEAGATE[\\w-]{5,}\\.htm)'"));//hdd только от seagate
    vectorReg.push_back(QRegExp("<a href='/(KINGSTON[\\w-]{5,}\\.htm)'"));//ssd только от kingston
    vectorReg.push_back(QRegExp("<a href='/(AEROCOOL[\\w-]{5,}\\.htm)'"));//БП только от AEROCOOL
    vectorReg.push_back(QRegExp("<a href='/(AEROCOOL[\\w-]{5,}\\.htm)'"));//корпус
    //после этого настроить поиск по всем страницам.
    //сформировать структуру в которую занести все ссылки типа /amd. или /intel ..... и проч. скорее всего опять вектор который будет vectorProc
    //
    //int vectorRegc=0;
    manager = new QNetworkAccessManager(this);
    for(int i=0;i<9;++i)
        u2arrayI[i]=0;
};



 void DataLoader::DownloadPage(QString &Html,QUrl &url) //максимально 24 процессора на странице. потом /(n-1)/ к адресу страницы
{
    QNetworkReply *response = manager->get(QNetworkRequest(url));
    QEventLoop event;
    connect(response,SIGNAL(finished()),&event,SLOT(quit()));
    event.exec();
    Html=response->readAll();
   /* if (Html.contains("/AMD-3600-OEM.htm"))
        qDebug()<<"YES1";
        else qDebug()<<"NO1";
    */

}

void DataLoader::Regex1lvl(int i,QString & Html,QVector<QRegExp>&vectorReg,QVector<QUrl> &tempVector)//максимально 24 процессора на странице. потом /(n-1)/ к адресу страницы
{
    qDebug()<<"in regex1lvl\n";
    qDebug()<<vectorReg[i];
       int lastPos = 0;
       while( ( lastPos = vectorReg[i].indexIn( Html, lastPos ) ) != -1 )
       {
           lastPos += vectorReg[i].matchedLength();
           qDebug() <<vectorReg[i].cap( 0 ) << ":" << vectorReg[i].cap( 1 )<<u2arrayI[i]<<"\n";
           tempVector.push_back(QUrl("https://www.e-katalog.ru/"+vectorReg[i].cap(1)));
           ++u2arrayI[i];
       }

}

void DataLoader::Parse1lvl(int i, QString &Html, QVector<QRegExp> &vectorReg, QVector<QVector<QUrl> > &u2array,int pages)
{
    qDebug()<<"in Parse1lvl\n";
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

