#include "Long_int2.h"

unsigned int Long_int::count_objects = 0;

Long_int::Long_int() : len(1), negative(false)
{
	arr = new int(0);
	count_objects++;
} // конструктор класса по умолчанию

void Long_int::clean_string_and_char_to_int(char buff[])
{
	negative = false;
	len = strlen(buff); // длина массива

	if (len != 0)
	{
		for (int i = 0; i < len; i++)
		{
			while ((buff[i] < '0' || buff[i] > '9') && buff[i] != '\0')
			{
				if (buff[i] == '-')
					negative = true;
				for (int j = i; buff[j] != '\0'; j++)
					buff[j] = buff[j + 1];
				len--;
			}
		}
	}
	if (len != 0)
	{
		arr = new int[len]; // создали массив
		for (int i = 0; i < len; i++)
			arr[i] = buff[i] - '0'; // заполнили массив
	}
	else
	{
		arr = new int(0);
		len = 1;
		negative = false;
	}
}
//конструктор копирования
Long_int::Long_int(const Long_int &object)
{
	len = object.len;
	negative = object.negative;
	arr = new int[len];
	copyr(arr, len, object.arr, object.len);
	count_objects++;
}

int Long_int::get_length()
{
	return len;
}
//сложение
Long_int Long_int::operator + (Long_int &val2)
{
	Long_int temp;
	int change_symbols = 0;
	work_with_symbols(val2, 1, change_symbols); // меняем символы, чтобы избежать циклического вызова

	if (change_symbols == 1)
	{
		temp = *this - val2;
	}
	else if (change_symbols == -1)
	{
		temp = val2 - *this;
	}
	else
	{
		temp.up_size_array(len + val2.len);
		int h = temp.len - 1;
		int sub = 0;
		int i = len - 1, j = val2.len - 1;

		while (j >= 0 && i >= 0 && h >= 0)
		{
			if (sub != 0)
			{
				temp.arr[h] = (arr[i] + val2.arr[j] + sub) % 10;
				if (arr[i] + val2.arr[j] >= 9)
					sub = 1;
				else
					sub = 0;
			}
			else
			{
				if (arr[i] + val2.arr[j] > 9)
				{
					temp.arr[h] = (arr[i] + val2.arr[j]) % 10;
					sub = 1;
				}
				else
					temp.arr[h] = arr[i] + val2.arr[j];
			}
			h--, i--, j--;
		}
		while (i >= 0 && h >= 0)
		{
			if (sub != 0)
			{
				temp.arr[h] = (arr[i] + sub) % 10;
				if (arr[i] == 9)
					sub = 1;
				else
					sub = 0;
			}
			else
				temp.arr[h] = arr[i];
			i--, h--;
		}
		while (j >= 0 && h >= 0)
		{
			if (sub != 0)
			{
				temp.arr[h] = (val2.arr[j] + sub) % 10;
				if (val2.arr[j] == 9)
					sub = 1;
				else
					sub = 0;
			}
			else
				temp.arr[h] = val2.arr[j];
			j--, h--;
		}
		if (sub != 0)
			temp.arr[h] = 1;
	}

	if (change_symbols == -2)
		temp.negative = true;
	if (change_symbols != 0)
		work_with_symbols(val2, 2, change_symbols);
	temp.clean_arr();

	return temp;
}
//вычитание
Long_int Long_int::operator - (Long_int &val2)
{
	int comp = 0;
	int change_symbols = 0;
	Long_int temp;

	work_with_symbols(val2, 1, change_symbols);

	if (change_symbols == 1 || change_symbols == -1)
	{
		temp = *this + val2;
	}
	else
	{
		temp.up_size_array(len + val2.len); // увеличили длину результирующего массива
		int h = temp.len - 1;
		int *arr1 = arr, *arr2 = val2.arr;
		int len1 = len, len2 = val2.len;
		comp = compare(val2);
		int sub = 0;

		if (comp < 0) //определяем, что из чего будем вычитать
		{
			arr1 = val2.arr;
			arr2 = arr;
			len1 = val2.len;
			len2 = len;
		}
		else if (comp == 0)
		{
			temp.arr[h] = 0;
		}
		if (comp != 0)
		{
			while (len2 - 1 >= 0 && len1 - 1 >= 0 && h >= 0)
			{
				if (sub != 0)
				{
					if (arr1[len1 - 1] > arr2[len2 - 1])
					{
						temp.arr[h] = arr1[len1 - 1] - arr2[len2 - 1] - sub;
						sub = 0;
					}
					else
					{
						temp.arr[h] = arr1[len1 - 1] - sub + 10 - arr2[len2 - 1];
						sub = 1;
					}
				}
				else
				{
					if (arr1[len1 - 1] >= arr2[len2 - 1])
					{
						temp.arr[h] = arr1[len1 - 1] - arr2[len2 - 1];
					}
					else
					{
						temp.arr[h] = arr1[len1 - 1] + 10 - arr2[len2 - 1];
						sub = 1;
					}
				}
				len1--, len2--, h--;
			}
			while (len1 - 1 >= 0 && h >= 0)
			{
				if (sub != 0)
				{
					if (arr1[len1 - 1] >= sub)
					{
						temp.arr[h] = arr1[len1 - 1] - sub;
						sub = 0;
					}
					else
					{
						temp.arr[h] = arr1[len1 - 1] - sub + 10;
						sub = 1;
					}
				}
				else
				{
					temp.arr[h] = arr1[len1 - 1];
				}
				len1--, h--;
			}
		}
	}

	if (change_symbols < 0 || comp < 0)
	{
		if (compare(val2) != 0)
			temp.negative = true;
		if (change_symbols == -2 && comp < 0)
			temp.negative = false;
	}
	if (change_symbols != 0)
		work_with_symbols(val2, 2, change_symbols);
	temp.clean_arr();

	return temp;
}
//умножение
Long_int Long_int::operator * (Long_int &val2)
{	//пока счетчик - массив не равен второму множителю, делаем сложение
	Long_int temp;

	if (!null(val2))
	{
		int change_symbols = 0;
		work_with_symbols(val2, 1, change_symbols);
		Long_int factor_second;// пустой массив для накопления результата

		while (val2 != factor_second)//пока массивы не равны
		{
			temp = temp + *this; // складываем пустой массив и 1 множ
			++factor_second; //складываем пустой массив и 1 - счетчик
		} //копируем счетчик в другой массив, чтобы снова сложить
		if (change_symbols == -1 || change_symbols == 1)
		{
			temp.negative = true;
		}
		if (change_symbols != 0)
			work_with_symbols(val2, 2, change_symbols);
	}
	return temp;
}
//деление
Long_int Long_int::operator / (Long_int &val2)// что делим, на что делим, куда пишем результат
{
	Long_int temp;

	if (!null(val2))
	{
		int change_symbols = 0;
		work_with_symbols(val2, 1, change_symbols);
		int h = temp.len - 1;
		int comp = compare(val2);// сравниваем, чтоб на большее не делить

		if (comp > 0) // если результат сравнения больше 0, то присваиваем этой переменной значение остатка
		{
			Long_int dividend(*this);
			while (dividend.compare(val2) >= 0)// пока делимое больше делителя
			{
				dividend = dividend - val2;// вычитаем из делимого делитель
				++temp;
			}
		}
		else if (comp == 0)
		{
			temp.arr[h] = 1;
		}
		else
		{
			temp.arr[h] = 0;
		}
		if (change_symbols == 1 || change_symbols == -1)
		{
			if (comp >= 0)
				temp.negative = true;
		}
		if (change_symbols != 0)
			work_with_symbols(val2, 2, change_symbols);
	}
	return temp;
}
//для вывода очистка от пустых старших разрядов
void Long_int::clean_arr()
{
	int i = 0;
	for (i; i < len; i++)
	{
		if (arr[i] != 0)
			break;
	}
	reduce_size_array(i);
}
//получить цифру по разряду
int Long_int::get_digit(int index)
{
	int digit = -1;
	if (index < len && index >= 0)
		digit = arr[index];
	return digit;
}

