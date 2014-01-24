
//#ifndef _VERIFY_H_
//#define _VERIFY_H_

#include "cs402.h"

extern void verifyBuffer(char buffer[]);
extern void verifyType(char type);
extern void verifyTime(int timeStamp);
extern int verifyDesc(char buffer[]);
extern void verifyCost(long maxima, char minima[]);
extern void verifyCmdLine(char *cmd);
extern char *formatNumber(long num);
extern int costMajorChecker(long maxima);
extern int digitExtract(long amount);
extern int lengthDigits(long num);





//#endif //_VERIFY_H_
