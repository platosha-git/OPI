/*!
\file
\brief Код функций, обрабатывающих строки

Данный файл содержит функции, используемые при переводе числа из одной СС в другую
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "exit_codes.h"
#include "str_processing.h"

char *get_string(FILE *f)
{
	char *str = (char *) malloc(sizeof(char));
	str[0] = '\0';

	int exit_code = SUCCESS;
	int i = 0;
	char symb = fgetc(f);

	while (symb != '\n' && symb != EOF && exit_code == SUCCESS)
	{
		i++;
		str = (char *) realloc(str, (i + 1) * sizeof(char));
		str[i - 1] = symb;
		str[i] = '\0';
		symb = fgetc(f);
	}

	if (symb == EOF || i == 0 || exit_code != SUCCESS)
		return NULL;
	else
		return str;
}

int correct_input(char *str, FILE *fw)
{
	int exit_code = SUCCESS;
	if (str != NULL)
	{
		for (int i = 0; i < strlen(str) && exit_code == SUCCESS; i++)
		{
			if (str[i] != '0' && str[i] != '1' && str[i] != EOF)
			{
				fwrite("The count is incorrect.\n", strlen("The count is incorrect.\n"), 1, fw);
				exit_code = SYMB_ERROR;
			}
		}
	}	
	return exit_code;
}

char *translate(char *number)
{
	int len = strlen(number);
	int deg = 1, res = 0, j = 0;

	char *hec_number = (char *) malloc(sizeof(char));
	hec_number[0] = '\0';

	for (int i = len - 1; i >= 0; i--)
	{
		int count = number[i] - '0';
		res += count * deg;
		if (deg == 8)
		{
			if (res == 10)
				hec_number[j] = 'A';
			else if (res == 11)
				hec_number[j] = 'B';
			else if (res == 12)
				hec_number[j] = 'C';
			else if (res == 13)
				hec_number[j] = 'D';
			else if (res == 14)
				hec_number[j] = 'E';
			else if (res == 15)
				hec_number[j] = 'F';
			else
				hec_number[j] = res + '0';

			hec_number = (char *) realloc(hec_number, (j + 1) * sizeof(char));
			hec_number[j + 1] = '\0';
			deg = 1;
			res = 0;
			j++;
		}
		else
			deg *= 2;
	}

	if (len % 4 != 0)
	{
		hec_number[j] = res + '0';
		hec_number = (char *) realloc(hec_number, (j + 1) * sizeof(char));
		hec_number[j + 1] = '\0';
		j++;
	}
	hec_number = (char *) realloc(hec_number, j * sizeof(char));
	hec_number[j] = '\n';

	return hec_number;
}

void inverse(char **string)
{
	int len = strlen(*string);
	for (int i = 0; i < (len - 1) / 2; i++)
	{
		char temp = (*string)[i];
		(*string)[i] = (*string)[len - 2 - i];
		(*string)[len - 2 - i] = temp;
	}

	int i = 0;
	while (**string == '0' && *string) {
		(*string)++;
		i++;
	}

	if (i == len - 1)
		*string = "0\n";
}