#include "processor.h"



QUrl Processor::getUrl() const
{
    return url;
}

void Processor::setUrl(const QUrl &value)
{
    url = value;
}

QString Processor::getSocket() const
{
    return socket;
}

void Processor::setSocket(const QString &value)
{
    socket = value;
}

int Processor::getCores() const
{
    return cores;
}

void Processor::setCores(int value)
{
    cores = value;
}

int Processor::getThreads() const
{
    return threads;
}

void Processor::setThreads(int value)
{
    threads = value;
}

double Processor::getFreq() const
{
    return freq;
}

void Processor::setFreq(double value)
{
    freq = value;
}

double Processor::getTurbo() const
{
    return turbo;
}

void Processor::setTurbo(double value)
{
    turbo = value;
}

int Processor::getTechprocess() const
{
    return techprocess;
}

void Processor::setTechprocess(int value)
{
    techprocess = value;
}

QString Processor::getIGraphic() const
{
    return iGraphic;
}

void Processor::setIGraphic(const QString &value)
{
    iGraphic = value;
}

int Processor::getTDP() const
{
    return TDP;
}

void Processor::setTDP(int value)
{
    TDP = value;
}

int Processor::getMaxMem() const
{
    return maxMem;
}

void Processor::setMaxMem(int value)
{
    maxMem = value;
}

double Processor::getMaxMemFreqDDR3() const
{
    return maxMemFreqDDR3;
}

void Processor::setMaxMemFreqDDR3(double value)
{
    maxMemFreqDDR3 = value;
}

double Processor::getMaxMemFreqDDR4() const
{
    return maxMemFreqDDR4;
}

void Processor::setMaxMemFreqDDR4(double value)
{
    maxMemFreqDDR4 = value;
}

int Processor::getPrice() const
{
    return price;
}

void Processor::setPrice(int value)
{
    price = value;
}

QString Processor::getName() const
{
    return name;
}

void Processor::setName(const QString &value)
{
    name = value;
}

Processor::Processor(){

}

Processor::Processor(QVector<QString>& data)
{
    setPrice((data[0].toInt()+data[1].toInt())/2);
    setUrl(QUrl(data[2]));
    setName(data[3]+data[4]);
    setSocket(data[5]);
    setCores(data[6].toInt());
    setThreads(data[7].toInt());
    setFreq(data[8].toDouble());
    setTurbo(data[9].toDouble());
    setTechprocess(data[10].toInt());
    setIGraphic(data[11]);
    setTDP(data[12].toInt());
    setMaxMem(data[13].toInt());
    setMaxMemFreqDDR3(data[14].toInt());
    setMaxMemFreqDDR4(data[15].toInt());
    arrsize=data.size();
}

QVector<QString>Processor::GetValues()
{
    QVector<QString> temp;
    temp.push_back(QString::number(getPrice()));
    temp.push_back((url.toString()));
    temp.push_back(getName());
    temp.push_back(getSocket());
    temp.push_back(QString::number(getCores()));
    temp.push_back(QString::number(getThreads()));
    temp.push_back(QString::number(getFreq()));
    temp.push_back(QString::number(getTurbo()));
    temp.push_back(QString::number(getTechprocess()));
    temp.push_back(getIGraphic());
    temp.push_back(QString::number(getTDP()));
    temp.push_back(QString::number(getMaxMem()));
    temp.push_back(QString::number(getMaxMemFreqDDR3()));
    temp.push_back(QString::number(getMaxMemFreqDDR4()));
    return temp;
}

QVector<QString>Processor::GetNames()
{
    QVector<QString> temp;
    temp.push_back("Цена, руб");
    temp.push_back("URL-ссылка на товар");
    temp.push_back("Название");
    temp.push_back("Сокет(Разъем)");
    temp.push_back("Количество ядер");
    temp.push_back("Количество потоков");
    temp.push_back("Тактовая частота, ГГц");
    temp.push_back("Частота TurboBoost, ГГц");
    temp.push_back("Техпроцесс, нм");
    temp.push_back("Интегрированное графическое ядро");
    temp.push_back("Тепловыделение, Вт");
    temp.push_back("Макс.объем RAM, Гб");
    temp.push_back("Макс.частота RAM DDR3, МГц");
    temp.push_back("Макс.частота RAM DDR4, МГц");
    return temp;
}

void Processor::ClearFields()
{
    setCores(0);
    setFreq(0);
    setIGraphic("");
    setMaxMem(0);
    setMaxMemFreqDDR3(0);
    setMaxMemFreqDDR4(0);
    setName("");
    setPrice(0);
    setSocket("");
    setTDP(0);
    setTechprocess(0);
    setThreads(0);
    setTurbo(0);
    setUrl(QUrl(""));
}
