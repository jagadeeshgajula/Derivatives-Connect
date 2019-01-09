#ifndef IDS_SIMPLE_CALENDAR_H
#define IDS_SIMPLE_CALENDAR_H 

#include "calendar.h"
#include<set>

using namespace std;
using namespace IRDConnect;

namespace IRDConnect {


class SimpleCalendar : public Calendar {

    // SimpleCalendar represents a holiday Schedule for one Location
public:
    const std::string & getHolidayCd() const;
    virtual bool isBusDay ( const Date & d ) const;
    virtual std::string  getName () const { return getHolidayCd ( ); }
   

protected:
  //  friend class                    SimpleCalendarList;


private:
    std::string holidayCd_ ;
    std::set<Date> holidaySet_ ;
    std::set<short> weekendSet_ ; 

public : 
    SimpleCalendar( const std::string & holidayCd );
    void addWeekend ( const short & wkd ) ;
    void  addHoliday( const Date & holiday );
    virtual ~SimpleCalendar();
private :
    // No copying ...
    SimpleCalendar( const SimpleCalendar & );
    void operator = ( const SimpleCalendar & );
 };

}
#endif
