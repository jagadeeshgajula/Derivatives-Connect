#ifndef MARCHINGCONV_H
#define MARCHINGCONV_H
#include<iostream>
#include<map>
#include "calendar.h"
#include "busDayConv.h"
#include "date.h"
#include "rollDayConv.h"
#include <list>

using namespace std;
using namespace IRDConnect;

namespace IRDConnect {

class DateMarcher  {
public:

	// The supported marching conventions ...
/*
	static DateMarcher	* _forward;
	static DateMarcher	* _backward;
	static DateMarcher	* _eurodollar;
	static DateMarcher	* _imm;
	static DateMarcher	* _immaud;
	static DateMarcher	* _immnzd;
	static DateMarcher	* _dayofweek;
	static DateMarcher	* _dayofmonth;*/

	// 'GenSchedule' is used by 'genSchedule()' below.  See 'genSchedule()'
	// for details.
	DateMarcher(const std::string);

	class GenSchedule {
	public:

		GenSchedule();
		GenSchedule( const GenSchedule & genSchedule );

		virtual ~GenSchedule();

		std::list<Date > & getEventList() { return _dates;}

		GenSchedule & operator = ( const GenSchedule & genSchedule );

		virtual int addEvent( const Date & date ) ;
		const Date			getESMinDate() const {return * _minESDate;};
		const Date			getESMaxDate() const {return * _maxESDate;};
		void setESMinDate(Date * date) { _minESDate = date; }
		void setESMaxDate(Date * date) { _maxESDate = date; }

		Date						* _minESDate;
		Date						* _maxESDate;


	private:

		std::list < Date > _dates;


	};


	virtual int genSchedule(
		const Date			& start,
		const Date			& end,
		const Frequency	freq,
		const Calendar		& calendar,
		const BusDayConv	* bdc,
		GenSchedule			& genSchedule,
		int					  evenFinalPeriod = 0,
		RollDayConv *  rollDayConv = 0 ) const = 0;

	// the firstAndLastEventsToGenSchedule only works for EuroDollor now, support needs
	// to be added to take care of other cases. Tried to keep the interface general.

	virtual int firstAndLastEventsToGenSchedule(
					const Date			& start,
					const Date			& end,
					int			  		  noOfPeriods,
					const Frequency	freq,
					const Calendar		& calendar,
					const BusDayConv	* bdc,
					GenSchedule			& genSchedule,
					int					  evenFinalPeriod,
					RollDayConv  * rollDayConv = 0) const { return false; }


	// UI Support ...

	static const DateMarcher * find( unsigned int index );

	// DB Support ...

	static const DateMarcher * find( const std::string & dateMarcher );
	void operator = ( const DateMarcher & );
	std::string getStr() const { return name_; };

protected:

	virtual ~DateMarcher();
	std::string name_;

private:


	typedef std::map<std::string, const  DateMarcher *> MarchMap ;
	static MarchMap & getMarchMap ( ) ;

	// No Copying ...



};


//----------------------------------------------------------------------
//
// 'DateGenScheduleWrapper' is used to keep track of the earlyest and
// latest dates successfully added to an 'GenSchedule'.
//

class DateStreamWrapper {
public:

	DateStreamWrapper( DateMarcher::GenSchedule & es );
	~DateStreamWrapper();

	int						addEvent( const Date & date );

	const Date					* getMinDate() const;
	const Date					* getMaxDate() const;

private:

	DateMarcher::GenSchedule			& _es;

	Date						* _minDate;
	Date						* _maxDate;


	DateStreamWrapper( DateStreamWrapper & );
	void operator = ( DateStreamWrapper & );
};

//----------------------------------------------------------------------
//

class GeneralForwardDateMarcher : public DateMarcher {
public:

	GeneralForwardDateMarcher( const std::string  dateMarcher );
	~GeneralForwardDateMarcher();

	virtual int		genSchedule(
					const Date			& start,
					const Date			& end,
					const Frequency	freq,
					const Calendar		& calendar,
					const BusDayConv	* bdc,
					GenSchedule			& genSchedule,
					int					  evenFinalPeriod,
					RollDayConv  * rollDayConv = 0  ) const;

	// the firstAndLastEventsToGenSchedule only works for EuroDollor now, support needs
	// to be added to take care of other cases. Tried to keep the interface general.

