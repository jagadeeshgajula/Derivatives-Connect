#ifndef AMORTSCHEDULE_H
#define AMORTSCHEDULE_H

#include "irdString.h"
#include <list>
#include "date.h"
#include <set>

using namespace std;
using namespace IRDConnect;

namespace IRDConnect
{


class AmortSchedule
{

public:

AmortSchedule (
double 	amortNotional,
Date   	endDate,
Date   	startDate);

AmortSchedule();

virtual ~AmortSchedule();

double getAmortNotional() { return _amortNotional; }
void setAmortNotional( double amortNotional ) { _amortNotional = amortNotional; }

Date getEndDate() { return _endDate; }
void setEndDate( Date endDate ) { _endDate = endDate; }

Date getStartDate() { return _startDate; }
void setStartDate( Date startDate ) { _startDate = startDate; }



protected:
double 	_amortNotional;
Date   	_endDate;
Date   	_startDate;



};

}


#endif // AMORTSCHEDULE_H
