#include <stdlib.h>
#include <math.h>
#include "List.h"

int chtbl_init(CHTbl **htbl, int (*hash)(CHTbl *htbl,void *key1), int (*match)(void *key1, void *key2),
	void (*destroy)(CHTbl *htbl), int (*remove)(CHTbl *htbl, void *key1), int (*insert)(CHTbl *htbl, void *key1), int (*get_size)(void *data),
	int (*search)(struct CHTbl_ *data, void *key1), size) {

	int i;
	if( ((*htbl)=(CHTbl*)malloc(sizeof(CHTbl))) == NULL)
		return -1;
		
	(*htbl)->size=size;
	(*htbl)->packets=0;
	(*htbl)->table=(void**)malloc((*htbl)->size*sizeof(void*));
	
	for(i=0;i<(*htbl)->size;i++)
	(*htbl)->table[i]=NULL;
	
	(*htbl)->hash=hash;
	(*htbl)->match=match;
	(*htbl)->destroy=destroy;
	(*htbl)->remove=remove;
	(*htbl)->insert=insert;
	(*htbl)->get_size=get_size;
	(*htbl)->search=search;
	
	return 0;
}

int chtbl_hash(CHTbl *htbl, void *key1) {
	
	int *ptr,number,htblIndex;
	double decFrac;
	
	ptr=(int*)key1;
	number=*ptr;

	decFrac=(double)number*((sqrt(5.0)-1.0)/2.0);
	htblIndex=( decFrac - (int) decFrac )*htbl->size;
	
	return htblIndex;
}

int chtbl_insert(CHTbl *htbl, void *key1) {
	
	int index;
	CList *list;
	LstElem *mvptr;
	
	index=chtbl_hash(htbl,key1);
	if(htbl->table[index]==NULL)
	{
		list=clist_crt();
		if(list->begpush(list,key1) != 0)
			return -1;
		htbl->table[index]=list;
	}
	else
	{
		list=htbl->table[index];
		mvptr=list->first;
		while(mvptr->next!=NULL)
		{
			if(htbl->match(mvptr->value,key1) == 0) //Are the same
				return -1;
			mvptr=mvptr->next;
		}
		if(list->endpush(list,key1) != 0)
			return -1;
	}
	
	htbl->packets++;
	return 0;
	
}

int chtbl_remove(CHTbl *htbl, void *key1) {
	
	
	if(htbl->search(htbl,key1) != 0)
		return -1;
		
	int index,lstindx;
	LstElem *mvptr;
	CList *list;
	index=htbl->hash(htbl,key1);
	list=htbl->table[index];
	mvptr=list->first;
	lstindx=0;
	
	while(mvptr!=NULL)
	{
		if(htbl->match(mvptr->value,key1) == 0)
		{
			list->pop(list,lstindx);
			htbl->packets--;
			return 0;
		}
		
		lstindx++;
		mvptr=mvptr->next;
	}
	
}

void chtbl_destroy(CHTbl *htbl) {
	
	int i;
	CList *list;
	for(i=0;i<htbl->size;i++)
	{
		list=htbl->table[i];
		if(list!=NULL)
		list->del(list);
		htbl->table[i]=NULL;
	}
	
	free(htbl);
	htbl->table=NULL;
	htbl->size=0;
	htbl->packets=0;
	return;

}

int chtbl_get_size(CHTbl *htbl) {
	
	return htbl->packets;
	
}

int chtbl_search(CHTbl *htbl, void *key1) {
	
	int index;
	LstElem *mvptr;
	CList *list;
	
	index=htbl->hash(htbl,key1);
	
	if(htbl->table[index]==NULL)
		return -1;
	
	list=htbl->table[index];
	mvptr=list->first;
	
	while(mvptr!=NULL)
	{
		if(htbl->match(mvptr->value,key1) == 0)
			return 0;
		
		mvptr=mvptr->next;
	}
	
	return -1;
	
}

CHTbl* chtbl_crt(int size, int (*match)(void *key1, void *key2))
{
	CHTbl *htbl;
	if( chtbl_init(&htbl,chtbl_hash,match,chtbl_destroy,chtbl_remove,chtbl_insert,chtbl_get_size,chtbl_search, size) == 0)
		return htbl;
	else
		return NULL;
}
