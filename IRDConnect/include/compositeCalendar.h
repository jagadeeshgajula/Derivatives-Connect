#ifndef IDS_COMPOSITE_CALENDAR_H
#define IDS_COMPOSITE_CALENDAR_H 

#include "calendar.h"
#include<set>
using namespace std;
using namespace IRDConnect;

namespace IRDConnect {


class CompositeCalendar : public Calendar { 

private:
    std::set<const Calendar *> calendarSet_ ;
public:

    CompositeCalendar();
    CompositeCalendar( const CompositeCalendar & compositeCal );
    virtual ~CompositeCalendar();
    CompositeCalendar & operator = ( const CompositeCalendar & compositeCal );
    virtual std::string  getName () const ; 
    // Conditional operators test if 'scl' contains the same/different
    // 'SimpleCalendar's as '*this'

    int operator == ( const CompositeCalendar & scl ) const;
    int operator != ( const CompositeCalendar & scl ) const;
    const Calendar            * add    ( const Calendar * sc ) ;
    const CompositeCalendar    & add ( const CompositeCalendar & scl ) ;

    // Remove 'sc' from the list.  Return 'sc' on success or zero if
    // 'sc' is not in the list.

    const Calendar            * remove ( const Calendar * sc ) ;
 
    // Remove all contained calendars.
    void                            clear () ;

    // Return number of contained calendars.
    unsigned int                    length () const ;
    
     virtual bool isBusDay ( const Date & d ) const;
};

}
#endif
