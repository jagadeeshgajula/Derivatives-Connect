#ifndef RIGHTTOTERMINATE_H
#define RIGHTTOTERMINATE_H
#include <iostream>
#include<string>
#include "irdString.h"
#include "date.h"

using namespace std;
using namespace IRDConnect;

namespace IRDConnect {

class RightToTerminate
{

public:

RightToTerminate(){;};  // default constructor

RightToTerminate(
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
);

~RightToTerminate();

Date getCommencementDate(){return _commencementDate;}
void setCommencementDate(Date commencementDate){ _commencementDate = commencementDate;}

String getEarlyTerminationProvision() {return _earlyTerminationProvision;}
void setEarlyTerminationProvision(String earlyTerminationProvision) { _earlyTerminationProvision = earlyTerminationProvision; }

String getEventAgent(){return _eventAgent;}
void setEventAgent(String eventAgent){ _eventAgent = eventAgent; }

String getExercise(){return _exercise;}
void setExercise(String exercise){ _exercise = exercise;}

String getExerciseBusinessCenters() {return _exerciseBusinessCenters;}
void setExerciseBusinessCenters(String exerciseBusinessCenters) { _exerciseBusinessCenters = exerciseBusinessCenters; }

String getExerciseBusinessDayConvention(){return _exerciseBusinessDayConvention;}
void setexerciseBusinessDayConvention(String exerciseBusinessDayConvention){ _exerciseBusinessDayConvention = exerciseBusinessDayConvention; }

String getExerciseFrequency(){return _exerciseFrequency;}
void setExerciseFrequency(String exerciseFrequency){ _exerciseFrequency = exerciseFrequency;}

Date getExpirationDate(){return _expirationDate;}
void setExpirationDate (Date expirationDate ){ _expirationDate = expirationDate ;}

String getMaxNoticeCutOff(){return _maxNoticeCutOff;}
void setMaxNoticeCutOff (String maxNoticeCutOff ){ _maxNoticeCutOff = maxNoticeCutOff ;}

String getMinNoticeCutOff(){return _minNoticeCutOff;}
void setMinNoticeCutOff(String minNoticeCutOff){ _minNoticeCutOff = minNoticeCutOff;}

int getMinNoticeDays(){return _minNoticeDays;}
void setMinNoticeDays (int minNoticeDays ) { _minNoticeDays = minNoticeDays ;}

String getNoticeBusDayConvention(){return _noticeBusDayConvention;}
void setNoticeBusDayConvention (String noticeBusDayConvention ){ _noticeBusDayConvention = noticeBusDayConvention ;}

String getNoticeBusinessCenters(){return _noticeBusinessCenters;}
void setNoticeBusinessCenters (String noticeBusinessCenters ){ _noticeBusinessCenters = noticeBusinessCenters ;}

String getNoticeDayConvention(){return _noticeDayConvention;}
void setNoticeDayConvention (String noticeDayConvention ){ _noticeDayConvention = noticeDayConvention ;}

private:
Date 		_commencementDate;
String 		_earlyTerminationProvision;
String 		_eventAgent;
String 		_exercise;
String 		_exerciseBusinessCenters;
String 		_exerciseBusinessDayConvention;
String 		_exerciseFrequency;
Date 		_expirationDate;
String 		_maxNoticeCutOff;
String 		_minNoticeCutOff;
int 		_minNoticeDays;
String 		_noticeBusDayConvention;
String 		_noticeBusinessCenters;
String 		_noticeDayConvention;
};

}

#endif // end of RIGHTTOTERMINATE_H
