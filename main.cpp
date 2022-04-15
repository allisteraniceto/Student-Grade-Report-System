/*
Programmer: Allister Aniceto
Purpose: Student grade report system
Date Modified: 2/17/2022
Compiler: MS VC++ 2019
*/

#include <iostream>
#include <fstream>
#include "grades_cls.h"
#include "add.h"
using namespace std;

//student grades class
class GradesCls {
private:
	string course;
	string letterGrade;
	double gpa;
public:
	GradesCls() { //Default Constructor
		course = "course";
		gpa = 0.0;
	}
	GradesCls(string c, double g) : course(c) { //intialization list
		this->gpa = g;
	}
	//set member functions
	void setCourse(string c) { this->course = c; };
	void setLetterGrade(string lg) { this->letterGrade = lg; }
	void setGpa(double g) { this->gpa = g; }

	//get member functions
	string getCourse() { return course; }
	string getLetterGrade() { return letterGrade; }
	double getGpa() { return gpa; }
};

//student class
class StudentCls {
private:
	int student_id;
	string fname, lname;
	GradesCls grades; //w
public:
	StudentCls() {
		student_id = 000000000;
		fname = "first name";
		lname = "last name";
		grades.setCourse("course");
		grades.setLetterGrade("N/A");
		grades.setGpa(0.0);
	}
	StudentCls(int id, string fn, string ln, string c, string lg, double g) {
		this->student_id = id;
		this->fname = fn;
		this->lname = ln;
		this->grades.setCourse(c);
		this->grades.setLetterGrade(lg);
		this->grades.setGpa(g);
	}

	//set member functions
	void setStudentID(int id) { student_id = id; }
	void setFname(string fn) { fname = fn; }
	void setLname(string ln) { lname = ln; }
	void setCourse(string c) { grades.setCourse(c); }
	void setLetterGrade(string lg) { grades.setLetterGrade(lg); }
	void setGpa(double g) { grades.setGpa(g); }

	//get member functions
	int getStudentID() { return student_id; }
	string getFname() { return fname; }
	string getLname() { return lname; }
	string getCourse() { return grades.getCourse(); }
	string getLetterGrade() { return grades.getLetterGrade(); }

	//store function (using serialization)
	void store(ofstream& outFile) {
		outFile.open("studentGrades.dat", ios::binary);

		//if there is an error opening the file 
		if (!outFile) {
			cout << "ERROR OPENING FILE...";
			cin.ignore();
			cin.get();
			exit(1);
		}
		else {
			int sID = student_id;
			outFile.write(reinterpret_cast<char*>(&student_id), sizeof(student_id));

			//write first name and last name( gets exact size of fname and lname and stores onto disk
			int fnameLength = fname.length();
			outFile.write(reinterpret_cast<char*>(&fnameLength), sizeof(int));
			outFile.write(fname.data(), fnameLength);

			int lnameLength = lname.length();
			outFile.write(reinterpret_cast<char*>(&lnameLength), sizeof(int));
			outFile.write(lname.data(), lnameLength);

			int c = grades.getCourse().length();
			outFile.write(reinterpret_cast<char*>(&c), sizeof(int));
			outFile.write(lname.data(), c);

			int g = grades.getLetterGrade().length();
			outFile.write(reinterpret_cast<char*>(&g), sizeof(int));
			outFile.write(lname.data(), g);
		}
		outFile.close();
	}
	//deserialization
	void load(ifstream& inFile) {
		inFile.open("studentGrades.dat", ios::binary);

		if (!inFile) {
			cout << "ERROR OPENING A FILE!";
			cin.ignore();
			cin.get();
			exit(1);
		}
		else {
			const int BUFFER_SIZE = 256;
			static char buffer[BUFFER_SIZE]; //used to read names

			inFile.read(reinterpret_cast<char*>(&student_id), sizeof(student_id));

			double gpa = grades.getGpa();
			inFile.read(reinterpret_cast<char*>(&gpa), sizeof(gpa));

			//get length and data for fname 
			int fnameLength;
			fnameLength = fname.length();
			inFile.read(reinterpret_cast<char*>(&fnameLength), sizeof(fnameLength));
			//read the data for fname into a local buffer
			inFile.read(buffer, fnameLength);
			//null terminate the buffer
			buffer[fnameLength] = '\0';
			fname = buffer;

			//do the same for lname, course, letterGrade
			int lnameLength;
			lnameLength = lname.length();
			inFile.read(reinterpret_cast<char*>(&lnameLength), sizeof(int));
			inFile.read(buffer, lnameLength);
			buffer[lnameLength] = '\0';
			lname = buffer;

			int courseLength;
			courseLength = grades.getCourse().length();
			inFile.read(reinterpret_cast<char*>(&courseLength), sizeof(int));
			inFile.read(buffer, courseLength);
			buffer[courseLength] = '\0';
			
			int letterGradeLength;
			courseLength = grades.getLetterGrade().length();
			inFile.read(reinterpret_cast<char*>(&letterGradeLength), sizeof(int));
			inFile.read(buffer, letterGradeLength);
			buffer[letterGradeLength] = '\0';
		}
		inFile.close();
	}
	//display fname, lname, gpa, grade, courses 
	void display() {
		cout << "Student ID: " << student_id << endl;
		cout << "Name: " << fname << " " << lname << endl;
		cout << "Grade: " << grades.getLetterGrade() << endl;
		cout << "Courses: " << grades.getCourse() << endl;
	}
};



void menu() {
	cout << endl;
	cout << "*--------------------------------------------------------*\n";
	cout << "|0. Exit                                                 |\n";
	cout << "|1. Enter ALL Student Information                        |\n";
	cout << "|2. Read ALL Student Information                         |\n";
	cout << "|3. Add Aditional Student Information                    |\n";
	cout << "|4. Search For a Particular Student by a Student ID      |\n";
	cout << "|5. List of All Students                                 |\n";
	cout << "*--------------------------------------------------------*" << endl;
}

string getFirstName() {
	string fname;
	cout << "What is you first name: ";
	cin >> fname;
	return fname;
}

string getLastName() {
	string lname;
	cout << "What is your last name: ";
	cin >> lname;
	return lname;
}

int main() {

	cout << "hello";

	//students
	int num;
	
	//ask user to enter how many students
	cout << "Please Enter # of Customers: ";
	cin >> num;


	//dynamic allocation of StudentCls array of objects
	StudentCls* studentList;
	studentList = new StudentCls[num];

	//variables for initializing
	int choice;
	string fn;
	string ln;

	menu();
	cout << "Enter a choice: ";
	cin >> choice;

	while (choice >= 0 && choice <= 5) {
		switch (choice) {
		case 0: //exit
			return 0;
		case 1: //enter student infromation
			for (int i = 0; i < num; i++) {
				cout << "*--------------------*" << endl;
				cout << "|CUSTOMER #" << i + 1 << " (ID: " << i << ") |" << endl;
				cout << "*--------------------*" << endl;
				studentList[i].setStudentID(1); //figure out a way to set SID and look up
				fn = getFirstName();
				studentList[i].setFname(fn);
				ln = getLastName();
				studentList[i].setLname(ln);


			}
		}
		menu();
		cout << "Enter a choice: ";
		cin >> choice;
		cout << endl;
	}

	delete[] studentList;
	system("pause");

	return 0;
}