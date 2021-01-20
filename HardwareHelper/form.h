#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QtNetwork/QNetworkAccessManager>

#include <QtNetwork/QNetworkRequest>

#include <QtNetwork/QNetworkReply>

#include <QUrl>

#include <QTextCodec>


namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT
private slots: //для интерактивных элементов

    void on_pushButton_clicked();

    void replyFinished(); // cлот, выполняемый при завершении запроса


public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();


private://создание формы
    Ui::Form *ui;

   QNetworkAccessManager* manager;// !! относится к парсеру
};

#endif // FORM_H
