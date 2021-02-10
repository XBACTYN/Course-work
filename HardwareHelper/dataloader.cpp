#include "dataloader.h"
DataLoader::DataLoader()
{
    uarray[0]=QUrl("https://www.e-katalog.ru/list/186/"); //проц
    uarray[1]=QUrl("https://www.e-katalog.ru/list/187/"); //мать
    uarray[2]=QUrl("https://www.e-katalog.ru/list/189/"); //видео
    uarray[3]=QUrl("https://www.e-katalog.ru/list/188/pr-4480/"); //оператива
    uarray[4]=QUrl("https://www.e-katalog.ru/list/303/pr-7151/");//кулер на процессор,т.к. OEM
    uarray[5]=QUrl("https://www.e-katalog.ru/ek-list.php?katalog_=190&presets_=3573,24728,33111&page_="); //hdd////////////изменено. https://www.e-katalog.ru/ek-list.php?katalog_=190&presets_=3573,24728&page_=
    uarray[6]=QUrl("https://www.e-katalog.ru/ek-list.php?katalog_=61&presets_=3680,32956&page_=");  //ssd
    uarray[7]=QUrl("https://www.e-katalog.ru/list/351/"); //блок питания
    //нужна доп фильтрация для уменьшения выборки
    uarray[8]=QUrl("https://www.e-katalog.ru/ek-list.php?katalog_=193&presets_=5469,5470,5473&page_="); //корпус

    vectorReg.push_back(QRegExp("<a href='/([\\w-]{5,}-OEM\\.htm)'"));//проц                                        [0]
    vectorReg.push_back(QRegExp("<a href='/([\\w-]{5,}\\.htm)'"));//мать  ВРОДЕ ФИЛЬТРЫ НА МАТЬ СТАВИТЬ СМЫСЛА НЕТ  [1]
    vectorReg.push_back(QRegExp("<a href='/([\\w-]{5,}\\.htm)'"));//видео И НА ВИДЕОКАРТЫ ТОЖЕ НЕ НАДО ФИЛЬТРОВ     [2]
    vectorReg.push_back(QRegExp("<a href='/(PATRIOT[\\w-]{5,}\\.htm)'"));//опера только от фирмы патриот            [3]
    vectorReg.push_back(QRegExp("<a href='/([\\w-]{5,}\\.htm)'"));//кулер на проц БЕЗ ФИЛЬРАЦИИ                     [4]
    vectorReg.push_back(QRegExp("<a href='/(SEAGATE[\\w-]{5,}\\.htm)'"));//hdd только от seagate                    [5]
    vectorReg.push_back(QRegExp("<a href='/(KINGSTON[\\w-]{5,}\\.htm)'"));//ssd только от kingston                  [6]
    vectorReg.push_back(QRegExp("<a href='/(AEROCOOL[\\w-]{5,}\\.htm)'"));//БП только от AEROCOOL                   [7]
    vectorReg.push_back(QRegExp("<a href='/(AEROCOOL[\\w-]{5,}\\.htm)'"));//корпус только от AEROCOOL               [8]
    //
    SetRegexProcessor();
    SetRegexMotherBoard();
    SetRegexGraphicsCard();
    SetRegexRAM();
    SetRegexCooler();
    SetRegexHDD();
    SetRegexSSD();
    SetRegexPower();

    manager = new QNetworkAccessManager(this);
    for(int i=0;i<9;++i)
        u2arrayI[i]=0;
    for(int i=0;i<9;++i)
        pages[i]=3;
    pages[4]=2;
    pages[5]=2;
    pages[7]=2;
};
void DataLoader::SetRegexProcessor()
{
    vectorReg2.push_back(QRegExp("<meta name=.description. content=.Цена: от (\\d{3,6}) р. до (\\d{3,6}) р."
                                 ".*hreflang=.ru-RU. href=.(https://www.e-katalog.ru/.{5,50}.htm).><link rel=.alternate"
                                 ".*<div class=.op1-tt.>(.{5,50})  <span class='item-conf-name ib nobr'>"
                                 "(.+ OEM)</span><.div><div class='m-c-f1'>"
                                 ".*Socket.*class=.op3.><a href='.{20,40}'>(.{3,20})</a></td></tr>"
                                 ".*class=.op3.>(\\d{1,2}).nbsp.cores<.td>"
                                 ".*class=.op3.>(\\d{1,2}).nbsp.threads<.td>"
                                 ".*Тактовая <span class='nobr ib'>частота<.span><.span><.td><td width=.\\d\\d.. class=.op3.>(\\d.?\\d?).nbsp.ГГц"
                                 ".*(?:Частота TurboBoost / <span class='nobr ib'>TurboCore</span></span></td><td width=...%. class=.op3.>(\\d.?\\d?)&nbsp;ГГц)?"
                                 ".*Техпроцесс</span></span></td><td width=.\\d\\d.. class=.op3.>(\\d{1,2}).nbsp.нм</td>"
                                 ".*(?:Модель <span class='nobr ib'>IGP</span></span></td><td width=...%. class=.op3.>(.{5,25})</td></tr>)?"
                                 ".*class=.op3.>(\\d{1,4}).nbsp.Вт</td>"
                                 ".*(?:class=.op3.>(\\d{1,4}).nbsp.ГБ</td>)?"
                                 ".*(?:Макс. частота <span class='nobr ib'>DDR3</span></span></td><td width=...%. class=.op3.>(\\d{3,5})&nbsp;МГц</td>)?"
                                 ".*(?:Макс. частота <span class='nobr ib'>DDR4</span></span></td><td width=...%. class=.op3.>(\\d{3,5})&nbsp;МГц</td>)?"
                                 ".*Официальный сайт"
                             ));


    fields[0]=16;
    //https://www.e-katalog.ru/AMD-2600X-OEM.htm
}
void DataLoader::RefPrepare(int i)
{
    QRegExp cutter("https://www.e-katalog.ru/([\\w-]{5,})\\.htm");
    for(int j=0;j<u2arrayI[i];++j)
    {

        int lastPos = 0;
        while( ( lastPos = cutter.indexIn( u2array[i][j].toString(), lastPos ) ) != -1 )
        {
            lastPos += cutter.matchedLength();
            u2array[i][j]=QUrl("https://www.e-katalog.ru/ek-item.php?resolved_name_="+cutter.cap(1)+"&view_=tbl");
        }
        //qDebug()<<u2array[i][j];
    }

}

