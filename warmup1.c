#include "my402list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void TraverseList(My402List *list);

typedef struct transactionObj
{
	char type;
	int  timeInt;
	char timeString[50];	
	long costMajor;
	float costMinor;
	double tempAmount;
	long amount;
	char costStrMin[4];
	char desc[1000];

	long num1;
	long num2;
	

}MyTransaction;


void verifyTimeDuplicity(My402List *list, int timeStamp)
{

	My402ListElem *elem = NULL;
	for(elem=My402ListFirst(list); elem!=NULL; elem=My402ListNext(list, elem))
	{
		MyTransaction *node = (MyTransaction *)(elem->obj);
		if(timeStamp == node->timeInt)
		{
			fprintf(stderr, "ERROR! Duplicate Time Stamp detected!\n");
			exit(0);
		}
	}
}


void readInput(FILE *fd, My402List *list)
{

	char buffer[1026];
	char timeBuffer[32];
	float tempAmount = 0.0;
	while (fgets(buffer, sizeof(buffer), fd) != '\0') 
	{
		verifyBuffer(buffer);
		MyTransaction *tNode = malloc(sizeof(MyTransaction));

		char *tokstr = strtok(buffer, "\t");
		sscanf(tokstr, "%c", &tNode->type);
		verifyType(tNode->type);	

		tokstr = strtok (NULL, "\t");
		sscanf(tokstr, "%d", &tNode->timeInt);
		verifyTime(tNode->timeInt);
		verifyTimeDuplicity(list, tNode->timeInt);
		
		time_t dateTime = (time_t)(tNode->timeInt);	
		strncpy(timeBuffer, ctime(&dateTime), sizeof(timeBuffer));			
		strncpy(tNode->timeString, timeBuffer, sizeof(tNode->timeString));
		verifyTime(tNode->timeInt);
	
		tokstr = strtok (NULL, "\t");
		sscanf(tokstr, "%ld.%s", &tNode->costMajor, tNode->costStrMin);
		sscanf(tokstr, "%f", &tempAmount);
		sscanf(tokstr, "%ld.%ld", &tNode->num1, &tNode->num2);
		tNode->amount = (tNode->num1*100) + tNode->num2;
		tNode->costMinor = ((float)(atoi(tNode->costStrMin)))/100;
		verifyCost(tNode->costMajor, tNode->costStrMin);


		tokstr = strtok(NULL, "\n");
		strncpy(tNode->desc, tokstr, sizeof(tNode->desc));


		int ret = My402ListAppend(list, (void *) tNode);
		if(!ret)
		{
			fprintf(stderr, "ERROR in Inserting to List.Check your Input!\n");
			exit(0);		
		}

	}
}

/*//////////////////////CODE NOT WRITTEN BY ME.///////////////////////////////////////

		Code Adapted from Professor Bill Cheng's Lecture CS402 Fall.

///////////////////////////////////////////////////////////////////////////////////*/

void BubbleForward(My402List *list, My402ListElem **pp_elem1, My402ListElem **pp_elem2)

{
    My402ListElem *elem1=(*pp_elem1), *elem2=(*pp_elem2);
    void *obj1=elem1->obj, *obj2=elem2->obj;
    My402ListElem *elem1prev=My402ListPrev(list, elem1);
    My402ListElem *elem2next=My402ListNext(list, elem2);

    My402ListUnlink(list, elem1);
    My402ListUnlink(list, elem2);
    if (elem1prev == NULL) {
        (void)My402ListPrepend(list, obj2);
        *pp_elem1 = My402ListFirst(list);
    } else {
        (void)My402ListInsertAfter(list, obj2, elem1prev);
        *pp_elem1 = My402ListNext(list, elem1prev);
    }
    if (elem2next == NULL) {
        (void)My402ListAppend(list, obj1);
        *pp_elem2 = My402ListLast(list);
    } else {
        (void)My402ListInsertBefore(list, obj1, elem2next);
        *pp_elem2 = My402ListPrev(list, elem2next);
    }
}


