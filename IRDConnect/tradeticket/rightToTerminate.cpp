#include <cstdlib>
#include <iostream>
#include "rightToTerminate.h"


using namespace std;

using namespace IRDConnect;

RightToTerminate::RightToTerminate (
Date 		commencementDate,
String 		earlyTerminationProvision,
String 		eventAgent,
String 		exercise,
String 		exerciseBusinessCenters,
String 		exerciseBusinessDayConvention,
String 		exerciseFrequency,
Date 		expirationDate,
String 		maxNoticeCutOff,
String 		minNoticeCutOff,
int 		minNoticeDays,
String 		noticeBusDayConvention,
String 		noticeBusinessCenters,
String 		noticeDayConvention

)
{


_commencementDate              = commencementDate;
_earlyTerminationProvision     = earlyTerminationProvision;
_eventAgent                    = eventAgent;
_exercise                      = exercise;
_exerciseBusinessCenters       = exerciseBusinessCenters;
_exerciseBusinessDayConvention = exerciseBusinessDayConvention;
_exerciseFrequency             = exerciseFrequency;  
_expirationDate                = expirationDate;
_maxNoticeCutOff               = maxNoticeCutOff;
_minNoticeCutOff               = minNoticeCutOff;
_minNoticeDays                 = minNoticeDays;
_noticeBusDayConvention        = noticeBusDayConvention;
_noticeBusinessCenters         = noticeBusinessCenters;
_noticeDayConvention           = noticeDayConvention;

}

RightToTerminate::~RightToTerminate()
{
	// do nothing
}
          
           

