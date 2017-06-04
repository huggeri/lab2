#include "Long_int2.h"
// �������� ������� � ������ ������ Unigned_fractional_number
Unsigned_fractional_number::Unsigned_fractional_number() : pos_point(0)
{ // arr = {0} len = 1 negative = false
} //����������� �� ���������, �������� ����������� �� ��������� Long_int

Unsigned_fractional_number::Unsigned_fractional_number(const Unsigned_fractional_number &object) //����������� � ��� ��������� ������, �.�. ������ ���. ������ ������
{
	if (len != object.len)
	{
		if (len < object.len)
			up_size_array(object.len - len);
		else
			reduce_size_array(len - object.len);
	}
	copyr(arr, len, object.arr, object.len);
	//fraction_part = new int[object.len - object.pos_point];// ����������� ������� �����
	//for(int i = 0; i object.len - object.pos_point)
	pos_point = object.pos_point;
	negative = object.negative;
} // ������. �����������

Unsigned_fractional_number & Unsigned_fractional_number::operator = (const Unsigned_fractional_number &object)// ���������� ��������� ������������
{
	Long_int::operator = (object);
	pos_point = object.pos_point;
	return *this;
} //����� � ����� ������������ ������������� ��������� �������� ������

Unsigned_fractional_number Unsigned_fractional_number::operator * (Unsigned_fractional_number &val2)
{
	Unsigned_fractional_number temp;
	temp.Long_int::operator = (Long_int::operator * (val2));
	if (temp.len < (len - pos_point) + (val2.len - val2.pos_point))
		temp.up_size_array(((len - pos_point) + (val2.len - val2.pos_point)) - temp.len + 1);
	temp.pos_point = temp.len - ((len - pos_point) + (val2.len - val2.pos_point));
	return temp;
}

Unsigned_fractional_number Unsigned_fractional_number::operator / (Unsigned_fractional_number &val2)
{
	Unsigned_fractional_number temp, copy_val1(*this), copy_val2(val2);
	copy_val1.magic_with_digits(copy_val2);
	int pow = 0, sub_pow = 0;
	if (copy_val1.compare(copy_val2) < 0)//���� ������ ������� ��������
	{
		if (copy_val2.len - copy_val1.len != 0)
		{
			pow = copy_val2.len - copy_val1.len;
			copy_val1.up_size_for_operations(pow); // ����������� �� ������ �����
		}
		if (copy_val1.compare(copy_val2) < 0 && copy_val2.len - copy_val1.len == 0)
		{
			pow += 1;
			copy_val1.up_size_for_operations(1);
		}
	}
	temp.Long_int::operator = (copy_val1.Long_int::operator / (copy_val2));; // ����� �������� ������� ���������
																			 //if (copy_val1.Long_int::operator != (temp.Long_int::operator * (copy_val2))) // ������ ���� ������� �� �������, ������� ����� ��������� � ������� �����
																			 //{
																			 //	int i = 1;
																			 //	while (i < 7)
																			 //	{
																			 //		temp.Long_int::operator = (temp.Long_int::operator * (copy_val2));
																			 //		temp.Long_int::operator = (copy_val1.Long_int::operator - (copy_val2));
																			 //		temp.Long_int::operator = (temp.Long_int::operator / (copy_val2));
																			 //		++sub_pow;
																			 //	}
																			 //}
	if (pow != 0) //���� ������ ���� ������ �������
	{
		temp.pos_point = 1;
		temp.up_size_array(pow); //��������� � ���� �������� � ������� ��������
	}
	else
		temp.pos_point = temp.len;//����� ������� ����� ���������� ����� �������� �� ��������� (����� ���������� - ���������)
	return temp;
}

Unsigned_fractional_number Unsigned_fractional_number::operator + (Unsigned_fractional_number &val2)
{
	Unsigned_fractional_number temp, copy_val1 = *this, copy_val2 = val2;
	copy_val1.magic_with_digits(copy_val2);
	temp.Long_int::operator = (copy_val1.Long_int::operator + (copy_val2));
	temp.convert_pos_point(*this, val2);
	return temp;
}

Unsigned_fractional_number Unsigned_fractional_number::operator - (Unsigned_fractional_number &val2)
{
	Unsigned_fractional_number temp, copy_val1 = *this, copy_val2 = val2;
	copy_val1.magic_with_digits(copy_val2);
	if (copy_val1.compare(val2) >= 0)
	{
		temp.Long_int::operator = (copy_val1.Long_int::operator - (copy_val2));
		temp.convert_pos_point(*this, val2);
	}
	else // ���� ��������� �������������
	{
		temp.pos_point = temp.len;
	}
	return temp;
}

