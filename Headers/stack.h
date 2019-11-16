#pragma once


typedef int elem_t;             ///<Тип элементов стэка


/**
*	Стэк
*/

#pragma pack(1)
struct stack_t {
#ifdef _DEBUG
	int secureVarBeg = 0;                    ///<Первая канарейка
#endif

	elem_t* data = {};                       ///<Элементы стэка
	const int delta = 5;                     ///<Значение дельта для реаллокации
	int curMaxSize = 0;                      ///<Количество элементов, выделенных в памяти
	int size = 0;                            ///<Настоящий размер стэка
	const elem_t emptyelem = -2147483647;    ///<Элемент, соответствующий пустому

#ifdef _DEBUG
	char name[30] = "";                      ///<Имя стэка
	int err = 0;                             ///<Код ошибки, содержащейся в стэке:\n
											 ///0 - нет ошибок\n
											 ///1 - выход за вержнюю границу стэка\n
											 ///2 - выход за нижнюю границу стэка\n
											 ///3, 4 - испорчена соответственно первая или правая канарейка
											 ///5 - неверная хэш-сумма
	int hash = 0;                            ///<Хэш-сумма
	int secureVarEnd = 0;                    ///<Вторая канарейка
#endif
};
#pragma pack()



/**
*	Преобразует elem_t в строку
*
*	@param[in] elem Элемент
*
*	@return Указатель на строку
*/

char* elem_tToStr(elem_t elem);


/**
*	Создает новый стэк, заполняя его "пустыми" элементами
*
*	@param[in] name Имя стэка
*
*	@return Указатель на созданный стэк
*/

stack_t StackConstructor(const char* name);


/**
*	Берет элемент их стэка
*
*	@param[in] stk Стэк
*	@param[in] value Значение нового элемента
*
*	@return 0 - все прошло нормально; 2 - не удалось увеличить размер стэка; 1 - проблемы со стэком
*/

int StackPush(stack_t* stk, elem_t value);


/**
*	Берет элемент их стэка
*
*	@param[in] stk Стэк
*	@param[in] variable Переменная для возврата элемента. Если стэк пустой, остается нетронутой
*
*	@return 3 - Была неудачная попытка уменьшить стэк; 2 - в стэке нет элементов;
1 - проблемы со стэком; 0 - все прошло нормально
*/

int StackPop(stack_t* stk, elem_t* variable);


/**
*	Удаляет стэк
*
*	@param[in] stk Стэк
*
*	@return 0 - все прошло нормально; 1 - проблемы со стэком
*/

int StackDestructor(stack_t* stk);