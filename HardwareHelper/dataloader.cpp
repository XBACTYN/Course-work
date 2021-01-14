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

    manager = new QNetworkAccessManager(this);

};

void DataLoader::ParseProcessors()
{



}

 void DataLoader::ParsePage()
{
  for(int i=0;i<9;++i)
  {
    QNetworkReply *response = manager->get(QNetworkRequest(uarray[i]));
    QEventLoop event;
    connect(response,SIGNAL(finished()),&event,SLOT(quit()));
    event.exec();
    vector[i] = response->readAll();
    //<пусто>теперь Функция с регулярными выражениями принимающая html по ссылке.

  }

}


