#include "dataloader.h"
<<<<<<< Updated upstream
=======
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

    vectorReg.push_back(QRegExp("<a href='(/[\\w-]+\\.htm)'")); //полностью рабочая структура "data-url='(/[\\w-]+\\.htm)'" но перчатает по три раза
    manager = new QNetworkAccessManager(this);

};

>>>>>>> Stashed changes

DataLoader::DataLoader(){
    url=QUrl("https://www.dns-shop.ru/catalog/17a899cd16404e77/processory.html");
}

void DataLoader::ParsePage()
{
   /* QNetworkRequest request(url);
    manager = new QNetworkAccessManager(this);
    QNetworkReply* reply=  manager->get(request);
    connect( reply, SIGNAL(finished()), this, SLOT(replyFinished()) );
    if (reply->error() == QNetworkReply::NoError)

    {
      QFile file("1.html");

      if( file.open(QIODevice::WriteOnly) )

      {

        QByteArray content= reply->readAll();

        file.write(content); // пишем в файл

        file.close();
      }
    }*/

}