const char* Long_int::get_symbol()
{
	const char *s = "";
	if (negative)
		s = "-";
	return s;
}
// обмен
//копирование значений
void Long_int::copyr(int *arr1, int len1, int *arr2, int len2)
{
	int i = len1 - 1, j = len2 - 1;
	while (j >= 0 && i >= 0)
	{
		arr1[i] = arr2[j];
		i--, j--;
	}
}
//сравнение значений в массивах
int Long_int::compare(const Long_int &val2)
{
	int result_compare = 0;
	int i = 0, j = 0;

	if (len > val2.len)
	{
		for (i; i < len - val2.len; i++)
		{
			if (arr[i] > 0)
			{
				result_compare = 1;
				break;
			}
		}
	}
	else if (len < val2.len)
	{
		for (j; j < val2.len - len; j++)
		{
			if (val2.arr[j] > 0)
			{
				result_compare = -1;
				break;
			}
		}
	}
	if (result_compare == 0)
	{
		while (i < len)
		{
			if (arr[i] == val2.arr[j])
			{
				result_compare = 0;
				i++, j++;
			}
			else if (arr[i] > val2.arr[j])
			{
				result_compare = 1;
				break;
			}
			else
			{
				result_compare = -1;
				break;
			}
		}
	}
	return result_compare;
}
//вывод статического эл-та
unsigned int Long_int::get_count_objects()
{
	return count_objects;
}
//перевод в тип long long
long long Long_int::to_long()
{
	long long value = 0LL;
	int pow = 1;
	for (int i = len - 1; i >= 0; i--)
	{
		value += arr[i] * pow;
		pow *= 10;
	}
	if (negative)
		value *= (-1);
	return value;
}
//показывает, есть ли нулевые значения
bool Long_int::null(Long_int val2)
{
	return (len == 1 && arr[0] == 0) || (val2.len == 1 && val2.arr[0] == 0);
}
// помогает определить знак результата арифметич. действия
void Long_int::work_with_symbols(Long_int &val2, int key, int &change_symbols)
{
	switch (key)
	{
	case 1:
	{
		if (!negative && val2.negative)//если первый положительный, а второй - отрицательный
		{
			val2.negative = false;
			change_symbols = 1;
		}
		else if (negative && !val2.negative)//если первый отрицательный, а второй - положительный
		{
			negative = false;
			change_symbols = -1;
		}
		else if (negative && val2.negative)//оба отрицательных
		{
			negative = false;
			val2.negative = false;
			change_symbols = -2;
		}
		else if (!negative && !val2.negative)//оба положительных
			change_symbols = 0;
		break;
	}
	case 2:
	{
		if (change_symbols != 0)
		{
			if (change_symbols == -2)
			{
				negative = true;
				val2.negative = true;
			}
			else if (change_symbols == -1)
				negative = true;
			else if (change_symbols == 1)
				val2.negative = true;
		}
		break;
	}
	default:
		exit(1);
	}
}

