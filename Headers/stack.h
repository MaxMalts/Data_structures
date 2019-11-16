#pragma once


typedef int elem_t;             ///<��� ��������� �����


/**
*	����
*/

#pragma pack(1)
struct stack_t {
#ifdef _DEBUG
	int secureVarBeg = 0;                    ///<������ ���������
#endif

	elem_t* data = {};                       ///<�������� �����
	const int delta = 5;                     ///<�������� ������ ��� �����������
	int curMaxSize = 0;                      ///<���������� ���������, ���������� � ������
	int size = 0;                            ///<��������� ������ �����
	const elem_t emptyelem = -2147483647;    ///<�������, ��������������� �������

#ifdef _DEBUG
	char name[30] = "";                      ///<��� �����
	int err = 0;                             ///<��� ������, ������������ � �����:\n
											 ///0 - ��� ������\n
											 ///1 - ����� �� ������� ������� �����\n
											 ///2 - ����� �� ������ ������� �����\n
											 ///3, 4 - ��������� �������������� ������ ��� ������ ���������
											 ///5 - �������� ���-�����
	int hash = 0;                            ///<���-�����
	int secureVarEnd = 0;                    ///<������ ���������
#endif
};
#pragma pack()



/**
*	����������� elem_t � ������
*
*	@param[in] elem �������
*
*	@return ��������� �� ������
*/

char* elem_tToStr(elem_t elem);


/**
*	������� ����� ����, �������� ��� "�������" ����������
*
*	@param[in] name ��� �����
*
*	@return ��������� �� ��������� ����
*/

stack_t StackConstructor(const char* name);


/**
*	����� ������� �� �����
*
*	@param[in] stk ����
*	@param[in] value �������� ������ ��������
*
*	@return 0 - ��� ������ ���������; 2 - �� ������� ��������� ������ �����; 1 - �������� �� ������
*/

int StackPush(stack_t* stk, elem_t value);


/**
*	����� ������� �� �����
*
*	@param[in] stk ����
*	@param[in] variable ���������� ��� �������� ��������. ���� ���� ������, �������� ����������
*
*	@return 3 - ���� ��������� ������� ��������� ����; 2 - � ����� ��� ���������;
1 - �������� �� ������; 0 - ��� ������ ���������
*/

int StackPop(stack_t* stk, elem_t* variable);


/**
*	������� ����
*
*	@param[in] stk ����
*
*	@return 0 - ��� ������ ���������; 1 - �������� �� ������
*/

int StackDestructor(stack_t* stk);