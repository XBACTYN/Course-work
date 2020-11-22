#include "dataloader.h"

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


