#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <iomanip>

void error_exit(std::string message){
      std::cerr << "ERROR: " << message << std::endl;
	  exit(1);
}
 
void parse_input(std::ifstream& infile, int& no_of_students, std::vector<double>& expenses){
      
	infile >> no_of_students;

	if(no_of_students == 0)
	       return;

	for(int i=0; i < no_of_students; i++){
		double expense;
		infile >> expense;
		expenses.push_back(expense);
	}     
}
 
double find_avg_expense(std::vector<double>& expenses){
	double total_expense = 0.0;
	for(int i=0; i < expenses.size(); i++){
		total_expense += expenses[i];
	}
	return total_expense/expenses.size();
}
 

double find_min_transfer_amount(int avg_expense, const std::vector<double>& expenses){
	double amount = 0.0;
	for(int i=0; i < expenses.size(); i++){
		if(expenses[i] < avg_expense){
			amount += (avg_expense - expenses[i]);
		}
	}
	return amount;
}

void usage(std::ostream &os, std::string message) {
	os << "ERROR: " << message << std::endl;
	os << "USAGE: bitmap <full-path-to-input-file>" << std::endl;
}

 
int main(int argc, char* argv[]){

	if(argc < 2){             
		usage(std::cerr, "Wrong Number of Inputs");
		exit(1);           
	}

	std::ifstream infile;
	infile.open(argv[1]);

	if(!infile){
		error_exit("Cannot Open Input File");
	}

	while(!infile.eof()){
		int no_of_students;
        	std::vector<double> expenses;
		parse_input(infile, no_of_students, expenses);

		if(no_of_students == 0){
			exit(0);
		}

		double avg_expense         = find_avg_expense(expenses);
		double min_transfer_amount = find_min_transfer_amount(avg_expense,expenses);
		std::cout << "$" << std::fixed << std::setprecision(2) << min_transfer_amount << std::endl;
	}

	infile.close();
	return 0;
}
