#include "form.h"
#include "ui_form.h"
Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    //Ниже парсинг страницы в str
    //
    QUrl uarray[]={QUrl("https://www.e-katalog.ru/list/186/"),QUrl("https://www.e-katalog.ru/list/187/"),
                   QUrl("https://www.e-katalog.ru/list/189/"),QUrl("https://www.e-katalog.ru/list/188/"),
                   QUrl("https://www.e-katalog.ru/list/190/"),QUrl("https://www.e-katalog.ru/list/61/"),
                   QUrl("https://www.e-katalog.ru/list/351/"),QUrl("https://www.https://www.e-katalog.ru/list/303/pr-7151/"),
                   QUrl("https://www.e-katalog.ru/list/193/")};
     ui->lineEdit1->setText(uarray[0].toString());
    //186-процессоры. 187-материнки 189-видеокарты 188-оперативка 190-HDD 61-SSD 351-БП 303/pr-7151 это кулер на процессор 193 это корпус
     //QUrl url("https://www.e-katalog.ru/list/186/");
       // Создаем объект менеджера
       manager = new QNetworkAccessManager(this);
       //QNetworkAccessManager manager;
           QNetworkReply *response = manager->get(QNetworkRequest(uarray[0]));
           QEventLoop event;
           connect(response,SIGNAL(finished()),&event,SLOT(quit()));
           event.exec();
           QString html = response->readAll();
           //qDebug()<<html;
           if (html.contains("/AMD-3600-OEM.htm"))
               qDebug()<<"YES";
           else qDebug()<<"NO";
     //Выше парсинг страницы в str
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
   connect( reply, SIGNAL(finished()), this, SLOT(replyFinished()) );
}

void Form::replyFinished()

{

  QNetworkReply *reply=qobject_cast<QNetworkReply *>(sender());

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
