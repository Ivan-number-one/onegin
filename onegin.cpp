#include "onegin.h"

int main(int argc, char** argv)
{	
	setlocale(LC_ALL, "ru_RU.cp1251");
	unit_tests();

	size_t size = 0;
	char* buf = input_file(&size, argv);
	long long nStrings = separator(buf, size);
	
	str* strings = (str*) calloc (nStrings + 1, sizeof (str));
	assert (strings != NULL);
	string_array(nStrings, buf, strings);

	qsort1;
	my_qsort1;
	output_file(nStrings, strings, "w");

	qsort2;
	my_qsort2;
	output_file(nStrings, strings, "a");

	print_array(buf, nStrings, "a");


	// DBG(printf("%d\n", comparator(strings, strings + 1));
	// for (int i = 0; i < strings[0].len; i++)
	// {
	// 	printf("symbol: %c  code: %d\n", *(strings[0].p + i), *(strings[0].p + i));
	// 	printf("%d", isalpha(*strings[10].p));
	// })

	
	free (buf);
	free (strings);

	return 0;
}



// ---------------------------------------------------------------- FUNCTIONS -------------------------------------------------------\\




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

	DBG(printf("Size of file: %ld\n", *size);)
	return buf; 
}

void unit_tests() 
{
	bool res1 = test1();
	if (res1 == false) printf("TEST 1 failed");
	else printf("TEST 1 passed\n");

	bool res2 = test2();
	if (res2 == false) printf("TEST 2 failed");
	else printf("TEST 2 passed\n");

	bool res3 = test3();
	if (res3 == false) printf("TEST 3 failed");
	else printf("TEST 3 passed\n");
}

bool test1()
{
	str s1 = {(char*) "aaa", 3};
	str s2 = {(char*) "bbb", 3};
	str s3 = {(char*) "ccc", 3};

	str s[] = {s2, s1, s3};

	my_qsort(s, 0, 2, &comparator);

	if ((s[0].p == (char*) "aaa") && (s[1].p == (char*) "bbb") && (s[2].p == (char*) "ccc")) 
		return true;

    return false;
}

bool test2()
{
	str s1 = {(char*) "a*a*a",  5};
	str s2 = {(char*) "bb*b",   4};
	str s3 = {(char*) "ccc **", 6};

	str s[] = {s3, s1, s2};

	my_qsort(s, 0, 2, &comparator);

	if ((s[0].p == (char*) "a*a*a") && (s[1].p == (char*) "bb*b") && (s[2].p == (char*) "ccc **")) 
		return true;

    return false;
}

