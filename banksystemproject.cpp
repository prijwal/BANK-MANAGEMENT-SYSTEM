#include<bits/stdc++.h>
using namespace std;
const int MIN_BALANCE=500;
class Account{
	private:
		long accountNumber;
		string firstName;
		string lastName;
		float balance;
		static long NextAccountNumber;
	public:
		Account();
		Account(string fName,string lName,float balance);
		long getAccNo(){return accountNumber; };
		string getFirstName(){return firstName;	};
		string getLastName(){return lastName; };
		float getBalance(){return balance; };
		void deposit(float amount){balance+=amount; };
		void withdraw(float amount){balance-=amount; };
		static void setLastAccountNumber(long accountNumber){NextAccountNumber=accountNumber; };
		static long getLastAccountNumber(){return NextAccountNumber; };
	friend ostream & operator <<(ostream &os,Account &acc);
	friend ofstream & operator <<(ofstream &ofs,Account &acc);
	friend ifstream & operator >>(ifstream & ifs,Account & acc);
};
long Account::NextAccountNumber=0; //Allocating memory to static member variable.
Account::Account(){ // Making default constructor
    accountNumber=-1;
	firstName="";
	lastName=" ";
	balance=0;
}
Account::Account(string fName,string lName,float balance){ // Making parameterized constructor
	accountNumber=++NextAccountNumber;
	firstName=fName;
	lastName= lName;
	this->balance=balance;
}
ostream & operator <<(ostream &os,Account &acc){   //Operator overloading for user defined Account data type
	os<<"first name= "<<acc.getFirstName() <<endl;
	os<<"last name= "<<acc.getLastName()<<endl;
	os<<"Account Number= "<<acc.getAccNo()<<endl ;
	os<<"balance= "<<acc.getBalance()<<endl;
	return os;
}
ofstream & operator <<(ofstream &ofs,Account &acc){   //Operator overloading for ofstream object
	ofs<<acc.accountNumber<<endl;
	ofs<<acc.firstName<<endl;
	ofs<<acc.lastName<<endl;
	ofs<<acc.balance<<endl;
	return ofs;
}
ifstream & operator >> ( ifstream &ifs, Account &acc){   //Operator overloading for ifstream object
	ifs>>acc.accountNumber; 
	ifs>>acc.firstName;
	ifs>>acc.lastName;
	ifs>>acc.balance;
	return ifs;
}
class Bank{
	private:
		map<long,Account> accounts;   ///Records of accounts
		void check(map<long,Account> ::iterator itr);
		Account read();   // To read details of already exixting accounts
		void write();     // To write the chnages took place within the program
	public:
		Bank();
		Account openAccount(string fname,string lname,float balance);
		Account balanceEnquiry(long accountNumber);
		Account deposit(long accountNumber,float amount);
		Account withdraw(long accountNumber,float amount);
		void closeAccount(long accountNumber);
		void showAllAcounts();

