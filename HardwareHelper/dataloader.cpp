#include "dataloader.h"

DataLoader::DataLoader(QObject *parent) : QObject(parent)
{
    // Инициализируем менеджер ...
    manager = new QNetworkAccessManager();
    // ... и подключаем сигнал о завершении получения данных к обработчику полученного ответа
    connect(manager, &QNetworkAccessManager::finished, this, &DataLoader::onResult);
}

void DataLoader::getData()
{
    QUrl url("http://www.mtbank.by/currxml.php"); // URL, к которому будем получать данные
    QNetworkRequest request;    // Отправляемый запрос
    request.setUrl(url);        // Устанавлвиваем URL в запрос
    QNetworkReply* reply=manager->get(request);      // Выполняем запрос
    if (reply->error() == QNetworkReply::NoError)

    {
      QFile file("1.html");
      if( file.open(QIODevice::WriteOnly))
      {
        QByteArray content= reply->readAll();
        file.write(content); // пишем в файл
      }
    }
    reply->deleteLater();
}

void DataLoader::onResult(QNetworkReply *reply)
{
    // Если в процесе получения данных произошла ошибка
    if(reply->error()){
        // Сообщаем об этом и показываем информацию об ошибках
        qDebug() << "ERROR";
        qDebug() << reply->errorString();
    } else {
        // В противном случае создаём объект для работы с файлом
        QFile *file = new QFile("C:/example/file.xml");
        // Создаём файл или открываем его на перезапись ...
        if(file->open(QFile::WriteOnly)){
            file->write(reply->readAll());  // ... и записываем всю информацию со страницы в файл
            file->close();                  // закрываем файл
        qDebug() << "Downloading is completed";
        emit onReady(); // Посылаем сигнал о завершении получения файла


       // file->remove(); ///////////////////////////////////////////////////////////////////////
        }
    }
}