void DataLoader::SetRegexMotherBoard()
{
    vectorReg2.push_back(QRegExp("<meta name=.description. content=.Цена: от (\\d{3,6}) р. до (\\d{3,6}) р."
                                 ".*hreflang=.ru-RU. href=.(https://www.e-katalog.ru/.{5,100}=tbl).><link rel=.alternate. hreflang=.ru-UA."
                                 ".*<div class=.op1-tt.>(.{5,50})</div>"
                                 ".*Socket.*class=.op3.><a href='.{20,40}'>(.{3,20})</a></td></tr>"
                                 ".*Форм-фактор</span></span></td><td width=...%. class=.op3.><a href='.{20,40}'>(.{3,20})</a></td></tr>"
                                 ".*(?:DDR4</span></span></td><td width=...%. class=.op3.><a href='.{20,40}'>(\\d{1,2}).nbsp.слота.ов.)?"
                                 ".*Форм-фактор слота для <span class='nobr ib'>памяти</span></span></td><td width=.51%. class=.op3.>(.{3,7})</td></tr>"
                                 ".*class=.op3.>(\\d{3,5}).nbsp.МГц</td></tr>"
                                 ".*class=.op3.>(\\d{1,3}).nbsp.ГБ</td></tr>"
                                 ".*(VGA)?"
                                 ".*(DVI)?"
                                 ".*(HDMI)?"
                                 ".*(DisplayPort)?"
                                 ".*Аудиочип</span></span></td><td width=..... class=.op3.>(.{10,20})</td></tr>"
                                 ".*SATA3 .. <span class='nobr ib'>Гбит/с.</span></span></td><td width=...%. class=.op3.>(\\d)&nbsp;шт</td>"
                                 ".*(?:M.2 .+</span></span></td><td width=..... class=.op3.>(\\d{1,2}).nbsp.шт</td></tr>)?"
                                 ".*Поддержка PCI .+</span></span></td><td width=..... class=.op3.>(\\d\\.\\d)</td></tr>"
                                 ".*USB <span class='nobr ib'>2.0</span></span></td><td width=...%. class=.op3.>(\\d)&nbsp;шт</td>"
                                 ".*(?:USB 3.2 <span class='nobr ib'>gen1</span></span></td><td width=...%. class=.op3.>(\\d)&nbsp;шт</td></tr>)?"
                                 ".*(?:USB C 3...<span class='nobr ib'>gen2</span></span></td><td width=...%. class=.op3.>(\\d)&nbsp)?"
                                 ".*Официальный сайт"
                                ));


    fields[1]=20;
}

