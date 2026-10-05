#include<iostream>
#include<fstream>
#include<iomanip>
#include<string.h>
#include<cstdlib>
#include<conio.h>
using namespace std;

//---------CLASS-----------//

class student
{
	int rollno;
	char name[50];
	int CD_marks, DT_marks, OOAD_marks, SE_marks, CG_marks, DSP_marks;
	double per;
	char grade;
	string user,password;
	void calculate();
public:
	void getdata();
	void showdata() const;
	void show_tabular() const;
	int retrollno() const;
	void login();
};


void student::calculate()
{
	per=(CD_marks + DT_marks + OOAD_marks + SE_marks + CG_marks + DSP_marks)/6.0;
	if(per>=80)
		grade='A';
	else if(per>=70)
		grade='B';
	else if(per>=40)
		grade='C';
    else if(per>=33)
		grade='D';
	else
		grade='F';
}

void student::getdata()
{
	cout<<"\nEnter The roll number of student ";
	cin>>rollno;
	cout<<"\n\nEnter The Name of student ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nEnter The marks in Compiler Design out of 100 : ";
	cin>>CD_marks;
	cout<<"\nEnter The marks in Data & Telecommunication out of 100 : ";
	cin>>DT_marks;
	cout<<"\nEnter The marks in Object Oriented Analysis & Design out of 100 : ";
	cin>>OOAD_marks;
	cout<<"\nEnter The marks in Software Engineering out of 100 : ";
	cin>>SE_marks;
	cout<<"\nEnter The marks in Computer Graphics out of 100 : ";
	cin>>CG_marks;
	cout<<"\nEnter The marks in Digital Signal Processing out of 100 : ";
	cin>>DSP_marks;
	calculate();
}

void student::showdata() const
{
	cout<<"\n\t\tRoll number of student : "<<rollno;
	cout<<"\n\t\tName of student : "<<name;
	cout<<"\n\t\tMarks in Compiler Design : "<<CD_marks;
	cout<<"\n\t\tMarks in Data & Telecommunication : "<<DT_marks;
	cout<<"\n\t\tMarks in Object Oriented Analysis & Design : "<<OOAD_marks;
	cout<<"\n\t\tMarks in Software Engineering : "<<SE_marks;
	cout<<"\n\t\tMarks in Computer Graphics :"<<CG_marks;
	cout<<"\n\t\tMarks in Digital Signal Processing :"<<DSP_marks;
	cout<<"\n\t\tPercentage of student is  :"<<per;
	cout<<"\n\t\tGrade of student is :"<<grade;
}

void student::show_tabular() const
{
    int len=strlen(name);
    int gap=15-len;
	cout<<rollno<<setw(6)<<" "<<name<<setw(gap)<<CD_marks<<setw(8)<<DT_marks<<setw(8)<<OOAD_marks<<setw(8)
		<<SE_marks<<setw(8)<<CG_marks<<setw(8)<<DSP_marks<<setw(8)<<per<<setw(7)<<grade<<endl;
}

int  student::retrollno() const
{
	return rollno;
}
//----------function declaration-----------//

void write_student();
void display_all();
void display_sp(int);
void modify_student(int);
void delete_student(int);
void class_result();
void result();
void intro();
void entry_menu();

//---------MAIN FUNCTION--------------//

int main()
{
    student ob;
	char ch;
	cout.setf(ios::fixed|ios::showpoint);
	cout<<setprecision(2);
	intro();
	do
	{
		system("cls");
		system("Color 7");
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\t01. RESULT MENU";
		cout<<"\n\n\t02. ENTRY/EDIT MENU";
		cout<<"\n\n\t03. EXIT";
		cout<<"\n\n\tPlease Select Your Option (1-3) ";
		cin>>ch;
		switch(ch)
		{
			case '1': result();
				break;
			case '2': ob.login();
				break;
			case '3':
				break;
			default :cout<<"\a";
		}
    }while(ch!='3');
	return 0;
}
//----------login function------------//

void student::login()
{
    system("cls");
    fstream file;
    string inputUser,inputPass;
    cout<<"\n\n\tEnter Admin Username and Password\n";
    file.open("login.txt",ios::in);
    cout<<"\n\n\tUsername: ";
    cin>>inputUser;
    cout<<"\n\n\tPassword: ";
    cin>>inputPass;
    file>>user>>password;
    if(user==inputUser)
    {
        if(password==inputPass)
        {
            entry_menu();
        }
        else
        {
            system("Color 4");
        cout<<"\n\n\tWrong password\n";
        }

    }
    else
        {
        system("Color 4");
        cout<<"\n\n\tWrong username\n";
        }

    file.close();


getch();

}
//---------function to write in file-----------//

void write_student()
{
	student st;
	ofstream outFile;
	outFile.open("student.dat",ios::binary|ios::app);
	st.getdata();
	outFile.write(reinterpret_cast<char *> (&st), sizeof(student));
	outFile.close();
    	cout<<"\n\nStudent record Has Been Created ";
	cin.ignore();
	cin.get();
	entry_menu();
}
//-------function to read all records from file----------//

void display_all()
{
	student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	cout<<"\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
	{
		st.showdata();
		cout<<"\n\n===========================================================\n";
	}
	inFile.close();
	cin.ignore();
	cin.get();
	entry_menu();
}
//--------function to read specific record from file---------//

