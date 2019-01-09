/*
 * BlackVol.h
 *
 *  Created on: 15-Feb-2013
 *      Author: vishist
 */

#ifndef BLACKVOL_H_
#define BLACKVOL_H_

namespace IRDConnect {
class BlackPricer {
public:
	BlackPricer();
	virtual ~BlackPricer();
	double getIntrinsicValue( double price, double strikePrice, bool isCall );
	double calcBlackValue( double fwd, double strike, double vol, double t, double phi );
};
}
#endif /* BLACKVOL_H_ */