void DataLoader::SetRegexGraphicsCard()
{
    vectorReg2.push_back(QRegExp("<meta name=.description. content=.Цена: от (\\d{3,6}) р. до (\\d{3,6}) р."
                                 ".*hreflang=.ru-RU. href=.(https://www.e-katalog.ru/.{5,50}.htm).><link rel=.alternate"
                                 ".*<div class=.op1-tt.>(.{5,50})</div>"
                                 ".*class=.op3.>PCI-E v(\\d\\.\\d)</td>"
                                 ".*class=.op3.>(\\d{1,2}).nbsp.ГБ</td>"
                                 ".*class=.op3.>(GDDR\\d)</td>"
                                 ".*class=.op3.>(\\d{2,3}).nbsp.бит</td>"
                                 ".*памяти.*class=.op3.>(\\d{3,7}).nbsp.МГц</td>"
                                 ".*разрешение.*class=.op3.>(\\d{4,6}x\\d{4,6}).nbsp.пикс</td>"
                                 ".*(?:VGA.*class=.op3.>(\\d).nbsp.шт</td>)?"
                                 ".*(?:DVI-D.*class=.op3.>(\\d).nbsp.шт</td>)?"
                                 ".*(?:HDMI.*class=.op3.>(\\d).nbsp.шт</td>)?"
                                 ".*мониторов.*class=.op3.>(\\d)</td>"
                                 ".*class=.op3.>(\\d{2,3}).nbsp.Вт</td>"));
    fields[2]=15;
}

void DataLoader::SetRegexRAM()
{
    vectorReg2.push_back(QRegExp("<meta name=.description. content=.Цена: от (\\d{3,6}) р. до (\\d{3,6}) р."
                                 ".*hreflang=.ru-RU. href=.(https://www.e-katalog.ru/.{5,50}.htm).><link rel=.alternate"
                                 ".*<div class=.op1-tt.>(.{5,50})</div>"
                                 ".*комплекта</span></span></div></td><td class=.val.>(\\d{1,3})&nbsp;ГБ</td>"
                                 ".*комплекте</span></span></div></td><td class=.val.>(\\d)&nbsp;шт</td>"
                                 ".*Форм-фактор <span class='nobr ib'>памяти</span></span></div></td><td class=.val.>(.{4,})</td>"
                                 ".*Тип <span class='nobr ib'>памяти</span></span></div></td><td class=.val.>(.{4,})</td>"
                                 ".*Тактовая <span class='nobr ib'>частота</span></span></div></td><td class=.val.>(\\d{3,4})&nbsp;МГц</td>"

                             ));
   fields[3]=9;
}

