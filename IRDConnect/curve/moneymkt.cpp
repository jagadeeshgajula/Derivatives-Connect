/*
 * moneymkt.cpp
 *
 *  Created on: 24-Oct-2010
 *      Author: vishist
 */

#include "moneymkt.h"
#include <assert.h>
# include <iostream>
#include <map>
#include "frequency.h"
#include "timeUnit.h"
#include "dayCountConv.h"

#include <math.h>
typedef int RetCode;

using namespace std;


namespace IRDConnect {


//
// The Moneymkt class member function implementation
//

// --- Constructors and Destructor ---
Moneymkt::Moneymkt(
        const std::string&     id,
//        const InstrumentTypeCd * instrTypeCd,
        const Currency *     ccy,
        const int            settlementDateOffset,
        const Period &       maturityDateOffset,
        double               rate,
        const BusDayConv *   bdc,
        const DayCountConv * dcc,
        const Calendar * calendar,
        Frequency        compFreq
   )
   :  id_                   ( id ) ,
       _ccy                 ( ccy ),
       _settlementDateOffset( settlementDateOffset ),
       _maturityDateOffset  ( maturityDateOffset ),
       _rate                ( rate ),
       _bdc                 ( bdc ),
       _dcc                 ( dcc ),
       _calendar            ( calendar ),
       compFreq_            ( compFreq)

{
}


Moneymkt::~Moneymkt()
{

}

Moneymkt::Moneymkt( const Moneymkt & mm )
      : id_                 ( mm.id_ ),
       _ccy                 ( mm._ccy ),
       _settlementDateOffset( mm._settlementDateOffset ),
       _maturityDateOffset  ( mm._maturityDateOffset ),
       _rate                ( mm._rate ),
       _bdc                 ( mm._bdc ),
       _dcc                 ( mm._dcc ),
       _calendar            ( mm._calendar ),
       compFreq_            ( mm.compFreq_)
{
  //  _maturityDateOffset = Tenor( mm._maturityDateOffset.getAmount(),
  //                               mm._maturityDateOffset.getPeriod(),
  //                               &_calendar );
}


Moneymkt & Moneymkt::operator= ( const Moneymkt & mm )
{
    if ( this == &mm )
       return *this;
    id_                   = mm.id_; 
    _ccy                  = mm._ccy;
    _settlementDateOffset = mm._settlementDateOffset;
    _maturityDateOffset   = mm._maturityDateOffset;
    _rate                 = mm._rate;
    _bdc                  = mm._bdc;
    _dcc                  = mm._dcc ;
    _calendar             = mm._calendar;
    compFreq_             = mm.compFreq_;
  //  _maturityDateOffset = Tenor( mm._maturityDateOffset.getAmount(),
 //                                mm._maturityDateOffset.getPeriod(),
 //                                &_calendar );

    return *this;
}


// --- Accessor Methods ---
// defined as inline in moneymkt.h

Period
Moneymkt::getValueDayLag() const
{
   return Period( _settlementDateOffset, Days) ;
   // return Tenor ( _settlementDateOffset,
   //                Period::busdays,
   //                &_calendar );
}


void
Moneymkt::setCalendar(const Calendar * cal)
{
    _calendar = cal;
   // Tenor t( _maturityDateOffset.getAmount(),
   //          _maturityDateOffset.getPeriod(),
   //          &_calendar );
   // _maturityDateOffset = t;
}

/*void
Moneymkt::setCompFreq( const Frequency * f )
{

   double               value = _rate.getRate();
// const Frequency    * freq  = _rate.getCompFreq();
   const YieldType    * yield = _rate.getYieldType();
   const DayCountConv * dcc   = _rate.getDayCountConv();

   _rate = Rate( value, f, yield, dcc );

   return;
}
*/

/*
void
Moneymkt::setYieldType( const YieldType * y )
{

   double               value = _rate.getRate();
   const Frequency    * freq  = _rate.getCompFreq();
// const YieldType    * yield = _rate.getYieldType();
   const DayCountConv * dcc   = _rate.getDayCountConv();

   _rate = Rate( value, freq, y, dcc );

   return;
}


void
Moneymkt::setDayCountConv( const DayCountConv * d )
{

   double               value = _rate.getRate();
   const Frequency    * freq  = _rate.getCompFreq();
 //  const YieldType    * yield = _rate.getYieldType();
 const DayCountConv * dcc   = _rate.getDayCountConv();

  // _rate = Rate( value, freq, yield, d );

   return;
}


void
Moneymkt::setRateValue( const double v )
{

// double               value = _rate.getRate();
   const Frequency    * freq  = _rate.getCompFreq();
//   const YieldType    * yield = _rate.getYieldType();
   const DayCountConv * dcc   = _rate.getDayCountConv();

 //  _rate = Rate( v, freq, yield, dcc );

   return;
}
*/

Date
Moneymkt::getSettlementDate( const Date & d ) const
{

    Date settleDate( d );
    _calendar->addBusDayToDate( settleDate, _settlementDateOffset );

    return settleDate;
}

Date
Moneymkt::getQuoteDate( const Date & settleDate ) const
{

    Date quoteDate( settleDate );
    _calendar->addBusDayToDate( quoteDate, -1 * _settlementDateOffset );

    return quoteDate;
}


Date
Moneymkt::getMaturityDate( const Date & d ) const
{
	Date matureDate ;
    if ( _maturityDateOffset.units () == Days )
    	matureDate = _calendar->addBusDay ( getSettlementDate(d), _maturityDateOffset.length () ) ;
    else
        matureDate = getSettlementDate(d) + _maturityDateOffset;

    if ( _bdc )
    {
    	   matureDate =  _bdc->adjustToBusDay( matureDate, *_calendar ) ;
    }

    return matureDate;
}

// --- Analytic Functions ---


double
Moneymkt::getFwdAmount( const Date & d, const double & quote ) const
{
   double result = 0.0;

   Date settleDate = getSettlementDate( d );
   Date matureDate = getMaturityDate ( d ) ;
/*   Date matureDate = settleDate + getMaturityDateOffset();
   if ( _bdc )
      matureDate = ( _bdc->adjustToBusDay( matureDate, *_calendar ) );
*/

   double dcf = _dcc -> getFraction( settleDate, matureDate) ;
   //cout << settleDate <<"," << matureDate << "RATE = " << quote << "DCF = " << dcf << endl ;  // RAM - NO NEED TO PRINT

   if ( compFreq_ > 0 and compFreq_ <= 365 )
	   result =  pow( 1 + quote / compFreq_, compFreq_ * dcf ) ;
   else
       result = ( 1 + quote * dcf ) ;

   //return exp (_rate * dcf ) ;
   return result;
}



bool
Moneymkt::validateQuote(double quote) const
{
   //return (bool) (_isSpread ? true : (quote > 0.0));
   return (bool) true;
}

/*void
Moneymkt::getProjectDates(const Date & quoteDate, Date & effDate,
            Date & matDate) const
{
   effDate = getSettlementDate(quoteDate);
   matDate = getMaturityDate(quoteDate);
}
*/

}
