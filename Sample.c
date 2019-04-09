#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "vector.h"

void appendToVector(char* str, strVec* vec){
	strVec_append(vec, str);
};

void printVector(strVec* vec){
	for(size_t i=0; i < vec->size; i++){
		printf("%s\n", strVec_get_copy(vec, i));
	}
};
		

int main(){
	char* s1 = "This is string 1";
	char* s2 = "This is string 2";
	char* s3 = "This is string 3";
	char* s4 = "This is string 4";
	char* s5 = "This is string 5";

	strVec* vec = strVec_make();
	appendToVector(s5,vec);
	appendToVector(s4,vec);
	strVec_insert(vec, s3, 4);
	printVector(vec);


	return 0;
};
