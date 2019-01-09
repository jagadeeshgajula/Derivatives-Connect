/*
 * roundingConv.h
 *
 *  Created on: 25-Sep-2010
 *      Author: vishist
 */

#ifndef ROUNDINGCONV_H_
#define ROUNDINGCONV_H_

#include "irdString.h"
#include<iostream>
#include <map>
#include <set>

using namespace std;
using namespace IRDConnect;

namespace IRDConnect {

class RoundingConv  {
public:

	virtual double	round( double	v,
										    int		nd ) const = 0;

	//static bool getRoundingFlag();

	//static RoundingConv	* _nearest;
	//static RoundingConv	* _sciNotaNearest;
	//static RoundingConv	* _down;

	static const RoundingConv		* find( );

	static const RoundingConv		* find( const std::string	& name_ );



	RoundingConv(  const IRDConnect::String	& name );

	virtual ~RoundingConv();

private:

	//static void						init();
	//static void						cleanup();
	//friend class					RoundingConvInit;


	String name_;
	RoundingConv( const RoundingConv & );
	void operator = ( const RoundingConv & );

	typedef std::map<std::string, const  RoundingConv *> RoundConvMap ;
		   	    	 static RoundConvMap & getRoundConvMap ( ) ;

};

}

#endif /* ROUNDINGCONV_H_ */
