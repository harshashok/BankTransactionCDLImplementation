#include "my402list.h"
#include <stdio.h>
#include <stdlib.h>



int  My402ListLength(My402List* list)
{ 
	return list->num_members;

}

int  My402ListEmpty(My402List* list)
{
	
	int retVal = FALSE;
	if (list->anchor.next == NULL && list->anchor.prev == NULL)
		retVal = TRUE;
	return retVal;
}


My402ListElem *My402ListFirst(My402List* list)
{
	My402ListElem *retElem = NULL;
	if (list->anchor.next)
		retElem = list->anchor.next;
	return retElem;
}


My402ListElem *My402ListLast(My402List* list)
{
	My402ListElem *retElem = NULL;
	if (list->anchor.prev)
		retElem = list->anchor.prev;

	return retElem;
}

My402ListElem *My402ListNext(My402List* list, My402ListElem* elem)
{
	
	My402ListElem *retElem = NULL;
	
	if(elem->next == (&list->anchor))
		retElem = NULL;
	else retElem = elem->next;
	 
	return retElem;

}

My402ListElem *My402ListPrev(My402List* list, My402ListElem* elem)
{
	
	My402ListElem *retElem = NULL;
	
	if(elem->prev == (&list->anchor))
		retElem = NULL;
	else retElem = elem->prev;

	return retElem;
}

int  My402ListAppend(My402List* list, void* data)
{
	int retVal = FALSE;
	My402ListElem *node = malloc(sizeof(My402ListElem));
	if(!node)
	{
		fprintf(stderr,"Error! Could not allocate memory[Append]\n");
		return retVal;
	}
	node->obj = data;
	retVal = TRUE;
	list->num_members+=1;
	if (My402ListEmpty(list))
	{
		list->anchor.next = node;
		list->anchor.prev = node;
		node->next = (&list->anchor);
		node->prev = (&list->anchor);
	}
	else{
		My402ListElem *lastNode = My402ListLast(list);
		lastNode->next = node;
		node->next = (&list->anchor);
		list->anchor.prev = node;
		node->prev = lastNode;
	}
	return retVal;				
}

int  My402ListPrepend(My402List* list, void* data)
{
	int retVal = FALSE;
	My402ListElem * node = malloc(sizeof(My402ListElem));
	if(!node)
	{
		fprintf(stderr, "Error! Could not allocate moemory[Prepend]\n");
		return retVal;
	}
	node->obj = data;
	retVal = TRUE;
	list->num_members+=1;
	if(My402ListEmpty(list))
	{
		list->anchor.next = node;
		list->anchor.prev = node;
		node->next = (&list->anchor);
		node->prev = (&list->anchor);
	}
	else{
		My402ListElem *firstNode = My402ListFirst(list);
		list->anchor.next = node;
		node->next = firstNode;
		firstNode->prev = node;
		node->prev = (&list->anchor);	
	     }
	return retVal;
}

int  My402ListInsertBefore(My402List* list, void* data, My402ListElem* elem)
{
	int retVal = FALSE;
	if(elem == NULL)
		retVal = My402ListPrepend(list, data);
	else{
		My402ListElem * node = malloc(sizeof(My402ListElem));
		if(!node)
		{
			fprintf(stderr, "Error! Could not allocate moemory[InsertAfter]\n");
			return retVal;
		}
		node->obj = data;
		retVal = TRUE;
		list->num_members+=1;
		if(My402ListEmpty(list))
		{
			retVal = My402ListPrepend(list, data);
		}
		else
		{
			My402ListElem *prevNode = elem->prev;
			prevNode->next = node;
			node->next = elem;
			elem->prev = node;
			node->prev = prevNode;
		}
	    }			
			
	return retVal;
}


