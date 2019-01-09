/*
 * DayCountConv.cpp
 *
 *  Created on: 26-Aug-2010
 *      Author: vishist
 */

#include "dayCountConv.h"
#include "types.h"
#include <assert.h>
#include "calendarUtil.h"

namespace IRDConnect {

using namespace std;


DayCountConv::DayCountConv() {
	name_ = "_actAct";

}

DayCountConv::~DayCountConv() {
	// do nothing
}

DayCountConv::DayCountConv ( const std::string  & dayCountConv)
{
	name_ = dayCountConv;
}

void DayCountConv::setCalendar(std::string cal)
{
	_calendar.insert(cal);
}

void DayCountConv::setCalendar( std::set < std::string > cal)
{
	_calendar = cal;
}

ActAct::ActAct():DayCountConv("_actAct")
{
	// do nothing
}

ActAct::ActAct(const std::string &dayCountConv)
:DayCountConv(dayCountConv)
{
//do nothing
}

ActAct::~ActAct()
{
}

double
ActAct::getDiffInDay( const Date & startDate, const Date & endDate ) const
{


    if (startDate == endDate)  return 0.0;

    int sign = startDate<endDate ? 1 : -1;


    const Date & firstDate(sign>0 ? startDate : endDate);
    const Date & secondDate(sign>0 ? endDate : startDate);

    return (double) (secondDate.serialNumber() - firstDate.serialNumber()) ;

}

double
ActAct::getPeriodFraction( const Date & actualStart, const Date & actualEnd,
                           const Date & psuedoStart, const Date & psuedoEnd,
                           const int, const bool ) const
{
   // test for division by zero
   double denominator = getDiffInDay(psuedoStart, psuedoEnd);
   denominator = denominator ? denominator : 1.0 ;
   return getDiffInDay(actualStart, actualEnd) / denominator;
}

double
ActAct::getFraction( const Date startDate, const Date endDate, const bool,
                        const bool, const int ) const
{


    double value;

    if (startDate == endDate)
        return 0;

    int sign = startDate<endDate ? 1 : -1;

    const Date & firstDate = sign > 0 ? startDate : endDate;
    const Date & secondDate = sign > 0 ? endDate : startDate;

    // are the dates in the same year?
    if (firstDate.year() == secondDate.year()) {
        value = (double)(secondDate.serialNumber() - firstDate.serialNumber());
        value /= (double)(firstDate.isLeap(firstDate.year())?366:365);
    } else {
        Date endYr1((Day)1,January,firstDate.year() + 1);
        value =
            ((double)(endYr1.serialNumber() - firstDate.serialNumber()))
            / (double)(firstDate.isLeap(firstDate.year())?366:365);


        value += (double)(secondDate.year()-firstDate.year()-1);


        Date startYr2((Day)1,January,secondDate.year());
        value +=
            ((double)(secondDate.serialNumber() - startYr2.serialNumber()))
            / (double)(secondDate.isLeap(secondDate.year())?366:365);
    }

    return sign * value;
}

double
ActAct::getDayInYear( Year year) const
{
    Date firstDate( 31,December,year);
    return firstDate.dayOfYear();
}

int
ActAct::includeFeb29( const Date & start, const Date & end ) const
{
    if ( start.isLeap(start.year()) ) {
       Date feb29(start.year(), Month(2), Day(29));
       if (  start < feb29 ) {
          return 1;
       }
    }
    if ( end.isLeap(end.year()) ) {
       Date feb29(end.year(), Month(2), Day(29));
       if ( feb29 <= end ) {
          return 1;
       }
    }
    return 0;
}

//----------------------------------------------------------------------

ActActISMA251::ActActISMA251() :
    ActAct( "_actActISMA251" )
{
}

ActActISMA251::~ActActISMA251()
{
}

double
ActActISMA251::getFraction(
    const Date firstDate,
    const Date secondDate,
    const bool finalPeriod ,
    const bool stubPeriod ,
    const int numPeriodPerYear ) const
{

    if (!numPeriodPerYear)
        return 0;

    if (!stubPeriod)
        return (1.0 / numPeriodPerYear) ;


    // Initial and final irregular period calculations

    int monthsInPeriod = 12 / numPeriodPerYear;
    Date tmpStart;
    Date tmpEnd;
    double ret = 0.0;
    double d = 0.0;
    Date dt1 = tmpStart;
    Date dt2 = tmpEnd;

    if (finalPeriod)        // Back stub calculation
    {

        tmpStart =  firstDate;
        tmpEnd = tmpStart;
        tmpEnd += Period(monthsInPeriod,Months);


        while (( tmpEnd < secondDate) )
        {
            ret += 1.0 / numPeriodPerYear;
            tmpStart = tmpEnd;
            //add_month mf(1);
            //tmpEnd = tmpEnd + mf.get_offset(d);
            tmpEnd += Period(monthsInPeriod,Months);

        }
        dt1 = tmpStart;
        dt2 = tmpEnd;

        d = getDiffInDay(dt1, secondDate);
        d /= (getDiffInDay (dt1, dt2) * numPeriodPerYear);
        ret += d;

    }
    else                        // Front stub calculation
    {
        monthsInPeriod *= -1;
        tmpEnd = (Date) secondDate;
        tmpStart = tmpEnd;
        tmpStart += Period(monthsInPeriod, Months);

        while ( tmpStart > firstDate )
        {
            ret += 1.0 / numPeriodPerYear;
            tmpEnd = tmpStart;
            tmpStart += Period(monthsInPeriod, Months);
        }
        dt1 = tmpStart;
        dt2 = tmpEnd;

        d = getDiffInDay(firstDate, dt2);
        d /= (getDiffInDay (dt1, dt2) * numPeriodPerYear);
        ret += d;

    }

    return ret;
}


double
ActActISMA251::getPeriodFraction(
                  const Date & actualStart,
                  const Date & actualEnd,
                  const Date & psuedoStart,
                  const Date & psuedoEnd,
                  const int numPeriodPerYear, const bool ) const
{
   if ( !numPeriodPerYear ) return 0.0;

   double ret = 0.0;
   double d = 0.0;
   double denominator = getDiffInDay(psuedoStart, psuedoEnd);
   denominator = denominator ? denominator : 1.0;

   if (   psuedoStart <  actualStart &&
         psuedoEnd   <   actualEnd ) {

        d = getDiffInDay(actualStart, psuedoEnd);
        ret = (d / denominator) * ( 1.0 + 1.0 / numPeriodPerYear);
   }
   else if ( psuedoStart >   actualStart &&
               psuedoEnd   >   actualEnd ) {

        d = getDiffInDay(psuedoStart, actualEnd);
        ret = ( 1.0 + 1.0 / numPeriodPerYear ) * ( d / denominator );
   } else {

        d = getDiffInDay(actualStart, actualEnd);
        ret = (d / denominator ) * ( 1.0 / numPeriodPerYear );
   }

   return ret;
}

Act365F::Act365F() :
    DayCountConv("_act365F" )

{
}

Act365F::~Act365F()
{
}

double
Act365F::getFraction( const Date startDate, const Date endDate, const bool,
                        const bool, const int ) const
{
    double value = (double) (endDate.serialNumber() - startDate.serialNumber());
    value /= 365.0;
    return value;
}


double
Act365F::getPeriodFraction( const Date & actualStart,
                            const Date & actualEnd,
                            const Date & psuedoStart,
                            const Date & psuedoEnd,
                            const int numOfPeriodPerYear,
                            const bool ) const
{
   if ( numOfPeriodPerYear == 0 )
      return 0.0;

   double result = getFraction(actualStart, actualEnd)
                   * numOfPeriodPerYear;


   if ( result > 1.0 ) {
      result  = psuedoEnd.serialNumber()   - actualEnd.serialNumber();
      result -= psuedoStart.serialNumber() - actualStart.serialNumber();
      if ( result <= 2.0 ) {   // make sure do not over-adjusted, kludgy
         double tmp = 365.0 / numOfPeriodPerYear;
         result = ( tmp - result ) / tmp;
      }
      else
         result = 0.0;
   }
   return result;
}


double
Act365F::getDayInYear( Year year) const
{
   return 365.0;
}

//----------------------------------------------------------------------

Act360::Act360() :
    DayCountConv( "_act360" )
{
}

Act360::~Act360()
{
}

double
Act360::getFraction( const Date startDate, const Date endDate, const bool,
                        const bool, const int ) const
{
    double value = (double) (endDate.serialNumber() - startDate.serialNumber());
    value /= 360.0;
    return value;
}

double
Act360::getPeriodFraction( const Date & actualStart, const Date & actualEnd,
                           const Date & , const Date & ,
                           const int numOfPeriodPerYear, const bool ) const
{
   return getFraction(actualStart, actualEnd) * numOfPeriodPerYear;
}

double
Act360::getDayInYear( Year year ) const
{
   return 360.0;
}

Bus360::Bus360(): DayCountConv ( "_bus360" )
{
}

Bus360::~Bus360 ()
{
}

int Bus360::getDay(const Date& startDate, const Date& endDate) const
{
    int value = 0;

    if (startDate == endDate)
        return 0;

    int sign = startDate < endDate ? 1 : -1;

    Date firstDate = sign > 0 ? startDate : endDate;
    const Date& secondDate = sign > 0 ? endDate : startDate;


    // if ( getenv("IRD_DEBUG") == std::string("Yes"))
    	  logFile << "start : end date " << firstDate << ":" << secondDate << endl;

    while ( firstDate < secondDate )
    {

        if (( CalendarUtil::getCalendar( _calendar ))->isBusDay(firstDate) )
        {
            ++value ;

            // if ( getenv("IRD_DEBUG") == std::string("Yes"))
            	  logFile << "date and count " << value << " : " << firstDate << endl;
        }


        ++firstDate ;
    }

    logFile << "total days " << value << endl;

    return value * sign;
}

double
Bus360::getDayInYear( Year year) const
{
   return 360.0;
}


Bus252::Bus252 ()
    : DayCountConv ("_bus252" )
{
}

Bus252::~Bus252 ()
{
}

int Bus252::getDay ( const Date & startDate,
                      const Date & endDate ) const
{
    int value = 0;

    if ( startDate == endDate )
         return 0;

    int sign = startDate < endDate ? 1 : -1;

    Date firstDate = sign > 0 ? startDate : endDate;

    const Date & secondDate = sign > 0 ? endDate : startDate;


    while ( firstDate < secondDate )
    {
    	  if ( CalendarUtil::getCalendar(_calendar)->isBusDay(firstDate) )
            value++ ;

        ++firstDate ;
    }

    return value * sign;
}

double
Bus252::getDayInYear ( Year year) const
{
   return 252.0;
}


Dcc30360Based::Dcc30360Based( const std::string & name ) :
    DayCountConv( name )
{
}

Dcc30360Based::~Dcc30360Based()
{
}

double
Dcc30360Based::getFraction(
const Date      startDate,
const Date      endDate,
const bool          finalPeriod,
const bool,
const int ) const

{
    if ( startDate == endDate )
        return 0;

    const int sign = startDate < endDate ? 1 : -1;

    const Date & firstDate = sign > 0 ? startDate : endDate;
    const Date & secondDate = sign > 0 ? endDate : startDate;

    assert( firstDate < secondDate );

    double value = 360.0 * (secondDate.year() - firstDate.year());
    value += 30.0 * (secondDate.month() - firstDate.month());
    value += getDayCountForGivenDates( firstDate, secondDate, finalPeriod );

    value /= 360.0;

    return sign * value;
}

double
Dcc30360Based::getPeriodFraction(
const Date      & actualStart,
const Date      & actualEnd,
const Date      & /** psuedoStart **/,
const Date      & /** psuedoEnd **/,
const int           numOfPeriodPerYear,
const bool          finalPeriod ) const
{
   return getFraction( actualStart, actualEnd, finalPeriod ) * numOfPeriodPerYear;
}

int
Dcc30360Based::isLastDayOfFebruary( const Date & d )
{
    if ( February == d.month() )
        if ( d.dayOfMonth() == d.endOfMonth(d).dayOfMonth())
            return 1;

    return 0;
}

inline Day
Dcc30360Based::min( Day firstDate, Day secondDate )
{
    return firstDate < secondDate ? firstDate : secondDate;
}


double
Dcc30360Based::getDayInYear( Year year ) const
{
   return 360.0;
}

//----------------------------------------------------------------------



Dcc30S360::Dcc30S360() :
    Dcc30360Based( "_thirtyS360" )
{
}

Dcc30S360::~Dcc30S360()
{
}


double
Dcc30S360::getDayCountForGivenDates( const Date & startDate, const Date & endDate, const bool finalPeriod) const
{
    assert( startDate < endDate );
    Day firstDate, secondDate;

        firstDate = min( startDate.dayOfMonth(), 30 );
        secondDate = min( endDate.dayOfMonth(), 30 );

    return secondDate - firstDate;
}


//----------------------------------------------------------------------


Dcc30I360::Dcc30I360() :
    Dcc30360Based( "_thirtyI360" )
{
}

Dcc30I360::~Dcc30I360()
{
}

double
Dcc30I360::getDayCountForGivenDates( const Date & startDate, const Date & endDate, const bool ) const
{
    assert( startDate < endDate );

    const Day firstDate = min( startDate.dayOfMonth(), 30 );
    const Day secondDate = (endDate.dayOfMonth() == 31) && (firstDate == 30) ? 30 : endDate.dayOfMonth();

    return secondDate - firstDate;
}


//----------------------------------------------------------------------


Dcc30B360::Dcc30B360() :
    Dcc30360Based( "_thirtyB360")
{
}

Dcc30B360::~Dcc30B360()
{
}

double
Dcc30B360::getDayCountForGivenDates( const Date & startDate, const Date & endDate, const bool ) const
{
    assert( startDate < endDate );

    const Day firstDate = isLastDayOfFebruary( startDate ) ? 30 : min( startDate.dayOfMonth(), 30 );
    const Day secondDate = (endDate.dayOfMonth() == 31) && (firstDate == 30) ? 30 : endDate.dayOfMonth();

    return secondDate - firstDate;
}



Dcc30E360::Dcc30E360() :
    Dcc30360Based("_thirtyE360" )
{
}

Dcc30E360::~Dcc30E360()
{
}

double
Dcc30E360::getDayCountForGivenDates( const Date  & startDate, const Date  & endDate, const bool finalPeriod ) const
{
    assert( startDate < endDate );
    Day firstDate, secondDate;

        firstDate = isLastDayOfFebruary( startDate ) ? 30 : min( startDate.dayOfMonth(), 30 );
        secondDate = (isLastDayOfFebruary( endDate ) && !finalPeriod) ? 30 : min( endDate.dayOfMonth(), 30 );


    return secondDate - firstDate;
}

Dcc30E360last::Dcc30E360last() :
    Dcc30360Based( "_thirtyE360last")
{
}

Dcc30E360last::~Dcc30E360last()
{
}

double
Dcc30E360last::getDayCountForGivenDates( const Date  & startDate, const Date  & endDate, const bool finalPeriod ) const
{
    assert( startDate < endDate );

    const Day firstDate = isLastDayOfFebruary( startDate ) ? 30 : min( startDate.dayOfMonth(), 30 );
    const Day secondDate = min( endDate.dayOfMonth(), 30 );

    return secondDate - firstDate;
}

//----------------------------------------------------------------------

// Actual/365.25 is _not_ an ISDA standard, but may be used internally.



Act36525::Act36525() :
    DayCountConv( "_act36525" )
{
}

Act36525::~Act36525()
{
}

double
Act36525::getFraction( const Date startDate, const Date endDate, const bool,
                        const bool, const int ) const
{
    double value = (double)(endDate.serialNumber() - startDate.serialNumber());
    value /= 365.25;
    return value;
}

double
Act36525::getPeriodFraction( const Date & actualStart, const Date & actualEnd,
                             const Date & , const Date & ,
                             const int numOfPeriodPerYear, const bool ) const
{
   return getFraction(actualStart, actualEnd) * numOfPeriodPerYear;
}

double
Act36525::getDayInYear( Year year) const
{
   return 365.25;
}

EqualPayment::EqualPayment() :
    DayCountConv( "_equalPayment" )
{
}

EqualPayment::~EqualPayment()
{
}

double EqualPayment::getFraction( const Date firstDate, const Date secondDate, const bool final,
                                const bool stub, const int freq ) const
{
	if ( stub )
	{
		return DayCountConv::find("_thirtyI360")->getFraction(firstDate,secondDate);
	}
	else
		return 1.0/freq;
}

double
EqualPayment::getPeriodFraction(
const Date      & actualStart,
const Date      & actualEnd,
const Date      & psuedoStart,
const Date      & psuedoEnd,
const int           numOfPeriodPerYear,
const bool                  ) const
{
          return DayCountConv::find("_thirtyI360")->getPeriodFraction( actualStart, actualEnd,
                                                     psuedoStart, psuedoEnd,
                                                     numOfPeriodPerYear );
}

double EqualPayment::getDayInYear( Year year ) const
{
   return DayCountConv::find("_thirtyI360")->getDayInYear(year);
}


FullPayment::FullPayment() :
    DayCountConv( "_fullPayment" )
{
}

FullPayment::~FullPayment()
{
}

double
FullPayment::getPeriodFraction( const Date & actualStart,
                            const Date & actualEnd,
                            const Date & psuedoStart,
                            const Date & psuedoEnd,
                            const int numOfPeriodPerYear,
                            const bool ) const
{
    return 1/numOfPeriodPerYear;
}

double
FullPayment::getFraction( const Date firstDate, const Date secondDate, const bool,
                                const bool, const int numPerPeriod ) const
{
    return 1.0/numPerPeriod;
}

double
FullPayment::getDayInYear( Year year ) const
{
    return DayCountConv::find("_act365F")->getDayInYear( year );
}


DayCountConv *
DayCountConv::find( const std::string & name )
{
    DccMap::iterator it = getDccMap().find( name ) ;
    if ( it != getDccMap().end() )
        return it->second ;
	return 0;
}

std::map<std::string, DayCountConv *> & DayCountConv::getDccMap ()

{
     static DccMap dccMap ;
     static bool inited = false ;
     if ( !inited ) {
         dccMap.insert ( DccMap::value_type("_actAct", new ActAct )) ;
         dccMap.insert ( DccMap::value_type("_actActISMA251", new ActActISMA251 )) ;
         dccMap.insert ( DccMap::value_type("_act365F", new Act365F )) ;
         dccMap.insert ( DccMap::value_type("_act360", new Act360 )) ;
         dccMap.insert ( DccMap::value_type("_thirtyE360", new Dcc30E360 )) ;
         dccMap.insert ( DccMap::value_type("_thirtyI360", new Dcc30I360 )) ;
         dccMap.insert ( DccMap::value_type("_thirtyB360", new Dcc30B360 )) ;
         dccMap.insert ( DccMap::value_type("_thirtyS360", new Dcc30S360 )) ;
         dccMap.insert ( DccMap::value_type("_thirtyE360last", new Dcc30E360last )) ;
         dccMap.insert ( DccMap::value_type("_equalPayment", new EqualPayment )) ;
         dccMap.insert ( DccMap::value_type("_act36525", new Act36525 )) ;
         dccMap.insert ( DccMap::value_type("_bus360", new Bus360 )) ;
         dccMap.insert ( DccMap::value_type("_bus252", new Bus252 )) ;
         dccMap.insert ( DccMap::value_type("_fullPayment", new FullPayment )) ;

         inited = true ;
     }
     return dccMap ;
}

}

// End-Of-File ---------------------------------------------------------

