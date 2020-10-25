#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>

struct string {
	char* p;
	int len;
};

typedef struct string str;

size_t size_file();
void input_file(char* buf, size_t size);
long long separator(char* buf, size_t size);
void string_array(long long nStrings, char* buf, str* text);
int comparator(const void *str1, const void *str2);
void output_file(long long nStrings, str* strings);



int main()
{
	size_t size = size_file();
	char* buf = (char*) calloc (size + 1, sizeof (char));
	input_file(buf, size);
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

size_t size_file()
{
	FILE* ptrFile = fopen("hamlet.txt", "r");
	assert (ptrFile != NULL);

	int c = fseek(ptrFile, 0, SEEK_END);
	assert (c == 0);
	// assert ((feof(ptrFile + 1)) != 0);
	size_t size = ftell(ptrFile);
	assert (size > 0);
	fclose(ptrFile);

	// printf("Size of file: %ld\n", size);
	return size; 
}


void input_file(char* buf, size_t size)
{
	FILE* ptrFile = fopen("hamlet.txt", "r");
	assert (ptrFile != NULL);
	fread(buf, sizeof (char), size, ptrFile);
	fclose(ptrFile);

	// for (int i = 0; i < size; i++)
	// {
	// 	printf("%c", buf[i]);
	// 	// printf("\n");
	// }

	// // printf("\n");
}

long long separator(char* buf, size_t size)
{
	long long nStrings = 0;

	for (int i = 0; i < size; i++)
	{
		if (buf[i] == '\n')
		{ 
			buf[i] = '\0';
			nStrings++;
		}
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

 int comparator(const void *str1, const void *str2)
 {
 	str*  first_string = (str*) str1;
 	str* second_string = (str*) str2;


	// printf("%s\n",  first_string->p);
	// printf("%s\n", second_string->p);

 	return strcmp(first_string->p, second_string->p);
 }

 
 void output_file(long long nStrings, str* strings)
 {
 	FILE* ptrFile = fopen("output.txt", "w");
	assert (ptrFile != 0);

	for (int i = 0; i < nStrings; i++)
	{
		// if (isspace(((int) *(strings[i].p)) == false)) 
		fprintf(ptrFile, "%s\n", strings[i].p);
	}

	fclose(ptrFile);
 }