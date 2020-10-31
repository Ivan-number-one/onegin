#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>

struct string {
	char* p = NULL;
	int len = 0;
};

typedef struct string str;

char* input_file(size_t* size, char** argv);
long long separator(char* buf, size_t size);
void string_array(long long nStrings, char* buf, str* text);
int comparator(const void *str1, const void *str2);
void output_file(long long nStrings, str* strings);



int main(int argc, char** argv)
{
	size_t size = 0;
	char* buf = input_file(&size, argv);
	long long nStrings = separator(buf, size);
	
	str* strings = (str*) calloc (nStrings + 1, sizeof (str));
	assert (strings != NULL);
	string_array(nStrings, buf, strings);

	qsort(strings, nStrings, sizeof (str), &comparator);
	output_file(nStrings, strings);
	// printf("%d\n", comparator(strings, strings + 1));


	
	free (buf);
	free (strings);

	return 0;
}

char* input_file(size_t* size, char** argv)
{
	FILE* ptrFile = fopen(argv[1], "r");
	assert (ptrFile != NULL);

	int c = fseek(ptrFile, 0, SEEK_END);
	assert (c == 0);
	*size = ftell(ptrFile);
	assert (*size > 0);
    rewind(ptrFile);

	char* buf = (char*) calloc (*size + 1, sizeof (char));
	assert (buf != NULL);
	fread(buf, sizeof (char), *size, ptrFile);
	fclose(ptrFile);

	// printf("Size of file: %ld\n", size);
	return buf; 
}


long long separator(char* buf, size_t size)
{
	long long nStrings = 0;
	char* c = buf;

	while ((c = strchr(c, '\n')) != NULL)
	{
		*c = '\0';
		c++;
		nStrings++;
	}

	// for (int i = 0; i < size; i++)
	// {
	// 	printf("%c", buf[i]);
	// }

	// printf("\n");
	// printf ("%lld\n", nStrings);

	return nStrings;
}

void string_array(long long nStrings, char* buf, str* text)
{
	int n = 0;
	char* isZero = NULL;
	char* ptr = buf;
	text[0].p = buf;
	text[0].len = strlen(buf);

	for (int i = 0; i < nStrings; i++)
	{
		if ((isZero = strchr(ptr, '\0')) && (n < nStrings))
		{
			n++;
			text[n].p = isZero + 1;
			text[n].len = strlen(isZero + 1);
		}
		ptr = isZero + 1;
		assert (isZero != NULL);
	}
	assert (n  == nStrings);
	// printf("%d\n", n);
	// printf("%s\n", text[0]);
	// printf("%s\n%d\n", text[6].p, text[6].len);
}

 int comparator(const void *first_string, const void *second_string)
 {
 	str* str1 = (str*) first_string;
 	str* str2 = (str*) second_string;

    int max_len = 0;
 	int k1, k2  = 0;
 	if ((str1->len) > (str2->len)) max_len = str1->len;
    else max_len = str2->len;

 	for (; (k1 < str1->len) && (k2 < str2->len) && (str1->p[k1] != '\0') && (str2->p[k2] != '\0'); )
 	{
 		if (isalpha(str1->p[k1]) != 0 && isalpha(str2->p[k2]) != 0)                   // a*a ba
 		{                                                                             // aabc
 			if      (str1->p[k1] >  str2->p[k2]) return  1;                           // max_len = 5
 			else if (str1->p[k1] <  str2->p[k2]) return -1;
 			else if (str1->p[k1] == str2->p[k2]) 
 				{
 					k1++;
 					k2++;
 					// i++;
 				}

 			// if (i - 1 == max_len) return 0;
 		}

 		else
 		{
 		if      (isalpha(str1->p[k1]) == 0 && isalpha(str2->p[k2]) != 0) k1++;
 		else if (isalpha(str1->p[k1]) != 0 && isalpha(str2->p[k2]) == 0) k2++;
 		else if (isalpha(str1->p[k1]) == 0 && isalpha(str2->p[k2]) == 0)
			{
				k1++;
				k2++;
			}
		// i++;
		}
	}

 	// if (isalpha(first_string->(p + i))

	// printf("%s\n", str1->p);
	// printf("%s\n", str2->p);
	// printf("%c\n", str2->p[1]);
	// printf("%d\n", max_len);

 	// return strcmp(first_string->p, second_string->p);
 	return 0;
 }

 
 void output_file(long long nStrings, str* strings)
 {
 	FILE* ptrFile = fopen("output.txt", "w");
	assert (ptrFile != 0);

	for (int i = 0; i < nStrings; i++)
	{
		if (strings[i].len > 0) 
		fprintf(ptrFile, "%-s\n", strings[i].p);
	}

	fclose(ptrFile);
	// printf("%d\n", strings[0].len);
 } 