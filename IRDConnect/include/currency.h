/*
 * currency.h
 *
 *  Created on: 18-Sep-2010
 *      Author: vishist
 */

#ifndef IRDCURRENCY_H_
#define IRDCURRENCY_H_

#include "irdString.h"
#include "frequency.h"
#include "calendar.h"
#include "date.h"
#include "busDayConv.h"
#include "dayCountConv.h"
#include "roundingConv.h"
#include <list>


using namespace std;
using namespace IRDConnect;

namespace IRDConnect {

class Currency;

typedef int RetCode;
typedef std::list <Currency *> CurrencyList;
static CurrencyList _currencyList;


class Currency  {
public:

	static const Currency	* eur;
	Currency( const Currency & );
	//Currency( String ccy);

	~Currency();

	Currency(
			  const std::string 		name,
			  const String				defaultDiscountCurve,
			  const DayCountConv	* 	dcc,
			  const BusDayConv		* 	bdc,
			  const Calendar		* 	cal,
			  const Calendar  		* 	secondCal,
			  const String				mktType,
			  const String				timeSeries,
			  const RoundingConv	* 	roundingConv,
			  const String				defaultONInstrument,
			  const Frequency		 	defaultSwpFloatSettleFreq,
			  const Frequency		 	defaultSwpFixSettleFreq,
			  const DayCountConv	* 	defaultSwaFixDcc,
			  unsigned int		  		numDecimal,
			  int		  	  			valueDayLag,
	          const String	 			emuFlg,
			  double		  			euroConvRate,
			  const Date		 		euroSettleEffDate,
	          const String 				xccyBasisTsirId);

	static void init();

	const String				getDefaultDiscountCurve() const;
	const String				getXccyBasisTsirId() const;
	const DayCountConv			* getDayCountConv() const;
	const DayCountConv			* getDefaultSwpFixDcc() const
		{ return _defaultSwaFixDcc; }
	const Calendar			* getCalendar() const;
	const Calendar            * getSecondCalendar() const;
	const BusDayConv			* getBusDayConv() const;
	const String				getMktType() const;
	const String				getTimeSeries() const;
	const String				getDefaultONInstrument() const
		{ return _defaultONInstrument; }
	const RoundingConv			* getRoundingConv() const;
	unsigned int			 	  getNumDecimal() const;

	const Frequency			 getDefaultSwpFloatSettleFreq() const
		{ return _defaultSwpFloatSettleFreq; }
	const Frequency			 getDefaultSwpFixSettleFreq() const
		{ return _defaultSwpFixSettleFreq; }
	int				 	  getValueDayLag() const;



	double					  getEuroConvRate() const;
	const Date			      getEuroSettleEffDate() const;


	const bool 				  isInEMU() const;
	const bool 				  isEur() const;
	const bool				  isEuroSettleEffDateNull() const;


	static const Currency		* find( unsigned index );
	static const Currency		* find();


	static const Currency		* find( const std::string & name );


	static const Currency		* getEUR();

	static int					getNumCurrencies();
	//added nagesh for currency
    const std::string   getCurrencyCode() const;
	void operator = ( const Currency & );


private:

	const std::string      		name_;
	const String			 	_defaultDiscountCurve;
    const String              	_xccyBasisTsirId ;
	const DayCountConv	* 		_dcc;
	const BusDayConv	* 		_bdc;
	const Calendar	    * 		_cal;
	const Calendar      * 		_secondCal;
	const String		 		_mktType;
	const String			  	_timeSeries;
	const String				_defaultONInstrument;
	const Frequency			 	_defaultSwpFloatSettleFreq;
	const Frequency			 	_defaultSwpFixSettleFreq;
	const DayCountConv	* 		_defaultSwaFixDcc;
	const RoundingConv	* 		_roundingConv;
	const unsigned int		  	_numDecimal;
 	int			  				_valueDayLag;
	const double  				_euroConvRate;
	const String				_emuFlg;
	const Date					_euroSettleEffDate;





};


std::istream & operator >> ( std::istream & is, const Currency ** currency );

}

#endif /* IRDCURRENCY_H_ */

