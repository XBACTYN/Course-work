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
    SetRegexCase();

    manager = new QNetworkAccessManager(this);
    for(int i=0;i<9;++i)
        u2arrayI[i]=0;
    for(int i=0;i<9;++i)
        pages[i]=3;

    pages[0]=2;
    pages[1]=1;
    pages[3]=2;
    pages[4]=1;
    pages[5]=1;
    pages[7]=1;
    ClearConfig();
    demand.Price=0;
    demand.DDRtype="";
    demand.FreqDDR3=0;
    demand.FreqDDR4=0;
    demand.M2=0;
    demand.MaxFreqRAM=0;
    demand.MinPower=0;
    demand.MotherForm="";
    demand.PowerForm="";
    demand.Socket="";
    demand.TDP=0;
    srand(time(0));

};
void DataLoader::SetRegexProcessor()
{
    vectorReg2.push_back(QRegExp("<meta name=.description. content=.Цена: от (\\d{3,6}) р. до (\\d{3,6}) р."
                                 ".*hreflang=.ru-RU. href=.(https://www.e-katalog.ru/.{5,50}.htm).><link rel=.alternate"
                                 ".*<div class=.op1-tt.>(.{5,50})<span class=.item-conf-name ib nobr.>"
                                 "(.+ OEM)</span><.div><div class='m-c-f1'>"
                                 ".*Socket.*class=.op3.><a href='.{20,40}'>(.{3,20})</a></td></tr>"
                                 ".*class=.op3.>(\\d{1,3}).nbsp.cores<.td>"
                                 ".*class=.op3.>(\\d{1,3}).nbsp.threads<.td>"
                                 ".*Тактовая <span class='nobr ib'>частота<.span><.span><.td><td width=.\\d\\d.. class=.op3.>(\\d.?\\d?\\d?\\d?).nbsp.ГГц"
                                 ".*(?:Частота TurboBoost / <span class='nobr ib'>TurboCore</span></span></td><td width=...%. class=.op3.>(\\d.?\\d?\\d?\\d?)&nbsp;ГГц)?"
                                 ".*Техпроцесс</span></span></td><td width=.\\d\\d.. class=.op3.>(\\d{1,2}).nbsp.нм</td>"
                                 ".*(?:Модель <span class='nobr ib'>IGP</span></span></td><td width=...%. class=.op3.>(.{5,25})</td></tr>)?"
                                 ".*class=.op3.>(\\d{1,4}).nbsp.Вт</td>"
                                 ".*(?:class=.op3.>(\\d{1,4}).nbsp.ГБ</td>)?"
                                 ".*(?:Макс. частота <span class='nobr ib'>DDR3</span></span></td><td width=...%. class=.op3.>(\\d{3,5})&nbsp;МГц</td>)?"
                                 ".*(?:Макс. частота <span class='nobr ib'>DDR4</span></span></td><td width=...%. class=.op3.>(\\d{3,5})&nbsp;МГц</td>)?"
                                 ".*Дата добавления"
                             ));
    fields[0]=16;
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
    }

}

void DataLoader::SetRegexMotherBoard()
{
    vectorReg2.push_back(QRegExp("<meta name=.description. content=.Цена: от (\\d{3,6}) р. до (\\d{3,6}) р."
                                 ".*hreflang=.ru-RU. href=.(https://www.e-katalog.ru/.{5,100}=tbl).><link rel=.alternate. hreflang=.ru-UA."
                                 ".*<div class=.op1-tt.>(.{5,50})</div>"
                                 ".*Socket.*class=.op3.><a href='.{20,40}'>(.{3,20})</a></td></tr>"
                                 ".*Форм-фактор</span></span></td><td width=...%. class=.op3.><a href='.{20,40}'>(.{3,20})</a></td></tr>"
                                 ".*(?:DDR3</span></span></td><td width=...%. class=.op3.><a href='.{20,40}'>(\\d{1,2}).nbsp.слота.ов.)?"
                                 ".*(?:DDR4</span></span></td><td width=...%. class=.op3.><a href='.{20,40}'>(\\d{1,2}).nbsp.слота.ов.)?"
                                 ".*Форм-фактор слота для <span class='nobr ib'>памяти</span></span></td><td width=.51%. class=.op3.>(.{3,7})</td></tr>"
                                 ".*class=.op3.>(\\d{3,5}).nbsp.МГц</td></tr>"
                                 ".*class=.op3.>(\\d{1,3}).nbsp.ГБ</td></tr>"
                                 ".*(VGA)?"
                                 ".*(DVI)?"
                                 ".*(HDMI)?"
                                 ".*(DisplayPort)?"
                                 ".*Аудиочип</span></span></td><td width=..... class=.op3.>(.{5,20}).?<(?:/td></tr>|span class)"
                                 ".*SATA3 .{1,7}<span class='nobr ib'>Гбит/с.</span></span></td><td width=...%. class=.op3.>(\\d)&nbsp;шт</td>"
                                 ".*(?:M.2 <span class=.nobr ib.>разъем</span></span></td><td width=..... class=.op3.>(\\d{1,2}).nbsp.шт</td></tr>)?"
                                 ".*(?:Поддержка PCI .+</span></span></td><td width=..... class=.op3.>(\\d\\.\\d)</td></tr>)?"
                                 ".*USB <span class='nobr ib'>2.0</span></span></td><td width=...%. class=.op3.>(\\d)&nbsp;шт</td>"
                                 ".*(?:USB 3.2 <span class='nobr ib'>gen.</span></span></td><td width=...%. class=.op3.>(\\d)&nbsp;шт</td></tr>)?"
                                 ".*(?:USB C 3...<span class='nobr ib'>gen.</span></span></td><td width=...%. class=.op3.>(\\d)&nbsp)?"
                                 ".*Дата добавления"
                                ));
    fields[1]=22;
}