void Long_int::up_size_array(int length)
{
	int *sub_arr = new int[len + length];
	for (int i = 0; i < len + length; i++)
		sub_arr[i] = 0;
	copyr(sub_arr, len + length, arr, len);
	delete[] arr;
	len += length;
	arr = new int[len];
	for (int i = 0; i < len; i++)
		arr[i] = 0;
	copyr(arr, len, sub_arr, len);
	delete[] sub_arr;
}

void Long_int::reduce_size_array(int length)
{
	if (len == length)
	{
		delete[] arr;
		arr = new int(0);
		len = 1;
	}
	else if (len > length)
	{
		int *sub_arr = new int[len - length];
		for (int i = 0; i < len - length; i++)
			sub_arr[i] = 0;
		copyr(sub_arr, len - length, arr, len);
		delete[] arr;
		len -= length;
		arr = new int[len];
		for (int i = 0; i < len; i++)
			arr[i] = 0;
		copyr(arr, len, sub_arr, len);
		delete[] sub_arr;
	}
	else
	{
		exit(1);
	}
}

Long_int & Long_int::operator = (const Long_int & object)
{
	if (*this != object)
	{
		if (len < object.len)
			up_size_array(object.len - len);
		else if (len > object.len)
			reduce_size_array(len - object.len);
		copyr(arr, len, object.arr, object.len);
		negative = object.negative;
	}
	return *this;
}

bool Long_int::operator == (const Long_int &object)
{
	bool result = false;
	if (compare(object) == 0)
		result = true;
	return result;
}

bool Long_int::operator != (const Long_int &object)
{
	bool result = true;
	if (*this == object)
		result = false;
	return result;
}

Long_int& Long_int::operator ++ ()
{
	int i = len - 1;
	if (!negative)
	{
		++arr[i];
		while (arr[i] == 10 && i > 0)
		{
			arr[i] = 0;
			arr[--i]++;
		}
		if (arr[i] == 10 && i == 0)
		{
			arr[i] = 0;
			up_size_array(1);
			arr[i] = 1;
		}
	}
	else
	{
		--arr[i];
		while (arr[i] == -1 && i > 0)
		{
			arr[i] = 9;
			arr[--i]--;
		}
	}
	clean_arr();
	return *this;
}

Long_int& Long_int::operator -- (int)
{
	int i = len - 1;
	if (!negative)
	{
		--arr[i];
		while (arr[i] == -1 && i > 0)
		{
			arr[i] = 9;
			arr[--i]--;
		}
	}
	else
	{
		++arr[i];
		while (arr[i] == 10 && i > 0)
		{
			arr[i] = 0;
			arr[--i]++;
		}
		if (arr[i] == 10 && i == 0)
		{
			arr[i] = 0;
			up_size_array(1);
			arr[i] = 1;
		}
	}
	clean_arr();
	return *this;
}
//деструктор
Long_int::~Long_int()
{
	delete[] arr;
	count_objects--;
}
//перегрузка операторов ввода-вывода
ostream & operator << (ostream &out, Long_int &object)
{
	out << object.get_symbol();
	for (int i = 0; i < object.len; i++)
		out << object.arr[i];
	return out;
}

istream & operator >> (istream &in, Long_int &object)
{
	char buff[100];
	in >> buff;
	delete[] object.arr;
	object.clean_string_and_char_to_int(buff);
	return in;
}

ofstream & operator << (ofstream & out, Long_int &object)
{
	out << object.get_symbol();
	for (int i = 0; i < object.len; i++)
		out << object.arr[i];
	return out;
}

ifstream & operator >> (ifstream & in, Long_int &object)
{
	char buff[100];
	in.getline(buff, 100);
	delete[] object.arr;
	object.clean_string_and_char_to_int(buff);
	return in;
}
