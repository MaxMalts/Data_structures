#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define EOB -1   //признак конца буфера
#define ERR_BUF {NULL, 0, -1, 0}    //буфер - ошибка

#define BSEEK_SET 0
#define BSEEK_CUR 1
#define BSEEK_END 2


/**
*	Буфер (строка с курсором)
*/

struct buf_t {
	char* str = {};
	int cursor = 0;
	int size = 0;
	char mode = 0;
	int lastChar = 0;
};



/**
*	Создает буфер в режиме чтения
*
*	@param[in] mode Режим (должен быть 'r')
*	@param str Строка, которую кладем в буфер
*	@param[in] strSize Размер строки (буфера)
*	@param[out] err Код ошибки: 1 - mode != 'r'; 0 - все прошло нормально
*
*	@return Созданный буфер (в случае ошибки равен ERR_BUF).
*/

buf_t BufConstructor(const char mode, char* str, const int strSize, int* err = NULL);


/**
*	Создает буфер в режиме записи
*
*	@param[in] mode Режим (должен быть 'w')
*	@param[out] err Код ошибки: 1 - mode != 'w'; 0 - все прошло нормально
*
*	@return Созданный буфер (в случае ошибки равен ERR_BUF).
*/

buf_t BufConstructor(const char mode, int* err = NULL);


/**
*	Пишет символ в буфер
*
*	@param buf Буфер
*	@param[in] ch Символ
*
*	@return 1 - буфер не в режиме записи; 2 - не удалось увеличить размер буфера;\
 0 - все прошло нормально
*/

int Bputc(buf_t* buf, const char ch);


/**
*	Читает символ из буфера
*
*	@param[in] buf Буфер
*
*	@return Считанный символ. При достижении конца буфера, возвращает EOB.\
 Если вернулось -2, то буфер не в режиме чтения.
*/

char Bgetc(buf_t* buf);


/**
*	Аналогичная printf функция для буфера
*
*	@param[in] buf Буфер
*	@param[in] format Строка фармата
*	@param[in] args Аргументы
*
*	@return В случае успеха возвращает количество записанныз символов.\
 Если значение отрицательно, то произошли следующие ошибки:\
 -403 - буфер не в режиме записи; -401 - не удалось увеличить размер буфера\
 ост. - ошибка при записи, проверьте корректность входных параметров
*/

template<typename... args_t>
int Bprintf(buf_t* buf, const char* format, args_t... args);


/**
*	Аналогичная scanf функция для буфера
*
*	@param[in] buf Буфер
*	@param[in] format Строка фармата
*	@param[in] args Аргументы
*
*	@return В случае успеха возвращает количество прочитанных параметров.\
 Если значение отрицательно, то произошли следующие ошибки:\
 -1 - буфер не в режиме чтения; -2 - ошибка при чтении,\
 проверьте корректность входных параметров
*/

template<typename... args_t>
int Bscanf(buf_t* buf, const char* format, args_t... args);


/**
*	Пишет строку в конец буфера
*
*	@param buf
*	@param[in] str
*
*	@return 1 - буфер не в режиме записи; 2 - проблема при дописывании; 0 - все прошло нормально
*/

int Bufcat(buf_t* buf, const char* str);


/**
*	Прверяет, является ли символ одним из данных
*
*	@param[in] ch Проверяемый символ
*	@param[in] chars Массив символов
*
*	@return 0 (false) - не является; 1 (true) - является
*/

int IsOneOfChars(const char ch, const char* chars);


/**
*	Читает из буфера до одного из заданного символов
*
*	@param[out] str Строка, в которую прочитается
*	@param[in] buf Буфер
*	@param[in] chars Массив конечных символов
*
*	@return 1 - символ не найден, курсор остается на том же месте;\
 0 - все прошло нормально
*/

int ReadToChar(char* str, buf_t* buf, const char* chars);


/**
*	Устанавливает курсор в буфере в соответствии со значениями offset и origin
*
*	@param buf Буфер
*	@param[in] offset Сдвиг относительно позиции, соответствуйщей origin
*	@param[in] origin Начальная позиция: BSEEK_SET - начало буфера;\
 BSEEK_CUR - текущая позиция курсора; BSEEK_END - конец буфера
*
*	@return 1 - некорректное значение origin; 2 - курсор выходит за границы буфера;\
 0 - все прошло нормально
*/

int Bseek(buf_t* buf, int offset, int origin);


/**
*	Возвращает текущее положение курсора в буфере
*
*	@param[in] buf Буфер
*
*	@return Текущее положение курсора в буфере
*/


int Btell(buf_t* buf);


/**
*	Удаляет буфер. Если он был в режиме чтения, то память со строкой не освобождается!
*
*	@param[in] buf Буфер
*
*	@return 1 - некорректный буфер на входе; 0 - все прошло нормально
*/

int BufDestructor(buf_t* buf);





int IncreaseBuf(buf_t* buf, const int newSize);

void RecalcLastChar(buf_t* buf);


/*
*	Аналогичная printf функция для буфера
*
*	@param[in] buf Буфер
*	@param[in] format Строка фармата
*	@param[in] args Аргументы
*
*	@return В случае успеха возвращает количество записанныз символов.\
 Если значение отрицательно, то произошли следующие ошибки:\
 -403 - буфер не в режиме записи; -401 - не удалось увеличить размер буфера\
 ост. - ошибка при записи, проверьте корректность входных параметров
*/

template<typename... args_t>
int Bprintf(buf_t* buf, const char* format, args_t... args) {
	assert(buf != NULL);
	assert(format != NULL);

	const int stringMaxSize = 100000;

	if (buf->mode != 'w') {
		return -403;
	}

	char tempStr[stringMaxSize] = "";
	int printLen = sprintf(tempStr, format, args...);

	if (printLen < 0) {
		return printLen;
	}
	
	if (buf->cursor + printLen >= buf->size) {
		if (IncreaseBuf(buf, (buf->size + printLen) * 2) != 0) {
			return -401;
		}
	}

	strncpy(&buf->str[buf->cursor], tempStr, printLen);
	buf->cursor += printLen;

	RecalcLastChar(buf);

	return printLen;
}


/*
*	Аналогичная scanf функция для буфера
*
*	@param[in] buf Буфер
*	@param[in] format Строка фармата
*	@param[in] args Аргументы
*
*	@return В случае успеха возвращает количество прочитанных параметров.\
 Если значение отрицательно, то произошли следующие ошибки:\
 -1 - буфер не в режиме чтения; -2 - ошибка при чтении,\
 проверьте корректность входных параметров
*/

template<typename... args_t>
int Bscanf(buf_t* buf, const char* format, args_t... args) {
	assert(buf != NULL);
	assert(format != NULL);

	if (buf->mode != 'r') {
		return -1;
	}

	int formatLen = strlen(format);
	const char* newFormat = (char*)calloc(formatLen + 3, sizeof(char));
	sprintf((char*)newFormat, "%s%%n", format);

	int charsRead = 0;
	int scanRet = sscanf(&buf->str[buf->cursor], newFormat, args..., &charsRead);
	if (scanRet != sizeof...(args)) {
		return -2;
	}

	buf->cursor += charsRead;

	return scanRet;
}