void DataLoader::SetRegexCooler()
{
    vectorReg2.push_back(QRegExp("<meta name=.description. content=.Цена: от (\\d{3,6}) р. до (\\d{3,6}) р."
                                 ".*hreflang=.ru-RU. href=.(https://www.e-katalog.ru/.{5,100}=tbl).><link rel=.alternate. hreflang=.ru-UA."
                                 ".*<div class=.op1-tt.>(.{5,50})</div>"
                                 ".*Вентиляторов</span></span></td><td width=...%. class=.op3.>(\\d)&nbsp;шт</td>"
                                 ".*Socket</span></span></td><td width=...%. class=.op3.>(.*)<BR></td></tr></table>"
                                 ".*(?:Минимальные <span class=.nobr ib.>обороты</span></span></td><td width=...%. class=.op3.>(\\d{3,5})&nbsp;об/мин)?"
                                 ".*Максимальные <span class=.nobr ib.>обороты</span></span></td><td width=...%. class=.op3.>(\\d{3,5})&nbsp;об/мин"
                                 ".*(?:поток</span></span></td><td width=...%. class=.op3.>(\\d{2,4})&nbsp;CFM)?"
                                 ".*TDP</span></span></td><td width=...%. class=.op3.>(\\d{2,4})&nbsp;Вт"
                                 ".*(?:Уровень <span class=.nobr ib.>шума</span></span></td><td width=...%. class=.op3.>(\\d{1,3})&nbsp;дБ)?"
                                 ".*Дата добавления"

                             )); //при возникновении прблем обратить внимание на <BR>. возможно в некоторых местах <br>
    fields[4]=11;
}
void DataLoader::SetRegexHDD()
{
    vectorReg2.push_back(QRegExp("<meta name=.description. content=.Цена: от (\\d{3,6}) р. до (\\d{3,6}) р."
                                 ".*hreflang=.ru-RU. href=.(https://www.e-katalog.ru/.{5,50}.htm).><link rel=.alternate"
                                 ".*<div class=.op1-tt.>(.{5,50})(?:</div>|<span class)"
                                 ".*Объем</span></span>(?:</td><td width=...%. class=.op3.>|</div></td><td class=.val.>)?(\\d{3,5})&nbsp;ГБ"
                                 ".*подключения</span></span>(?:</td><td width=...%. class=.op3.>|</div></td><td class=.val.>)?(.{3,35})</td></tr>"
                                 ".*обмена</span></span>(?:</td><td width=...%. class=.op3.>|</div></td><td class=.val.>)?(\\d{1,3})&nbsp;МБ"
                                 ".*шпинделя</span></span>(?:</td><td width=...%. class=.op3.>|</div></td><td class=.val.>)?(\\d{3,5}) об/мин"
                                 ".*Потребляемая мощность при <span class=.nobr ib.>работе</span></span>(?:</td><td width=...%. class=.op3.>|</div></td><td class=.val.>)?(.{1,5})&nbsp;Вт"
                                 ".*(?:чтении</span></span>(?:</td><td width=...%. class=.op3.>|</div></td><td class=.val.>)?(\\d{1,3})&nbsp;дБ)?"
                                 ".*Дата добавления"

                                 ));
     fields[5]=10;
}

void DataLoader::SetRegexSSD()
{
    vectorReg2.push_back((QRegExp("<meta name=.description. content=.Цена: от (\\d{3,6}) р. до (\\d{3,6}) р."
                                  ".*hreflang=.ru-RU. href=.(https://www.e-katalog.ru/.{5,50}.htm).><link rel=.alternate"
                                  ".*<div class=.op1-tt.>(.{5,50})</div>"
                                  ".*Объем</span></span></div></td><td class=.val.>(\\d{2,4})&nbsp;ГБ"
                                  ".*Форм-фактор</span></span></div></td><td class=.val.>(.{1,12})(?:\")?</td>"
                                  ".*(?:Интерфейс <span class=.nobr ib.>M.2</span></span></div></td><td class=.val.>(.{3,15})</td>)?"
                                  ".*(?:Разъем</span></span></div></td><td class=.val.>(.{2,15})</td>)?"
                                  ".*(?:обмена</span></span></div></td><td class=.val.>(\\d{2,4})&nbsp;МБ)?"
                                  ".*записи</span></span></div></td><td class=.val.>(\\d{2,4})&nbsp;МБ/с"
                                  ".*считывания</span></span></div></td><td class=.val.>(\\d{2,4})&nbsp;МБ/с"
                                  ".*TBW</span></span></div></td><td class=.val.>(\\d{1,4})&nbsp;ТБ"
                                  ".*Дата добавления"

                              )));

    fields[6]=12;
}