		~Bank();
};
Bank::Bank() {   //Calling bank constructor
	Account account;
	account=read();
	Account::setLastAccountNumber(account.getAccNo() );
}
void Bank::check(map<long,Account> ::iterator itr)  // Checking Giving account exist or not in data file
{
    try{
        if(itr==accounts.end())
        {
            string s="Account not found";
            throw s;
        }
    }
    catch(string msg){
        cout<<msg<<endl;
        this->Bank::~Bank(); //  calling destructor explicitly
    }
}
Account Bank::read()  // Reading bank data file
{
    Account account;
    ifstream infile;
	infile.open("bank.data");
	if(!infile.is_open()){
		std::cout<<"sorry your file is not open yet\n";
		return account;
	}

	while(!infile.eof()){
		infile>>account;
		accounts[account.getAccNo()]=account;
	}
	infile.close();
    return account;
}
void Bank::write()  // Writing into bank data file
{
    ofstream outfile;
	outfile.open("Bank.data",ios::trunc);
	map<long,Account>::iterator itr;
	for(itr = accounts.begin();itr!=accounts.end();itr++){
		outfile<<itr->second;
	}
	outfile.close();
}
Account Bank:: openAccount(string fname,string lname,float balance){  // Opening account
	Account account(fname,lname,balance);
	cout<<"got acc number "<<account.getAccNo()<<endl;
	accounts[account.getAccNo()]=account;
	return account;
}
Account Bank::balanceEnquiry(long accountNumber){   //Quering for account details
	map<long,Account>:: iterator itr= accounts.find(accountNumber);
	check(itr);
	return itr->second;
}
Account Bank::deposit(long accountNumber,float amount) {  //Depositing in account
	map<long,Account>::iterator itr = accounts.find(accountNumber);
    	check(itr);
	itr->second.deposit(amount);
	return itr->second;
}
Account Bank::withdraw(long accountNumber,float amount) {   //Withdrawing from account
	map<long,Account>::iterator itr = accounts.find(accountNumber);
	check(itr);

	float balance=itr->second.getBalance();
	cout<<"its balance is "<<balance<<"\n";
	try{
		if(balance-amount<MIN_BALANCE)
		{
		    throw balance;
		}
	}
	catch(float balance){
		cout<<"Insufficient Funds"<<endl;
		cout<<"Min "<<MIN_BALANCE<<" balance need to be maintained"<<endl;
		cout<<"Your current bal is "<<balance<<endl;
		this->Bank::~Bank(); //  calling destructor explicitly
	}
    	itr->second.withdraw(amount);
	return itr->second;
}
void Bank::closeAccount(long accountNumber) {      // Closing account
	map<long,Account>::iterator itr = accounts.find(accountNumber);
    	check(itr);
	cout<<"Your Account is deleted Successfully\n"<<itr->second;
	accounts.erase(accountNumber);
}
void Bank::showAllAcounts() {   //Showing account details
	map<long,Account>::iterator itr;
	for(itr = accounts.begin();itr!= accounts.end();itr++){
		cout<<"Account "<<itr->first<<endl<<itr->second<<endl;
	}
}
Bank::~Bank(){   // Calling destructor
	cout<<"Saving data"<<endl;
	write();
	exit(0);
}
main(){
	Bank b;
	Account acc;
	int choice;
	string fname,lname;
	long accountNumber;
	float balance;
	float amount;
	std::cout<<"****Banking system******\n";
	do{
		cout<<"\n\tSelect one option below ";
		cout<<"\n\t1 Open an Account";
		cout<<"\n\t2 Balance Enquiry";
		cout<<"\n\t3 Deposit";
		cout<<"\n\t4 Withdrawal";
		cout<<"\n\t5 Close an Account";
		cout<<"\n\t6 Show All Accounts";
		cout<<"\n\t7 Quit";
		cout<<"\nEnter your choice: ";
		cin>>choice;
	switch(choice){
		case 1:
			cout<<"Enter your first Good name\n";
			cin>>fname;
			cout<<"Enter your last Good name\n";
			cin>>lname;
			cout<<"enter initial balance to deposit\n";
			cin>>balance;
			acc=b.openAccount(fname,lname,balance);
			cout<<endl<<"Congratulations "<<fname<<" "<<lname<<" you created your Account Successfully\n"<<endl;
			cout<<acc;
			break;
		case 2:
			cout<<"Enter the customer accountNumber ";
			cin>>accountNumber;
			acc=b.balanceEnquiry(accountNumber);
			cout<<"****your Account Details*******"<<endl;
			cout<<acc;
			break;
		case 3:
			cout<<"Enter Your account number\t"<<endl;
			cin>>accountNumber;
			cout<<"Enter the amount to be submit\t"<<endl;
			cin>>amount;
			acc=b.deposit(accountNumber,amount);
			cout<<endl<<"\nAmount deposited successfully\n"<<endl;
			cout<<acc;
			break;
		case 4:
			cout<<"Enter Your AccountNumber\t"<<endl;
			cin>>accountNumber;
			cout<<"Enter the balance to withdraw\t"<<endl;
			cin>>amount;
			acc = b.withdraw(accountNumber,amount);
			cout<<"Withdraw operation is successfully executed"<<endl;
			cout<<acc;
			break;
		case 5:
			cout<<"Enter your account to be close\t"<<endl;
			cin>>accountNumber;
			b.closeAccount(accountNumber);
			cout<<"\nThis account with accountNumber\n "<<accountNumber<<" is successfully closed"<<endl;
			break;
		case 6:
			b.showAllAcounts();
			break;
		case 7:
			cout<<"\nDo you really want to quit\n"<<endl;
			break;
		default:
			cout<<"\nEnter the correct choice\n"<<endl;
			b.~Bank();   //  calling destructor explicitly
			exit(0);
		}
	}while(choice!=7);
}
