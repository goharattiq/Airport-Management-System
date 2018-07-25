#include <iostream> 
#include <string>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <conio.h>   ///to use _getche
#include <Windows.h> ///to  use  gotoxy and  setcolor
using namespace std;


///Structs
struct staff
{
	int n;
	string name1;
	string name2;
	char name[20];
	string age;
	string  dh;
	string pay;
	string  exp;
	string categ;
};

struct ticket
{
	char name[20];
	string dep;
	string des;
	string sc;
	string gen;
	string age;
	string ltime;
	string ttime;
	string flightno;
};

struct flight
{
	string n;
	string dep;
	string des;
	string ltime;
	string ttime;
	string flightno;
};


///Functions Protoypes
void gotoxy(short int, short int);
void setColor(int);
bool loading();
void my_exit();
void draw_board();
void name_and_rol_no();
void Mainmenu();
bool Access();
void FlightMenu();
void Staff();
void Coustomer();
void Ticket(string, string);
void FlightChanging(string, struct flight l[], int);
void Add(string);
void Replace(string fname, struct flight l[], int b);
void Adds(int);
void Replaces(int);
void display(struct flight l[], int b);


void main()
{
	///system("color 10");
	name_and_rol_no();
	bool flag = loading();
	if (flag)
	{
	label: if (Access())
		Mainmenu();
		   else
			   goto label;
	}
	if (!(flag))
		my_exit();
}


void gotoxy(short int x, short int y)
{
	COORD cur = { x, y }; SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);
}


void setColor(int c)
{			///if (c < 15&& c> 0) font  color  else  background color  
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	SetConsoleTextAttribute(hConsole, (csbi.wAttributes & 0xFFF0) | (WORD)c);/// For ground colors take up the least significant byte
}


bool loading()
{
	char ch;
	gotoxy(20, 23);   /// Loading
	setColor(8);
	cout << "Loading...  ";
	gotoxy(5, 24);
	for (int i = 5; i <= 105; i++)
	{
		cout << "|";
		Sleep(30);
		gotoxy(37, 23);
		cout << i - 5 << " %";
		Sleep(30);
		gotoxy(i, 24);
	}
	gotoxy(30, 26);
	cout << "Press any key to continue ....";
	gotoxy(30, 27);
	cout << "Press Esc to Exit";
	bool flag = true;
	int num = 9;
	while (flag)
	{

		if (_kbhit())
		{
			ch = _getch();
			flag = false;
		}
	}
	if (ch == 27)
		return false;
	else
		return true;
}


void name_and_rol_no()
{
	///system("color fc");
	gotoxy(30, 16);
	setColor(11);
	cout << "PROJECT BY...";
	gotoxy(30, 18);
	setColor(14);
	char name[] = "GOHAR ATTIQ		MANHAR OMAR";
	for (int i = 0; name[i] != '\0'; i++)
	{
		Sleep(80);
		cout << name[i];
	}
	setColor(14);
	gotoxy(30, 19);
	char rollno[] = "BCSF17M026		BCSF17M052";
	for (int i = 0; rollno[i] != '\0'; i++)
	{
		Sleep(80);
		cout << rollno[i];
	}
}


void my_exit()
{
	system("cls");
	gotoxy(55, 13);
	setColor(11);
	cout << "Good Bye !!!";
	gotoxy(47, 17);
	_getch();
	exit(1);
}


void draw_board()
{
	int i = 30, j;
	gotoxy(i, 5);
	setColor(14);
	cout << "* * * * * * * * * * * * * * * * * * * * * * * * * * *";  /// above line of asterics
	cout << endl;

	for (j = 5; j <= 20; j++)   /// vertical  lines   of  asterics
	{
		gotoxy(i, j);
		cout << "*";
		gotoxy(84, j);
		cout << "*";
	}
	gotoxy(i, j - 1);
	cout << "* * * * * * * * * * * * * * * * * * * * * * * * * * *"; /// lower line of asterics
}


