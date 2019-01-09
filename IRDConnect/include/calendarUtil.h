#ifndef CALENDAR_UTIL_H
#define CALENDAR_UTIL_H

#include "calendar.h"
#include <set>
#include <list>

using namespace std;
using namespace IRDConnect;

namespace IRDConnect {


class CalendarUtil { 
      
      public :
             static Calendar * getCalendar ( const std::string & holidayCd ) ;
             static Calendar * getCalendar ( const std::set<std::string> & holidayCdSet ) ;
      
      
      private : 
               
              static void readCalendars () ;
              
      
};



}


#endif