void DataLoader::SetRegexPower()
{
    vectorReg2.push_back(QRegExp("<meta name=.description. content=.Цена: от (\\d{3,6}) р. до (\\d{3,6}) р."
                                 ".*hreflang=.ru-RU. href=.(https://www.e-katalog.ru/.{5,50}.htm).><link rel=.alternate"
                                 ".*<div class=.op1-tt.>(.{5,50})(?:</div>|<span class)"
                                 ".*Мощность</span></span></td><td width=...%. class=.op3.>(\\d{1,4})&nbsp;Вт"
                                 ".*Форм-фактор</span></span></td><td width=...%. class=.op3.>(.{3,4})</td>"
                                 ".*вентилятора</span></span></td><td width=...%. class=.op3.>(\\d{1,4})&nbsp;мм"
                                 ".*SATA</span></span></td><td width=...%. class=.op3.>(\\d{1,2})&nbsp;шт"
                                 ".*(?:MOLEX</span></span></td><td width=...%. class=.op3.>(\\d{1,2})&nbsp;шт)?"
                                 ".*(?:PCI-E.{1,10}<span class=.nobr ib.>.{1,10}</span></span></td><td width=...%. class=.op3.>(\\d{1,2})&nbsp;шт)?"
                                 ".*(?:шума</span></span></td><td width=...%. class=.op3.>(\\d{1,3})&nbsp;дБ)?"
                                 ".*Дата добавления"

                             ));
    fields[7]=11;
}
void DataLoader::DownloadPage(QString &Html,QUrl &url) //максимально 24 процессора на странице. потом /(n-1)/ к адресу страницы
{
    qDebug()<<"in DownloadPage()\n";
    QNetworkReply *response = manager->get(QNetworkRequest(url));
    QEventLoop event;
    connect(response,SIGNAL(finished()),&event,SLOT(quit()));
    event.exec();
    Html=response->readAll();

}

void DataLoader::Regex1lvl(int i,QString & Html,QVector<QRegExp>&vectorReg,QVector<QUrl> &tempVector)//максимально 24 процессора на странице. потом /(n-1)/ к адресу страницы
{
   // qDebug()<<"in Regex1lvl()\n";
   // qDebug()<<vectorReg[i];
       int lastPos = 0;
       while( ( lastPos = vectorReg[i].indexIn( Html, lastPos ) ) != -1 )
       {
           lastPos += vectorReg[i].matchedLength();
           qDebug() <<vectorReg[i].cap( 0 ) << ":" << vectorReg[i].cap( 1 )<<u2arrayI[i]<<"\n";
           tempVector.push_back(QUrl("https://www.e-katalog.ru/"+vectorReg[i].cap(1)));
           ++u2arrayI[i];
       }

}

void DataLoader::Parse1lvl(int i, QString &Html, QVector<QRegExp> &vectorReg, QVector<QVector<QUrl> > &u2array,int pages)
{
    //qDebug()<<"in Parse1lvl()\n";
    DownloadPage(Html,uarray[i]);
    QVector<QUrl> tempVector;
    Regex1lvl(i,Html,vectorReg,tempVector);
    if(pages>1)
        for(int j=1;j<=pages-1;++j)
        {
            QUrl nextPage=QUrl(uarray[i].toString()+QString::number(j)+"/");
            qDebug()<<nextPage;
             Html="";
            DownloadPage(Html,nextPage);
            Regex1lvl(i,Html,vectorReg,tempVector);
        }
    u2array.push_back(tempVector);

}

void DataLoader::Regex2lvl(int i,QString & Html,QVector<QRegExp> &vectorReg2)
{
    //настроить на прием количества полей для каждого элемента
    qDebug()<<"in Regex2lvl()\n";
   // qDebug()<<vectorReg2[i];
    int lastPos = 0;
    while( ( lastPos = vectorReg2[i].indexIn( Html, lastPos ) ) != -1 )
    {
        qDebug()<<"in while";
        lastPos += vectorReg2[i].matchedLength();

        for(int j=1;j<=fields[i];++j)
            qDebug()<<vectorReg2[i].cap(j);

    }
   // qDebug()<<"end regex2lvl";
}

