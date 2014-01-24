#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "cs402.h"
#include "verify.h"

void verifyBuffer(char buffer[])
{
	if(strlen(buffer) > 1024)
	{
		fprintf(stderr, "ERROR! Input line is greater than 1024 bytes!\n");
		exit(0);	
	}
}


void verifyType(char type)
{
	
	if(type != '+' && type != '-')
	{
		fprintf(stderr, "ERROR! Transaction type is not recognised!Use '+' or '-'!\n");
		exit(0);
	}
}


void verifyTime(int timeStamp)
{
	int currentTime = (int)time(NULL);

	//TODO: Implement strlength of the time.
	if( timeStamp > currentTime)
	{	
		fprintf(stderr, "ERROR! Input time is greater than current time!\n");
		exit(0);	
	}
	if (lengthDigits(timeStamp) > 10)
	{
		fprintf(stderr, "ERROR! Input time is malformed!\n");
		exit(0);
	}
}	

int verifyDesc(char buffer[])
{
	int retVal = FALSE;
	if(strlen(buffer) > 999)
	{
		fprintf(stderr, "ERROR! Input description is too large!\n");
		exit(0);	
	}
	retVal = TRUE;
	return retVal;
}

void verifyCost(long maxima, char minima[])
{
	//TODO: Implement for costMajor. Remember abs().
	if(strlen(minima) > 2)
	{
		fprintf(stderr, "ERROR! Malformed Input. Exactly 2 digits after the decimal point is needed!\n");
		exit(0);
	}
}

void verifyCmdLine(char *cmd)
{
	if (strncmp("sort", cmd, sizeof(cmd)) != 0)
	{
		fprintf(stderr, "ERROR! Wrong command line arguments.\n");
		fprintf(stderr, "Usage: warmup1 sort [file]\n");
		exit(0);
	}
}

int costMajorChecker(long maxima)
{
	int retVal = FALSE;
	if (maxima >= 10000000)
		retVal = TRUE;
	
	return retVal;
}

int lengthDigits(long num)
{
	int ctr = 0;
	while(num != 0)
	{
		num = num/10;
		ctr++;
	}
	return ctr;
}

int digitExtract(long amount)
{
	int num = 0,number = 0;
	int digit = 0;
	long long amount1 = amount;
		digit = amount1%10;
		amount1 = amount1/10;
		num = digit;
		digit = amount1%10;
		number = 10*digit + num;
		//printf(" EXT: %d ", abs(number));
	//printf("AMT: %lld RET: %d\n", amount, number);
	return number;
}

char *formatNumber(long num)
{
	int length = lengthDigits(num);
	char *str = malloc(sizeof(length));
	char *retVal = malloc(sizeof(length+2));
	int digit = 0;
	int i=0, j = 0;
	int len = length;
	

	while( num != 0)
	{
		digit = num%10;
		num = num/10;
		str[--len] = digit+48;
	}
	str[length] = '\0';
	retVal[length] = '\0';
	int ctr = 0;
	if(length < 4)
		return str;

	for(i=length-1,j=length; i >= 0 ; i--)
	{
		retVal[j--] = str[i];
		ctr++;
		if(ctr == 3)
		{
			retVal[j--] = ',';
			ctr=0;
		}
	}

	return retVal; 
}

