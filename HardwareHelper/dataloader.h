#ifndef DATALOADER_H
#define DATALOADER_H

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QUrl>
#include <QTextCodec>
#include <QFile>
#include <QEventLoop>
#include <QString>
#include <QVector>
#include <QRegExp>

class DataLoader : public QObject
{
    QString url;
    QNetworkAccessManager* manager;
    QUrl uarray[9];//массив с адресами первого уровня на разные компоненты

public:
    QVector<QString> vectorHtml;//массив со страницами первого уровня в формате строк.
    QVector<QRegExp> vectorReg; //двухмерный массив регулярок
    DataLoader();
    void DownloadPage(int i,QVector<QString>&vectorHtml);//test
    void ParseProcessors();
    void Regex1lvl(int i,QVector<QString>&vectorHtml,QVector<QRegExp>&vectorReg);
};


#endif // DOWNLOADER_H
