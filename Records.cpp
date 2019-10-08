#include "Records.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <strstream>

Student::Student() {
	count = 0;
	firstname = "";
	lastname = "";
	for (int i = 0; i < NUM_SCORES; i++)
		scores[i] = 0;
	proj_score = -1;
}
Records::Records() {
	count = 0;
}
Records::~Records() {
}
Student::~Student() {
}

//add student to the record
int Records::add_student(string firstname, string lastname) {
	
	for (int j = 0; j < count; j++) {
		if (student[j]->firstname == firstname && student[j]->lastname == lastname) { //if both first AND last name match
			return -2;//report duplicate entry
		}
	}
	student[count] = new Ugrad;//assigning newstedunt to record
	student[count]->firstname = firstname; //assign firstname
	student[count]->lastname = lastname; //assign lastname
	count++; //incr count
	return 0;
}
	

//add student to the record
int Records::add_grad(string firstname, string lastname) {

	for (int j = 0; j < count; j++) {
		if (student[j]->firstname == firstname && student[j]->lastname == lastname) { //if both first AND last name match
			return -2;//report duplicate entry
		}
	}
	student[count] = new Grad;//assigning newstedunt to record
	student[count]->firstname = firstname; //assign firstname
	student[count]->lastname = lastname; //assign lastname
	count++; //incr count
	return 0;
}

//find correct student in record to add score
int Records::add_score(string f_read, string l_read, float score_in) {
	int added = 0; //declared to store return value
	for (int j = 0; j < count; j++) {
		if (student[j]->firstname == f_read && student[j]->lastname == l_read) { //if both first AND last name match
			added = student[j]->add_score(score_in); //call student add score function to add value to their scores
			if (added == 0) return 0; //return added success
		}
		if (added == -1) return -1; //return that the student exists, but the scores are full.
	}
	return -2;//return that student doesnt exist.
}

//find correct student in record to add project score
int Records::add_proj_score(string f_read, string l_read, float score_in) {
	int added = 0; //declared to store return value
	for (int j = 0; j < count; j++) {
		if (student[j]->firstname == f_read && student[j]->lastname == l_read) { //if both first AND last name match
			student[j]->add_proj_score(score_in); //call student add score function to add value to their scores
			return 0; //return added success
		}
		if (added == -1) return -1; //return that the student exists, but the scores are full.
	}
	return -2;//return that student doesnt exist.
}

//add a score to the student
int Student::add_score(float score_in) {
	if (count < NUM_SCORES) { //if there is space
		scores[count] = score_in; //assign score_in to available space
		count++; //increment count
		return 0;// return added success
	}
	else
		return -1;//return scores full.
}

//add a score to the student
void Student::add_proj_score(float score_in) {
		proj_score = score_in; //assign score_in to available space
}

//save the record
bool Records::saveF(string filename) {

	ofstream outfile; //output filestream object
	outfile.open(filename);//open file
	
	for (int i = 0; i < get_count(); i++) { //loops through to get the names

		outfile << student[i]->firstname << " " << student[i]->lastname << " " << student[i]->student_type << " " << student[i]->proj_score;//save name
		
		for (int j = 0; j < student[i]->count; j++) { //loops through each student scores
			outfile << " " << student[i]->scores[j];//saves scores
		}
		outfile << endl;//new line
	}

	outfile.close(); //close file
	return true;
}

char Ugrad::get_grade() {
	float grade= -1; // declare variables
	int i=0, x=0, y = 0;
	if (count == 0) i = 5;

	//sum scores
	while (i < count) {
		x = scores[i];
		y = x + y;
		i++;
	}
	
	//calculate numeric grade
	if (proj_score >= 0) {
		grade = ((y + proj_score) / (i + 1));
	}

	if (proj_score < 0) {
		grade = (y / i);
	}

	if (grade >= 90) return 'A';//return letter grades
	if (grade >= 80 && grade < 90) return 'B';
	if (grade >= 70 && grade < 80) return 'C';
	if (grade >= 60 && grade < 70) return 'D';
	if (grade >= 00 && grade < 60) return 'F';
	else {
		cout << "grade couldnt be calculated";
		return 'k';
	}
}

char Grad::get_grade() {
	float grade = -1;// declare variables
	int i = 0, x = 0, y = 0;
	if (count == 0) i = 5;

	//sum scores
	while (i < count) {
		x = scores[i];
		y = x + y;
		i++;
	}

	//calculate numeric grade
	if (proj_score >= 0) {
		grade = ((y + (5*proj_score)) / (i + 5));
	}

	if (proj_score < 0) {
		grade = (y / i);
	}
	if (proj_score < 65) return 'F';
	if (grade > 65 ) return 'P';//return letter grade
	if (grade >= 0 && grade <= 65) return'F';
	else {
		return 'e';
	}
}

//load the record
bool Records::loadF(string filename) {
	ifstream infile; //input filestream object
	infile.open(filename); //open the file
	
	if (!infile.is_open()) //if file isnt open
		return false; //return file doesnt exist
	else {
		float score, projscore;//to hold score to be added
		char type, i;
		string fname, lname, line; //to hold name and temp line
		strstream SS;

		for (int j = 0; j < 30; j++) {//load all students 1 at a time
			
			fname.clear(), lname.clear(); //clear variables each time
			line.clear(), SS.clear(), type = 0 , projscore = -1, score = -1;

			getline(infile, line); //get each line from infile
			SS << line; //put line into SS
			SS >> fname >> lname >> type >> projscore;
			
			if (fname.empty() || lname.empty()) j = 30;//set j to 30 to stop loop
			else {
				if (type == 'U') add_student(fname, lname); //add student
				if (type == 'G') add_grad(fname, lname); //add grad
			}
			if (projscore >= 0) add_proj_score(fname, lname, projscore);

			for (int k = 0; k < 5; k++) {//load all of a students scores 1 at a time
				score = -1;//"clear" score
				SS >> score;
				if (score == -1) k = 5;//set k to 5 to stop loop
				else
					add_score(fname, lname, score);//add score
			}
			SS >> i ;// discard score from save file
		}
		infile.close();//close file
		return true;
	}
}