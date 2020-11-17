#include "parsemachine.h"

ParseMachine::ParseMachine()
{

}

void ParseMachine::Insert(QString str, Element el)
{
    map.insert(str,el);
}
