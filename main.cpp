#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <locale.h>
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
	
	free (buf);
	free (strings);

	return 0;
}