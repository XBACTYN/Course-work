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

    pages[0]=1;  //поменяю с 2 на 1.
    pages[1]=1;  //поменяю с 2 на 1
    pages[2]=2;
    //pages[3]=1;

    pages[4]=2;
    pages[5]=1;
    pages[7]=1;

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

void DataLoader::RepairCooler(QString & str) //              УДАЛИТЬ
{
   QRegExp reg("R>(.{2,22})(?:/|<B)");
   QString nstr="<BR>";
   nstr+=str;
   nstr+="<BR>";
  // qDebug()<<nstr;
   nstr.replace("/","//");
   qDebug()<<nstr;
   str.clear();
   int lastPos = 0;
   while( ( lastPos = reg.indexIn( nstr, lastPos ) ) != -1 )
   {
       lastPos += reg.matchedLength();
           qDebug()<<reg.cap(1);
           str+=reg.cap(1)+" ";

   }
  qDebug()<<str;

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
void DataLoader::RepairHDD(QString &str)     //              УДАЛИТЬ
{
    QRegExp reg("R>(.{4,6})<B");
    QString nstr="<BR>";
    nstr+=str;
    nstr.replace("<br>","<BR>");
    str.clear();
    int lastPos = 0;
    while( ( lastPos = reg.indexIn( nstr, lastPos ) ) != -1 )
    {
        lastPos += reg.matchedLength();
            qDebug()<<reg.cap(1);
            str+=reg.cap(1)+" ";

    }
   qDebug()<<str;
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
void DataLoader::DownloadPage(QString &Html,QUrl &url) //максимально 24 процессора на странице. потом /(n-1)/ к адресу страницы
{
    qDebug()<<"in DownloadPage()";
    QNetworkReply *response = manager->get(QNetworkRequest(url));
    QEventLoop event;
    connect(response,SIGNAL(finished()),&event,SLOT(quit()));
    event.exec();
    Html=response->readAll();

}

void DataLoader::Regex1lvl(int i,QString & Html,QVector<QRegExp>&vectorReg,QVector<QUrl> &tempVector)//максимально 24 процессора на странице. потом /(n-1)/ к адресу страницы
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

void DataLoader::Regex2lvl(int i,QString & Html,QVector<QRegExp> &vectorReg2,QVector<QString>&data)//cюда захуярить tempVector& data
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

void DataLoader::ClearElArrays()
{
    if(arrProcessors.size()!=0)
    { arrProcessors.clear();
      arrProcessors.squeeze();
    }
    if(arrMotherboards.size()!=0)
    {arrMotherboards.clear();
     arrMotherboards.squeeze();
    }
    if(arrGraphicsCards.size()!=0)
    {arrGraphicsCards.clear();
    arrGraphicsCards.squeeze();
    }
    if(arrRAMs.size()!=0)
    {arrRAMs.clear();
    arrRAMs.squeeze();
    }
    if(arrCoolers.size()!=0)
    {arrCoolers.clear();
    arrCoolers.squeeze();
    }
    if(arrHDDs.size()!=0)
    {arrHDDs.clear();
    arrHDDs.squeeze();
    }
    if(arrSSDs.size()!=0)
    {arrSSDs.clear();
    arrSSDs.squeeze();
    }
    if(arrPowers.size()!=0)
    {
    arrPowers.clear();
    arrPowers.squeeze();
    }
    if(arrCases.size()!=0)
    {
    arrCases.clear();
    arrCases.clear();
    }
    for(int i=0;i<9;++i)
        u2arrayI[i]=0;

    for(int i=0;u2array.size();i++)
    {
        u2array[i].clear();
        u2array[i].squeeze();
    }
    if(u2array.size()!=0)
        u2array.clear();
    u2array.squeeze();
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

/*template < class T>
T DataLoader::BinaryPrice(QVector<T> & arr,int size, const int value)
{
    int left=0;
    int right=size-1;
    int middle;
    while(true)
    {
        middle=(left+right)/2;
        if(value>arr[middle].price)
        {left=middle+1;
            qDebug()<<"middle"<<middle<<"left"<<left;
        }
        else if(value<arr[middle].price)
        {
            right=middle-1;
            qDebug()<<"middle"<<middle<<"right"<<right;
        }
        else return arr[middle];
        if(left>right)
            return arr[right]; //изменил с left на right
    }
};*/
template<class T>
int DataLoader::BinaryIndex(QVector<T>&arr,int size,const int value)
{
    int left=0;
    int right=size-1;
    int middle;
    while(true)
    {
        middle=(left+right)/2;
        qDebug()<<"middle"<<middle;
        if(value>arr[middle].price)
        {
            left=middle+1;
            qDebug()<<"left"<<left;
            qDebug()<<"middle1"<<arr[middle].price<<"left1"<<arr[left].price;
        }
        else if(value<arr[middle].price)
        {
            right=middle-1;
            qDebug()<<"right"<<right;
            qDebug()<<"middle2"<<arr[middle].price<<"right2"<<arr[right].price;
        }
        else return middle;
        if(left>right)
        {qDebug()<<"left return"<<left;
            return left; //изменил с left на right
        }
    }
}
void DataLoader::ChooseGraphicCard(int sum, int &surplus)
{
    //ищем верхнюю границу цены.
   int maxIndex= BinaryIndex(arrGraphicsCards,arrGraphicsCards.size(),sum);
   if(maxIndex!=0)
       --maxIndex;
   bool compatible=false;
   while(maxIndex>=0&&!compatible)
   {
       config.graphicscard=arrGraphicsCards[maxIndex];
       compatible=true;
   }
   demand.MinPower=config.graphicscard.getPower();
   demand.Price=config.graphicscard.getPrice();
   surplus=sum-config.graphicscard.getPrice();
   qDebug()<<config.graphicscard.name<<config.graphicscard.price;
}
void DataLoader::ChooseProcessor(int sum, int &surplus,int type) // НУЖНА ПРОВЕРКА НА КОЛИЧЕСТВО ЯДЕР.
{
    int maxIndex=BinaryIndex(arrProcessors,arrProcessors.size(),sum);
    if(maxIndex!=0)
        --maxIndex;
    bool compatible=false;
    while(maxIndex>=0&&!compatible)
    {
        if(type==0&&arrProcessors[maxIndex].getCores()>=6)
        {
            config.processor=arrProcessors[maxIndex];
            demand.Socket=config.processor.getSocket();
            demand.FreqDDR4=config.processor.getMaxMemFreqDDR4();
            demand.FreqDDR3=config.processor.getMaxMemFreqDDR3();
            demand.TDP=config.processor.getTDP();
            demand.Price+=config.processor.getPrice();
            surplus+=sum-config.processor.getPrice();
            compatible=true;
        }
        --maxIndex;
    }
    qDebug()<<config.processor.name<<config.processor.price;
}
void DataLoader::ChooseMotherBoard(int sum, int &surplus)
{
    int maxIndex=BinaryIndex(arrMotherboards,arrMotherboards.size(),sum);
    if(maxIndex!=0)
        --maxIndex;
    qDebug()<<maxIndex;
    bool compatible=false;
    while(maxIndex>=0&&!compatible)
    {
        if(arrMotherboards[maxIndex].getSocket()==demand.Socket)//пока оставлю равенство.надо заменить на поиск по подстроке.
            if((demand.FreqDDR4!=0&&arrMotherboards[maxIndex].getDDR4count()!=0)||(demand.FreqDDR3!=0&&arrMotherboards[maxIndex].getDDR3count()!=0))
                {
                    demand.MotherForm=arrMotherboards[maxIndex].getForm();
                    if(arrMotherboards[maxIndex].getM2()!=0)
                        demand.M2=arrMotherboards[maxIndex].getM2();
                    if(arrMotherboards[maxIndex].getDDR4count()!=0)
                        demand.DDRtype="DDR4";
                    demand.MaxFreqRAM=arrMotherboards[maxIndex].getMaxFreq();
                    demand.Price+=arrMotherboards[maxIndex].getMaxFreq();
                    config.motherboard=arrMotherboards[maxIndex];
                    surplus+=config.motherboard.getPrice();   //конфиг пораньше перенести можно было.
                    compatible=true;
                    //demand.USB3=arrMotherboards[maxIndex].getUSB3();
                    qDebug()<<config.motherboard.getName()<<config.motherboard.getPrice();
                }

        --maxIndex;
    }
}
void DataLoader::GenerateConfig(int type,int sum) //Ощущение что надо сделать класс совместимости. QString Socket, int TDP...
{


    int surplus=0;
    SortFromCheapest();
    switch(type)
    {
        case 0:
        {  // используем игровые проценты.
            for(int i=0;i<9;++i)
               { maxSum[i]=(sum*gamerConfig[i])/100;
               qDebug()<<maxSum[i];
                }
            ChooseGraphicCard(maxSum[2],surplus);
            ChooseProcessor(maxSum[0],surplus,type);
            ChooseMotherBoard(maxSum[1],surplus);
            break;
        }
        case 1:
        {
            break;
        }
    }
}


