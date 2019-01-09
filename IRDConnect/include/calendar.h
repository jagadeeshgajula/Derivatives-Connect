#ifndef CALENDAR_H
#define CALENDAR_H
#include "date.h"
#include<string>

using namespace std;
using namespace IRDConnect;

namespace IRDConnect {


class Calendar { 
public : 
       virtual ~Calendar () ; 

       // Returns true if 'date' is a business day.
       virtual bool isBusDay ( const Date & d ) const;
       bool isBusDay ( const Date    & d, 
                       const Calendar & secondCalendar ) const; 

       // Returns the first day after 'date' which is a business day.
       Date   nextBusDay ( const Date & d ) const ;
       Date   nextBusDay ( const Date & d, 
                                             const Calendar& secondCalendar ) const;

       // Returns the first day before 'date' which is a business day.
       Date   prevBusDay ( const Date & d ) const ;
       Date   prevBusDay ( const Date & d, 
                                             const Calendar & secondCalendar ) const ;
       // If 'numBusDay' > 0 then 'addBusDay()' returns the 'numBusDay'th
       // _after_ 'date'.  If 'numBusDay' < 0 then 'addBusDay()' returns
       // the 'numBusDay'th _before_ 'date'.  Note that the method doesn't
       // care if 'date' is a business day.

       Date   addBusDay ( const Date & d, 
                          int numBusDay ) const ;

       Date   addBusDay ( const Date & d, 
                          int numBusDay, 
                          const Calendar & secondCalendar ) const ;

       // increments date to next business day 
       void   setToNextBusDay ( Date & d ) const ;

       // decrements date to previous business day 
       void   setToPrevBusDay ( Date & d ) const ;

       void   addBusDayToDate ( Date & d, 
                                int numBusDay ) const ;

       void   addBusDayToDate ( Date & d, 
                                int numBusDay, 
                                const Calendar & secondCalendar ) const ;

       // Returns the number of buisness days between 'd1' and 'd2'.
       // -- what happens with d1 < d2, d1 == d2 & d1 < d2

       int    busDayDiff ( const Date & d1, 
                           const Date & d2 ) const ; 
       Calendar();
       virtual std::string  getName () const { return "S";}  
protected:
     


private:

        // No copying ...
        Calendar( const Calendar & );
        void operator = ( const Calendar & );
};

}

#endif