int Unsigned_fractional_number::compare_fraction_part(const Unsigned_fractional_number &val2)
{
	int result = 0;
	if (len - pos_point > val2.len - val2.pos_point)
		result = 1;// ���� ������� ����� ������� ������ ��. ����� �������
	else if (len - pos_point < val2.len - val2.pos_point)
		result = -1;
	return result;
}

int Unsigned_fractional_number::clean_string_and_char_to_int_with_dot(char buff[])
{
	negative = false;
	len = strlen(buff); // ����� �������
	bool slap = false;

	if (len != 0)
	{
		for (int i = 0; i < len; i++)
		{
			while ((buff[i] < '0' || buff[i] > '9') && buff[i] != '\0')
			{
				if (buff[i] == '-')
					negative = true;
				if (buff[i] == '.' && !slap)
				{
					pos_point = i;
					slap = true;
				}
				for (int j = i; buff[j] != '\0'; j++)
					buff[j] = buff[j + 1];
				len--;
			}
		}
	}
	if (!slap)
		pos_point = len;
	if (len != 0)
	{
		arr = new int[len]; // ������� ������
		for (int i = 0; i < len; i++)
			arr[i] = buff[i] - '0'; // ��������� ������
	}
	else
	{
		arr = new int(0);
		len = 1;
		negative = false;
	}
	return pos_point;
}

void Unsigned_fractional_number::up_size_for_operations(int pow)//���������� ����� � ������� ������� (� ������� �� Up_size_array)
{
	int i = 0;
	int *sub_arr = new int[len];
	copyr(sub_arr, len, arr, len);
	delete[] arr;
	len += pow;
	arr = new int[len];
	copyr(arr, len - pow, sub_arr, len - pow);
	for (int i = len - pow; i < len; i++)
		arr[i] = 0;
	delete[] sub_arr;
}

void Unsigned_fractional_number::magic_with_digits(Unsigned_fractional_number &val2)
{
	int pow = 0;
	if (len - pos_point != 0 || val2.len - val2.pos_point != 0) //���� ���� � ������
	{
		if (compare_fraction_part(val2) > 0)
		{
			pow = (len - pos_point) - (val2.len - val2.pos_point);
			val2.up_size_for_operations(pow);
		}
		else if (compare_fraction_part(val2) < 0)
		{
			pow = (val2.len - val2.pos_point) - (len - pos_point);
			up_size_for_operations(pow); // ��������� ������� ��������
		} //����� �� ����������, ���� ������� ����� ���������
	}
}

void Unsigned_fractional_number::convert_pos_point(Unsigned_fractional_number &val1, const Unsigned_fractional_number &val2) //�������� ��� ���� �������, ������� ��������
{
	if (len < val2.len || len < val1.len)//���� ������ ���� ����������� ��� ���������
	{
		if (val1.compare_fraction_part(val2) > 0)//������� ���� �����, pos_point = len
		{
			up_size_array(val1.len - len); // ��������� ������ ������� �������, ������� ����������
			pos_point = val1.pos_point;
		}
		else if (val1.compare_fraction_part(val2) < 0)
		{
			up_size_array(val2.len - len); // ��������� ������ ������� �������, ������� ����������
			pos_point = val2.pos_point;
		}
		else if (val2.len - val2.pos_point != 0 && val1.len - val1.pos_point != 0)//���� ����� �������� ���� ���������, �� ��� ���� ������ 1
		{
			up_size_array(val1.len - len);
			pos_point = val1.pos_point;
		}
	}
	else if (val2.len - val2.pos_point != 0 || val1.len - val1.pos_point != 0) //���� ���� ������� �����
	{
		if (val1.compare_fraction_part(val2) >= 0)
			pos_point = len - (val1.len - val1.pos_point);
		else
			pos_point = len - (val2.len - val2.pos_point);
	}
	if (val2.len - val2.pos_point == 0 && val1.len - val1.pos_point == 0)
		pos_point = len;
}

Unsigned_fractional_number::~Unsigned_fractional_number()
{
	/*	delete[] fraction_part;*/
}

istream & operator >> (istream &in, Unsigned_fractional_number &object)
{
	char buff[100];
	in >> buff;
	delete[] object.arr;
	object.pos_point = object.clean_string_and_char_to_int_with_dot(buff); // ��������� ��������, ��������� ������� �����
	if (object.negative)
	{
		Unsigned_fractional_number temp;
		object = temp;
	}
	return in;
}

ostream & operator << (ostream &out, Unsigned_fractional_number &object)
{
	int i = 0;
	for (i; i < object.pos_point; i++)
		out << object.arr[i];
	if (object.pos_point == 0)
		out << "0";
	if (object.pos_point != object.len)
	{
		out << ".";
		for (i; i < object.len; i++)
			out << object.arr[i];
	}
	return out;
}
