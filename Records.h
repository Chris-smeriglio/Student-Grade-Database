#ifndef RECORDS_H
#define RECORDS_H

#define NUM_SCORES 5
#define NUM_STUDENTS 30
#define MIN_PROJ_SCORE 65

#include <string>

using namespace std;
// The Student class is an abstract base class 
// (Student objects cannot be instantiated, but can use pointers of type Student)
class Student {
public:
	int count;
	string firstname;
	string lastname;
	char student_type; // U (for undergrad) or G (for grad)
	float scores[NUM_SCORES];
	float proj_score;

	Student();
	~Student();
	int add_score(float score);
	void add_proj_score(float score);

	// overridables
	virtual char get_grade() = 0;		// This is a pure virtual function -> Student is an abstract class
										// It is defined to force children to implement this interface function.
};

// Child classes (Must define the pure virtual function)
class Ugrad : public Student {
public:
	Ugrad() { student_type = 'U'; }
	char get_grade();
};
class Grad : public Student {
public:
	Grad() { student_type = 'G'; }
	char get_grade();
};

// The actual database
class Records {
	Student* student[NUM_STUDENTS];			// To create a student we must use dynamic memory allocation
	int count;
public:
	Records();
	~Records();

	// Member functions for adding students and their scores
	int add_student(string, string);		// for adding an undergraduate student
	int add_grad(string, string);			// for adding a gradyate student
	int add_score(string, string, float);	// for adding a score to a student (of any kind)
	int add_proj_score(string, string, float);// for adding a project score to a student (of any kind)

											  // member functions for accessing a student
	int get_count() { return count; }
	Student& operator[](int idx) {
		return *student[idx];
	}

	// Member functions for loading and saving files
	bool loadF(string filename);
	bool saveF(string filename);
};
#endif