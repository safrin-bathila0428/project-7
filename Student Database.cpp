#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;
class student
{
	int idnum;
	char name[50];
	int english,mathematics,physics,chemistry,comscience;
	double per;
	char grade;
	void calculate();
public:
	void getdata();
	void showdata()const;
	void show_tabular()const;
	int getIDNum()const;
};
void student::calculate()
{
	per=(english+mathematics+physics+chemistry+comscience)/5.0;
	if(per>=90)
	grade='A+';
	else if(per>=80)
	grade='A';
	else if(per>=70)
	grade='B+';
	else if(per>=65)
	grade='B';
	else if(per>=60)
	grade='B-';
	else if(per>=55)
	grade='C+';
	else if(per>=50)
	grade='C-';
	else
	grade='F';
}
void student::getdata()
{
	cout<<"\n\nEnter Students Name:";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nEnter students english grade:";
	cin>>english;
	cout<<"\nEnter students mathematics grade:";
	cin>>mathematics;
	cout<<"\nEnter students physics grade:";
	cin>>physics;
	cout<<"\nEnter students chemistry grade:";
	cin>>chemistry;
	cout<<"\nEnter students comscience grade:";
	cin>>comscience;
	calculate();
}
void student::showdata()const
{
	cout<<"\nName:"<<name;
	cout<<"\nEnglish:"<<english;
	cout<<"\nMathematics:"<<mathematics;
	cout<<"\nPhysics:"<<physics;
	cout<<"\nChemistry:"<<chemistry;
	cout<<"\nComscience:"<<comscience;
	cout<<"\nPercentage:"<<per;
	cout<<"\nLetter Grade:"<<grade;
}
void student::show_tabular()const
{
	cout<<idnum<<setw(6)<<""<<name<<setw(10)<<english<<setw(4)<<mathematics<<setw(4)<<physics<<setw(4)
	<<chemistry<<setw(4)<<comscience<<setw(8)<<per<<setw(6)<<grade;
}
int student::getIDNum()const
{
	return idnum;
}


void Savestudent();
void displayAll();
void Searchdisplay();
void modifystudent();
void deletestudent();
void DispalyClassResults();




void DisplayResults();
void write_student()
{
	student st;
	ofstream outFile;
	outFile.open("student.dat",ios::binary|ios::app);
	st.getdata();
	outFile.write(reinterpret_cast<char*>(&st),sizeof(student));
	outFile.close();
	cout<<"\n\nStudent record has been Created";
	cin.ignore();
	cin.get();
}
void display_all()
{
	student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open!! Press any key...";
		cin.ignore();
		cin.get();
		return;
	}
	cout<<"\n\n\n\t\tDisplay All Records!!!\n\n";
	while(inFile.read(reinterpret_cast<char*>(&st),sizeof(student)))
	{
		st.showdata();
		cout<<"\n\n===========================\n";
	}
	inFile.close();
	cin.ignore();
	cin.get();
}


void display_sp(int n)
{
	student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not open!!Press any key...";
		cin.ignore();
		cin.get();
		return;
	}
	bool flag=false;
	while(inFile.read(reinterpret_cast<char*>(&st),sizeof(student)))
	{
		if(st.getIDNum()==n)
		{
			st.showdata();
			flag=true;
		}
	}
	inFile.close();
	if(flag==false)
	cout<<"\n\nrecord not exits";
	cin.ignore();
	cin.get();
}


void modify_student(int n)
{
	bool found=false;
	student st;
	fstream File;
	File.open("student.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open!!Press any key...";
		cin.ignore();
		cin.get();
		return;
	}
	while(!File.eof()&&found==false)
	{
		File.read(reinterpret_cast<char*>(&st),sizeof(student));
		if(st.getIDNum()==n)
		{
			st.showdata();
			cout<<"\n\nPlease Enter The New Details of student ";
			st.getdata();
			int pos=(-1)*static_cast<int>(sizeof(st));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char*>(&st),sizeof(student));
			cout<<"\n\n\t Record Updated";
			found=true;
		}
	}
	File.close();
	if(found==false)
	cout<<"\n\n Record Not Found";
	cin.ignore();
	cin.get();
	}
	
	
void delete_student(int n)
{
	student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could notb be open!!Press any key...";
		cin.ignore();
		cin.get();
		return;
	}
	ofstream outFile;
	outFile.open("Temp.dat,ios::out");
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char*>(&st),sizeof(student)))
	{
		if(st.getIDNum()!=n)
		outFile.write(reinterpret_cast<char*>(&st),sizeof(student));
	}
	
}


void class_result()
{
	student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open!!Press any key...";
		cin.ignore();
		cin.get();
		return;
	}
	cout<<"\n\n\t\tALL STUDENTS RESULT\n\n";
	cout<<"==============================================\n";
	cout<<"R.NO     NAME   E  M  P  C  CS   %age  Grade";
	cout<<"==============================================\n";
	while(inFile.read(reinterpret_cast<char*>(&st),sizeof(student)))
	{
		st.show_tabular();
	}
	cin.ignore();
	cin.get();
	inFile.close();
}
int main()
{
	char ch;
	int num;
	cout.setf(ios::fixed|ios::showpoint);
	cout<<setprecision(2);
	do
	{
		system("cls");
		cout<<"\t**********************************";
		cout<<"\n\n\t1.CREATE STUDENT RECORD";
		cout<<"\n\n\t2.DISPLAY ALL STUDENTS RECORDS";
		cout<<"\n\n\t3.SEARCH STUDENT RECORD";
		cout<<"\n\n\t4.MODIFY STUDENT RECORD";
		cout<<"\n\n\t5.DELETE STUDENT RECORD";
		cout<<"\n\n\t6.DISPLAY CLASS RESULTS";
		cout<<"\n\n\t7.EXIT";
		cout<<"\n\n\t********************************";
		cout<<"\n\n\tEnter your choice(1-7):";
		cin>>ch;
		system("cls");
		switch(ch)
		{
			case'1':write_student();break;
			case'2':display_all();break;
			case'3':cout<<"\n\n\tEnter studentss ID number:";cin>>num;
			display_sp(num);break;
			case'4':cout<<"\n\n\tEnter students ID number: ";cin>>num;
			modify_student(num);break;
			case'5':cout<<"\n\n\tEnter students ID number:";cin>>num;
			delete_student(num);break;
			case'6':class_result();break;
			case'7':exit(0);;
			default:cout<<"\a";
		}
	}while(ch!='7');
	return 0;	
}

