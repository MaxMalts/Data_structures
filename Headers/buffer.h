#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define EOB -1   //������� ����� ������
#define ERR_BUF {NULL, 0, -1, 0}    //����� - ������

#define BSEEK_SET 0
#define BSEEK_CUR 1
#define BSEEK_END 2


/**
*	����� (������ � ��������)
*/

struct buf_t {
	char* str = {};
	int cursor = 0;
	int size = 0;
	char mode = 0;
	int lastChar = 0;
};



/**
*	������� ����� � ������ ������
*
*	@param[in] mode ����� (������ ���� 'r')
*	@param str ������, ������� ������ � �����
*	@param[in] strSize ������ ������ (������)
*	@param[out] err ��� ������: 1 - mode != 'r'; 0 - ��� ������ ���������
*
*	@return ��������� ����� (� ������ ������ ����� ERR_BUF).
*/

buf_t BufConstructor(const char mode, char* str, const int strSize, int* err = NULL);


/**
*	������� ����� � ������ ������
*
*	@param[in] mode ����� (������ ���� 'w')
*	@param[out] err ��� ������: 1 - mode != 'w'; 0 - ��� ������ ���������
*
*	@return ��������� ����� (� ������ ������ ����� ERR_BUF).
*/

buf_t BufConstructor(const char mode, int* err = NULL);


/**
*	����� ������ � �����
*
*	@param buf �����
*	@param[in] ch ������
*
*	@return 1 - ����� �� � ������ ������; 2 - �� ������� ��������� ������ ������;\
 0 - ��� ������ ���������
*/

int Bputc(buf_t* buf, const char ch);


/**
*	������ ������ �� ������
*
*	@param[in] buf �����
*
*	@return ��������� ������. ��� ���������� ����� ������, ���������� EOB.\
 ���� ��������� -2, �� ����� �� � ������ ������.
*/

char Bgetc(buf_t* buf);


/**
*	����������� printf ������� ��� ������
*
*	@param[in] buf �����
*	@param[in] format ������ �������
*	@param[in] args ���������
*
*	@return � ������ ������ ���������� ���������� ���������� ��������.\
 ���� �������� ������������, �� ��������� ��������� ������:\
 -403 - ����� �� � ������ ������; -401 - �� ������� ��������� ������ ������\
 ���. - ������ ��� ������, ��������� ������������ ������� ����������
*/

template<typename... args_t>
int Bprintf(buf_t* buf, const char* format, args_t... args);


/**
*	����������� scanf ������� ��� ������
*
*	@param[in] buf �����
*	@param[in] format ������ �������
*	@param[in] args ���������
*
*	@return � ������ ������ ���������� ���������� ����������� ����������.\
 ���� �������� ������������, �� ��������� ��������� ������:\
 -1 - ����� �� � ������ ������; -2 - ������ ��� ������,\
 ��������� ������������ ������� ����������
*/

template<typename... args_t>
int Bscanf(buf_t* buf, const char* format, args_t... args);


/**
*	����� ������ � ����� ������
*
*	@param buf
*	@param[in] str
*
*	@return 1 - ����� �� � ������ ������; 2 - �������� ��� �����������; 0 - ��� ������ ���������
*/

int Bufcat(buf_t* buf, const char* str);


/**
*	��������, �������� �� ������ ����� �� ������
*
*	@param[in] ch ����������� ������
*	@param[in] chars ������ ��������
*
*	@return 0 (false) - �� ��������; 1 (true) - ��������
*/

int IsOneOfChars(const char ch, const char* chars);


/**
*	������ �� ������ �� ������ �� ��������� ��������
*
*	@param[out] str ������, � ������� �����������
*	@param[in] buf �����
*	@param[in] chars ������ �������� ��������
*
*	@return 1 - ������ �� ������, ������ �������� �� ��� �� �����;\
 0 - ��� ������ ���������
*/

int ReadToChar(char* str, buf_t* buf, const char* chars);


/**
*	������������� ������ � ������ � ������������ �� ���������� offset � origin
*
*	@param buf �����
*	@param[in] offset ����� ������������ �������, ��������������� origin
*	@param[in] origin ��������� �������: BSEEK_SET - ������ ������;\
 BSEEK_CUR - ������� ������� �������; BSEEK_END - ����� ������
*
*	@return 1 - ������������ �������� origin; 2 - ������ ������� �� ������� ������;\
 0 - ��� ������ ���������
*/

int Bseek(buf_t* buf, int offset, int origin);


/**
*	���������� ������� ��������� ������� � ������
*
*	@param[in] buf �����
*
*	@return ������� ��������� ������� � ������
*/


int Btell(buf_t* buf);


/**
*	������� �����. ���� �� ��� � ������ ������, �� ������ �� ������� �� �������������!
*
*	@param[in] buf �����
*
*	@return 1 - ������������ ����� �� �����; 0 - ��� ������ ���������
*/

int BufDestructor(buf_t* buf);





int IncreaseBuf(buf_t* buf, const int newSize);

void RecalcLastChar(buf_t* buf);


/*
*	����������� printf ������� ��� ������
*
*	@param[in] buf �����
*	@param[in] format ������ �������
*	@param[in] args ���������
*
*	@return � ������ ������ ���������� ���������� ���������� ��������.\
 ���� �������� ������������, �� ��������� ��������� ������:\
 -403 - ����� �� � ������ ������; -401 - �� ������� ��������� ������ ������\
 ���. - ������ ��� ������, ��������� ������������ ������� ����������
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
*	����������� scanf ������� ��� ������
*
*	@param[in] buf �����
*	@param[in] format ������ �������
*	@param[in] args ���������
*
*	@return � ������ ������ ���������� ���������� ����������� ����������.\
 ���� �������� ������������, �� ��������� ��������� ������:\
 -1 - ����� �� � ������ ������; -2 - ������ ��� ������,\
 ��������� ������������ ������� ����������
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