#ifndef LIST_H
#define LIST_H

/*
Operacje:
1.Utwórz								CList* clist_crt(void)
2.Dodaj element na pocz¹tek				int List_begpush(CList *head,void *elem)
3.Usuñ element z pocz¹tku				void List_begpop(CList *head)
4.Dodaj element na koñcu				int List_endpush(CList *head,void *elem)
5.Usuñ element z koñca					void List_endpop(CList *head)
6.Dodaj element w dow. miejscu			int List_push(CList *head,void *elem,int index)
7.Usuñ element z dow. miejsca			void List_pop(CList *head,int index)
8.Podaj rozmiar							int List_size(CList *head)
9.Usuñ									void List_del(CList *head)
10.Wypisz								void List_print(CList *head)
*/

typedef struct LstElem_ {
	
	void *value;
	struct LstElem_ *next;
		
} LstElem;

typedef struct CList_ {
	
	struct LstElem_ *first;
	struct LstElem_ *last;
	int iSize;
	
	int 	(*begpush)	(struct CList_ *head,void *elem);
	void* 	(*begpop)	(struct CList_ *head);
	int 	(*endpush)	(struct CList_ *head,void *elem);
	void* 	(*endpop)	(struct CList_ *head);
	int 	(*push)		(struct CList_ *head,void *elem,int index);
	void* 	(*pop)		(struct CList_ *head,int index);
	int 	(*size)		(struct CList_ *head);
	void 	(*del)		(struct CList_ *head);
	void 	(*print)	(struct CList_ *head);
		
} CList;

CList* clist_crt(void);

#endif