void BubbleSortForwardList(My402List *list)
{
    	My402ListElem *elem=NULL;
    	int i=0;
	int num_items = My402ListLength(list);
    	for (i=0; i < num_items; i++) {
       	 int j=0, something_swapped=FALSE;
       	 My402ListElem *next_elem=NULL;

        for (elem=My402ListFirst(list), j=0; j < num_items-i-1; elem=next_elem, j++) {
            
	     MyTransaction *curVal=(MyTransaction *)(elem->obj), *nextVal=0;

            next_elem=My402ListNext(list, elem);
            nextVal = (MyTransaction *)(next_elem->obj);

            if (curVal->timeInt > nextVal->timeInt) {
                BubbleForward(list, &elem, &next_elem);
                something_swapped = TRUE;
            }
        }
        if (!something_swapped) break;
    }
}

//////////////////////DERIVED CODE ENDS HERE//////////////////////////////////////

void TraverseList(My402List *list)
{
	My402ListElem *elem = NULL;
	double balance = 0.0;
	long amount = 0;

	for(elem=My402ListFirst(list); elem!=NULL; elem=My402ListNext(list, elem))
	{
		
		MyTransaction *node = (MyTransaction *)(elem->obj);		
		fprintf(stdout, "| %.10s %.4s ",node->timeString, &node->timeString[20]); 
		fprintf(stdout, "| %-24.24s ",(node->desc));
	
		if(node->type == '-')
		{
			balance = balance - (node->costMajor + node->costMinor);
			amount = amount - node->amount;

			if(costMajorChecker(node->costMajor))
				fprintf(stdout, "|   ?,???,???.?? ");
			else
			{
				fprintf(stdout, "| (%9s.%.2d) ", formatNumber(node->amount/100), node->num2/*node->costStrMin*/);
			}
		}
		else
		{
			//printf("%ld - (%ld + %f)\n", balance, node->costMajor, node->costMinor);
			balance = balance + ((((float)node->costMajor)*1.0) + node->costMinor);

			amount = amount + node->amount;
			if(costMajorChecker(node->costMajor))
				fprintf(stdout, "|   ?,???,???.?? ");
			else
			{
				char *str = formatNumber(node->costMajor);
				fprintf(stdout, "|%11s.%.2d  ", str, node->num2/*node->costStrMin*/);
			}
		}
		//printf("NAMT: %ld FAMT:  %ld ", node->amount, amount); 
		if(abs(balance) > 10000000.00)
		{
			fprintf(stdout, "|   ?,???,???.?? |\n");
		}
		else
		{	if( amount > 0 )
			{
				fprintf(stdout, "|%11s.%.2d  |\n", formatNumber(amount/100), digitExtract(amount)/*(int)abs(balMinor*100)*/);  
			}
			else
			{
				fprintf(stdout, "| (%9s.%.2d) |\n", formatNumber(-1*(amount/100)),abs(digitExtract(amount)) /*(int)abs(balMinor*100)*/);
			}
				
		}
	}
}

void printStatement(My402List *list)
{
	fprintf(stdout, "+-----------------+--------------------------+----------------+----------------+\n");
	fprintf(stdout, "|       Date      | Description              |         Amount |        Balance |\n");
	fprintf(stdout, "+-----------------+--------------------------+----------------+----------------+\n");
	TraverseList(list);
	fprintf(stdout, "+-----------------+--------------------------+----------------+----------------+\n");
}


int main(int argc, char* argv[])
{
	FILE *fd;

	if(argc == 1)
	{
		fprintf(stderr, "Too Few Parameters.\n");
		fprintf(stderr, "Usage: warmup1 sort [file]\n");
		exit(0);
	}


	verifyCmdLine(argv[1]);		
	if(argv[2] != NULL)
	{
		fd = fopen(argv[2], "r");
		if(!fd)
		{
			fprintf(stderr, "ERROR! Unable to open file\n");
			exit(0);
		}	

	}
	else if(argv[2] == NULL)
	{
		fd = stdin;
	}
	else
	{
		fprintf(stderr, "ERROR! Wrong CommandLine argument\n");
		exit(0);
	}
	
	
	My402List *list = malloc(sizeof(My402List));
 	if(!My402ListInit(list))
	{
		fprintf(stderr, "ERROR! Initialization error!.Exiting.\n");
		exit(0);
	}
	readInput(fd, list);
	BubbleSortForwardList(list);
	printStatement(list);
	free(list);
	return 0;
}

