/*______________________________________________________________________________
[]                                                                            []
[] This is a part of the PROJECT: 'BX'                                        []
[] Copyright (C) 2000 Alex Vershinin.                                         []
[] All rights reserved.                                                       []
[] __________________________________________________________________________ []
[]                                                                            []
[] Name:            BX_IPRecord.h                                             []
[] Date:            03.01.2000                                                []
[] Author:          Alex Vershinin                                            []
[] Description:                                                               []
[] Last Modified:                                                             []
[]____________________________________________________________________________*/
                                                                  
#ifndef BX_IPRecord_H
#define BX_IPRecord_H

struct	BX_IPRecord_Args
{
	BX_IPRecord_Args()
	{
		Count		= 0;
		Checked	= false;
		objID		= NA;
	}

	int				Count;			// Счётчик хитов с этого диапазона IP.
	string			Mask;				// Маска диапазона адресов (т.е. адрес без последней цифры).
	string			First;			// Начало диапазона.
	string			Last;				// Конец диапазона.
	bool				Checked;			// Проверено администратором
											
											
	identifier_arr	ConceptID;		// Идентификаторы концептов, соответствующие этому диапазону.

	string			AdminPassword;	// Пароль админа.
	identifier		objID;			// Идентификатор объекта диапазона.

	int				objFirstNo;		// Номер объекта, начиная с которого выводятся объекты функцией Enumerate(). По умолчанию равен 0. 
	int				objLastNo;		// Номер объекта, с которого прекращаются выводиться объекты функцией Enumerate(). По умолчанию равен последнему порядковому номеру.

	identifier_arr	objIDs;			// Идентификаторы объектов.
	string_arr		objNames;		// Информация о диапазонах.
};
//----------------------------------------------------------------------------[]
// Регистрирует IP-адрес в базе. Если для этого адреса установлены концепты, то
// инкрементирует у зрителя поле CRA_Inquiry.
BX_RESULT
RegisterIP(
	const string&	IPAddressStr,
	OC_Viewer&		oc_viewer,
	bool				bHost,
	bool				bNewVisitor,
	time_t			CurrentTime);

// Вывод зарегистрированных IP-диапазонов.
BX_RESULT BX_IPRecord_Enumerate	(BX_IPRecord_Args& arg);

// Установить границы диапазона адресов и соответствующие ему концепты.
BX_RESULT BX_IPRecord_Check		(BX_IPRecord_Args& arg);

// Получить параметры диапазона адресов.
BX_RESULT BX_IPRecord_GetData		(BX_IPRecord_Args& arg);

