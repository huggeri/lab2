#pragma once
//¬ариант 6.

#include <iostream>
#include <string>
#include <climits>
#include <fstream>

using namespace std;

class Long_int
{
	static unsigned int count_objects; //статическа¤ переменна¤, считающа количество созданных за всю работу программы объектов
	int len;
	int *arr; // указатель на массив
	bool negative; //знак числа
	void copyr(int *arr1, int len1, int *arr2, int len2);//работа с массивами
	void work_with_symbols(Long_int &val2, int key, int &change_symbol);
	int compare(const Long_int &val2);//сравнение
	void clean_arr();
	bool null(Long_int val2);
	void up_size_array(int length);
	void reduce_size_array(int length);
	void clean_string_and_char_to_int(char buff[]);
public:
	Long_int();
	Long_int(const Long_int &object); // конструктор копирования
  bool operator == (const Long_int &object);
	bool operator != (const Long_int &object);
  Long_int & operator = (const Long_int &object);// перегрузка оператора присваивани¤
	Long_int operator * (Long_int &val2);
	Long_int operator / (Long_int &val2);
	Long_int operator + (Long_int &val2);
	Long_int operator - (Long_int &val2);
	Long_int & operator ++ ();
	Long_int & operator -- (int);
	friend istream & operator >> (istream &in, Long_int &object);
	friend ostream & operator << (ostream &out, Long_int &object);
	friend ofstream & operator << (ofstream & out, Long_int &object);
	friend ifstream & operator >> (ifstream & in, Long_int &object);
	long long to_long();
	const char* get_symbol();
	int get_length();
	int get_digit(int index);
	static unsigned int get_count_objects();
	~Long_int(); //деструктор
};