void DataLoader::SetRegexGraphicsCard()
{
    vectorReg2.push_back(QRegExp("<meta name=.description. content=.Цена: от (\\d{3,6}) р. до (\\d{3,6}) р."
                                 ".*hreflang=.ru-RU. href=.(https://www.e-katalog.ru/.{5,50}.htm).><link rel=.alternate"
                                 ".*<div class=.op1-tt.>(.{5,50})</div>"
                                 ".*class=.op3.>PCI-E v(\\d\\.\\d)</td>"
                                 ".*class=.op3.>(\\d{1,2}).nbsp.ГБ</td>"
                                 ".*class=.op3.>(GDDR\\d.?)</td>"
                                 ".*class=.op3.>(\\d{2,3}).nbsp.бит</td>"
                                 ".*GPU</span></span></td><td width=...%. class=.op3.>(\\d{2,4}).nbsp.МГц</td>"
                                 ".*памяти.*class=.op3.>(\\d{3,7}).nbsp.МГц</td>"
                                 ".*разрешение.*class=.op3.>(\\d{4,6}x\\d{4,6}).nbsp.пикс</td>"
                                 ".*(?:VGA.*class=.op3.>(\\d).nbsp.шт</td>)?"
                                 ".*(?:DVI-D.*class=.op3.>(\\d).nbsp.шт</td>)?"
                                 ".*(?:HDMI</span></span></td><td width=...%. class=.op3.>(\\d).nbsp.шт</td>)?"
                                 ".*(?:DisplayPort</span></span></td><td width=...%. class=.op3.>(\\d).nbsp.шт</td>)?"
                                 ".*мониторов.*class=.op3.>(\\d)</td>"
                                 ".*(?:от</span></span></td><td width=...%. class=.op3.>(\\d{2,3}).nbsp.Вт</td>)?"
                                 ".*Дата добавления"));
    fields[2]=17;
}

