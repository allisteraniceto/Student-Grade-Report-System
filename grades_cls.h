#pragma once
#include <iostream>
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