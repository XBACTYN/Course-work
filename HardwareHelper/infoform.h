#ifndef INFOFORM_H
#define INFOFORM_H

#include <QWidget>
#include <QLayout>
#include <QTableWidget>
#include <QHeaderView>
#include <QDebug>
namespace Ui {
class InfoForm;
}

class InfoForm : public QWidget
{
    Q_OBJECT

public:
    QHBoxLayout *mainlay;
    QVBoxLayout *nameslay;
    QVBoxLayout *valueslay;
    QTableWidget *table;
    InfoForm(QVector<QString> names,QVector<QString>values,QWidget *parent = nullptr);
    explicit InfoForm(QWidget *parent = nullptr);
    ~InfoForm();

private:
    Ui::InfoForm *ui;
};

#endif // INFOFORM_H