void Mainmenu()
{
	char n;
	system("CLS");
hell:
	setColor(9);
	gotoxy(20, 1);
	cout << "*************** Welcome to the Allama Iqbal International Airport ***************";
	gotoxy(45, 3);
	cout << "****** Main Menu ******";
	draw_board();
	setColor(2);
	gotoxy(35, 10);
	cout << "Press [1] to goto Flight Menu";
	gotoxy(35, 12);
	cout << "Press [2] to goto Staff Manegment";
	gotoxy(35, 14);  
	cout << "Press [3] to goto Coustomer Complaint Box";
	gotoxy(35, 16);
	cout << "Press [4] to Exit From Program";
	gotoxy(35, 22);
	bool flag = true;
	setColor(10);
	while (flag)
	{
			if (_kbhit())
			{
				n = _getch();
				flag = false;
			}
	}
	switch (n)
	{
	case '1': {FlightMenu(); break; }
	case '2': {Staff(); break; }
	case '3': {Coustomer(); break; }
	case '4': {my_exit(); break; }
	default: {
		setColor(12);
		cout << endl << "\aPress Correct Button" << endl; goto hell; }
	}
}
bool Access()
{
	system("CLS");
	string user, pass;
	draw_board();
	gotoxy(32, 8);
	setColor(9);
	cout << "LOG IN";                           
	gotoxy(32, 10);
	cout << "* * * * * * * * * * * * * * * * * * * * * * * * *";
	gotoxy(32, 13);
	setColor(9);
	cout << "User Name : "; // hint: admin
	cin >> user;
	gotoxy(32, 15);
	cout << "Password : ";    // hint: 123
	cin >> pass;
	if (user == "admin" && pass == "123")
	{
		return true;
	}
	else
	{
		return false;
	}
}


void FlightMenu()
{
	struct flight l[100];
	system("CLS");
hell1:	char n;
	string g;
	string fname;
	draw_board();
	setColor(2);
	gotoxy(33, 10);
	cout << "Press [1] to see International Flights Description";
	gotoxy(33, 13);
	cout << "Press [2] to see Local Flights Description";
	gotoxy(35, 22);
	setColor(10);
	bool flag = true;
	while (flag)
	{
		if (_kbhit())
		{
			n = _getch();
			flag = false;
		}
	}
	switch (n)
	{
	case '1': { fname = "Flight_International.txt"; break; }
	case '2': { fname = "Flight_Local.txt"; break; }
	default: {
		setColor(12);
		cout << endl << "\aPress Correct Button " << endl; goto hell1; }
	}
	cout << endl;
	int b = 0;
	system("CLS");
	ifstream fin;
	fin.open(fname);
	for (int i = 0; !(fin.eof()); i++)
	{
		fin >> l[i].n;
		fin >> l[i].des;
		fin >> l[i].dep;
		fin >> l[i].ltime;
		fin >> l[i].ttime;
		fin >> l[i].flightno;
		b++;
	}
	fin.close();
	display(l, b);
	system("pause");
	system("ClS");
hell: draw_board();
	setColor(2);
	gotoxy(35, 8);
	cout << "Press [1] to goto Ticket Generator" << endl;
	gotoxy(35, 10);
	cout << "Press [2] to goto Flight Changing" << endl;
	gotoxy(35, 12);
	cout << "Press [3] to goto Main Menu" << endl;
	gotoxy(35, 14);
	cout << "Press [4] to Exit from Program" << endl;
	gotoxy(35, 22);
	bool flag2 = true;
	while (flag2)
	{
		if (_kbhit())
		{
			n = _getch();
			flag2 = false;
		}
	}
	b--;
	bool flag1;
	switch (n)
	{
	case '1': {
		system("CLS");
		display(l, b);
		setColor(10);
		cout << endl << "Press Filght Number : ";
	label3: setColor(10);
		bool flag4 = true;
		while (flag4)
		{
			if (_kbhit())
			{
				cin >> g;
				flag4 = false;
			}
		}
		for (int i = 0; i <= b; i++)
		{
			if (g == l[i].n)
			{
				flag1 = true;
				break;
			}
			else
			{
				flag1 = false;
			}
		}
		if (flag1)
		{
			Ticket(g, fname);
		}
		else
		{
			setColor(12);
			cout << endl << "\aPress Correct Flight Number : "; goto label3;
		}
		break; }
	case '2': {FlightChanging(fname, l, b); break; }
	case '3': {Mainmenu(); break; }
	case '4': {my_exit(); break; }
	default: {
		setColor(12);
		cout << endl << "\aPress Correct Button " << endl; goto hell; }
	}
}


