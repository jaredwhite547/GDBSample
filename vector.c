#include <wchar.h>
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "vector.h"

/*
struct strVec{
	size_t capacity;
	size_t size;
	char** arrP;
};

*/
//Returns a strvec, or NULL if allocation failed.
strVec* strVec_make(void){
	strVec* vec = malloc(sizeof(strVec));
	if(!vec){ return vec; }

	vec->capacity = 1;
	vec->size = 0;
	vec->arrP = malloc(sizeof(char*));
	if(!vec->arrP){
		free(vec);
		return NULL;
	}
	return vec;
}

//Adds a copy of str to rear of vec. Returns 0 if success, 1 otherwise;
int strVec_append(strVec* vec, const char* str){
	//assert(vec);

	return strVec_insert(vec, str, vec->size);
}


//Adds a copy of str into vec at position pos. Returns 0 if success, 1 otherwise
int strVec_insert(strVec* vec, const char* str, size_t pos){
	//assert(vec);
	//assert(vec->arrP);
	//assert(vec->capacity >= vec->size);
	//assert(pos <= vec->size);

	//Grow 
	if(vec->capacity == vec->size){
		char** expand = realloc(vec->arrP, sizeof(char*)*(vec->capacity*2));
		if(!expand) return 1;
		vec->arrP = expand;
		vec->capacity *=2;
	}

	//Shift
	if(vec->size != 0 && pos < vec->size){
		memmove(&(vec->arrP[pos+1]), &(vec->arrP[pos]), sizeof(char*) * (vec->size-pos));
	}

	//Copy and add
	char* arrString = malloc(sizeof(char)*(strlen(str)+1));
	if(!arrString) return 1;
	
	strcpy(arrString, str);
	
	vec->arrP[pos] = arrString;
	
	vec->size++;
	return 0;
}

//Deletes the last element
void strVec_pop_back(strVec* vec){
	//assert(vec);
	//assert(vec->arrP);
	//assert(vec->size != 0);

	//free(vec->arrP[--vec->size]);
	free(vec->arrP[vec->size]);
}

//Removes string at index, deleting it.
void strVec_remove(strVec* vec, size_t pos){
	//assert(vec);
	//assert(vec->arrP);
	//assert(pos < vec->size);

	if(vec->size - 1 == pos){	//End of vec 
		strVec_pop_back(vec);
		return;
	}

	free(vec->arrP[pos]);
	memmove(&(vec->arrP[pos]), &(vec->arrP[pos+1]), sizeof(char*) * (vec->size-1 - pos));
	vec->size--;
}

//Deletes and returns element at index
char* strVec_remove_return(strVec* vec, size_t pos){
	//assert(vec);
	//assert(vec->arrP);
	//assert(pos < vec->size);

	char* rval = strVec_get_copy(vec, pos);
	strVec_remove(vec, pos);
	return rval;
}

//Returns a copy of string at the given index
char* strVec_get_copy(const strVec* vec, size_t pos){
	//assert(vec);
	//assert(vec->arrP);
	//assert(pos < vec->size);

	char* result = malloc(sizeof(char)*(strlen(vec->arrP[pos])+1));
	if(!result) return NULL;
	strcpy(result, vec->arrP[pos]);
	return result;
}

//Deletes vec and the strings it contains. Using vec after calling this method is UB. frees vec itself.
void strVec_delete(strVec* vec){
	//assert(vec);
	//assert(vec->arrP);

	for(size_t i=0; i < vec->size; ++i){
		free(vec->arrP[i]);
	}

	free(vec->arrP);
	free(vec);
}

//Counts the number of strings in vec that match str exactly
size_t strVec_count(const strVec* vec, const char* str){
	//assert(vec);
	//assert(vec->arrP);

	size_t count = 0;
	for(size_t i= 0; i < vec->size; ++i){
		if(0 == strcmp(str, vec->arrP[i])) { ++count; }
	}
	return count;
}

//Returns index where str was found, or SIZE_MAX if not found
size_t strVec_findStr(const strVec* vec, const char* str){
	//assert(vec);
	//assert(vec->arrP);

	for(size_t i = 0; i < vec->size; ++i){
		if(0 == strcmp(str, vec->arrP[i])) { return i; }
	}
	return SIZE_MAX;
}


void strVec_print(const strVec* vec){
	//assert(vec);
	//assert(vec->arrP);
	for(unsigned long i=0; i < vec->size; ++i){
		printf("%lu%s\n", i, vec->arrP[i]);
	}
}
