#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFile>

#include <dataloader.h>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void readFile();

private:
    Ui::Widget *ui;
    DataLoader *downloader; // Объявляем объект класса для скачивания данных по http
};

#endif // WIDGET_H
