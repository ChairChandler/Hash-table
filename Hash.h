#ifndef HASH_H
#define HASH_H

typedef struct CHTbl_ {

	int (*hash)(struct CHTbl_ *htbl, void *key1); //Return the index of the object;
	int (*match)(void *key1, void *key2); //Compares the values of hash table index;
	void (*destroy)(struct CHTbl_ *data); //Delete the Hash table;
	int (*remove)(struct CHTbl_ *data, void *key1); //Delete the value from the Hash table;
	int (*insert)(struct CHTbl_ *data, void *key1); //Insert the value to the hash table;
	int (*get_size)(struct CHTbl_ *data); //Return the size of the hash table;
	int (*search)(struct CHTbl_ *data, void *key1); //Exchange the founded element in the Hash table; 

	int size; //Size of the table;
	int packets; //Amount of the all elements
	void **table; //Begin pointer of the table;

} CHTbl;

CHTbl* chtbl_crt(int size, int (*match)(void *key1, void *key2));

#endif
