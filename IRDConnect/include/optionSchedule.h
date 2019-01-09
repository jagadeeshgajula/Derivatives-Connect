#ifndef OPTIONSHEDULE_H
#define OPTIONSHEDULE_H

#include <iostream>
#include <string>
#include "irdString.h"
#include "date.h"

using namespace std;
using namespace IRDConnect;

namespace IRDConnect {


class OptionSchedule
{
public:

OptionSchedule(){;};
OptionSchedule(
int 		executeFlag,
Date 		endDate,
Date 		startDate,
String 		tradeRef
)
{
_executeFlag		=	executeFlag;
_endDate 			=	endDate;
_startDate			=	startDate;
_tradeRef			=	tradeRef;
   }
   
int getExecuteFlag(){return _executeFlag;}
void setExecuteFlag(int executeFlag){ _executeFlag = executeFlag;}

Date getEndDate() { return  _endDate;}
void setEndDate(Date endDate) { _endDate = endDate; }

Date getStartDate() { return  _startDate;}
void setStartDate(Date startDate) { _startDate = startDate; }

String getTradeRef(){return _tradeRef;}
void setTradeRef(String tradeRef){ _tradeRef = tradeRef; }

protected:
   
int 		_executeFlag;
Date 		_endDate;
Date 		_startDate;
String 		_tradeRef;
};

}


#endif //OPTIONSHEDULE_H