void display(struct flight l[], int b)
{
	setColor(7);
	cout << left << setw(6) << "S.No" << left << setw(15) << "Destination" << left << setw(15) << "Depature" << left << setw(15) << "Landing Time" << left << setw(15) << "Take off Time" << "Flight No." << endl;
	setColor(3);
	for (int i = 0; i <= b; i++)
	{
		cout << left << setw(6) << l[i].n << left << setw(15) << l[i].des << left << setw(15) << l[i].dep << left << setw(15) << l[i].ltime << left << setw(15) << l[i].ttime << l[i].flightno << endl;
	}
}

void Ticket(string g, string fname)
{
	struct flight c[100];
	int pas;
	string g1;
	ifstream fin;
	fin.open(fname);
	setColor(10);
	cout << endl << "How many tiekts You want to book : ";
hell:setColor(10);
	cin >> g1;
	stringstream e(g1);
	e >> pas;
	if (pas >= 0 && pas <= 9999999)
	{
		ticket* t = new ticket[pas];
		for (int i = 0; !(fin.eof()); i++)
		{
			fin >> c[i].n;
			if (c[i].n == g)
			{
				for (int j = 0; j<pas; j++)
				{
					setColor(10);
					cout << "Enter infomation about passenger no." << j + 1 << endl;
					cout << "Name : ";
					cin.ignore();
					setColor(9);
					cin.getline(t[j].name, 20);
					setColor(10);
					cout << "Age : ";
					setColor(9);
					cin >> t[j].age;
					setColor(10);
					cout << "Gender : ";
					setColor(9);
					cin >> t[j].gen;
					setColor(10);
					cout << "Seat And Class : ";
					setColor(9);
					cin >> t[j].sc;
					if (j == 0)
					{
						fin >> c[i].des;
						fin >> c[i].dep;
						fin >> c[i].ltime;
						fin >> c[i].ttime;
						fin >> c[i].flightno;
					}
					t[j].des = c[i].des;
					t[j].dep = c[i].dep;
					t[j].ltime = c[i].ltime;
					t[j].ttime = c[i].ttime;
					t[j].flightno = c[i].flightno;
				}
			}
			fin >> c[i].dep;
			fin >> c[i].des;
			fin >> c[i].ltime;
			fin >> c[i].ttime;
			fin >> c[i].flightno;
		}
		setColor(10);
		cout << "\n\n\n**Tickets**" << endl;
		setColor(14);
		for (int i = 0; i<pas; i++)
		{
			cout << "\n_________________________________________________________________________\n";
			cout << "|\t\t\t\t\t\t\t\t\t|\n";
			cout << "|\t\t\t\t\t\t\t\t\t|\n";
			cout << "| Name: " << left << setw(15) << t[i].name << "\t\t\tSeat & Class: " << left << setw(10) << t[i].sc << "\t|" << endl;
			cout << "| age: " << left << setw(15) << t[i].age << "\t\t\tFlight Number: " << left << setw(10) << t[i].flightno << "\t|" << endl;
			cout << "| Gender: " << left << setw(15) << t[i].gen << "\t\t\tDate: " << left << setw(10) << t[i].flightno << "\t|" << endl;
			cout << "|\t\t\t\t\t\t\t\t\t|\n";
			cout << "| \tTake Off Time: " << left << setw(15) << t[i].ttime << "\tLanding Time: " << left << setw(10) << t[i].ltime << "\t|" << endl;
			cout << "| \tDepature: " << left << setw(15) << t[i].dep << "\tDestination: " << left << setw(10) << t[i].des << "\t\t|" << endl;
			cout << "|\t\t\t\t\t\t\t\t\t|\n";
			cout << "|_______________________________________________________________________|\n";
		}
		fin.close();
		char n;
		system("pause");
		system("CLS");
	hell2: 	draw_board();
		setColor(2);
		gotoxy(35, 10);
		cout << "Press [1] to goto Mian Menu" << endl;
		gotoxy(35, 14);
		cout << "Press [2] to Exit from Program" << endl;
		gotoxy(35, 22);
		bool flag4 = true;
		while (flag4)
		{
			if (_kbhit())
			{
				n = _getch();
				flag4 = false;
			}
		}
		switch (n)
		{
		case '1': {Mainmenu(); break; }
		case '2': {my_exit(); break; }
		default: {
			setColor(12);
			cout << endl << "\aPress Correct Button " << endl; goto hell2; }
		}
	}
	else
	{
		setColor(12);
		cout << "\aPress Correct Button\n"; goto hell;
	}
}


