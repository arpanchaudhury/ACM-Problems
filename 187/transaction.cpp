#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <cmath>
using namespace std;

class Account{
	private:
		string acNo;
		string acName;
	public : 
		
		Account(string acNo, string acName){
			this->acNo = acNo;
			this->acName = acName;		
		}
		string getAcName(){
			return acName;
		}
		string getAcNo(){
			return acNo;
		}
};

class TransactionUnit{
	private:
		string seqNo;
		string acNo;
		string amount;
	public :
		TransactionUnit(string seqNo,string acNo,string amount){
			this->seqNo = seqNo;
			this->acNo = acNo;
			this->amount = amount;
		}
		
		string getSeqNo(){
			return seqNo;
		}
		string getAcNo(){
			return acNo;
		}
		string getAmount(){
			return amount;
		}
};

class Transaction{
        public:
                vector<TransactionUnit> transactionUnits;
};

void getTransactions(vector<Transaction>& transactions, char* argv[]){
	ifstream infile;
	const unsigned short size = 20;
	char transactionUnit[size];
	infile.open(argv[2]);
	if(!infile){
		cout << "ERROR:: File Missing..."<<endl;
		exit(0);
	}
	string* currentTransaction = new string("");
	int j=0;
	do{
		infile.getline(transactionUnit,size);
		char seqNo[4];
		char acNo[4];
		char amount[10];
		int i;
		for(i=0;i<3;i++)
                        seqNo[i]=transactionUnit[i];
                seqNo[i]='\0';
		for(;i<6;i++)
			acNo[i-3]=transactionUnit[i];
		acNo[i-3]='\0';
		i++;
                while(transactionUnit[i]){
                        amount[i-7]=transactionUnit[i];
                        i++;
                }
                amount[i-7]='\0';
		if(strcmp(seqNo,"000") == 0){
			break;
		}
		if((*currentTransaction).compare(string(""))==0){
			currentTransaction = new string(seqNo);
			transactions.push_back(Transaction());
			transactions[j].transactionUnits.push_back(TransactionUnit(seqNo,acNo,amount));
		}
                else if(((*currentTransaction).compare(seqNo))==0){
			transactions[j].transactionUnits.push_back(TransactionUnit(seqNo,acNo,amount));
		}
		else{
			currentTransaction = new string(seqNo);
			transactions.push_back(Transaction());
			j++;
			transactions[j].transactionUnits.push_back(TransactionUnit(seqNo,acNo,amount));
		}
	}while(!infile.eof());
	infile.close();
}

void getAccounts(vector<Account>& accounts, char* argv[]){
	ifstream infile;
	const unsigned short size = 50; 
	char account[size];
	infile.open(argv[1]);
	if(!infile) 
	{
		cout << "Error:: File Missing..."<<endl;	
		exit(0);
	}
	do{
		infile.getline(account,size);
		char acNo[4];
		char acName[31];
		int i;
		for(i=0;i<3;i++)
			acNo[i]=account[i];
		acNo[i]='\0';
		while(account[i]){
			acName[i-3]=account[i];
			i++;
		}
		acName[i-3]='\0';
		if(strcmp(acNo,"000") == 0)
			break;		
		accounts.push_back(Account(acNo,acName));
	}while(!infile.eof());
	infile.close();
}

int main(int argc, char* argv[]){
	vector<Account> accounts;
	vector<Transaction> transactions;
	getAccounts(accounts, argv);
	getTransactions(transactions, argv);
	vector<Transaction>:: iterator iter;
	for(iter=transactions.begin();iter!=transactions.end();iter++){
		vector<TransactionUnit>:: iterator it;
		long amount = 0;
		for(it=(*iter).transactionUnits.begin();it!=(*iter).transactionUnits.end();it++){
			amount+=atoi((*it).getAmount().c_str());
		}
		if(amount != 0){
			cout<<"*** Transaction "<<(*iter).transactionUnits[0].getSeqNo()<<" is out of balance ***"<<endl<<endl;
			for(it=(*iter).transactionUnits.begin();it!=(*iter).transactionUnits.end();it++){
				string acNo = (*it).getAcNo();
				string acName;
				vector<Account> :: iterator itA;
				for(itA=accounts.begin();itA!=accounts.end();itA++){
					if(acNo.compare((*itA).getAcNo()) == 0)
						acName = (*itA).getAcName();
				}
				cout<<(*it).getSeqNo()<<" "<<acName<<" "<<(double)(atol((*it).getAmount().c_str())/100.0)<<endl;
                	}
			cout<<"999 Out of balance "<<fabs((double)(amount/100.0))<<endl<<endl<<endl;
		}
	}
	return 0;
}
