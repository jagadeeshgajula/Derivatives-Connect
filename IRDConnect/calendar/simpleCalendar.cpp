#include "simpleCalendar.h"

namespace IRDConnect {

SimpleCalendar::SimpleCalendar(
const std::string & holidayCd ) :
    holidayCd_(holidayCd)
{
}

SimpleCalendar::~SimpleCalendar()
{
                                 
}

const std::string  &
SimpleCalendar::getHolidayCd() const
{
    return holidayCd_;
}

void 
SimpleCalendar::addHoliday( const Date & holiday )
{
    holidaySet_.insert ( holiday ) ;
}

void 
SimpleCalendar::addWeekend( const short & wkd )
{
    weekendSet_.insert ( wkd ) ;
}

bool SimpleCalendar::isBusDay (const Date & d ) const
{
   //  std::cout << d << std::endl ; 
   //  std::cout << d.day_of_week() << std::endl ;
   //  std::cout << ( d.day_of_week() == 7 ) << std::endl ;
    // std::cout << gregorian_calendar::day_of_week ( d ) << std::endl ; 
    
     // first check if the date is a weekend. if it is a weekend return false 
     std::set<short>::const_iterator weekendsIter = weekendSet_.find ( d.weekday() ) ;
     if ( weekendsIter != weekendSet_.end() ) 
         return false ;
     
     // comes here only if the date is not a weekend. check if the date 
     // is a holiday and return the correct value 
     std::set<Date>::const_iterator holidayIter = holidaySet_.find ( d ) ;
     if ( holidayIter == holidaySet_.end() ) 
         return true ;
     else 
         return false ; 
} 

}
