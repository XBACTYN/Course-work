#pragma once
#ifndef MODELVIEWWIDGET_H
#define MODELVIEWWIDGET_H
#include <QWidget>
#include <QLineEdit>
#include <QListView>
#include <QTableView>
#include <QHeaderView>
#include <QLayout>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QMessageBox>
#include <QSpinBox>
#include <QSpacerItem>
#include <QDebug>
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include <QProgressBar>
#include <QTabWidget>
#include <QRadioButton>
#include <QLineEdit>
#include <QVector>
#include <QFile>
#include <QTextStream>
#include "tabform.h"
#include "mymodel.h"
#include "dataloader.h"
#include "infoform.h"
class ModelViewWidget : public QWidget
{
    Q_OBJECT

private:
    QTabWidget * tabw;
    int tabIndex;

    QPushButton * buttonload;
    QComboBox * combotype;
    QLabel * lbprice1;
    QLabel * lbprice2;
    QSpinBox * spinprice1;
    QSpinBox * spinprice2;
    QPushButton * buttonstart;

    QVBoxLayout * groupLay;
    QHBoxLayout * saveLay;
    QVector<QString> confNames{"Процессор","Материнская плата","Видеокарта",
                           "Оперативная память","Кулер на процессор","Жесткий диск",
                           "Твердотельный накопитель","Блок питания","Корпус"};
    QVector<QLabel*>      arrlab;   //QVector<QLabel*>      arrlab;
    QVector<QLineEdit*>   arrline;
    QVector<QHBoxLayout*> arrlay;
    QVector<QPushButton*> infbn;
    QVector<QPushButton*> arrbn;
    QPushButton* bAdd;
    QPushButton* savebn;
    QProgressBar *progbar;
    QPushButton* bInfo;
    QPushButton* bSort;
    QRadioButton *rbCheap;
    QRadioButton *rbExpens;
    QLabel*pricelab;
    QLineEdit* priceline;
    DataLoader* loader;
    bool bycheap;
private slots:
    void load_data();
    void tab_clicked(int);
    void get_info();
    void radio1_toggled(bool);
    void radio2_toggled(bool);
    void sort_all();
    void generate();
    void iConfProcessor();
    void iConfMotherBoard();
    void iConfGraphicCard();
    void iConfRAM();
    void iConfCooler();
    void iConfHDD();
    void iConfSSD();
    void iConfPower();
    void iConfCase();
    void savetxt();
    void add();
    void dConfProcessor();
    void dConfMotherBoard();
    void dConfGraphicCard();
    void dConfRAM();
    void dConfCooler();
    void dConfHDD();
    void dConfSSD();
    void dConfPower();
    void dConfCase();
    void AddElement(QVector<QString>&data,int type);
public:
    ModelViewWidget( QWidget* parent = 0 );
    ~ModelViewWidget();


};

#endif // MODELVIEWWIDGET_H
