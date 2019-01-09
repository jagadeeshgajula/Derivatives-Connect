/*
 * instrumentCalssCd.cpp
 *
 *  Created on: 24-Oct-2010
 *      Author: vishist
 */

#include "instrumentClassCd.h"
#include <ostream>
using namespace std;
using namespace IRDConnect;

namespace IRDConnect {


 std::ostream& operator<<(std::ostream& out,
		 const InstrumentClassCd& instrumentClass)
 {
        switch (instrumentClass)
        {

        case BND:
        	return out << "Income Bond";
        case CAP:
        	return out << "Cap/Floor";
        case BFT:
        	return out << "Bond Future";
        case BFO:
        	return out << "Bond Future Option";
        case CMPIDX:
        	return out << "Composite Index";
        case EOPT:
        	return out << "Exchange Traded Option";
        case EQUITY:
        	return out << "Equity/Stock";
        case FRA:
        	return out << "FRA";
        case FXRES:
        	return out << "FX Reset";

        case FUT:
        	return out << "Exchange Traded Future";
        case FX:
        	return out << "Foreign Exchange";
        case MM:
        	return out << "Money Market";
        case SWP:
        	return out << "Swap";
        case SWT:
        	return out << "Swaption";
        case BASIS:
        	return out << "BASIS";
        case JUMP:
        	return out << "JUMP";
        case SFT:
        	return out << "Swap Future";


        }
        return out << ""; // return empty.
 }
}