void DataLoader::SetRegexRAM()
{
    vectorReg2.push_back(QRegExp("<meta name=.description. content=.Цена: от (\\d{3,6}) р. до (\\d{3,6}) р."
                                 ".*hreflang=.ru-RU. href=.(https://www.e-katalog.ru/.{5,50}.htm).><link rel=.alternate"
                                 ".*<div class=.op1-tt.>(.{5,50})</div>"
                                 ".*комплекта</span></span></div></td><td class=.val.>(\\d{1,3})&nbsp;ГБ</td>"
                                 ".*комплекте</span></span></div></td><td class=.val.>(\\d)&nbsp;шт</td>"
                                 ".*Форм-фактор <span class='nobr ib'>памяти</span></span></div></td><td class=.val.>(.{4,})</td>"
                                 ".*Тип <span class='nobr ib'>памяти</span></span></div></td><td class=.val.>(.{4,6})</td>"
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
                                 ".*Socket</span></span></td><td width=...%. class=.op3.>(.*)(?:<BR>|<br>)</td></tr>"
                                ".*(?:Минимальные <span class=.nobr ib.>обороты</span></span></td><td width=...%. class=.op3.>(\\d{3,5})&nbsp;об/мин)?"
                                 ".*Максимальные <span class=.nobr ib.>обороты</span></span></td><td width=...%. class=.op3.>(\\d{3,5})&nbsp;об/мин"
                                 ".*(?:поток</span></span></td><td width=...%. class=.op3.>(\\d{2,4}.?\\d?\\d?)&nbsp;CFM)?"
                                 ".*(?:TDP</span></span></td><td width=...%. class=.op3.>(\\d{2,4})&nbsp;Вт)?"
                                 ".*(?:Уровень <span class=.nobr ib.>шума</span></span></td><td width=...%. class=.op3.>(\\d{1,3})&nbsp;дБ)?"
                                 ".*Дата добавления"

                             )); // обратить внимание на <BR>. возможно в некоторых местах <br>
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
                                 ".*(?:Потребляемая мощность при <span class=.nobr ib.>работе</span></span>(?:</td><td width=...%. class=.op3.>|</div></td><td class=.val.>)?(.{1,5})&nbsp;Вт)?"
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

void DataLoader::SetRegexCase() //нету поля длины видеокарты. остается на совести.
{
     vectorReg2.push_back(QRegExp("<meta name=.description. content=.Цена: от (\\d{3,6}) р. до (\\d{3,6}) р."
                                  ".*hreflang=.ru-RU. href=.(https://www.e-katalog.ru/.{5,100}=tbl).><link rel=.alternate. hreflang=.ru-UA."
                                  ".*<div class=.op1-tt.>(.{5,50})(?:</div>|<span class)"
                                  ".*Форм-фактор</span></span></td><td width=...%. class=.op3.>(.{3,12})</td>"
                                 ".*платы</span></span></td><td width=...%. class=.op3.><a href='.{20,40}'>(.{2,12})</a>(?:</td>|<span class)?"
                                 ".*БП</span></span></td><td width=...%. class=.op3.><a href='.{20,40}'>(.{2,20})</a></td>"
                                  ".*Внутренних отсеков <span class=.nobr ib.>3.5.</span></span></td><td width=...%. class=.op3.>(\\d{1,2})&nbsp;шт"
                                  ".*Внутренних отсеков <span class=.nobr ib.>2.5.</span></span></td><td width=...%. class=.op3.>(\\d{1,2})&nbsp;шт"
                                  ".*(?:вентиляторов</span></span></td><td width=...%. class=.op3.>(\\d)</td>)?"
                                  ".*(?:USB <span class=.nobr ib.>2..</span></span></td><td width=...%. class=.op3.>(\\d{1,2})&nbsp;шт)?"
                                  ".*(?:USB 3.. <span class=.nobr ib.>gen.</span></span></td><td width=...%. class=.op3.>(\\d{1,2})&nbsp;шт)?"
                                  ".*Дата добавления"
                                  ));
     fields[8]=12;
}
void DataLoader::DownloadPage(QString &Html,QUrl &url)
{
    qDebug()<<"in DownloadPage()";
    QNetworkReply *response = manager->get(QNetworkRequest(url));
    QEventLoop event;
    connect(response,SIGNAL(finished()),&event,SLOT(quit()));
    event.exec();
    Html=response->readAll();

}

void DataLoader::Regex1lvl(int i,QString & Html,QVector<QRegExp>&vectorReg,QVector<QUrl> &tempVector)
{
       int lastPos = 0;
       while( ( lastPos = vectorReg[i].indexIn( Html, lastPos ) ) != -1 )
       {
           lastPos += vectorReg[i].matchedLength();
           qDebug()<< vectorReg[i].cap( 1 )<<u2arrayI[i];
           tempVector.push_back(QUrl("https://www.e-katalog.ru/"+vectorReg[i].cap(1)));
           ++u2arrayI[i];
       }

}

void DataLoader::Parse1lvl(int i, QString &Html, QVector<QRegExp> &vectorReg, QVector<QVector<QUrl> > &u2array,int pages)
{
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

void DataLoader::Regex2lvl(int i,QString & Html,QVector<QRegExp> &vectorReg2,QVector<QString>&data)
{
    if(data.size()!=0)
   {
   data.clear();
   }
   data.squeeze();
    qDebug()<<"in Regex2lvl()\n\n";
    int lastPos = 0;
    while( ( lastPos = vectorReg2[i].indexIn( Html, lastPos ) ) != -1 )
    {
        lastPos += vectorReg2[i].matchedLength();

     for(int j=1;j<=fields[i];++j)
     {
           data.push_back(vectorReg2[i].cap(j));
     }
    }


   if(data.size()==0)
   {
       data.squeeze();
       for(int k=1;k<=fields[i];++k)
           data.push_back("");
   }
}



void DataLoader::SortFromCheapest()
{
    std::sort(arrProcessors.begin(),arrProcessors.end(),[] (const auto& lhs, const auto& rhs){return lhs.price < rhs.price;});
    std::sort(arrMotherboards.begin(),arrMotherboards.end(),[] (const auto& lhs, const auto& rhs){return lhs.price < rhs.price;});
    std::sort(arrGraphicsCards.begin(),arrGraphicsCards.end(),[] (const auto& lhs, const auto& rhs){return lhs.price < rhs.price;});
    std::sort(arrRAMs.begin(),arrRAMs.end(),[] (const auto& lhs, const auto& rhs){return lhs.price < rhs.price;});
    std::sort(arrCoolers.begin(),arrCoolers.end(),[] (const auto& lhs, const auto& rhs){return lhs.price < rhs.price;});
    std::sort(arrHDDs.begin(),arrHDDs.end(),[] (const auto& lhs, const auto& rhs){return lhs.price < rhs.price;});
    std::sort(arrSSDs.begin(),arrSSDs.end(),[] (const auto& lhs, const auto& rhs){return lhs.price < rhs.price;});
    std::sort(arrPowers.begin(),arrPowers.end(),[] (const auto& lhs, const auto& rhs){return lhs.price < rhs.price;});
    std::sort(arrCases.begin(),arrCases.end(),[] (const auto& lhs, const auto& rhs){return lhs.price < rhs.price;});
}

void DataLoader::SortFromMostExpensive()
{
    std::sort(arrProcessors.begin(),arrProcessors.end(),[] (const auto& lhs, const auto& rhs){return lhs.price > rhs.price;});
    std::sort(arrMotherboards.begin(),arrMotherboards.end(),[] (const auto& lhs, const auto& rhs){return lhs.price > rhs.price;});
    std::sort(arrGraphicsCards.begin(),arrGraphicsCards.end(),[] (const auto& lhs, const auto& rhs){return lhs.price > rhs.price;});
    std::sort(arrRAMs.begin(),arrRAMs.end(),[] (const auto& lhs, const auto& rhs){return lhs.price > rhs.price;});
    std::sort(arrCoolers.begin(),arrCoolers.end(),[] (const auto& lhs, const auto& rhs){return lhs.price > rhs.price;});
    std::sort(arrHDDs.begin(),arrHDDs.end(),[] (const auto& lhs, const auto& rhs){return lhs.price > rhs.price;});
    std::sort(arrSSDs.begin(),arrSSDs.end(),[] (const auto& lhs, const auto& rhs){return lhs.price > rhs.price;});
    std::sort(arrPowers.begin(),arrPowers.end(),[] (const auto& lhs, const auto& rhs){return lhs.price > rhs.price;});
    std::sort(arrCases.begin(),arrCases.end(),[] (const auto& lhs, const auto& rhs){return lhs.price > rhs.price;});
}

void DataLoader::ClearConfig()
{
    qDebug()<<"clearConfig()";
    config.processor.ClearFields();
    config.motherboard.ClearFields();
    config.graphicscard.ClearFields();
    config.ram.ClearFields();
    config.cooler.ClearFields();
    config.ssd.ClearFields();
    config.hdd.ClearFields();
    config.power.ClearFields();
    config.box.ClearFields();
}
template<class T>
int DataLoader::BinaryIndex(QVector<T>&arr,int size,const int value)
{
    qDebug()<<"BinaryIndex()";
    int left=0;
    int right=size-1;
    int middle;
    while(true)
    {
        middle=(left+right)/2;
        if(value>arr[middle].price)
        {
            left=middle+1;
        }
        else if(value<arr[middle].price)
        {
            right=middle-1;
        }
        else return middle;
        if(left>right)
        {
            return left;
        }
    }
}
bool DataLoader::ChooseGraphicCard(int index,int sum, int &surplus)
{
   qDebug()<<"ChooseGraphicCard()";
   bool compatible=false;
   config.graphicscard=arrGraphicsCards[index];
   demand.MinPower=config.graphicscard.getPower();
   demand.Price+=config.graphicscard.getPrice();
   surplus+=sum-config.graphicscard.getPrice();
   compatible=true;
   return compatible;
}
bool DataLoader::ChooseProcessor(int index,int sum, int &surplus,int type)
{
    qDebug()<<"ChooseProcessor()";
    bool compatible=false;
    if(arrProcessors[index].getSocket()==demand.Socket)
        {
            if(type==1)
            {
                if(arrProcessors[index].getIGraphic()!="отсутствует")
                {
                    if((demand.DDRtype=="DDR3"&&arrProcessors[index].getMaxMemFreqDDR3()!=0))
                        demand.FreqDDR3=arrProcessors[index].getMaxMemFreqDDR3();
                    if((demand.DDRtype=="DDR4"&&arrProcessors[index].getMaxMemFreqDDR4()!=0))
                           demand.FreqDDR4=arrProcessors[index].getMaxMemFreqDDR4();
                    config.processor=arrProcessors[index];
                    demand.TDP=config.processor.getTDP();
                    demand.Price+=config.processor.getPrice();
                    surplus+=sum-config.processor.getPrice();
                    compatible=true;
                }
             }
            else
            {   if(arrProcessors[index].getCores()>=6)
                {
                    if((demand.DDRtype=="DDR3"&&arrProcessors[index].getMaxMemFreqDDR3()!=0))
                        demand.FreqDDR3=arrProcessors[index].getMaxMemFreqDDR3();
                    if((demand.DDRtype=="DDR4"&&arrProcessors[index].getMaxMemFreqDDR4()!=0))
                        demand.FreqDDR4=arrProcessors[index].getMaxMemFreqDDR4();
                    config.processor=arrProcessors[index];
                    demand.TDP=config.processor.getTDP();
                    demand.Price+=config.processor.getPrice();
                    surplus+=sum-config.processor.getPrice();
                    compatible=true;
                }
            }
         }

    return compatible;
}
bool DataLoader::ChooseMotherBoard(int index,int sum, int &surplus)
{
    qDebug()<<"ChooseMotherBoard()";
    bool compatible=false;
    demand.MotherForm=arrMotherboards[index].getForm();
    demand.Socket=arrMotherboards[index].getSocket();
    if(arrMotherboards[index].getDDR3count()!=0)
        demand.DDRtype="DDR3";
    if(arrMotherboards[index].getDDR4count()!=0)
        demand.DDRtype="DDR4";
    if(arrMotherboards[index].getM2()!=0)
        demand.M2=arrMotherboards[index].getM2();
    demand.MaxFreqRAM=arrMotherboards[index].getMaxFreq();
    demand.Price+=arrMotherboards[index].getPrice();
    config.motherboard=arrMotherboards[index];
    surplus+=sum-config.motherboard.getPrice();   //конфиг пораньше перенести можно было.
    compatible=true;


    return compatible;
}
bool DataLoader::ChooseRAM(int index,int sum, int &surplus)
{
    qDebug()<<"ChooseRAM()";
    bool compatible=false;
        if(demand.DDRtype==arrRAMs[index].getMemType())
            if(demand.MaxFreqRAM>=arrRAMs[index].getMemFreq())
            {
                config.ram=arrRAMs[index];
                surplus+=sum-config.ram.getPrice();
                demand.Price+=config.ram.getPrice();
                compatible=true;
            }



    return compatible;
}
bool DataLoader::ChooseHDD(int index, int sum, int &surplus)
{
    qDebug()<<"ChooseHDD()";
    bool compatible=false;
    config.hdd=arrHDDs[index];
    surplus+=sum-config.hdd.getPrice();
    demand.Price+=config.hdd.getPrice();
    compatible=true;
    return compatible;
}
bool DataLoader::ChooseSSD(int index,int sum, int &surplus)
{
    qDebug()<<"ChooseSSD()";
    bool compatible=false;          
                config.ssd=arrSSDs[index];
                surplus+=sum-config.ssd.getPrice();
                demand.Price+=config.ssd.getPrice();
                compatible=true;

    return compatible;
}
bool DataLoader::CheckCoolerSoket(QString find,QString list)
{
    bool compatible=false;
    QRegExp amd("AMD.*(..\\d\\+?)");
    QRegExp intel("Intel.*(\\d{3,4}.?v?\\d?)");
    QString socket1="";
    QString socket2="";
    QString isEmpty1="";
    QString isEmpty2="";
    qDebug()<<"socket on processor"<<find;
    qDebug()<<"cooler sockets"<<list;
    int lastPos = 0;

        while( ( lastPos = amd.indexIn( find, lastPos ) ) != -1 )
        {
            lastPos += amd.matchedLength();
            socket1=amd.cap( 1 );
        }
    lastPos=0;
        while( ( lastPos = intel.indexIn( find, lastPos ) ) != -1 )
        {
            lastPos += intel.matchedLength();
            socket2=intel.cap( 1 );
        }
    if(socket1!="")
    {
        QRegExp socket("("+socket1+")");
        lastPos=0;
        while((lastPos=socket.indexIn(list,lastPos))!=-1)
        {
            lastPos+=socket.matchedLength();
            isEmpty2=socket.cap(1);
        }
    }
    if(socket2!="")
    {
        QRegExp socket("("+socket2+")");
        lastPos=0;
        while((lastPos=socket.indexIn(list,lastPos))!=-1)
        {
            lastPos+=socket.matchedLength();
            isEmpty2=socket.cap(1);
        }
    }
    if(isEmpty1!=""||isEmpty2!="")
        compatible=true;
    return compatible;
}
bool DataLoader::ChooseCooler(int index,int sum,int&surplus)
{
    qDebug()<<"ChooseCooler()";
    bool socket=false;
    bool compatible=false;
       socket=CheckCoolerSoket(demand.Socket,arrCoolers[index].getSockets());
        if(socket)
        {
            if((arrCoolers[index].getTDP()!=0)&&(arrCoolers[index].getTDP()>=demand.TDP))
            {
                config.cooler=arrCoolers[index];
                demand.Price+=config.cooler.getPrice();
                surplus+=sum-config.cooler.getPrice();
                compatible=true;
            }

        }
        return compatible;
}
bool DataLoader::ChoosePower(int index,int sum, int &surplus)
{
    qDebug()<<"ChoosePower()";
    bool compatible=false;

        if(arrPowers[index].getPower()>=demand.MinPower)
        {
            config.power=arrPowers[index];
            demand.PowerForm=config.power.getForm();
            demand.Price+=config.power.getPrice();
            surplus+=sum-config.power.getPrice();
            compatible=true;
        }
   return compatible;
}
bool DataLoader::ChooseCase(int index,int sum, int &surplus)
{
    qDebug()<<"ChooseCase()";
    bool compatible=false;

        if(demand.MotherForm==arrCases[index].getMotherForm())
        {
            QString check="";
            QRegExp reg("("+demand.PowerForm+")");
            int lastPos=0;
            while((lastPos=reg.indexIn(arrCases[index].getPowerForm(),lastPos))!=-1)
            {
                lastPos+=reg.matchedLength();
                check=reg.cap(1);
            }
            if(check==demand.PowerForm)
            {
                config.box=arrCases[index];
                demand.Price+=arrCases[index].getPrice();
                surplus+=sum-config.box.getPrice();
                compatible=true;
            }
        }
    return compatible;

}
bool DataLoader::CheckCompatibility(QVector<QString> &newEl,int typeEl,QString& feedback)
{
    qDebug()<<"CheckCompatibility()";
    bool compatible=true;
    feedback="Если хотите добавить несовместимый элемент,нажмите YES\n\nЭлемент не совместим c\n";
    switch(typeEl)
    {
        case 0:
        {

            Processor el(newEl);
            if(config.motherboard.getSocket()!=""&&config.motherboard.getSocket()!=el.getSocket())
               {
                    compatible=false;
                    feedback+="-Материнской платой:\n"
                             "Сокет Мат.платы: "+config.motherboard.getSocket()+"\tПротив "+el.getSocket()+"\n";
                }
            if((config.ram.getMemType()=="DDR3"&&el.getMaxMemFreqDDR3()==0)||(config.ram.getMemType()=="DDR4"&&el.getMaxMemFreqDDR4()==0))
            {
                compatible=false;
                feedback+="-Оперативной памятью:\n"
                          "Тип Оперативной памяти: "+config.ram.getMemType()+"\tМакс.частота DDR4: "+el.getMaxMemFreqDDR4()+" Макс.частота DDR3: "+el.getMaxMemFreqDDR3()+"\n";

            }
            if(config.ram.getMemType()=="DDR4"&&el.getMaxMemFreqDDR4()!=0&&config.ram.getMemFreq()>(int)el.getMaxMemFreqDDR4())
            {
                compatible=false;
                feedback+="-Оперативной памятью:\n"
                          "Частота Оперативной памяти DDR4: "+config.ram.getMemFreq()+"\tПротив "+el.getMaxMemFreqDDR4()+"\n";
            }
            if(config.ram.getMemType()=="DDR3"&&el.getMaxMemFreqDDR3()!=0&&config.ram.getMemFreq()>(int)el.getMaxMemFreqDDR3())
            {
                compatible=false;
                feedback+="-Оперативной памятью:\n"
                          "Частота Оперативной памяти DDR3: "+config.ram.getMemFreq()+"\tПротив "+el.getMaxMemFreqDDR3()+"\n";
            }
            if(config.cooler.getTDP()!=0&&el.getTDP()!=0&&config.cooler.getTDP()<el.getTDP())
            {
                compatible=false;
                feedback+="-Кулером:\n"
                          "Отвод тепла кулера: "+QString::number(config.cooler.getTDP())+"\tПротив Тепловыделения "+el.getTDP()+"\n";
            }
            if(config.cooler.getName()!="")
            {
                    if(!CheckCoolerSoket(el.getSocket(),config.cooler.getSockets()))
                {
                    compatible=false;
                    feedback+="-Кулером\n"
                              "Сокет процессора не подходит к поддерживающимся сокетам кулера\n";
                }
            }
         break;
        }

    case 1:
    {
        MotherBoard el(newEl);
        if(config.processor.getSocket()!=""&&el.getSocket()!=0&&el.getSocket()!=config.processor.getSocket())
        {
            compatible=false;
            feedback+="-Процессором:\n"
                      "Сокет процессора: "+config.processor.getSocket()+"\tПротив "+el.getSocket()+"\n";
        }
        if((config.ram.getMemType()=="DDR4"&&el.getDDR4count()==0)||(config.ram.getMemType()=="DDR3"&&el.getDDR3count()==0))
        {
            compatible=false;
            feedback+="-Оперативной памятью:\n"
                      "Тип ОП: "+config.ram.getMemType()+"\t Количество планок для DDR4: "+el.getDDR4count()+" для DDR3: "+el.getDDR3count()+"\n";
        }
        if(config.ram.getMemFreq()!=0&&config.ram.getMemFreq()>el.getMaxFreq())
        {
            compatible=false;
            feedback+="-Оперативной памятью:\n"
                      "Частота ОП:"+config.ram.getMemFreq()+"\t Против максимальной "+el.getMaxFreq()+"\n";
        }
        if(el.getMaxMem()!=0&&config.ram.getSumMem()>el.getMaxMem())
        {
            compatible=false;
            feedback+="-Оперативной памятью:\n"
                      "Общее количество ОП: "+QString::number(config.ram.getSumMem())+"\t Против максимального "+el.getMaxMem()+"\n";
        }
        if(config.box.getMotherForm()!=""&&config.box.getMotherForm()!=el.getForm())
        {
            compatible=false;
            feedback+="-Корпусом:\n"
                      "Форм-фактор Мат.платы в корпусе: "+config.box.getMotherForm()+"\t Против "+el.getForm()+"\n";
        }
        break;
    }
    case 2:
        {

         GraphicsCard el(newEl);
            if(config.power.getPower()!=0&&el.getPower()!=0&&config.power.getPower()<el.getPower())
            {
                compatible=false;
                feedback+="-Блоком питания:\n"
                          "Мощность блока питания: "+QString::number(config.power.getPower())+"\t Против требуемой "+el.getPower()+"\n";
            }
            break;
        }
    case 3:
    {
        RAM el(newEl);
        if(config.processor.getName()!=""&&((el.getMemType()=="DDR3"&&config.processor.getMaxMemFreqDDR3()==0)||(el.getMemType()=="DDR4"&&config.processor.getMaxMemFreqDDR4()==0)))
        {
            compatible=false;
            feedback+="-Процессором:\n"
                      "У процессора макс.частота DDR4: "+QString::number(config.processor.getMaxMemFreqDDR4())+" DDR3: "+config.processor.getMaxMemFreqDDR3()+"\tТип памяти "+el.getMemType()+"\n";
        }
        if((config.processor.getMaxMemFreqDDR4()!=0&&(int)config.processor.getMaxMemFreqDDR4()<el.getMemFreq())||(config.processor.getMaxMemFreqDDR3()!=0&&(int)config.processor.getMaxMemFreqDDR3()<el.getMemFreq()))
        {
            compatible=false;
            feedback+="-Процессором:\n"
                      "У процессора макс частота : "+QString::number(config.processor.getMaxMemFreqDDR4())+"\tПротив "+el.getMemFreq()+"\n";
        }
        if(config.motherboard.getName()!=""&&config.motherboard.getDDR4count()==0&&el.getMemType()=="DDR4")
        {
            compatible=false;
            feedback+="-Материнской платой:\n"
                      "Макс. планок мат.платы типа DDR4: "+QString::number(config.motherboard.getDDR4count())+"\tТип Оперативной памяти: DDR4\n";
        }
        if(config.motherboard.getName()!=""&&config.motherboard.getDDR3count()==0&&el.getMemType()=="DDR3")
        {
            compatible=false;
            feedback+="-Материнской платой:\n"
                      "Макс. планок мат.платы типа DDR3: "+QString::number(config.motherboard.getDDR3count())+"\tТип Оперативной памяти: DDR3\n";
        }
        if(config.motherboard.getMaxMem()!=0&&config.motherboard.getMaxMem()<el.getSumMem())
        {
            compatible=false;
            feedback+="-Материнской платой:\n"
                     "Макс ОП у мат. платы: "+QString::number(config.motherboard.getMaxMem())+"\tПротив "+el.getSumMem()+"\n";
        }
        if(config.motherboard.getMaxFreq()!=0&&config.motherboard.getMaxFreq()<el.getMemFreq())
        {
            compatible=false;
            feedback+="-Материнской платой:\n"
                      "Макс частота ОП у мат.платы: "+QString::number(config.motherboard.getMaxFreq())+"\tПротив "+el.getMemFreq()+"\n";
        }
        break;
    }
    case 4:
    {
        Cooler el(newEl);
        if(config.processor.getSocket()!="")
                if(!CheckCoolerSoket(config.processor.getSocket(),el.getSockets()))
                {
                    compatible=false;
                    feedback+="-Процессором:\n"
                              "Сокет процессора не подходит к поддерживающимся сокетам кулера.\n";
                }
        if(config.processor.getTDP()!=0&&config.processor.getTDP()>el.getTDP())
        {
            compatible=false;
            feedback+="-Процессором:\n"
                      "Тепловыделение процессора: "+QString::number(config.processor.getTDP())+"\tПротив Теплоотвода "+QString::number(el.getTDP())+"\n";
        }
        break;
    }
    case 5:
    {
        compatible=true;
        break;
    }
    case 6:
    {
        SSD el(newEl);
        if(config.motherboard.getName()!=""&&config.motherboard.getM2()==0&&el.getForm()=="M.2")
        {
            compatible=false;
            feedback+="-Материнской платой\n"
                      "У материнской платы отсутствует разъем M.2\n";
        }
        break;
    }
    case 7:
    {
        Power el(newEl);
        if(config.graphicscard.getName()!=0&&config.graphicscard.getPower()>el.getPower())
        {
            compatible=false;
            feedback+="-Видеокартой\n"
                      "Требуемая мощность БП для видеокарты: "+QString::number(config.graphicscard.getPower())+"\tПротив "+el.getPower()+"\n";
        }
        break;
    }
    case 8:
    {
        Case el(newEl);
        if(config.motherboard.getForm()!=""&&config.motherboard.getForm()!=el.getMotherForm())
        {
            compatible=false;
            feedback+="-Материнской платой\n"
                      "Форм фактор мат.платы: "+config.motherboard.getForm()+"\t Против "+el.getMotherForm();
        }
        break;
    }

    }
    if(compatible)
        feedback="";
    return compatible;
}
template<class T>
void DataLoader::GetMinMaxIndexes(QVector<T> & arr,int min,int max,int i)
{
    SortFromCheapest();
    QVector<int>temp;
    int minIndex;
    int maxIndex;
    maxSum[i]=max;
    minSum[i]=min;
        maxIndex=BinaryIndex(arr,arr.size(),maxSum[i]);
        minIndex=BinaryIndex(arr,arr.size(),minSum[i]);
        if(minIndex!=0)
            --minIndex;
        if(maxIndex!=0)
            --maxIndex;
        for(int j=minIndex;j<=maxIndex;++j)
        {
            temp.push_back(j);
        }
        if(availableIndexes.size()==9)
           {    if(availableIndexes[i].size()==1)
                {
                for(int j=0;j<temp.size();++j)
                   { availableIndexes[i].push_back(temp[j]);
                }
                availableIndexes[i].remove(0);
                }
                else availableIndexes.push_back(temp);
            }
        else
            {
            availableIndexes.push_back(temp);
            }

}
void DataLoader::FindAllVariants(int min,int max, int configType)
{
    SortFromCheapest();
    if(configType==0)
        for(int i=0;i<9;++i)
        {
            maxSum[i]=(max*gamerConfig[i])/100;
            minSum[i]=(min*gamerConfig[i])/100;
        }
    if(configType==1)
    {
        for(int i=0;i<9;++i)
        {
            maxSum[i]=(max*officeConfig[i])/100;
            minSum[i]=(min*officeConfig[i])/100;
        }
    }
    GetMinMaxIndexes(arrProcessors,minSum[0],maxSum[0],0);
    GetMinMaxIndexes(arrMotherboards,minSum[1],maxSum[1],1);
    GetMinMaxIndexes(arrGraphicsCards,minSum[2],maxSum[2],2);
    GetMinMaxIndexes(arrRAMs,minSum[3],maxSum[3],3);
    GetMinMaxIndexes(arrCoolers,minSum[4],maxSum[4],4);
    GetMinMaxIndexes(arrHDDs,minSum[5],maxSum[5],5);
    GetMinMaxIndexes(arrSSDs,minSum[6],maxSum[6],6);
    GetMinMaxIndexes(arrPowers,minSum[7],maxSum[7],7);
    GetMinMaxIndexes(arrCases,minSum[8],maxSum[8],8);

                   for(int i=0;i<9;++i)
                       qDebug()<<availableIndexes[i];

}
void DataLoader::GenerateConfig(int minsum,int maxsum,int type)
{

    if(availableIndexes.size()!=0)
        availableIndexes.clear();
    availableIndexes.squeeze();
    ClearConfig();
    demand.Price=0;
    demand.DDRtype="";
    demand.FreqDDR3=0;
    demand.FreqDDR4=0;
    demand.M2=0;
    demand.MaxFreqRAM=0;
    demand.MinPower=0;
    demand.MotherForm="";
    demand.PowerForm="";
    demand.Socket="";
    demand.TDP=0;

    int surplus=0;
    int checkIndex=0;
    FindAllVariants(minsum,maxsum,type);

    //МАТЕРИНКА
    bool compatible=false;
    while(!compatible)
    {
        if(arrMotherboards[0].getPrice()>maxSum[1])
        {
            compatible=ChooseMotherBoard(0,maxSum[1],surplus);
        }
        else
        {
            if(availableIndexes[1].size()==1)
            {
            checkIndex=0;
            }
            else
                checkIndex=rand()%(availableIndexes[1].size());
            compatible=ChooseMotherBoard(availableIndexes[1][checkIndex],maxSum[1],surplus);
            if(!compatible) 
                availableIndexes[1].remove(checkIndex);

        }

    }
    //ВИДЕОКАРТА
    compatible=false;
    while(!compatible&&maxSum[2]>arrGraphicsCards[0].getPrice()&&availableIndexes[2].size()!=0)
    {
        if(availableIndexes[2].size()==1)
        {
            checkIndex=0;
        }
        else
        checkIndex=rand()%(availableIndexes[2].size());
        compatible=ChooseGraphicCard(availableIndexes[2][checkIndex],maxSum[2],surplus);
        if(!compatible)
            availableIndexes[2].remove(checkIndex);

    }
    //ПРОЦЕССОР
    compatible=false;
    while(!compatible&&maxSum[0]>arrProcessors[0].getPrice()&&availableIndexes[0].size()!=0)
    {
        if(availableIndexes[0].size()==1)
        {
            checkIndex=0;
        }
        else
        checkIndex=rand()%(availableIndexes[0].size());
        compatible=ChooseProcessor(availableIndexes[0][checkIndex],maxSum[0],surplus,type);
        if(!compatible)
           { if(surplus!=0&&minSum[0]!=0&&availableIndexes[0].size()==1)
                {
                maxSum[0]+=surplus;
                surplus=0;
                minSum[0]=0;
                GetMinMaxIndexes(arrProcessors,minSum[0],maxSum[0],0);
                }
            else
                {
                availableIndexes[0].remove(checkIndex);
                }
        }

    }
    //ОПЕРАТИВКА
    compatible=false;
    while(!compatible&&maxSum[3]>arrRAMs[0].getPrice()&&availableIndexes[3].size()!=0)
    {
        if(availableIndexes[3].size()==1)
        {
            checkIndex=0;
        }
        else
        checkIndex=rand()%(availableIndexes[3].size());
        compatible=ChooseRAM(availableIndexes[3][checkIndex],maxSum[3],surplus);
        if(!compatible)
            availableIndexes[3].remove(checkIndex);

    }
    //Кулер
    compatible=false;
    while(!compatible&&maxSum[4]>arrCoolers[0].getPrice()&&availableIndexes[4].size()!=0)
    {
        if(availableIndexes[4].size()==1)
        {
            checkIndex=0;
        }
        else
        checkIndex=rand()%(availableIndexes[4].size());
        compatible=ChooseCooler(availableIndexes[4][checkIndex],maxSum[4],surplus);
        if(!compatible)
            availableIndexes[4].remove(checkIndex);

    }
    //HDD
    compatible=false;
    while(!compatible&&maxSum[5]>arrHDDs[0].getPrice()&&availableIndexes[5].size()!=0)
    {
        if(availableIndexes[5].size()==1)
        {
            checkIndex=0;
        }
        else
        checkIndex=rand()%(availableIndexes[5].size());
        compatible=ChooseHDD(availableIndexes[5][checkIndex],maxSum[5],surplus);
        if(!compatible)
            availableIndexes[5].remove(checkIndex);

    }
    //ССД
    compatible=false;
    while(!compatible&&availableIndexes[6].size()!=0&&maxSum[6]!=0)
    {
        if(availableIndexes[6].size()==1)
        {
            checkIndex=0;
        }
        else
            checkIndex=rand()%(availableIndexes[6].size());//
        compatible=ChooseSSD(availableIndexes[6][checkIndex],maxSum[6],surplus);
        if(!compatible)
        {
            if(surplus!=0&&minSum[6]!=0&&availableIndexes[6].size()==1)
            {
                maxSum[6]+=surplus;
                surplus=0;
                minSum[6]=0;
                GetMinMaxIndexes(arrSSDs,minSum[6],maxSum[6],6);
            }
            else
                availableIndexes[6].remove(checkIndex);
        }

    }
    //БЛОК ПИТАНИЯ
    compatible=false;
    while(!compatible&&availableIndexes[7].size()!=0)
    {
        if(availableIndexes[7].size()==1)
        {
            checkIndex=0;
        }
        else
        checkIndex=rand()%(availableIndexes[7].size());
        compatible=ChoosePower(availableIndexes[7][checkIndex],maxSum[7],surplus);
        if(!compatible)
        {
            if(surplus!=0&&minSum[7]!=0&&availableIndexes[7].size()==1)
            {
                maxSum[7]+=surplus;
                surplus=0;
                minSum[7]=0;
                GetMinMaxIndexes(arrPowers,minSum[7],maxSum[7],7);
            }
            else
                availableIndexes[7].remove(checkIndex);
        }

    }

    //КОРПУС
    compatible=false;
    while(!compatible&&availableIndexes[8].size()!=0)
    {
        if(availableIndexes[8].size()==1)
        {
            checkIndex=0;
        }
        else
        checkIndex=rand()%(availableIndexes[8].size());
        compatible=ChooseCase(availableIndexes[8][checkIndex],maxSum[8],surplus);
        if(!compatible)
        {
            if(surplus!=0&&minSum[8]!=0&&availableIndexes[8].size()==1)
            {
                maxSum[8]+=surplus;
                surplus=0;
                minSum[8]=0;
                GetMinMaxIndexes(arrCases,minSum[8],maxSum[8],8);
            }
            else
                availableIndexes[8].remove(checkIndex);
        }

    }
}