	virtual int firstAndLastEventsToGenSchedule(
					const Date			& start,
					const Date			& end,
					int			  		  noOfPeriods,
					const Frequency	freq,
					const Calendar		& calendar,
					const BusDayConv	* bdc,
					GenSchedule			& genSchedule,
					int					  evenFinalPeriod,
					RollDayConv *  rollDayConv = 0) const;

	class DateCtl : public Date {
	public:

		DateCtl( const Date & date );
		virtual ~DateCtl();

		virtual void	next() = 0;

	private:

		DateCtl( const DateCtl & );
		void operator = ( const DateCtl & );
	};

	virtual DateCtl		* createDateCtl(
					const Date		& start,
					const Frequency	freq,
					const Calendar		& calendar,
					const BusDayConv	* bdc,
					RollDayConv  * rollDayConv = 0 ) const = 0;

private:

	GeneralForwardDateMarcher( const GeneralForwardDateMarcher & );
	void operator = ( const GeneralForwardDateMarcher & );
};

//----------------------------------------------------------------------
//
class ForwardDateMarcher : public GeneralForwardDateMarcher {
public:

	ForwardDateMarcher();
	virtual ~ForwardDateMarcher();

protected:

	class DateCtl : public GeneralForwardDateMarcher::DateCtl {
	public:

		DateCtl( const Date			& start,
				 const Frequency	freq,
				 const Calendar		& cal,
				 const BusDayConv	* bdc );

		virtual ~DateCtl();

		virtual void	next();

	private:

		Date _date;
		Date _startDate;
		const Period	_period;
		Period _periodAddedToStartDate;
		const Calendar	& _cal;
		const BusDayConv * _bdc;

		// No Copying ...
		DateCtl( const DateCtl & );
		void operator = ( const DateCtl & );
	};

	virtual GeneralForwardDateMarcher::DateCtl * createDateCtl(
				const Date		& start,
			 	const Frequency	freq,
				const Calendar		& calendar,
				const BusDayConv	* bdc,
				RollDayConv  * rollDayConv = 0 ) const;

private:

	ForwardDateMarcher( const ForwardDateMarcher & );
	void operator = ( const ForwardDateMarcher & );
};

//----------------------------------------------------------------------
//
// Generates a stream of dates like the forward marching convention
// with the following conditions :
//
// The resultant dates will always fall on the same numerical date
// as the previously generated date.  If this date lands on a holiday
// use the modified following bus day convention to adjust to a
// business day.  If the previously generated date fell on the last
// business day of the month then all subsequent dates must also
// fall on the last business day of the month.
//

class EuroDollarDateMarcher : public GeneralForwardDateMarcher {
public:

	EuroDollarDateMarcher();
	virtual ~EuroDollarDateMarcher();

	//virtual int	isBDCRequired() const;
	//virtual int isValidFrequency( const Frequency * freq ) const;

	class DateCtl : public GeneralForwardDateMarcher::DateCtl {
	public:

		DateCtl(	const Date	& start,
				const Frequency	freq,
				const Calendar	& cal );

		virtual ~DateCtl();

		// Add '_tenor' to '*this' and adjust for all of those ugly
		// conventions associated with Euro Dollar marching.

		virtual void	next();

	private:

		const Period	  _period;
		const Calendar	& _cal;
		int		  _lastBusDay;

		// Return the last business day in '*this's year and month.

		Date	findLastBusDay() const;

		DateCtl( const DateCtl & );
		void operator = ( const DateCtl & );
	};

	virtual GeneralForwardDateMarcher::DateCtl * createDateCtl(
				const Date		& start,
			 	const Frequency	freq,
				const Calendar		& calendar,
				const BusDayConv	* bdc,
				RollDayConv * rollDayConv = 0 ) const;

private:

	EuroDollarDateMarcher( const EuroDollarDateMarcher & );
	void operator = ( const EuroDollarDateMarcher & );
};

//----------------------------------------------------------------------
//

class IMMDateMarcher : public GeneralForwardDateMarcher {
public:

	IMMDateMarcher();
	virtual ~IMMDateMarcher();



	class DateCtl : public GeneralForwardDateMarcher::DateCtl {
	public:

		DateCtl( const Date			& start,
				 const Frequency	freq,
				 const Calendar		& cal,
				 const BusDayConv	* bdc);

		virtual ~DateCtl();

		virtual void	next();

	private:

		const Period		  _period;
		const Calendar		& _cal;
		const BusDayConv	* _bdc;

		DateCtl( const DateCtl & );
		void operator = ( const DateCtl & );
	};

	virtual GeneralForwardDateMarcher::DateCtl * createDateCtl(
				const Date		& start,
			 	const Frequency	freq,
				const Calendar		& calendar,
				const BusDayConv	* bdc,
				RollDayConv * rollDayConv ) const;

private:

	IMMDateMarcher( const IMMDateMarcher & );
	void operator = ( const IMMDateMarcher & );
};


//----------------------------------------------------------------------

class DOWDateMarcher : public GeneralForwardDateMarcher {
public:

	DOWDateMarcher();
	virtual ~DOWDateMarcher();


	class DateCtl : public GeneralForwardDateMarcher::DateCtl {
	public:

		DateCtl( const Date			& date,
				 const Frequency	freq,
				 const Calendar		& cal,
				 const BusDayConv	* bdc,
				 RollDayConv  * rollDayConv);

		virtual ~DateCtl();

		virtual void				next();

	private:

		Date						  _date;
		Date						  _sdate;
		const Period				  _period;
		Period						  _currentPeriod;
		const Calendar				& _cal;
		const BusDayConv			* _bdc;
		RollDayConv *  _rollDayConv;

		DateCtl( const DateCtl & );
		void operator = ( const DateCtl & );
	};

	virtual GeneralForwardDateMarcher::DateCtl * createDateCtl(
				const Date			& date,
			 	const Frequency	freq,
				const Calendar		& calendar,
				const BusDayConv	* bdc,
				RollDayConv  * rollDayConv = 0) const;

private:

	DOWDateMarcher( const DOWDateMarcher & );
	void operator = ( const DOWDateMarcher & );
};

//-------------------------------------------------------------------------

class DOMDateMarcher : public GeneralForwardDateMarcher {
public:

	DOMDateMarcher();
	virtual ~DOMDateMarcher();

	//virtual int isValidFrequency( const Frequency * freq ) const;

	class DateCtl : public GeneralForwardDateMarcher::DateCtl {
	public:

		DateCtl( const Date			& date,
				 const Frequency	freq,
				 const Calendar		& cal,
				 const BusDayConv	* bdc,
				 RollDayConv  * rollDayConv);

		virtual ~DateCtl();

		virtual void				next();

	private:

		Date                         _date;
        Date                 _sdate;
        const Period                   _period;
        Period                         _currentPeriod;
        const Calendar              & _cal;
        const BusDayConv            * _bdc;
        RollDayConv *  _rollDayConv;

		DateCtl( const DateCtl & );
		void operator = ( const DateCtl & );
	};

	virtual GeneralForwardDateMarcher::DateCtl * createDateCtl(
				const Date			& start,
			 	const Frequency	freq,
				const Calendar		& calendar,
				const BusDayConv	* bdc,
				RollDayConv  * rollDayConv ) const;

private:

	DOMDateMarcher( const DOMDateMarcher & );
	void operator = ( const DOMDateMarcher & );
};


//----------------------------------------------------------------------
//

class BackwardDateMarcher : public DateMarcher {
public:

	BackwardDateMarcher();
	~BackwardDateMarcher();

	virtual int genSchedule(	const Date			& start,
									const Date			& end,
									const Frequency	freq,
									const Calendar		& calendar,
									const BusDayConv 	* bdc,
									GenSchedule			& genSchedule,
									int					  evenFinalPeriod,
									RollDayConv  * rollDayConv = 0) const;

private:

	class BackDate : public Date {
	public:

		BackDate( const Date		& start,
			  const Frequency	freq,
			  const Calendar	& cal,
			  const BusDayConv	* bdc );

		~BackDate();

		void	next();

	private:

		Date			_date;
		Date			_startDate;
		const Period		_period;
		Period			_periodAddedToStartDate;
		const Calendar	& _cal;
		const BusDayConv * _bdc;

		// No Copying ...
		BackDate( const BackDate & );
		void operator = ( const BackDate & );
	};

	// No Copying ...
	BackwardDateMarcher( const BackwardDateMarcher & );
	void operator = ( const BackwardDateMarcher & );
};

}


//----------------------------------------------------------------------
//

#endif   // MARCHINGCONV_H

// End-Of-File ---------------------------------------------------------
