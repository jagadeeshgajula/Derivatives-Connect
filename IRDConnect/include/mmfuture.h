/*
 * mmfuture.h
 *
 *  Created on: 02-Jan-2011
 *      Author: vishist
 */

#ifndef MMFUTURE_H_
#define MMFUTURE_H_

#include <string>
#include "date.h"
#include "dayCountConv.h"
#include "currency.h"

using namespace std;
namespace IRDConnect {


class Currency ;
class MMFuture {

public:

	MMFuture( const MMFuture & mmfut );
	MMFuture & operator = ( const MMFuture & mmfut );

	// --- Constructors and Destructor ---
	MMFuture ( const std::string &         id,
            const Currency *          ccy,
            const Date &              deliveryDate,
            const Date &              lastTradeDate,
            const Date &              expiryDate,
            const Date &              endDate,
            const Calendar *          cal,
            const DayCountConv *      dcc,
            const BusDayConv *        bdc,
            double                    rate);

	virtual ~MMFuture();

	// virtual constructor...
//	virtual Instrument *clone() const;

	double getFwdPrice( const Date & valueDate,
								double futQuote ) const;
	const Date & getExpiryDate () const { return expiryDate_ ; } ;
	const Date & getEndDate () const { return endDate_; } ;
        const std::string & getId () const { return id_ ; } ;
private :
	std::string id_ ;
	const Currency * ccy_;
	Date deliveryDate_ ;
	Date lastTradeDate_ ;
	Date expiryDate_ ;
	Date endDate_ ;
	const Calendar   * calendar_;        // calendar
	const DayCountConv * dcc_ ;
	const BusDayConv *   bdc_;
	double rate_;
};

}
#endif /* MMFUTURE_H_ */
