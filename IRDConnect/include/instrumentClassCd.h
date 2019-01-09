/*
 * instrumentClassCd.h
 *
 *  Created on: 02-Oct-2010
 *      Author: vishist
 */

#ifndef INSTRUMENTCLASSCD_H_
#define INSTRUMENTCLASSCD_H_
#include <ostream>


namespace IRDConnect
{

enum InstrumentClassCd
{
	BND,
	CAP,
	BFT,
	BFO,
	CMPIDX,
	EOPT,
	EQUITY,
	FRA,
	FXRES,
	FUT,
	FX,
	MM,
	SWP,
	SWT,
	BASIS,
	JUMP,
	SFT

};

std::ostream& operator<<(std::ostream& a,
                            const InstrumentClassCd& b);

}
#endif /* INSTRUMENTCLASSCD_H_ */


