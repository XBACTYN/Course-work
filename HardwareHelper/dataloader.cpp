#include "dataloader.h"
DataLoader::DataLoader()
{
    uarray[0]=QUrl("https://www.e-katalog.ru/list/186/"); //проц
    uarray[1]=QUrl("https://www.e-katalog.ru/list/187/"); //мать
    uarray[2]=QUrl("https://www.e-katalog.ru/list/189/"); //видео
    uarray[3]=QUrl("https://www.e-katalog.ru/list/188/"); //оператива
    uarray[4]=QUrl("https://www.e-katalog.ru/list/190/"); //hdd
    uarray[5]=QUrl("https://www.e-katalog.ru/list/61/");  //ssd
    uarray[6]=QUrl("https://www.e-katalog.ru/list/351/"); //блок питания
    //uarray[7]=QUrl("https://www.https://www.e-katalog.ru/list/303/pr-7151/"); //кулер на процессор
    uarray[7]=QUrl("https://www.e-katalog.ru/list/193/"); //корпус

    vectorReg.push_back(QRegExp("<a href='/([\\w-]{5,}-BOX\\.htm)'")); //полностью рабочая структура "<a href='(/[\\w-]{5,}\\.htm)'"

    //оптимизировать,чтобы не брал OEM, только BOX. Или что-то одно из двух. так спиоск в два раза меньше станет.
    //после этого настроить поиск по всем страницам.
    //сформировать структуру в которую занести все ссылки типа /amd. или /intel ..... и проч. скорее всего опять вектор который будет vectorProc
    //
    //int vectorRegc=0;
    manager = new QNetworkAccessManager(this);
    for(int i=0;i<8;++i)
        u2arrayI[0]=0;
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

void DataLoader::Regex1lvl(int i,QString & Html,QVector<QRegExp>&vectorReg,QVector<QVector<QUrl>>& u2array)//максимально 24 процессора на странице. потом /(n-1)/ к адресу страницы
{
   //ЕСТЬ МЫСЛЬ СДЕЛАТЬ ФУНКЦИЮ ОБОЛОЧКУ ДЛЯ ПРОСМОТРА ПЕРВЫХ ТРЕХ СТРАНИЦ ВМЕСТО ДУБЛИРОВАНИЯ СО СТРОКИ 55. А то выборка получается мала.
    QVector<QUrl> tempVector;
       int lastPos = 0;
       while( ( lastPos = vectorReg[i].indexIn( Html, lastPos ) ) != -1 )
       {
           lastPos += vectorReg[i].matchedLength();
           qDebug() <<vectorReg[i].cap( 0 ) << ":" << vectorReg[i].cap( 1 )<<u2arrayI[i]<<"\n";
           tempVector.push_back(QUrl("https://www.e-katalog.ru/"+vectorReg[i].cap(1)));
           ++u2arrayI[i];;
       }

       QUrl secondPage=QUrl(uarray[i].toString()+"1/");
       Html="";
       DownloadPage(Html,secondPage);
       lastPos=0;
       while( ( lastPos = vectorReg[i].indexIn( Html, lastPos ) ) != -1 )
       {
           lastPos += vectorReg[i].matchedLength();
           qDebug() <<vectorReg[i].cap( 0 ) << ":" << vectorReg[i].cap( 1 )<<u2arrayI[i]<<"\n";
           tempVector.push_back(QUrl("https://www.e-katalog.ru/"+vectorReg[i].cap(1)));
           ++u2arrayI[i];;
       }
        qDebug()<<"\n";
    u2array.push_back(tempVector);

}