void FlightChanging(string fname, struct flight l[], int b)
{
	system("CLS");
	char n;
hell: 	draw_board();
	setColor(2);
	gotoxy(35, 9);
	cout << "Press [1] to goto Add Flight Descriptin" << endl;
	gotoxy(35, 11);
	cout << "Press [2] to goto Replace in Flight Descriptin" << endl;
	gotoxy(35, 13);
	cout << "Press [3] to Exit from Program" << endl;
	gotoxy(35, 22);
	bool flag4 = true;
	while (flag4)
	{
		if (_kbhit())
		{
			n = _getch();
			flag4 = false;
		}
	}
	switch (n)
	{
	case '1': {Add(fname); break; }
	case '2': {Replace(fname, l, b); break; }
	case '3': {my_exit(); break; }
	default: {
		setColor(12);
		cout << endl << "\aPress Correct Button " << endl; goto hell; }
	}
}


void Replace(string fname, struct flight l[], int b)
{
	system("CLS");
	display(l, b);
	bool flag = false;
	int e = 0;
	int add;
	string c;
	ifstream fin;
	fin.open(fname);
	cout << endl << "Press Flight Serial Number\n";
hell1:
	setColor(10);
	cin >> c;
	stringstream g(c);                          ///string to int conversion
	g >> add;
 	if (add >= 0 && add <= 99999999)
	{
		for (int i = 0; !(fin.eof()); i++)
		{
			fin >> l[i].n;
			if (l[i].n == c)
			{
				flag = true;
				fin >> l[i].des;
				setColor(10);
				cout << "New Destination : ";
				setColor(9);
				cin >> l[i].des;
				fin >> l[i].dep;
				setColor(10);
				cout << "New Depature : ";
				setColor(9);
				cin >> l[i].dep;
				fin >> l[i].ltime;
				setColor(10);
				cout << "New landing time : ";
				setColor(9);
				cin >> l[i].ltime;
				fin >> l[i].ttime;
				setColor(10);
				cout << "New take off time : ";
				setColor(9);
				cin >> l[i].ttime;
				fin >> l[i].flightno;
				setColor(10);
				cout << "New flight number : ";
				setColor(9);
				cin >> l[i].flightno;
				i++;
				fin >> l[i].n;
			}
			fin >> l[i].des;
			fin >> l[i].dep;
			fin >> l[i].ltime;
			fin >> l[i].ttime;
			fin >> l[i].flightno;
			e++;
		}
		fin.close();
		if (!(flag))
		{
			setColor(12);
			cout << "\aEnter Correct Button : "; goto hell1;
		}
		ofstream fout;
		fout.open(fname);
		system("CLS");
		display(l, b);
		system("pause");
		FlightMenu();
	}
	else
	{
		setColor(12);
		cout << "\aEnter Correct Button : ";  goto hell1;
	}
}


void Add(string fname)
{
	system("CLS");
	setColor(10);
	int b = 0;
	int add;
	string e;
	ifstream fin;
	fin.open(fname);
	struct flight l[100];
	for (int i = 0; !(fin.eof()); i++)
	{
		fin >> l[i].n;
		fin >> l[i].des;
		fin >> l[i].dep;
		fin >> l[i].ltime;
		fin >> l[i].ttime;
		fin >> l[i].flightno;
		b++;
	}
	b--;
	fin.close();
	cout << endl << "How many Flights you want to add\n";
hell:
	setColor(10);
	cin >> e;
	stringstream g(e);                          /// string to int conversion
	g >> add;
	if (add >= 0 && add <= 99999999)
	{
		for (int i = b, j = 0; j < add; i++, j++)
		{
			stringstream g;                  /// int to string conversion
			g << i;
			l[i].n = g.str();
			cout << "Enter Destination : ";
			setColor(9);
			cin >> l[i].des;
			setColor(10);
			cout << "Enter Depature : ";
			setColor(9);
			cin >> l[i].dep;
			setColor(10);
			cout << "Enter Landing time : ";
			setColor(9);
			cin >> l[i].ltime;
			setColor(10);
			cout << "Enter Take Off Time : ";
			setColor(9);
			cin >> l[i].ttime;
			setColor(10);
			cout << "Enter Flight Number : ";
			setColor(9);
			cin >> l[i].flightno;
		}
		ofstream fout;
		fout.open(fname);
		for (int i = 0; i < b + add; i++)
		{
			fout << left << setw(10) << l[i].n << left << setw(20) << l[i].des << left << setw(15) << l[i].dep << left << setw(15) << l[i].ltime << left << setw(15) << l[i].ttime << l[i].flightno << endl;
		}
		b = b + add;
		fout.close();
		system("CLS");
		display(l, b);
		system("pause");
		FlightMenu();
	}
	else
	{
		setColor(12);
		cout << endl << "\aPress Correct Number" << endl; goto hell;
	}
}


