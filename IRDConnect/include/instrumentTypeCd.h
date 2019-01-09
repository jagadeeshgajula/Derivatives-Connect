/*
 * instrumentTypeCd.h
 *
 *  Created on: 02-Oct-2010
 *      Author: vishist
 */

#ifndef INSTRUMENTTYPECD_H_
#define INSTRUMENTTYPECD_H_

#include <ostream>


namespace IRDConnect
{
  enum InstrumentTypeCd {
   BA,
   BAFUT,
   BAOPT,
   BOPTION,
   CAP,
   CASHFLOW,
   CD,
   CP,
   CURRSWAP,
   ED,
   EDFUT,
   EDOPT,
   EQTSWAP,
   FED,
   FLOOR,
   FRA,
   SPFXBUY,
   SPFXSELL,
   SPFXARB,
   INTRSWAP,
   LDFXBUY,
   LDFXSELL,
   LDFXARB,
   OISWAP,
   POL,
   PRIME,
   REPO,
   SPRDSWAP,
   SWT,
   SWAPFUT,
   TBILL,
   TBILLFUT,
   TBNDFUT,
   TBNDOPT,
   TBOND,
   TMP,
   TMM,
   T4M,
   TAM,
   TAG,
   TMMSWP,
   T4MSWP,
   TAMSWP,
   TAGSWP,
   ZCMAT,
   ZCPNSWAP

};

std::ostream& operator<<(std::ostream& a,
                            const InstrumentTypeCd&);

}

#endif /* INSTRUMENTTYPECD_H_ */

