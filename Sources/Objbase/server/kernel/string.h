/*
________________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'ObjBase'												[]
[] Copyright (C) 1998 W:Brain Software Inc.                                   []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            string.h																	[]
[] Date:            16.04.99                                                  []
[] Author:          Roman V. Koshelev														[]
[] Description:     Класс - строковая переменная
[]____________________________________________________________________________[]
*/
#ifndef string_H
#define string_H

//______________________________________________________________________________
//                                                                            []
// string																							[]
typedef const char * const_char_ptr;
class string: public CPtr<char>
{
// Класс - строковая переменная
// Создан из-за того, что в стандартном классе (STL) 
// некорректно реализован оператор присваивания.
// ВНИМАНИЕ: Нельзя возвращать указатели на локальные переменные:
// const char * BadFunction()
// {
//    string local_str "Хуё-моё";
//    return  local_str;
// }
	protected: void About_class_string (){}


//______________________________________________________________________________
//                                                                            []
//` Присваивание																					[]
//                                                                            []

//	Конструктор = ""
	public: string ();
//	Конструктор (string, const char *, char)
	public: string (char from);
//	Конструктор (string, const char *, char)
	public: string (const char* from);
//	Конструктор (string, const char *, char)
	public: string (const string& from);
//	Оператор присваивания (string, const char *, char)
	public: string& operator = (char from);
//	Оператор присваивания (string, const char *, char)
	public: string& operator = (const char* from);
//	Оператор присваивания (string, const char *, char)
	public: string& operator = (const string& from);
//	Копирование другой строки (const char*)
	public: string& Copy (const char* from, size_t str_len);
// Сгенерировать случайную строку указанной длины на основе заданного алфавита.
// Если bRandomLen==true, то длина строки выбирается случайным образом в пределах от 0 до strLen.
	public: void Randomize (int strLen=16, const char *alfabet="1234567890_qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM", bool bRandomLen=false);
// Запомнить значение предусмотренного типа в определённом формате
	public: string& SetVariant (const identifier&	val) {Format ("%u",	val); return *this;};
	public: string& SetVariant (const int&				val) {Format ("%d",	val); return *this;};
	public: string& SetVariant (const char&			val) {Format ("%c",	val); return *this;};
	public: string& SetVariant (const float&			val) {Format ("%f",	val); return *this;};
	public: string& SetVariant (const char *			val) {Format ("%s",	val); return *this;};
// Выдать значение предусмотренного типа
	public: void GetVariant (identifier&	val);
	public: void GetVariant (int&				val);
	public: void GetVariant (char&			val);
	public: void GetVariant (float&			val);
	public: void GetVariant (string&			val);	


//______________________________________________________________________________
//                                                                            []
//` Поиск и разбивка                                                          []                
//                                                                            []

//	Нахождение подстроки или символа. По умолчанию ищется с самого начала.
// Возвращает позицию или -1, если не найдено.
	public: int Find (const char * Substr, int nPos=0);
//	Нахождение подстроки или символа. По умолчанию ищется с самого начала.
// Возвращает позицию или -1, если не найдено.
	public: int Find (char C, int nPos=0);
// Взять подстроку
	public: void SubStr (string& Substr, int nPos1=0, int nPos2=-1);
//	Упаковка из массива. По умолчанию разделяется переходами строк '\n'
	public: void implode (CPtr<string>& arr, const char * sDelimiter="\n");
//	Разбиение на массив. По умолчанию разбивается на строки '\n'
	public: void explode (CPtr<string>& arr, const char * sDelimiter="\n", bool PrintPercent=false);
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` Изменения																						[]
//                                                                            []

//	Оператор конкатенации строк (const char* или string)
	public: const char * operator + (const char * add);
//	Оператор конкатенации строк (const char* или string)
	public: const char * operator + (const string& add);
//	Добавить строку (const char* или string)
	public: string operator += (const char * add);
//	Добавить строку (const char* или string)
	public: string& operator += (const string& add);
//	Добавить символ (char)
	public: string& operator += (char C);
//	Добавить строку (const char*)
	public: string& AddString (const char* add, size_t add_len);
//	Убрать с конца строки пустые символы:
// ПРОБЕЛ ТАБУЛЯЦИЯ \r \n
	public: void rtrim ();
//	Убрать из начала строки пустые символы:
// ПРОБЕЛ ТАБУЛЯЦИЯ \r \n
	public: void ltrim ();
//	Убрать из начала и с конца строки пустые символы:
// ПРОБЕЛ ТАБУЛЯЦИЯ \r \n
	public: void trim ();
// Переводит символы строки в верхний регистр.
// Предполагается, что кириллица имеет кодировку Win1251.
	public: void strupr(void);
// Переводит символы строки в нижний регистр.
// Предполагается, что кириллица имеет кодировку Win1251.
	public: void strlwr(void);
//____________________________________________________________________________[]




//______________________________________________________________________________
//                                                                            []
//` Сравнение																						[]
//                                                                            []
//	Сравнение на равенство со строкой (const char* или string)
	public: bool operator == (const string& to) const;
//	Сравнение на равенство со строкой (const char* или string)
	public: bool operator == (const char * to) const;
//	Сравнение на неравенство со строкой (const char* или string)
	public: bool operator != (const string& to) const;
//	Сравнение на неравенство со строкой (const char* или string)
	public: bool operator != (const char * to) const;
//	Сравнение на равенство со строкой (const char* или string)
	public: bool operator <= (const string& to) const;
//	Сравнение на равенство со строкой (const char* или string)
	public: bool operator < (const string& to) const;
//	Сравнение на равенство со строкой (const char* или string)
	public: bool operator >= (const string& to) const;
//	Сравнение на равенство со строкой (const char* или string)
	public: bool operator > (const string& to) const;
//____________________________________________________________________________[]



//______________________________________________________________________________
//                                                                            []
//` Длина																							[]
//                                                                            []
//	Число выделенных байт -- длина строки+1 !
	public: public: size_t GetSize () const {return m_nSize;}
//	Длина строки == число выделенных байт - 1 (без нуля)
	public: size_t len ()	const	{return m_nSize-1;}
//	Длина строки == число выделенных байт - 1 (без нуля)
	public: size_t Len ()	const	{return len();}
//	Длина строки == число выделенных байт - 1 (без нуля)
	public: size_t Length ()	const	{return len();}
//	Длина строки == число выделенных байт - 1 (без нуля)
	public: size_t length ()	const	{return len();}
//	Длина строки == число выделенных байт - 1 (без нуля)
	public: size_t size ()	const	{return len();}
//	Длина строки == число выделенных байт - 1 (без нуля)
	public: size_t Size ()	const	{return len();}
//	Строка является пустой (=="")
	public: bool IsEmpty	() const {return m_pData==NULL || m_pData[0]==0;};
//____________________________________________________________________________[]


// Очистить строку (="") тоже что и Erase()
   public:  void Delete();
// Очистить строку (="") тоже что и Delete()
   public:  void Erase();


//______________________________________________________________________________
//                                                                            []
//` Указатель																						[]
//                                                                            []

//	Получить указатель на строку - данные
	public: const char * c_str () const
	{
		SERVER_DEBUG_ASSERT_RETURN (m_pData, "string::c_str () -- m_pData=NULL", NULL);
		return m_pData;
	}
//	Получить указатель на строку - данные
	public: operator const_char_ptr () const
	{
		SERVER_DEBUG_ASSERT_RETURN (m_pData, "string::const_char_ptr () -- m_pData=NULL", NULL);
		return m_pData;
	}
//____________________________________________________________________________[]


//	Вывод строки на экран
	void Print () const;
// CPtr:: Выделить память и считать в неё 		
// данные из файла OS, открытого по имени.
	public:	size_t ReadFile(const char *fileName);
//	Вывод строки на экран
	void Println () const;
// Заполнить строку в соответствии с форматом и аргументами
// Работает как функция sprintf().
	void Format (const char * sFormat, ...);
//	Получить 32-х разрядную свёртку от строки.
	public: unsigned long GetCRC (void) const;
// Преобразовать строку в DOS-кодировку
	public: string& win_2_dos ();
// Проверить, является ли строка построенной по 
//	правилам образования имен переменных С++
	public: bool CheckSysName (void) const;
};
//____________________________________________________________________________[]





//______________________________________________________________________________
//                                                                            []
//` Helpers																							[]
//                                                                            []
bool operator == (const char * str1, string& str2);
bool operator != (const char * str1, string& str2);
//____________________________________________________________________________[]




#endif
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________[]
*/