void Staff()
{
	system("CLS");
	struct staff p[100];
	ifstream fin;
	fin.open("Staff.txt");
	system("CLS");
	int b = 0;
	setColor(14);
	cout << endl << "List of Staff Members\n\n";
	for (int i = 0; !(fin.eof()); i++)
	{
		fin >> p[i].n;
		fin >> p[i].name1;
		fin >> p[i].name2;
		fin >> p[i].age;
		fin >> p[i].dh;
		fin >> p[i].pay;
		fin >> p[i].exp;
		fin >> p[i].categ;
		b++;
	}
	fin.close();
	setColor(3);
	for (int i = 0; i<b; i++)
	{

		cout << p[i].n << ". Name: " << p[i].name1 << " " << left << setw(27) << p[i].name2 << " Age: " << p[i].age << endl;
		cout << "   Duty Hours: " << left << setw(27) << p[i].dh << "Income: " << p[i].pay << endl;
		cout << "   Experience: " << left << setw(27) << p[i].exp << "Category: " << p[i].categ << endl << endl;
	}
	system("pause");
	system("CLS");
hell: draw_board();
	setColor(2);
	gotoxy(35, 8);
	cout << "Press [1] to Add Staff Member" << endl;
	gotoxy(35, 10);
	cout << "Press [2] to Replace Staff Member" << endl;
	gotoxy(35, 12);
	cout << "Press [3] to goto Main Menu" << endl;
	gotoxy(35, 14);
	cout << "Press [4] to Exit from Program" << endl;
	gotoxy(35, 22);
	char d;
	bool flag4 = true;
	while (flag4)
	{
		if (_kbhit())
		{
			d = _getch();
			flag4 = false;
		}
	}
	switch (d)
	{
	case '3': {Mainmenu(); break; }
	case '1': {Adds(b); break; }
	case '2': {Replaces(b); break; }
	case '4': {my_exit(); break; }
	default: {
		setColor(12);
		cout << endl << "\aPress Correct Button " << endl; goto hell; }
	}
}


void Adds(int b)
{
	system("CLS");
	int add;
	string g;
	setColor(10);
	cout << endl << "How many Members you want to add : ";
hell1:setColor(10);
	cin >> g;
	stringstream s(g);
	s >> add;
	if (add >= 0 && add <= 9999999)
	{
		staff* p = new staff[add];
		for (int i = 0, j = b; i < add; j++, i++)
		{
			p[i].n = j;
			setColor(10);
			cout << "Enter Name : ";
			cin.ignore();
			setColor(9);
			cin.getline(p[i].name, 20);
			setColor(10);
			cout << "Enter Age : ";
			setColor(9);
			cin >> p[i].age;
			setColor(10);
			cout << "Enter Duty Hours : ";
			setColor(9);
			cin >> p[i].dh;
			setColor(10);
			cout << "Enter Pay : ";
			setColor(9);
			cin >> p[i].pay;
			setColor(10);
			cout << "Enter Experince : ";
			setColor(9);
			cin >> p[i].exp;
			setColor(10);
			cout << "Enter Category : ";
			setColor(9);
			cin >> p[i].categ;
		}
		ofstream fout;
		fout.open("Staff.txt", fout.app);
		for (int i = 0; i < add; i++)
		{
			fout << endl << p[i].n << " " << left << setw(38) << p[i].name << left << setw(40) << p[i].age << endl;
			fout << left << setw(40) << p[i].dh << left << setw(40) << p[i].pay << endl;
			fout << left << setw(40) << p[i].exp << setw(40) << p[i].categ;
		}
		fout.close();
		system("pause");
		system("CLS");
		Staff();
	}
	else
	{
		setColor(12);
		cout << "\aPress Correct Button : "; goto hell1;
	}
}


