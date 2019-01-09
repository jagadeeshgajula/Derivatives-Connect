#ifndef MONEYMKT_H_
#define MONEYMKT_H_

#include <iostream>
#include "date.h"
#include "dayCountConv.h"
#include "currency.h"

namespace IRDConnect {

// Foward Declaration
class Currency;
//class MktType;
//class RTQuote;
//class SpreadOperation;
//class TermStructIR;

//class InstrumentTypeCd;
//class Quote;

class Moneymkt {

public:

   Moneymkt( const Moneymkt & m );
   Moneymkt & operator = ( const Moneymkt & m );

   // --- Constructors and Destructor ---

   // ctor for interest being specified as a rate
   Moneymkt(
        const std::string &     id,
 //       const InstrumentTypeCd * instrTypeCd,
        const Currency *     ccy,
        int                  settlementDateOffset,
        const Period &       maturityDateOffset,
        double               rate,
        const BusDayConv *   bdc, 
        const DayCountConv * dcc,
        const Calendar *     calendar,
        Frequency            compFreq
   );

   virtual ~Moneymkt();

     // --- Accessor Methods ---
   const std::string &  getId () const { return id_; };
   const Currency *     getCurrency() const;
   int                  getSettlementDateOffset() const;
   Period               getValueDayLag () const ;
   Period               getMaturityDateOffset() const;
   double               getRate() const;
   double               getInterestAmt() const;
   const DayCountConv * getDayCountConv() const;
   const BusDayConv *   getBusDayConv() const;

   void setCurrency(const Currency * c);
   void setSettlementDateOffset(const int t);
   void setMaturityDateOffset(const Period & t);
   void setRate(const double & r);
   void setDayCountConv(const DayCountConv * d);
   void setBusDayConv(const BusDayConv * b);
   void setCalendar(const Calendar * cal);

   Date   getSettlementDate( const Date & d ) const;
   Date   getQuoteDate( const Date & settleDate ) const;
   Date   getMaturityDate( const Date & d ) const;
   double getSettlementAmt( const Date & d ) const;
   double getMaturityAmt( const Date & d ) const;
   double getInterest( const Date & d ) const;
   const Calendar *  getCalendar() const;
   Date   getMaturityDateAsOfSettlementCalendar( const Date & d, const Calendar & settleCalList, const BusDayConv * bdc ) const;

 //  const YieldType * getYieldType() const;
//   void setYieldType( const YieldType * y );
//   const Frequency * getCompFreq() const;
//   void setCompFreq( const Frequency * f );
//   double getRateValue() const;
//   void setRateValue( const double v );

//   virtual const TermStructIR * getDiscountTSIR() const;
//   Tenor getValueDayLag() const;

   // This is for TermStruct only. 
   virtual double getFwdAmount( const Date & date, const double & quote ) const;

   virtual bool validateQuote(double value) const;

//   virtual void getProjectDates(const Date & quoteDate,
//								Date & effDate, Date & matDate) const;

protected:

   std::string       id_ ;
   const Currency *     _ccy;                  // the currency of the settlement and maturity amount
   int                  _settlementDateOffset; // settlement date offset from trade day (in units of business days)
   Period                _maturityDateOffset;   // maturity date offset from settlement day
   double                 _rate;                 // interest rate relating the settlement
                                                //    and maturity amount
   const BusDayConv *   _bdc;                  // business day convention
   const DayCountConv * _dcc ;
   const Calendar   * _calendar;        // calendar
   Frequency         compFreq_;

};

inline const Currency *     Moneymkt::getCurrency() const
   { return _ccy; }

inline int                  Moneymkt::getSettlementDateOffset() const
   { return _settlementDateOffset; }

inline Period                Moneymkt::getMaturityDateOffset() const
   { return _maturityDateOffset; }

inline double                 Moneymkt::getRate() const
   { return _rate; }

inline const BusDayConv *   Moneymkt::getBusDayConv() const
   { return _bdc; }

inline const DayCountConv *   Moneymkt::getDayCountConv() const
   { return _dcc; }

inline const Calendar *     Moneymkt::getCalendar() const
   { return _calendar; }

/*
inline const YieldType *    Moneymkt::getYieldType() const
   { return _rate.getYieldType(); }
*/

// inline void Moneymkt::setType(const MoneymktType *t)           { _type = t; }
inline void Moneymkt::setCurrency(const Currency * c)
   { _ccy = c; }

inline void Moneymkt::setSettlementDateOffset(const int d)
   { _settlementDateOffset = d; }

inline void Moneymkt::setMaturityDateOffset(const Period & d)
   { _maturityDateOffset = d; }

inline void Moneymkt::setRate(const double & r)
   { _rate = r;  }

inline void Moneymkt::setBusDayConv(const BusDayConv * b)
   { _bdc = b; }

inline void Moneymkt::setDayCountConv(const DayCountConv * d)
   { _dcc = d; }

// Overloaded output operator
std::ostream & operator << ( std::ostream & os, const Moneymkt & mm );

}
#endif
