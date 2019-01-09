#include "calendarUtil.h"
#include <iostream>
#include <fstream>
#include "simpleCalendar.h"
#include "compositeCalendar.h"


namespace IRDConnect {


static std::list<SimpleCalendar *>  calendarList ;

Calendar * CalendarUtil::getCalendar( const std::string & holidayCd ) 
{
         static bool initialized = false ; 
         if ( !initialized ) 
         {
              readCalendars () ;
              initialized = true ; 
         }
         std::list<SimpleCalendar *>::const_iterator calIter = calendarList.begin () ;
         for (; calIter != calendarList.end() ; ++calIter)
             if ( (*calIter)->getHolidayCd () == holidayCd ) 
                 return *calIter ; 
         return 0 ;
}
Calendar * CalendarUtil::getCalendar ( const std::set<std::string> & holidayCdSet )
{
         CompositeCalendar * c  = new CompositeCalendar ( ) ;
         std::set<std::string>::const_iterator iter = holidayCdSet.begin () ;
         
         for ( ; iter != holidayCdSet.end () ; ++iter ) 
         {
             c->add( getCalendar ( *iter )) ;
         }
         return c ; 
}
      
void CalendarUtil::readCalendars () 
{  
     SimpleCalendar * sc; /* = new SimpleCalendar ( "LON" ) ;

    sc->addWeekend ( Sunday ) ;
  sc->addWeekend ( Saturday ) ;

     sc->addHoliday ( Date (01,01 ,2010) ) ;
  //   sc->addHoliday ( Date (15,10 ,2010) ) ;
     sc->addHoliday ( Date (27,12 ,2010) ) ;
     sc->addHoliday ( Date (28,12 ,2010) ) ;
     sc->addHoliday ( Date (03,01 ,2011) ) ;
     sc->addHoliday ( Date (22,04 ,2011) ) ;
     sc->addHoliday ( Date (25,04 ,2011) ) ;
     sc->addHoliday ( Date (02,05 ,2011) ) ;
     sc->addHoliday ( Date (30,05 ,2011) ) ;
     sc->addHoliday ( Date (29,8,2011) ) ;
     sc->addHoliday ( Date (26,12 ,2011) ) ;
     sc->addHoliday ( Date (27,12 ,2011) ) ;
     sc->addHoliday ( Date (02,01 ,2012) ) ;
     sc->addHoliday ( Date (06,04 ,2012) ) ;
     sc->addHoliday ( Date (9,04 ,2012) ) ;
     sc->addHoliday ( Date (7,05 ,2012) ) ;
     sc->addHoliday ( Date (28,05 ,2012) ) ;
     sc->addHoliday ( Date (27,8 ,2012) ) ;
     sc->addHoliday ( Date (25,12 ,2012) ) ;
     sc->addHoliday ( Date (26,12 ,2012) ) ;

     sc->addHoliday ( Date (17,04 ,2017) ) ;
     sc->addHoliday ( Date (15,04 ,2022) ) ;
     sc->addHoliday ( Date (18,04 ,2022) ) ;
     
     calendarList.push_back ( sc ) ;
     
     sc = new SimpleCalendar ( "ABU" ) ; 
    
     sc->addWeekend ( 5 ) ; 
     sc->addHoliday ( Date (02,Jan ,2011) ) ;
     sc->addHoliday ( Date (26,Dec ,2011) ) ;
     
     calendarList.push_back ( sc ) ;

*/
 	ifstream hols("/home/vishist/hols.txt", ios::out );

 	string hCode;
 	string  hDate;
 	string  prevHol("");

 	while ( hols >> hCode && hols>>hDate )
 	{

 		if ( prevHol != hCode && prevHol != "" )
				 calendarList.push_back ( sc ) ;

 		if ( prevHol != hCode )
 		{

 	 			sc = new SimpleCalendar ( hCode) ;
 	 		    sc->addWeekend ( Sunday ) ;
 	 		    sc->addWeekend ( Saturday ) ;
 	 		    prevHol = hCode;
 		}

 	 	sc->addHoliday ( Date ( hDate.c_str(), "d/m/Y") ) ;

   		//cout << "values are : " << prevHol << ":" << hCode << ":" << hDate << Date( hDate.c_str(), "d/m/Y") << endl;
 	}
	 calendarList.push_back ( sc ) ;


}
}
