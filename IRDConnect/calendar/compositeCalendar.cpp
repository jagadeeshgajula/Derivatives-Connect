#include "compositeCalendar.h" 


namespace IRDConnect {


CompositeCalendar::CompositeCalendar() 
{
    
}

CompositeCalendar::CompositeCalendar( const CompositeCalendar & compositeCal ) 
{
    calendarSet_ = compositeCal.calendarSet_ ;
}

CompositeCalendar::~CompositeCalendar()
{   
}

CompositeCalendar &
CompositeCalendar::operator = ( const CompositeCalendar & compositeCal )
{
    if ( *this != compositeCal ) 
        calendarSet_ = compositeCal.calendarSet_ ;
        
    return *this;
}

const Calendar *
CompositeCalendar::add( const Calendar * cal )
{
    if ( cal ) 
    {
        calendarSet_.insert(cal) ;
    }

    return cal;
}
const CompositeCalendar &
CompositeCalendar::add( const CompositeCalendar & compositeCal )
{
    std::set<const Calendar *>::const_iterator iter = calendarSet_.begin() ; 
    for ( ; iter != calendarSet_.end(); ++iter)
        add( *iter ) ; 
    return compositeCal;
}

const Calendar *
CompositeCalendar::remove( const Calendar * cal )
{
    if ( cal ) {

        calendarSet_.erase( cal ) ;
        return cal;
    }

    return 0;
}

void
CompositeCalendar::clear()
{
   calendarSet_.clear() ;
}

unsigned int
CompositeCalendar::length() const
{
    unsigned int length = calendarSet_.size() ;
    return length;
}

int
CompositeCalendar::operator == ( const CompositeCalendar & scl ) const
{
    return 1;
}

int
CompositeCalendar::operator != ( const CompositeCalendar & scl ) const
{
    return !operator == ( scl );
}

bool CompositeCalendar::isBusDay (const Date & d ) const
{
    std::set<const Calendar *>::const_iterator iter = calendarSet_.begin() ; 
    for ( ; iter != calendarSet_.end(); ++iter)
        if ( !(*iter)->isBusDay( d ) ) 
            return false ; 
    return true ;
}

std::string  CompositeCalendar::getName () const
{
    std::string name ;
    std::set<const Calendar *>::const_iterator iter = calendarSet_.begin() ; 
    
    for ( int i=0; iter != calendarSet_.end(); ++iter,++i)
    {
        if ( i != 0 )
           name += ","  ; 
        
        name += (*iter)->getName ();
         
            
    }
    return name;
        
}

}
