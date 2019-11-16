#pragma once


const int listMaxSize = 100;

typedef int list_elem_t;

#pragma pack(1)
struct list_t {
#ifdef _DEBUG
	int secureVarBeg = 0;                    ///<Первая канарейка
#endif

	list_elem_t data[listMaxSize] = {};
	int next[listMaxSize] = {};
	int prev[listMaxSize] = {};
	int head = 0;
	int tail = 0;
	int free = 1;
	list_elem_t emptyelem = -2147483647;    ///<Элемент, соответствующий пустому
	int size = 0;

#ifdef _DEBUG
	char name[30] = "";                      ///<Имя списка
	int err = 0;                             ///<Код ошибки, содержащейся в списке:\n
	                                         ///0 - нет ошибок\n
	                                         ///1, 2 - выход соответственно за вержнюю или нижнюю границу списка\n
	                                         ///3, 4 - испорчена соответственно левая или правая канарейка\n
	                                         ///5 - неверная хэш-сумма\n
	                                         ///6 - Проблемы с массивом next\n
	                                         ///7 - Проблемы с массивом prev\n
	                                         ///8 - Проблемы со свободными элементами
	unsigned int hash = 0;                   ///<Хэш-сумма
	int secureVarEnd = 0;                    ///<Вторая канарейка
#endif
};
#pragma pack()



/**
*	Преобразует list_elem_t в строку
*
*	@param[in] elem Элемент
*
*	@return Указатель на строку, не заюудьте освободить память по этому указателю!
*/

char* list_elem_tToStr(list_elem_t elem);


/**
*	Проверяет список и записывает в него код ошибки (только в режиме отладки)
*
*	@param[in] list Список
*
*	@return 0 - список некорректный; 1 - список корректный
*/

#ifdef _DEBUG
int ListOk(list_t* list);
#endif


/**
*	Создает новый список, заполняя его "пустыми" элементами
*
*	@param[in] name Имя списка
*
*	@return Указатель на созданный список
*/

list_t ListConstructor(const char name[]);


/**
*	Вставляет элемент в начало списка
*
*	@param list Список
*	@param[in] elem Элемент
*
*	@return Позиция, по которой вставился элемент; -1 - нет свободного места в списке; \
-2 - на вход подался список с ошибкой (только в режиме отладки)
*/

int InsertBeg(list_t* list, list_elem_t elem);


/**
*	Вставляет элемент в конец списка
*
*	@param list Список
*	@param[in] elem Элемент
*
*	@return Позиция, по которой вставился элемент; -1 - нет свободного места в списке; \
-2 - на вход подался список с ошибкой (только в режиме отладки)
*/

int InsertEnd(list_t* list, list_elem_t elem);


/**
*	Вставляет элемент в списка
*
*	@param list Список
*	@param[in] phIndex Позиция, после которой надо вставить элемент
*	@param[in] elem Элемент
*
*	@return Позиция, по которой вставился элемент; -1 - нет свободного места в списке; \
-2 - на вход подался список с ошибкой (только в режиме отладки)
*/

int Insert(list_t* list, int phIndex, list_elem_t elem);


/**
*	Удаляет элемент из начала списка
*
*	@param list Список
*
*	@return 1 - список пуст; 2 - на вход подался список с ошибкой (только в режиме отладки); \
0 - все прошло нормально
*/

int DeleteBeg(list_t* list);


/**
*	Удаляет элемент из конца списка
*
*	@param list Список
*
*	@return 1 - список пуст; 2 - на вход подался список с ошибкой (только в режиме отладки); \
0 - все прошло нормально
*/

int DeleteEnd(list_t* list);


/**
*	Удаляет элемент из списка
*
*	@param list Список
	@param[in] phIndex Позиция элемента, который нужно удалить
*
*	@return 1 - на вход подался список с ошибкой (только в режиме отладки); 0 - все прошло нормально
*/

int Delete(list_t* list, int phIndex);


/**
*	Удаляет список
*
*	@param[in] list Список
*
*	@return 1 - проблемы со списком; 0 - все прошло нормально
*/

int ListDestructor(list_t* list);