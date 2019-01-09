/*
 * swap.h
 *
 *  Created on: 30-Nov-2010
 *      Author: vishist
 */

#ifndef SWAP_H_
#define SWAP_H_

#include <string>
#include "date.h"
#include "currency.h"
#include "boost/shared_ptr.hpp"
//----------------------------------------------------------------------
// Forward declarations ...

namespace IRDConnect {

class Period;
class DayCountConv ;
class Moneymkt;
//class Currency ;
//----------------------------------------------------------------------

class Swap {
public:

	Swap( const std::string			& id,
		  const Currency            * ccy,
		  const Date				& today,
		  const Period				& period,
		  const std::string         & marchingConv,
		  const DayCountConv        * dcc,
		  const BusDayConv          * bdc,
		  const Calendar            * calendar,
		  const double              & swapRate,
		  const boost::shared_ptr<Moneymkt> & underlier,
		  unsigned int				startDateOffset = 0		   );

	Swap( const Swap & swap );			// deep copy of 'swap'
	virtual ~Swap();
	Swap & operator = ( const Swap & swap ); // deep copy of 'swap'

	virtual double		  getYTM( Date startDate ) const;
	virtual Period	      getValueDayLag() const;
    const Date 			& getEffectiveDate() const;
    const Date 			& getTerminationDate() const;
    unsigned int          getStartDateOffset() const;
	const Period	    & getTerm() const;
	Period				  getInstrTenor() const;
	std::string           getMarchingConv () const {
		return marchingConv_ ;
	}

	std::list<Date> generateSchedule ( const Date & startDate  ) ;
//	const QuoteType		* getQuoteType() const;


	const DayCountConv	* getDayCountConv() const{
		return dcc_ ;
	}

	const DayCountConv	* getInstrDayCountConv() const;

	double getSwapRate () const { return swapRate_; } ;
	Date getInstrEndDate ( const Date & startDate ) ;
	const std::string & getId () const { return id_ ; } ;

private :
	std::string id_ ;
	const Currency * ccy_ ;
	Date effectiveDate_ ;
	Date terminationDate_ ;
	Period period_ ;
	std::string marchingConv_ ;
	const DayCountConv * dcc_ ;
	const BusDayConv *   bdc_;                  // business day convention
	const Calendar   * calendar_;        // calendar
	double swapRate_ ;
	boost::shared_ptr<Moneymkt> underlier_ ;
	unsigned int startDateOffset_ ;


};

}
#endif /* SWAP_H_ */
