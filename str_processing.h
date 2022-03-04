/*!
\file
\brief Заголовочный файл с описанием функций, обрабатывающих строки

Данный файл содержит функции, используемые при переводе числа из одной СС в другую
*/

#ifndef STR_PROCESSING_H
#define STR_PROCESSING_H

/*!
Считывает посимвольно строку из файла
\param[out] char* Строка
\param[in] FILE* Файловый указатель
*/
char *get_string(FILE *f);
/*!
Проверка строки на корректность записи
\param[out] int Код ошибки
\param[in] char* Строка
*/
int correct_input(char *str, FILE *fw);

/*!
Перевод числа из 2-чной СС в 16-ричную
\param str Строка, куда записано исходное число
\return Строку в 16-ричной системе счисления
*/
char *translate(char *number);

/*!
Разворот строки
\param[in] char* Указатель на строку
*/
void inverse(char **string);

#endif
