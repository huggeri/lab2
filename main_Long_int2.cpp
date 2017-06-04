//(интерфейс)
#include "Long_int2.h"

char *menu_action(int key)
{
	char *action = " WHAT? ";
	switch (key)
	{
	case 1:
	{
		action = " * ";
		break;
	}
	case 2:
	{
		action = " / ";
		break;
	}
	case 3:
	{
		action = " + ";
		break;
	}
	case 4:
	{
		action = " - ";
		break;
	}
	case 5:
	{
		action = " = ";
		break;
	}
	}
	return action;
}

char *menu(int key)
{
	char *text = "Error!";
	switch (key)
	{
	case 1:
	{
		text = "Enter values:";
		break;
	}
	case 2:
	{
		text = "Select an action:\n"
			"1 - Summand\n2 - Division\n3 - Summary\n4 - Substraction\n5 - Get number by digit\n6 - Write in file\n7 - Read from file\n0 - Exit";
		break;
	}
	case 3:
	{
		text = "Enter digit and object number:";
		break;
	}
	case 4:
	{
		text = "Total objects: ";
		break;
	}
	}
	return text;
}

void main()
{
	bool flag = true;

	while (flag != !flag)
	{
		int menu_key = 0;
		cout << menu(1) << endl;
		Long_int val1;
		Long_int val2;
		Long_int result;
		cin >> val1;
		cin >> val2;
		cout << menu(2) << endl;
		cin >> menu_key;

		switch (menu_key)//вызываем функции
		{
		case 1://умножение
		{
			result = val1 * val2;
			cout << val1 << menu_action(menu_key) << val2 << menu_action(5) << result << "\t";
			cout << "LL " << result.to_long() << "\t";
			cout << menu(4) << Long_int::get_count_objects() << endl;
			break;
		}
		case 2://деление
		{
			result = val1 / val2;
			cout << val1 << menu_action(menu_key) << val2 << menu_action(5) << result << "\t";
			cout << "LL " << result.to_long() << "\t";
			cout << menu(4) << Long_int::get_count_objects() << endl;
			break;
		}
		case 3://сложение
		{
			result = val1 + val2;
			cout << val1 << menu_action(menu_key) << val2 << menu_action(5) << result << "\t";
			cout << "LL " << result.to_long() << "\t";
			cout << menu(4) << Long_int::get_count_objects() << endl;
			break;
		}
		case 4://вычитание
		{
			result = val1 - val2;
			cout << val1 << menu_action(menu_key) << val2 << menu_action(5) << result << "\t";
			cout << "LL " << result.to_long() << "\t";
			cout << menu(4) << Long_int::get_count_objects() << endl;
			break;
		}
		case 5://вывод цифры
		{
			int index = -1, key = 0;
			cout << menu(3) << endl;
			cin >> index;
			cin >> key;
			switch (key)
			{
			case 1:
			{
				index = val1.get_digit(index - 1);
				break;
			}
			case 2:
			{
				index = val2.get_digit(index - 1);
				break;
			}
			default:
				index = -1;
			}
			if (index >= 0)
			{
				cout << menu_action(menu_key) << index << endl;
			}
			else
				cout << menu(0) << endl;
			break;
		}
		case 6:
		{
			ofstream f("Newfile111222.txt", ios::out | ios::trunc);
			if (!f)
			{
				cerr << "Error: unable to write to Newfile.txt " << endl;
				system("pause");
				exit(1);
			}
			f << val1;
			f.close();
			break;
		}
		case 7:
		{
			ifstream f("Newfile111222.txt");
			if (!f)
			{
				cerr << "Error: unable to write to Newfile.txt " << endl;
				system("pause");
				exit(1);
			}
			f >> val2;
			f.close();
			cout << val2 << endl;
			break;
		}
		case 0:
		{
			cout << menu(4) << Long_int::get_count_objects() << endl;
			cout << LLONG_MAX << " & " << LLONG_MIN << endl;
			exit(0);
		}
		default:
			cout << menu(0) << endl;
		}
	}
}