void display_sp(int n)
{
	student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	bool flag=false;
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
	{
		if(st.retrollno()==n)
		{
	  		 st.showdata();
			 flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout<<"\n\nrecord not exist";
	cin.ignore();
	cin.get();
	entry_menu();
}
//---------function to view report card---------//

void report_card(int n)
{
	student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	bool flag=false;
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
	{
		if(st.retrollno()==n)
		{
	  		 st.showdata();
			 flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout<<"\n\nrecord not exist";
	cin.ignore();
	cin.get();
	result();
}
//-------function to modify record of file---------//

void modify_student(int n)
{
	bool found=false;
	student st;
	fstream File;
	File.open("student.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		entry_menu();
		return;
	}
    	while(!File.eof() && found==false)
	{

		File.read(reinterpret_cast<char *> (&st), sizeof(student));
		if(st.retrollno()==n)
		{
			st.showdata();
			cout<<"\n\nPlease Enter The New Details of student"<<endl;
			st.getdata();
		    	int pos=(-1)*static_cast<int>(sizeof(st));
		    	File.seekp(pos,ios::cur);
		    	File.write(reinterpret_cast<char *> (&st), sizeof(student));
		    	cout<<"\n\n\t Record Updated";
		    	found=true;
		}
	}
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
	cin.ignore();
	cin.get();
	entry_menu();
}
//--------function to delete single student from file--------//

void delete_student(int n)
{
    int file_found=0;
	student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	ofstream outFile;
	outFile.open("Temp.dat",ios::out);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
	{
		if(st.retrollno()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&st), sizeof(student));
		}
		else
        {
            file_found=1;
        }
	}
	outFile.close();
	inFile.close();
	remove("student.dat");
	rename("Temp.dat","student.dat");
	if(file_found==0)
    {
        cout<<"\n\n\tFile not found ..";
    }
    else
    {
        cout<<"\n\n\tRecord Deleted ..";
    }
	cin.ignore();
	cin.get();
	entry_menu();
}
//--------function to delete all student from file--------//

void delete_all(int n)
{
	if(n==1)
    {
        student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	ofstream outFile;
	outFile.open("Temp.dat",ios::out);
	inFile.seekg(0,ios::beg);

	inFile.clear();

	outFile.close();
	inFile.close();
	remove("student.dat");
	rename("Temp.dat","student.dat");

    cout<<"\n\n\tAll Record Deleted ..";
	cin.ignore();
	cin.get();
    }
	entry_menu();
}
//-------function to display all students grade report-------//

void class_result()
{
	student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	cout<<"\n\n\t\tALL STUDENTS RESULT \n\n";
	cout<<"=========================================================================================\n";
	cout<<"R.No           Name        CD      DT     OOAD     SE      CG     DSP    %      Grade"<<endl;
	cout<<"=========================================================================================\n";
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
	{
		st.show_tabular();
	}
	cin.ignore();
	cin.get();
	result();
	inFile.close();
}
//--------function to display result menu-----------//

void result()
{
	char ch;
	int num;
	system("cls");
	cout<<"\n\n\n\tRESULT MENU";
	cout<<"\n\n\n\t1. Class Result";
	cout<<"\n\n\n\t2. Student Report Card";
	cout<<"\n\n\n\t3. Back to Main Menu";
	cout<<"\n\n\n\tEnter Choice (1-3) ";
	cin>>ch;
	system("cls");
	switch(ch)
	{
	case '1' :	class_result(); break;
	case '2' : cout<<"\n\tPlease Enter The roll number "; cin>>num;
	report_card(num); break;
	case '3' :	break;
	default:	cout<<"\a";
	}
}
//----------INTRO FUNCTION-----------//

void intro()
{
	cout<<"\n\n\n\t\t  STUDENT";
        cout<<"\n\n\t\tREPORT CARD";
	    cout<<"\n\n\t MANAGEMENT SYSTEM PROJECT";
	    cout<<"\n\n\n\tMADE BY :\n\n\tJannatul Mawoa Jeba\n\n";
	    cout<<"\n\tUniversity :\n\n\tUniversity Of Global Village(UGV).";
	    cin.get();

}
//--------ENTRY / EDIT MENU FUNCTION----------//

void entry_menu()
{
	char ch;
	int num;
	system("cls");
	cout<<"\n\n\n\tENTRY MENU";
	cout<<"\n\n\t1.CREATE STUDENT RECORD";
	cout<<"\n\n\t2.DISPLAY ALL STUDENTS RECORDS";
	cout<<"\n\n\t3.SEARCH STUDENT RECORD ";
	cout<<"\n\n\t4.MODIFY STUDENT RECORD";
	cout<<"\n\n\t5.DELETE STUDENT RECORD";
    cout<<"\n\n\t6.DELETE ALL STUDENT RECORD";
	cout<<"\n\n\t7.Log Out";
	cout<<"\n\n\tPlease Enter Your Choice (1-7) ";
	cin>>ch;
	system("cls");
	switch(ch)
	{
	case '1':	write_student(); break;
	case '2':	display_all(); break;
	case '3':	cout<<"\n\n\tPlease Enter The roll number "; cin>>num;
			display_sp(num); break;
	case '4':	cout<<"\n\n\tPlease Enter The roll number "; cin>>num;
			modify_student(num);break;
	case '5':	cout<<"\n\n\tPlease Enter The roll number "; cin>>num;
			delete_student(num);break;
    case '6':	cout<<"\n\n\tDelete All File? \n\n\t1=Yes\n\n\t2=No\n\n\tPlease Enter Your Choice(1/2) "; cin>>num;
			delete_all(num);break;
	case '7':	main(); break;
	default:	cout<<"\a"; entry_menu();
	}
}
