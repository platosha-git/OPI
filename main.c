/*!
\file
\brief Функция main

Функция включает в себя работу с входным файлом и создает выходной, куда записывает данные 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "exit_codes.h"
#include "str_processing.h"

#define FILE_TO_WRITE "write.txt"

int main(void)
{
	int exit_code = SUCCESS;

/*!
    Содержит обработку входного файла: его открытие и проверку на корректность

    \code
	FILE *fr = fopen(FILE_TO_READ, "r");
	if (!fr)
	{
		printf("The file to read does not exist.\n");
		exit_code = READ_ERROR;
	}
    \endcode
*/
	char *file_to_read = (char *) malloc(sizeof(char));
    file_to_read[0] = '\0';

    char symb;
    int i = 0;
    while (scanf("%c", &symb) == 1)
    {
        i++;
        file_to_read = (char *) realloc(file_to_read, i * sizeof(char));
        if (symb != '\n')
            file_to_read[i - 1] = symb;
        else {
            file_to_read[i - 1] = '\0';
            break;
        }
    }
    FILE *fw = fopen(FILE_TO_WRITE, "w");
	FILE *fr = fopen(file_to_read, "r");
	if (!fr)
	{
		fwrite("The file to read does not exist.\n", strlen("The file to read does not exist.\n"), 1, fw);
		exit_code = READ_ERROR;
	}

	if (exit_code == SUCCESS)
	{
		char *bin_number = get_string(fr);
		if (bin_number == NULL)
		{
			fwrite("The file to read is empty.\n", strlen("The file to read is empty.\n"), 1, fw);
			exit_code = READ_EMPTY;
		}
		
		if (exit_code == SUCCESS)
		{

/*!
    Обработка строки в цикле: ее перевод(вызов необходимых функций) и запись в выходной файл 

    \code
		hec_number = translate(bin_number);
		inverse(&hec_number);
		fwrite(hec_number, strlen(hec_number), 1, fw);
    \endcode
*/
			exit_code = correct_input(bin_number, fw);
			char *hec_number = NULL;
			while (bin_number != NULL && exit_code == SUCCESS)
			{	 
				hec_number = translate(bin_number);
				inverse(&hec_number);
				fwrite(hec_number, strlen(hec_number), 1, fw);
				bin_number = get_string(fr);
				exit_code = correct_input(bin_number, fw);
			}

			if (bin_number == NULL && get_string(fr) != NULL)
			{
				fwrite("The count is incorrect.\n", strlen("The count is incorrect.\n"), 1, fw);
				exit_code = READ_EMPTY;
			}

			free(hec_number);
		}
		free(bin_number);
		fclose(fr);
	}
	fclose(fw);
	return exit_code;
}