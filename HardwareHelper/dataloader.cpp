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
    uarray[7]=QUrl("https://www.https://www.e-katalog.ru/list/303/pr-7151/"); //кулер на процессор
    uarray[8]=QUrl("https://www.e-katalog.ru/list/193/"); //корпус

    vectorReg.push_back(QRegExp("data-url='(/..............)"));
    manager = new QNetworkAccessManager(this);

};



 void DataLoader::DownloadPage(int i,QVector<QString>&vectorHtml) //максимально 24 процессора на странице. потом /(n-1)/ к адресу страницы
{
   //добавить в параметры ссылку на массив с регулярными выражениями.
    QNetworkReply *response = manager->get(QNetworkRequest(uarray[i]));
    QEventLoop event;
    connect(response,SIGNAL(finished()),&event,SLOT(quit()));
    event.exec();
    vectorHtml.push_back(QString(response->readAll()));////////////////////
    if (vectorHtml[0].contains("/AMD-3600-OEM.htm"))
        qDebug()<<"YES1";
    else qDebug()<<"NO1";
    //<пусто>теперь Функция с регулярными выражениями принимающая vector[i] по ссылке.

}

void DataLoader::Regex1lvl(int i,QVector<QString>&vectorHtml,QVector<QRegExp>&vectorReg)//максимально 24 процессора на странице. потом /(n-1)/ к адресу страницы
{ //по задумке там должны высветиться все ссылки для 24х процессоров с нулевой страницы. пока я их не сохраняю
  // qDebug()<<"Regular expression:"<<vectorReg[i]<<"\n";//<<vectorHtml[i]<<"\n\n\n";


       int lastPos = 0;
       while( ( lastPos = vectorReg[i].indexIn( vectorHtml[i], lastPos ) ) != -1 )
       {
           qDebug()<<"in while"<<endl;
           lastPos += vectorReg[i].matchedLength();
           qDebug() <<vectorReg[i].cap( 0 ) << ":" << vectorReg[i].cap( 1 );
       }
 qDebug()<<"end"<<endl;



}

