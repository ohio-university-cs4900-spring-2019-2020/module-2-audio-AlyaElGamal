#ifndef _ODE_PRECISION_H_
#define _ODE_PRECISION_H_

/* Define dSINGLE for single precision, dDOUBLE for double precision,
 * but never both!
 */

/// SLN single precision for the windows header files
#define dIDESINGLE

#if defined(dIDESINGLE)
#define dSINGLE
#elif defined(dIDEDOUBLE)
#define dDOUBLE
#else
#define dUNDEFINEDPRECISION
#endif

#endif
