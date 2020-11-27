#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <locale.h>

#define DEBUG false
#define DBG(expr) if (DEBUG) {expr}

#define    QSORT 1
#define	MY_QSORT 0

// Choosing qsort or my_qsort
#if QSORT
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

// String structure
struct string {
	char* p = NULL;
	int len = 0;
};

typedef struct string str;
//{
//!
//!  \mainpage
//!
//!  \author     banana_nigga
//!  \brief      String sort program
//!  \version    2.0
//!  \param[in]  Name_of_file
//!
//! This program sorts the strings at the beginning and the end.
//!
//}

/*!
 \brief Fills buffer from the file and counts amount of symbols
 \param [out] size - size of file i.e amount of symbols
 \param [in] argv - name of file
 \return buf - pointer to the beginning of array with symbols
*/
char* input_file(size_t* size, char** argv);

/*!
Counts amount of strings
\param[in] buf - pointer to the beginning of array with symbols
\param[in] size - size of file i.e amount of symbols
\
\return nStrings - amount of strings
*/
long long separator(char* buf, size_t size);

/*!
Fills array of string structures
\param[in] nStrings - amount of strings
\param[in] buf  - pointer to the beginning of array with symbols
\param[in] text - pointer to the beginning of array with string structures
*/
void string_array(long long nStrings, char* buf, str* text);

/*!
Quick sort for the strings
\param[in] strings - pointer to array of string structures
\param[in] end - right border for the comparison
\param[in] begin - left border for the comparison
*/
void my_qsort(str* strings, int begin, long long end, int compare(const void *first_string, const void *second_string));

/*!
Comparator for comparing strings in lexicographic order from the beginning of the string
\param[in] first_string  - pointer to the string structure
\param[in] second_string - pointer to the string structure
\return the result of the comparison
*/
int comparator(const void *first_string, const void *second_string);

/*!
Comparator for comparing strings in lexicographic order from the end of the string
\param[in] first_string  - pointer to the string structure
\param[in] second_string - pointer to the string structure
\return the result of the comparison
*/
int reverse_comparator(const void *first_string, const void *second_string);

/*!
Changes capital letter on small
\param[in] sym - capital letter
\param[out] letter - pointer to capital letter
*/
void changer(char sym, char* letter);

/*!
Prints text to a file from structure array
\param[in] nStrings - amount of strings
\param[in] strings - pointer to the beginning of array with string structures
\param[in] mode - mode of opening file
*/
void output_file(long long nStrings, str* strings, const char* mode);

/*!
Prints text to a file from symbol array
\param[in] buf  - pointer to the beginning of array with symbols
\param[in] nStrings - amount of strings
\param[in] mode - mode of opening file
*/
void print_array(char* buf, long long nStrings, const char* mode);

/*!
Swap two lines
\param[in] str1 - the right operand of the swap
\param[in] str2 - the right operand of the swap
*/
void swap (str* str1, str* str2);

void unit_tests();
bool test1();
bool test2();
bool test3();
