#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>

#define DEBUG false
#define DBG(expr) if (DEBUG) {expr}

#define    QSORT 1
#define	MY_QSORT 0

#if MY_QSORT
#define qsort1 qsort(strings, nStrings, sizeof (str), &comparator)
#define qsort2 qsort(strings, nStrings, sizeof (str), &reverse_comparator)
#define my_qsort1 ;
#define my_qsort2 ;
#else 
#define my_qsort1 my_qsort(strings, 0, nStrings - 1, &comparator)
#define my_qsort2 my_qsort(strings, 0, nStrings - 1, &reverse_comparator)
#define qsort1 ;
#define qsort2 ;
#endif

struct string {
	char* p = NULL;
	int len = 0;
};
	
typedef struct string str;

char* input_file(size_t* size, char** argv);
long long separator(char* buf, size_t size);
void string_array(long long nStrings, char* buf, str* text);
void my_qsort(str* strings, int begin, long long end, int compare(const void *first_string, const void *second_string));
int comparator(const void *first_string, const void *second_string);
int reverse_comparator(const void *first_string, const void *second_string);
void changer(char sym, char* letter);
void output_file(long long nStrings, str* strings, const char* mode);
void print_array(char* buf, long long nStrings, const char* mode);
void swap (str* str1, str* str2);
void unit_tests(); 
bool test1();
bool test2();
bool test3();