/*
 * mmfuture.cpp
 *
 *  Created on: 02-Jan-2011
 *      Author: vishist
 */

#ifndef MMFUTURE_H
#   include "mmfuture.h"
#endif
namespace IRDConnect {
MMFuture::MMFuture ( const std::string &  id,
                 const Currency *   ccy,
                 const Date &       dDate,
                 const Date &       lastTD,
                 const Date &       expiryDate,
                 const Date &       endDate,
                 const Calendar *   cal,
                 const DayCountConv *   dcc,
                 const BusDayConv *   bdc,
                 double              rate)
    : id_(id), ccy_(ccy ), deliveryDate_(dDate),
            lastTradeDate_(lastTD), expiryDate_(expiryDate),
            endDate_(endDate), calendar_(cal), dcc_(dcc),
            bdc_(bdc), rate_(rate)
{   }


MMFuture::~MMFuture(){}


MMFuture::MMFuture( const MMFuture & mmfut )
   : id_(mmfut.id_), ccy_(mmfut.ccy_ ), deliveryDate_(mmfut.deliveryDate_),
     lastTradeDate_(mmfut.lastTradeDate_), expiryDate_(mmfut.expiryDate_),
     endDate_(mmfut.endDate_), calendar_(mmfut.calendar_), dcc_(mmfut.dcc_),
     bdc_(mmfut.bdc_), rate_(mmfut.rate_)
{ }

MMFuture & MMFuture::operator= ( const MMFuture & mmfut )
{
    if ( this == &mmfut )
       return *this;

    id_ = mmfut.id_;
    ccy_ = mmfut.ccy_;
    deliveryDate_ = mmfut.deliveryDate_;
    lastTradeDate_ = mmfut.lastTradeDate_;
    expiryDate_= mmfut.expiryDate_;
    endDate_ = mmfut.endDate_;
    calendar_ = mmfut.calendar_ ;
    dcc_ = mmfut.dcc_ ;
    bdc_ = mmfut.bdc_ ;
    rate_ = mmfut.rate_ ;

    return *this;
}


double
MMFuture::getFwdPrice( const Date & valueDate, double futQuote ) const
{
    double result = 0.0;
    double rate = 1.0 - futQuote /100.0 ;
  //  double rate = 1.0 - futQuote /100.0 ;
    double dcf = dcc_->getFraction( valueDate, endDate_ );
    result = 1.0 + rate * dcf ;
/*
    Rate r = ( (const Moneymkt *) underlier)->getRate();

    // MMFuture Quote is always a price quote
    double rateFromFutQuote = 1.0 - futQuote.getPrice().getAmount() / 100.0;
    // r.setRate( rateFromFutQuote );
    // result = r.grow( valueDate, endDate );

    const DayCountConv * dcc = r.getDayCountConv();
    if ( dcc == NULL ) {
        TRACE( "Future", "getUnderlierFwdPrice",
                "DayCountConv is NULL! return incorrect result" );
        return result;
    }

    const YieldType * yieldType = r.getYieldType();
    if ( yieldType == NULL ) {
        TRACE( "Future", "getUnderlierFwdPrice",
                "YieldType is NULL! return incorrect result" );
        return result;
    }

    const Frequency * compFreq = r.getCompFreq();

// no need to check. compFreq == NULL for the case of no compounding

    double dcf = dcc->getFraction( _expiryDate, _endDate );
    result     = yieldType->getRate( rateFromFutQuote, dcf, compFreq );

    dcf = dcc->getFraction( valueDate, _endDate );

    result = 1.0 + result * dcf;

*/
    return result;
}

}
