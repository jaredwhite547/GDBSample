#ifndef VECTOR_H
#define VECTOR_H
#include <wchar.h>
#include <stdbool.h>

typedef struct strVec{
	size_t capacity;
	size_t size;
	char** arrP;
} strVec;


strVec* strVec_make(void);

int	strVec_append(strVec* vec, const char* str);

int	strVec_insert(strVec* vec, const char* str, size_t pos);

void	strVec_pop_back(strVec* vec);

void	strVec_remove(strVec* vec, size_t pos);

char*	strVec_remove_return(strVec* vec, size_t pos);

char*	strVec_get_copy(const strVec* vec, size_t pos);

void	strVec_delete(strVec* vec);

size_t	strVec_count(const strVec* vec, const char* str);

size_t	strVec_findStr(const strVec* vec, const char* str);

void strVec_print(const strVec* vec);

#endif	//VECTOR_H
