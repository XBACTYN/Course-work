#include "processor.h"

Processor::Processor(){}


   const QString& Processor::GetName() {return _name;}
   const QString &Processor::GetManuf(){return _manuf;}
   const QString &Processor::GetSocket(){return _socket;}
   const QString &Processor::GetMemType(){return _memType;}
   const QString &Processor::GetGraphic(){return _iGraphic;}
   size_t Processor::GetKernels(){return _kernels;}
   size_t Processor::GetmaxMem(){return _maxMem;}
   size_t Processor::GetHeat(){return _heat;}
   size_t Processor::GetPCI(){return _pciExpress;}
   size_t Processor::GetDate(){return _date;}
   double Processor::GetKerFreq(){return _kerFreq;}
   double Processor::GetPrice(){return _price;}
   double Processor::GetMinMemFreq(){return _minMemFreq;}
   double Processor::GetMaxMemFreq(){return _maxMemFreq;}
   bool Processor::GetMultiThreading(){return _multThreading;}

