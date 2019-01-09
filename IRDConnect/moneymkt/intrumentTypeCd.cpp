
/*
 * intrumentTypeCd.cpp
 *
 *  Created on: 02-Oct-2010
 *      Author: vishist
 */

#include "instrumentTypeCd.h"
//#include "errors.h"

using namespace std;
using namespace IRDConnect;

namespace IRDConnect {


 std::ostream& operator<<(std::ostream& classCd, const InstrumentTypeCd& instrumentType)
 {
        switch (instrumentType)
        {

            case BA:
                 //out << "Bankers Acceptances";
                 return classCd << "MM";
                 break;

            case BAFUT:
            	//out << "Banker Acceptance Futures";
            	return classCd << "FUT";
            	break;

            case BAOPT:
            	//out << "Banker Acceptance Futures Option";
            	return classCd << "EOPT";
            	break;
            case BOPTION:
            	//out << "European/American Bond Option";
            	return classCd << "MM";
            	break;
            case CAP:
            	//out << "Cap";
            	return classCd << "CAP";
            	break;
            case CASHFLOW:
            	//out << "Transaction Cost Cash Flow";
            	return classCd << "MM";
            	break;
            case CD:
            	//out << "MM Certificate of Deposits";
            	return classCd << "MM";
            	break;

            case CP:
            	//out << "MM Commercial Paper";
            	return classCd << "MM";
            	break;
            case CURRSWAP:
            	//out << "Cross Currency Swap";
            	return classCd << "SWP";
            	break;
            case ED:
            	//out << "EuroDollar Deposits (LIBOR)";
            	return classCd << "MM";
            	break;
            case EDFUT:
            	//out << "EuroDollarFutures";
            	return classCd << "FUT";
            	break;

            case EDOPT:
            	//out << "EuroDollar Futures Option";
            	return classCd<< "EOPT";
            	break;
            case EQTSWAP:
            	//out << "Equity Swap";
            	return classCd << "SWP";
            	break;
            case    FED:
            	//out << "Fed Funds";
            	return classCd << "MM";
            	break;
            case  FLOOR:
            	//out << "Floor";
            	return classCd << "CAP";
            	break;

            case FRA:
              //out<< "Foward Rate Agreement";
             return classCd << "SWP";
              break;
            case SPFXBUY:
                 //out << "Spot Foreign Exchange-Buy";
                 return classCd << "FX";
                 break;
            case SPFXSELL:
            	 //out << "Spot Foreign Exchange-Sell";
                 return classCd << "FX";
                 break;
            case SPFXARB:
            	 //out << "Spot Foreign Exchange-Arbitrage";
                 return classCd << "FX";
                 break;
            case INTRSWAP:	//out << "Interest Rate Swap";
            return classCd << "SWP";
            break;
            case LDFXBUY:	//out << "Long Dated Foreign Exchange-Buy";
            return classCd << "FX";
            break;
            case    LDFXSELL:
            	//out << "Long Dated Foreign Exchange-Sell";
            		return classCd << "FX";
            		break;
            case  LDFXARB:	//out << "Long Dated Foreign Exchange-Arbitrage";
            return classCd << "FX";
            break;
            case OISWAP:
            	//out << "Overnight Indexed Swap";
            return classCd << "SWP";
            break;
            case     POL:
            	//out << "Pool Rate";
                return classCd << "MM";
            break;
            case PRIME:
            	//out << "PRIME";
            	return classCd << 	"MM";
            break;
            case REPO:	//out << "REPO";
            return classCd <<	"MM";
            break;
            case SPRDSWAP:	//out << "Spread Lock Swap";
            return classCd << "SWP";
            break;

            case SWT:	//out << "Swaption";
            return classCd << "SWT";
            break;
            case SWAPFUT:	//out << "Swap Future";
            return classCd<< 	"SFT";
            break;
            case TBILL:	//out << "Treasury Bills";
            return classCd << "BND";
            break;
            case TBILLFUT:	//out << "T-Bill Futures";
            return classCd << "FUT";
            break;
            case TBNDFUT:	//out << "Treasury Bond Futures";
            classCd << "FUT";
            break;
            case TBNDOPT:	//out << "Treasury Bond Futures Options";
            return classCd << "EOPT";
            break;
            case TBOND:	//out << "Treasury Bonds/Notes";
            return classCd << "BND";
            break;
            case TMP:	//out << "French Weighted Average Rate";
            		return classCd << "MM";
            break;

            case TMM:	//out << "French TMP Monthly Average Rate";
            return classCd << "MM";
            break;
            case T4M:	//out << "French Money Market Average Monthly Rate";
            return classCd << "MM";
            break;
            case TAM:	//out << "French Annual Money Rate";
            return classCd << "MM";
            break;
            case TAG:	//out << "French TMM Annual Average Rate";
            return classCd << "MM";
            break;
            case TMMSWP:	//out << "French TMP Monthly Average Swap Rate";
            return classCd << "SWP";
            case T4MSWP:
            	//out << "French Money Market Average Monthly Swap Rate";
            	return classCd << "SWP";
            	break;
            case TAMSWP:	//out << "French Annual Money Swap Rate";
            return classCd << "SWP";
            break;
            case TAGSWP:	//out << "French TMM Annual Average Swap Rate";
            return classCd << "SWP";
            break;
            case ZCMAT:	//out << "Zero Coupon Maturity";
            return classCd << "BND";
            break;
            case ZCPNSWAP:	//out << "Zero Coupon Swap";
            return classCd << "SWP";

         }
        return classCd << ""; // no product - should never come here

    }
}