void Replaces(int b)
{
	system("CLS");
	struct staff p[100];
	int s;
	string g;
	setColor(10);
	cout << endl << "Enter Serial Number which you want to Replace : ";
hell1:
	setColor(10);
	cin >> g;
	stringstream e(g);
	e >> s;
	if (s >= 0 && s <= 9999999)
	{
		ifstream fin;
		fin.open("Staff.txt");
		for (int i = 0; !(fin.eof()); i++)
		{
			fin >> p[i].n;
			if (p[i].n == s)
			{
				setColor(10);
				cout << "Enter New Name : ";
				cin.ignore();
				setColor(9);
				cin.getline(p[i].name, 20);
				setColor(10);
				cout << "Enter New Age : ";
				setColor(9);
				cin >> p[i].age;
				setColor(10);
				cout << "Enter New Duty Hours : ";
				setColor(9);
				cin >> p[i].dh;
				setColor(10);
				cout << "Enter New Income : ";
				setColor(9);
				cin >> p[i].pay;
				setColor(10);
				cout << "Enter New Experience Years : ";
				setColor(9);
				cin >> p[i].exp;
				setColor(10);
				cout << "Enter New Category : ";
				setColor(9);
				cin >> p[i].categ;
			}
			fin >> p[i].name1;
			fin >> p[i].name2;
			fin >> p[i].age;
			fin >> p[i].dh;
			fin >> p[i].pay;
			fin >> p[i].exp;
			fin >> p[i].categ;
		}
		fin.close();
		ofstream fout;
		fout.open("Staff.txt");
		for (int i = 0; i < b - 1; i++)
		{
			if (p[i].n == s)
			{
				fout << endl << p[i].n << " " << left << setw(40) << p[i].name << p[i].age << endl;
				fout << left << setw(40) << p[i].dh << p[i].pay << endl;
				fout << left << setw(40) << p[i].exp << p[i].categ << endl;
			}
			else
			{
				fout << p[i].n << " " << p[i].name1 << " " << left << setw(36) << p[i].name2 << p[i].age << endl;
				fout << left << setw(40) << p[i].dh << p[i].pay << endl;
				fout << left << setw(40) << p[i].exp << p[i].categ << endl;
			}
		}
		fout.close();
		system("pause");
		system("CLS");
		Staff();
	}
	else
	{
		setColor(12);
		cout << "\aPress Correct Button : "; goto hell1;
	}
}


void Coustomer()
{
	system("CLS");
	string name;
	string mail;
	char c[100];
	setColor(10);
	cout << endl << "\t\t\t********** This Is Coustomer Care Box **********\n";
	cout << "Enter Your Name : ";
	setColor(14);
	cin.ignore();
	getline(cin, name);
	setColor(10);
	cout << "Enter Your E-mail : ";
	setColor(14);
	getline(cin, mail);
	setColor(10);
	cout << "Enter your Complaint Here \n";
	setColor(14);
	cin.getline(c, 100);
	ofstream fout;
	fout.open("complaint.txt");
	fout << "Name : " << name << endl;
	fout << "E-Mail : " << mail << endl;
	fout << "Complaint : ";
	for (int i = 0; !(c[i] == '\0'); i++)
	{
		fout << c[i];
	}
	char n;
	system("pause");
	system("CLS");
hell:
	draw_board();
	setColor(2);
	gotoxy(35, 10);
	cout << "Press [1] to goto Main Menu" << endl;
	gotoxy(35, 13);
	cout << "Press [2] to Exit from Program" << endl;
	gotoxy(35, 22);
	bool flag4 = true;
	while (flag4)
	{
		if (_kbhit())
		{
			n = _getch();
			flag4 = false;
		}
	}
	switch (n)
	{
	case '1': {Mainmenu(); break; }
	case '2': {my_exit(); break; }
	default: {
		setColor(12);
		cout << endl << "\aPress Correct Button " << endl; goto hell; }
	}
}