bool test3()
{
	str s1 = {(char*) " zzza", 5};
	str s2 = {(char*) "a b c", 5};
	str s3 = {(char*) "*8* hpo", 7};

	str s[] = {s2, s1, s3};

	my_qsort(s, 0, 2, &comparator);

	if ((s[0].p == (char*) "a b c") && (s[1].p == (char*) "*8* hpo") && (s[2].p == (char*) " zzza")) 
		return true;

    return false;
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

	DBG(for (int i = 0; i < size; i++)
	{
		printf("%c", buf[i]);
	}

	printf("\n");
	printf ("%lld\n", nStrings + 1);)

	return nStrings + 1;
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
	DBG(printf("%d\n", n);
	printf("%s\n", text[0].p);
	printf("%s\n%d\n", text[6].p, text[6].len);)
}

 int comparator(const void *first_string, const void *second_string)
 {
 	str* str1 = (str*) first_string;
 	str* str2 = (str*) second_string;

    
 	int  k1 = 0, k2  = 0;
 	int letter1 = 0, letter2 = 0; 

 	while ((k1 < str1->len) && (k2 < str2->len))
 	{
 		if (isalpha((int)(unsigned char) str1->p[k1]) != 0 && isalpha((int)(unsigned char)( str2->p[k2])) != 0)                 
 		{
 			letter1 = (int)(unsigned char)(str1->p[k1]);
 			letter2 = (int)(unsigned char)(str2->p[k2]);                                                               
 			if (letter1 >  letter2) return  1;        // Acts little of his will. Tell me, Laertes,                  
 			if (letter1 <  letter2) return -1;        // ACT V
 			if (letter1 == letter2) 
 				{
 					k1++;
 					k2++;
 					continue;
 				}
 		}

 	
 		if (isalpha((int)(unsigned char) (str1->p[k1])) == 0 && isalpha((int)(unsigned char) (str2->p[k2])) != 0) k1++;
 		if (isalpha((int)(unsigned char) (str1->p[k1])) != 0 && isalpha((int)(unsigned char) (str2->p[k2])) == 0) k2++;
 		if (isalpha((int)(unsigned char) (str1->p[k1])) == 0 && isalpha((int)(unsigned char) (str2->p[k2])) == 0)
			{
				k1++;
				k2++;
			}
	}


	DBG(printf("%s\n", str1->p);
	printf("%s\n", str2->p);
	printf("%c\n", str2->p[1]);)

 	return str1->len - str2->len;
 }


 int reverse_comparator(const void *first_string, const void *second_string)
{
	str* str1 = (str*) first_string;
 	str* str2 = (str*) second_string;

 	int  k1 = str1->len - 1, k2  = str2->len - 1;
 	unsigned char letter1 = 0, letter2 = 0; 

 	while ((k1 >= 0) && (k2 >= 0))
 	{
 		if (isalpha(str1->p[k1]) != 0 && isalpha(str2->p[k2]) != 0)                 
 		{
 			letter1 = tolower(str1->p[k1]);
 			letter2 = tolower(str2->p[k2]);
 			// if (letter1 < 'a')        
 		 //    changer(letter1, &letter1);
 		 //    if (letter2 < 'a')        
 		 //    changer(letter2, &letter2);
 			if (letter1 >  letter2) return  1;        // ssact]     len = 6                  
 			if (letter1 <  letter2) return -1;        // act{,      len = 5
 			if (letter1 == letter2) 
 				{
 					k1--;
 					k2--;
 					continue;
 				}
 		}

 	
 		if (isalpha(str1->p[k1]) == 0 && isalpha(str2->p[k2]) != 0) k1--;
 		if (isalpha(str1->p[k1]) != 0 && isalpha(str2->p[k2]) == 0) k2--;
 		if (isalpha(str1->p[k1]) == 0 && isalpha(str2->p[k2]) == 0)
			{
				k1--;
				k2--;
			}
	}

 	return str1->len - str2->len;
}



 void changer(char sym, char* letter)
{
	// z - a = Z - A
	// a = z - Z + A

	*letter = 'z' - ('Z' - sym);
}

 

 void output_file(long long nStrings, str* strings, const char* mode)
{
 	FILE* ptrFile = fopen("output.txt", mode);
	assert (ptrFile != 0);

	for (int i = 0; i < nStrings; i++)
	{
		if (strings[i].len > 0) 
		fprintf(ptrFile, "%-s\n", strings[i].p);
	}
	
	fprintf(ptrFile, "\n\n\n");	

	for (int i = 0; i < 30; i++)
	{
		fprintf(ptrFile, "%c%c%c", '-', '|', '-');
	}

	fprintf(ptrFile, "\n\n\n\n");
		
	fclose(ptrFile);
	DBG(printf("%d\n", strings[0].len);)
 }


 void print_array(char* buf, long long nStrings, const char* mode)
 {	
 	FILE* ptrFile = fopen("output.txt", mode);
	assert (ptrFile != 0);

 	int n = 0;

	for (int i = 0; i < nStrings; i++)
	{
		fprintf(ptrFile, "%s%n\n", buf, &n);
		buf += n + 1;
	}

	fclose(ptrFile); 	
 } 


void my_qsort(str* strings, int begin, long long end, int compare(const void *first_string, const void *second_string))
{
	int pivot = (begin + end) / 2;
	str base_str = strings[pivot];

	DBG(printf("\n\n\nqsort starts with %d ends with %lld\n", begin, end);
	printf("Pivot str = %s;\n", base_str.p);)

	int l = begin, r = end;

	DBG(printf("begin str = %s; end str = %s\n\n\n", strings[l].p, strings[r].p);)
	while (l <= r)
	{
		while (compare(&base_str, strings + l) >=  1) 
			l++;
		while (compare(&base_str, strings + r) <= -1)
			r--;
		if (l <= r)
		{
			DBG(printf("\n swapping %d with %d elem\n", l, r);)
			swap(strings + l, strings + r);
			l++;
			r--;
		}
	}

	if (begin < r)
		my_qsort(strings, begin, r, compare);
	if (l < end)
		my_qsort(strings, l, end, compare);
}

void swap (str* str1, str* str2)
{

	assert(str1);
	assert(str2);

	DBG(printf("\n\n\n before swapping %s ------------ with %s\n\n\n", str1->p, str2->p);)

	str temp = *str1;
	*str1 = *str2;
	*str2 = temp;

	DBG(printf("\n\n\n after swapping %s ------------ with %s\n\n\n", str1->p, str2->p);)
}