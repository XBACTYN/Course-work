#ifndef MOTHERBOARD_H
#define MOTHERBOARD_H
#include <QString>
#include <QUrl>
class MotherBoard
{
public:
    int position;
    int lowPrice;
    int HighPrice;
    QUrl url;
    QString name;
    QString socket;
    QString form;
    int DDR4count;
    QString formDDR;
    int maxFreq;
    int maxMem;
    QString VGA;
    QString DVI;
    QString HDMI;
    QString DispayPort;
    QString audio;
    int SATA3;
    int M2;
    double PCIE;
    int USB2;
    int USB3;
    int USBC;


    MotherBoard();
};

#endif // MOTHERBOARD_H
