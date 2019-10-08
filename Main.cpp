#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "Records.h"
using namespace std;

string tolcase(string k) {//to bring all commands to lowercase to avoid errors with caps
	for (int i = 0; i < k.length(); i++)
		k[i] = tolower(k[i]);
	return k;
}

int main() {
	string command; //to hold the command the user would like to perform
	string fname, lname, filename, line; //to hold name to add or modify score of.
	float score;
	int err;//err for addstudent and addscore
	bool err2 = false;//error for load

	stringstream SS;
	Records records;

	cout << "valid commands are: addstudent, addgrad, addpscore, addscore, print, load or save or quit" << endl;

	while (command != "quit") {//check for if user enters "quit"
		
		command.clear(), fname.clear(), lname.clear();//clear values for re-entry
		line.clear(), SS.clear(), filename.clear(), score = -1;
		
		cout << "command>";//prompt for user
		getline(cin,line);//get user line
		SS.str(line);// load line into SS string
		SS >> command;//enter each command and argument 1 at a time

		command = tolcase (command);

		if (command == "print") { //prints the data

			cout << setw(20) << "first name" << setw(20) << "last name" << setw(15) << "type" <<setw(15) << "project" << setw(15) << "scores" << setw(26) << "Grade\n";

			for (int i = 0; i < records.get_count(); i++) { //loops through to get the names
				cout << setw(20) << records[i].firstname << setw(20) << records[i].lastname << setw(15) << records[i].student_type;
				
				if (records[i].proj_score >= 0) cout << setw(15) << records[i].proj_score << setw(15);
				if (records[i].proj_score < 0) cout << setw(30);//print out project scores if they exist

				int j;
				for (j = 0; j < records[i].count; j++) { //loops through each student scores
					cout << records[i].scores[j] << setw(5);
				}
				int x;
				if (j == 5) x = 10;//setting spacing for grades 
				if (j != 0) x = ((5 - j) * 5)+5;
				if (j == 0) x = 40;
				if (j == 0 && records[i].proj_score < 0) x = 55;

				cout << setw(x) << records[i].get_grade();
				cout << endl;
			}
		}

		if (command == "addstudent") { //if command is addstudent then check names are valid.
			
			SS>> fname >> lname;
			fname = tolcase(fname); lname = tolcase(lname);
			if (fname.empty() || lname.empty())//prompt user for incorrect syntax
				cout << "Use format: addstudent firstname lastname.\n";

			else {//run the addstudent
				err = records.add_student(fname, lname);
				//possible errors
				if (err == -2) cout << "Error: Student already exists.\n";
				if (err == -1) cout << "Error: Records full.\n";
			}

		}

		if (command == "addgrad") { //if command is addgrad then check names are valid.

			SS >> fname >> lname;
			fname = tolcase (fname); lname = tolcase (lname);
			if (fname.empty() || lname.empty())//prompt user for incorrect syntax
				cout << "Use format: addgrad firstname lastname.\n";

			else {//run the addstudent
				err = records.add_grad(fname, lname);
				//possible errors
				if (err == -2) cout << "Error: Student already exists.\n";
				if (err == -1) cout << "Error: Records full.\n";
			}

		}

		if (command == "addpscore") {
			SS >> fname >> lname >> score;
			fname = tolcase(fname); lname = tolcase(lname);

			//prompt user for incorrect syntax
			if (fname.empty() || lname.empty() || score == -1) cout << "Use format: addpscore firstname lastname score.\n";

			//prompt user for incorrect score
			else if (score < 0) cout << "Error:Score cannot be negative\n";

			else {//add the score
				err = records.add_proj_score(fname, lname, score);
				if (err == -2) cout << "Error: Sudent does not exist.\n";
				if (err == -1) cout << "Error: Scores full.\n";
			}
		}

		if (command == "addscore")//if command is addscore, then allow user to enter info and add the score.
		{
			SS >> fname >> lname >> score;
			fname = tolcase(fname); lname = tolcase(lname);
			
			//prompt user for incorrect syntax
			if (fname.empty() || lname.empty() || score == -1) cout << "Use format: addscore firstname lastname score.\n";
			
			//prompt user for incorrect score
			else if (score < 0) cout << "Error:Score cannot be negative\n";
			
			else {//add the score
				err = records.add_score(fname, lname, score);
				if (err == -2) cout << "Error: Sudent does not exist.\n";
				if (err == -1) cout << "Error: Scores full.\n";
			}
		}
		
		if (command == "save") {
			
			SS >> filename;
			filename = tolcase(filename);
			if (filename.empty())//prompt user for incorrect syntax
				cout << "Use format: save filename.txt\n";
			else//run the save
				records.saveF(filename);
		}

		if (command == "load") {
			SS >> filename;
			filename = tolcase(filename);
			if (filename.empty())//prompt user for incorrect syntax
				cout << "Use format: load filename.txt\n";

			err2 = records.loadF(filename);//run the load
			if (err2 == false)//report file error
				cout << "File does not exist or cannot be opened\n";
		}

		//if string is not a valid command report and retry
		else if (command != "quit" && command != "print" 
			&& command != "addstudent" && command != "addscore" &&
			command != "save" && command != "load" && command != "addgrad" && command != "addpscore") {

			cout << "invalid entry, please retry" << endl;
		}
	}
	return 0;
}
