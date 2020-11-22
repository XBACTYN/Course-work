#include "form.h"
#include "ui_form.h"
Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    ui->lineEdit1->setText("http://findhard.ru/motherboards?send=1&orderdir=desc&orderby=ShopCount");
     QUrl url("http://findhard.ru/motherboards?send=1&orderdir=desc&orderby=ShopCount");
       // Создаем объект менеджера
       manager = new QNetworkAccessManager(this);
       //QNetworkAccessManager manager;
           QNetworkReply *response = manager->get(QNetworkRequest(url));
           QEventLoop event;
           connect(response,SIGNAL(finished()),&event,SLOT(quit()));
           event.exec();
           QString html = response->readAll();
           //qDebug()<<html;
           if (html.contains("/motherboards/model?id=1527&amp;m=asus-j1800i-c"))
               qDebug()<<"YES";
           else qDebug()<<"NO";
}

void Form::on_pushButton_clicked()

{

   // берем адрес введенный в текстовое поле

   QUrl url(ui->lineEdit1->text());

   // создаем объект для запроса

   QNetworkRequest request(url);



   // Выполняем запрос, получаем указатель на объект

   // ответственный за ответ

   QNetworkReply* reply=  manager->get(request);



   // Подписываемся на сигнал о готовности загрузки

   connect( reply, SIGNAL(finished()),

            this, SLOT(replyFinished()) );

}

void Form::replyFinished()

{

  QNetworkReply *reply=

    qobject_cast<QNetworkReply *>(sender());



  if (reply->error() == QNetworkReply::NoError)

  {

    // Получаем содержимое ответа

    QByteArray content= reply->readAll();



    // Реализуем преобразование кодировки

    // (зависит от кодировки сайта)

    QTextCodec *codec = QTextCodec::codecForName("utf8");



    // Выводим результат

    ui->textEdit->setPlainText(codec->toUnicode(content.data()) );

  }

  else

  {

    // Выводим описание ошибки, если она возникает.

    ui->textEdit->setPlainText(reply->errorString());

  }



  // разрешаем объекту-ответа "удалится"

  reply->deleteLater();

}

Form::~Form()
{
    delete ui;
}