// Создать новый диапазон адресов.
BX_RESULT BX_IPRecord_New			(BX_IPRecord_Args& arg);
//______________________________________________________________________________
//                                                                            []
//` IP_Address                                                                []          
//                                                                            []
class IP_Address
{
private:
	string	m_Address;		// 
	int_arr	m_Digits;

public:

//- - - - - - - - - - - - - - - - - - - - - - - - - -
// Инициализация объекта, используются первые 64 символа строки IP
// Разделители - '.', если встретится не цифра, то разбор заканчивается,
// т.е.	из '192.a168.200.8' получится '192',
//			из '192.168a.200.8' получится '192.168.200.8',
//			из '192.16a8.200.8' получится '192.16.200.8',
// но вообще-то все это сделано для того, чтобы из '192.168.*' получить '192.16.200'
	void Init(const string& IP)
	{
		const int	AddressBufSize = 64;
		const char	Separators[] = ". (),-\t\n\r";
		static char AddressBuf[AddressBufSize];
		char			*token = NULL;
		string		Str;
		int			IP_Digit = -1;

		m_Address.Erase();
		m_Digits.Erase();

		strncpy(AddressBuf, IP.c_str(), AddressBufSize-1);

		token = strtok(AddressBuf, Separators);
	// Цикл считыванияпоследовательность цифр адреса:
		while (token != NULL)
		{
			if (!isdigit(int(*token)))			break;

			IP_Digit = atoi(token);

			if (IP_Digit<0 || IP_Digit>255)	break;

			m_Digits.Add(IP_Digit);

			Str.Format("%s%d",
				m_Digits.Size() == 1 ? "" : ".",
				IP_Digit);
			m_Address += Str;

			if (m_Digits.Size() >= 4)			break;

			token = strtok(NULL, Separators);
		}
	// Добить звёздочками до 4 цифр:
		for (int i = m_Digits.Size(); i < 4; i++) {
			m_Address += ((i == 0) ? "*":".*");
		}

		return;
	}

//- - - - - - - - - - - - - - - - - - - - - - - - - -
// Конструктор из string'а
	IP_Address(const string& IP)
	{
		Init(IP);
	}
//- - - - - - - - - - - - - - - - - - - - - - - - - -
// Конструктор из const char*
	IP_Address(const char* IP)
	{
		Init(IP);
	}

//- - - - - - - - - - - - - - - - - - - - - - - - - -
// Конструктор по умолчанию
	IP_Address(void)
	{
		Init("0.0.0.0");
	}

//- - - - - - - - - - - - - - - - - - - - - - - - - -
// Конструктор копирования
	IP_Address(const IP_Address& ip_address)
	{
		CopyFrom(ip_address);
	}

//- - - - - - - - - - - - - - - - - - - - - - - - - -
// Копирование из другого объекта
	IP_Address& CopyFrom(const IP_Address& ip_address)
	{
		string Str;
		ip_address.GetIP(Str);
		Init(Str);
		
		return *this;
	}

//- - - - - - - - - - - - - - - - - - - - - - - - - -
// Оператор присваивания
	IP_Address& operator = (const IP_Address& from)
	{
		return CopyFrom (from);
	}

//- - - - - - - - - - - - - - - - - - - - - - - - - -
// Получение IP-адреса в виде string'а
// Если WithZeros==true, цифры добиваются слева нулями, если нужно.
// Печатается Digits цифр, которые при нехватке заменяются *.
	void GetIP(string& IP_Str, bool WithZeros = false, int Digits = 4) const
	{
		if (Digits < 0 || Digits > 50)	{
			Digits = 4;
		}

		string Str;
		IP_Str.Erase();
		int nSize = m_Digits.Size();
		int i;

		for (i = 0; i < nSize && i < Digits; i++)
		{
			if (WithZeros)	Str.Format("%s%03d", i == 0 ? "" : ".", (int)m_Digits[i]);
			else				Str.Format("%s%d",	i == 0 ? "" : ".", (int)m_Digits[i]);
			IP_Str += Str;
		}

		if (nSize < Digits) {
			for (i = 0; i < Digits; i++)
			{
				if (WithZeros)	IP_Str += "***";
				else				IP_Str += "*";
			}
		}

		return;
	}

//- - - - - - - - - - - - - - - - - - - - - - - - - -
// Получение IP-адреса в виде const char* 
	const char* GetIP(void) const
	{
		return m_Address.GetPtr();
	}
//- - - - - - - - - - - - - - - - - - - - - - - - - -
// Получение Level-ной цифры IP-адреса (счёт начинается с 0 слева направо)
// Возвращает -1 в случае, если цифры такого уровня нет.
	int GetDigit(int Level) const
	{
		int nSize = m_Digits.Size();
		if (Level < 0 || Level >= nSize) return -1;
		return m_Digits[Level];
	}
//- - - - - - - - - - - - - - - - - - - - - - - - - -
// Получение количества цифр в IP-адресе
	int Size(void) const
	{
		return m_Digits.Size();
	}

//- - - - - - - - - - - - - - - - - - - - - - - - - -
// Получение маски диапазона с уровнем Level в строке IP_Mask
// Т.е. выводится Level цифр адреса, а вместо остальных ставится '*'.
// Если WithZeros==true, цифры добиваются слева нулями, если нужно.
	void GetMask(string& IP_Mask, int Level = 3, bool WithZeros = false) const
	{
		IP_Mask.Erase();
		string Str;
		for (int i = 0; (i < Level) && (i < m_Digits.Size()); i++)
		{
			if (WithZeros)		Str.Format("%03d.", m_Digits[i]);
			else					Str.Format("%d.", m_Digits[i]);
			IP_Mask += Str;		
		}

		IP_Mask += "*";

		return;
	}

//- - - - - - - - - - - - - - - - - - - - - - - - - -
// Находится ли IP адрес в диапазоне, задаваемом аргументом;
// пропущенные цифры в аргументе считаются, как *, в this - 
// как нули.
	bool IsInRange(const char* ip_address) const
	{
		return IsInRange(IP_Address(ip_address));
	}
//- - - - - - - - - - - - - - - - - - - - - - - - - -
// Находится ли IP адрес в диапазоне, задаваемом аргументом;
// пропущенные цифры в аргументе считаются, как *, в this - 
// как нули.
	bool IsInRange(const string& ip_address) const
	{
		return IsInRange(IP_Address(ip_address));
	}

//- - - - - - - - - - - - - - - - - - - - - - - - - -
// Находится ли IP адрес в диапазоне, задаваемом аргументом;
// пропущенные цифры в аргументе считаются, как *, в this - 
// как нули.
	bool IsInRange(const IP_Address& ip_address) const
	{
		int nSize1 = m_Digits.Size();
		int nSize2 = ip_address.Size();
		int i;

	// Начальные цифры должны совпадать:
		for (i = 0; (i < nSize1) && (i < nSize2); i++)	{
			if (m_Digits[i] != ip_address.GetDigit(i)) {
				return false;
			}
		}
	// Если маска короче, то под неё подходит любой более длинный адрес:
		if (nSize1 >= nSize2) {
			return true;	// * == any num
		}

	// nSize1 < nSize2
	// Если маска длиннее, то недостающие в адресе цифры чситаем нулями:
		for (i = nSize1; i < nSize2; i++) {
			if (ip_address.GetDigit(i) != 0) {
				return false;
			}
		}

		return true;
	}
//- - - - - - - - - - - - - - - - - - - - - - - - - -
// Сравнение двух адресов. При неравных длинах
// недостающие цифры считаются нулями.
	bool operator > (const IP_Address& ip_address) const
	{
		int nSize1 = m_Digits.Size();
		int nSize2 = ip_address.Size();
		int Digit1, Digit2;
		int i;

		for (i = 0; (i < nSize1) && (i < nSize2); i++)
		{
			Digit1 = m_Digits[i];
			Digit2 = ip_address.GetDigit(i);

			if (Digit1 != Digit2) {
				return (Digit1 > Digit2);
			}
		}

		if (nSize1 <= nSize2) {
			return false; // они равны или более короткий массив не может быть больше.
		}

		// nSize1 > nSize2
		for (i = nSize2; i < nSize1; i++) {
			if (m_Digits[i] > 0) {
				return true;
			}
		}

		return false; // они равны
	}			
	bool operator > (const string& ip_address) const
	{
		return (*this > IP_Address(ip_address));
	}			
	bool operator > (const char* ip_address) const
	{
		return (*this > IP_Address(ip_address));
	}			
//- - - - - - - - - - - - - - - - - - - - - - - - - -
// Сравнение двух адресов. При неравных длинах
// недостающие цифры считаются нулями.
	bool operator >= (const IP_Address& ip_address) const
	{
		int nSize1 = m_Digits.Size();
		int nSize2 = ip_address.Size();
		int Digit1, Digit2;
		int i;

		for (i = 0; (i < nSize1) && (i < nSize2); i++)
		{
			Digit1 = m_Digits[i];
			Digit2 = ip_address.GetDigit(i);

			if (Digit1 != Digit2) {
				return (Digit1 > Digit2);	// больше
			}
		}

		if (nSize1 >= nSize2) {
			return true; // они равны или более короткий массив не может быть больше.
		}

		// nSize1 < nSize2
		for (i = nSize1; i < nSize2; i++) {
			if (ip_address.GetDigit(i) > 0) {
				return false; // меньше
			}
		}

		return true; // они равны
	}			
	bool operator >= (const string& ip_address) const
	{
		return (*this >= IP_Address(ip_address));
	}			
	bool operator >= (const char* ip_address) const
	{
		return (*this >= IP_Address(ip_address));
	}			

//- - - - - - - - - - - - - - - - - - - - - - - - - -
// Сравнение двух адресов. При неравных длинах
// недостающие цифры считаются нулями.
	bool operator == (const IP_Address& ip_address) const
	{
		int	nSize1 = m_Digits.Size();
		int	nSize2 = ip_address.Size();
		int	i;

		for (i = 0; (i < nSize1) && (i < nSize2); i++)
		{
			if (m_Digits[i] != ip_address.GetDigit(i))
				return false;
		}

		if (nSize1 == nSize2)
			return true;

		if (nSize1 > nSize2) {
			for (i = nSize2; i < nSize1; i++) {
				if (m_Digits[i] != 0) {
					return false;
				}
			}
			return true;
		}

		for (i = nSize1; i < nSize2; i++) {
			if (ip_address.GetDigit(i) != 0) {
				return false;
			}
		}

		return true;
	}
	bool operator == (const string& ip_address) const
	{
		return (*this == IP_Address(ip_address));
	}
	bool operator == (const char* ip_address) const
	{
		return (*this == IP_Address(ip_address));
	}

//- - - - - - - - - - - - - - - - - - - - - - - - - -
// Сравнение двух адресов. При неравных длинах
// недостающие цифры считаются нулями.
	bool operator != (const IP_Address& ip_address) const
	{
		return !(*this == ip_address);
	}
	bool operator != (const string& ip_address) const
	{

		return !(*this == IP_Address(ip_address));
	}
	bool operator != (const char* ip_address) const
	{
		return !(*this == IP_Address(ip_address));
	}
//- - - - - - - - - - - - - - - - - - - - - - - - - -
// Сравнение двух адресов. При неравных длинах
// недостающие цифры считаются нулями.
	bool operator < (const IP_Address& ip_address) const
	{
		return !(*this >= ip_address);
	}
	bool operator < (const string& ip_address) const
	{
		return !(*this >= IP_Address(ip_address));
	}
	bool operator < (const char* ip_address) const
	{
		return !(*this >= IP_Address(ip_address));
	}
//- - - - - - - - - - - - - - - - - - - - - - - - - -
// Сравнение двух адресов. При неравных длинах
// недостающие цифры считаются нулями.
	bool operator <= (const IP_Address& ip_address) const
	{
		return !(*this > ip_address);
	}
	bool operator <= (const string& ip_address) const
	{
		return !(*this > IP_Address(ip_address));
	}
	bool operator <= (const char* ip_address) const
	{
		return !(*this > IP_Address(ip_address));
	}
};
//----------------------------------------------------------------------------[] 


#endif
/*______________________________________________________________________________
[]                                                                            []
[]                                                                            []
[] END OF FILE                                                                []
[]                                                                            []
[]____________________________________________________________________________*/