int  My402ListInsertAfter(My402List* list, void* data, My402ListElem* elem)
{
	int retVal = FALSE;
	if(elem == NULL)
		retVal = My402ListAppend(list, data);
	else{
		My402ListElem * node = malloc(sizeof(My402ListElem));
		if(!node)
		{
			fprintf(stderr, "Error! Could not allocate moemory[InsertAfter]\n");
			return retVal;
		}
		node->obj = data;
		retVal = TRUE;
		list->num_members+=1;
		if(My402ListEmpty(list))
		{
			retVal = My402ListAppend(list, data);
		}
		else
		{
			My402ListElem *nextNode = elem->next;
			elem->next = node;
			node->next = nextNode;
			nextNode->prev = node;
			node->prev = elem;
		}
	     }
	return retVal;
}

void My402ListUnlink(My402List* list, My402ListElem* elem)
{
	if(My402ListEmpty(list))
		return;
	
	if(elem == (&list->anchor))
	{
		fprintf(stderr, "Error! Anchor can't be deleted.[Unlink]");
		return;
	}


	if( (elem->next == (&list->anchor)) && (elem->prev == (&list->anchor)) ) 
	{
		list->anchor.next = NULL;
		list->anchor.prev = NULL;
		free(elem);
		list->num_members-=1;
	}
	else{
		elem->prev->next = elem->next;
		elem->next->prev = elem->prev;
		free(elem);
		list->num_members-=1;
	    }	

}

void My402ListUnlinkAll(My402List* list)
{
	My402ListElem *elem = My402ListFirst(list);
	My402ListElem *temp = NULL;
	do{
	temp = elem->next;                 //My402ListNext(list, elem);
	My402ListUnlink(list, elem);
	elem = temp;
	}while(elem != (&list->anchor));

}

My402ListElem *My402ListFind(My402List* list, void* data)
{
	My402ListElem *retElem = NULL;
	My402ListElem *elem = NULL;

	if(My402ListEmpty(list))
		return retElem;
	for(elem=My402ListFirst(list); elem!=NULL; elem=My402ListNext(list, elem))
	{
		if((elem->obj) == data)
			retElem = elem;
	}
	return retElem;
			
}

void Traverse(My402List *list)
{/*
	My402ListElem *elem = NULL;
	for(elem=My402ListFirst(list); elem!=NULL; elem=My402ListNext(list, elem))
	{
		fprintf(stdout, "Trav Val: %d\n", (int)(elem->obj));
	}*/
}

int My402ListInit(My402List* list)
{
	list->num_members = 0;
	list->anchor.next = NULL;
	list->anchor.prev = NULL;
	list->anchor.obj = NULL;
	return TRUE;
}
/*
int main()
{
	int ret =FALSE;	
	My402List *list = malloc(sizeof(My402List));
	My402ListInit(list);
	ret = My402ListAppend(list, (void *)10);
	ret = My402ListAppend(list, (void *)20);
	ret = My402ListAppend(list, (void *)30);
	ret = My402ListPrepend(list, (void *)40);
	ret = My402ListPrepend(list, (void *)50);
	ret = My402ListPrepend(list, (void *)60); 
	fprintf(stdout, "Append value: %d\n",ret);
	My402ListElem *node = My402ListFirst(list);
	fprintf(stdout, "First value: %d\n",(int)node->obj);
	Traverse(list);
	node = My402ListFind(list, (void *)(50));
	fprintf(stdout, "NodeFind value: %d\n",(int)node->obj);
	ret = My402ListInsertBefore(list, (void *)70, node);
	node = My402ListFind(list, (void *)(10));
	ret = My402ListInsertAfter(list, (void *)80, node);
	fprintf(stdout,"Length: %d\n",My402ListLength(list));
	My402ListUnlink(list, node);
	Traverse(list);
	fprintf(stdout,"Length: %d\n",My402ListLength(list));
	My402ListUnlinkAll(list);
	fprintf(stdout,"Length: %d\n",My402ListLength(list));
	Traverse(list);
	return 0;
}*/
