#include<bits/stdc++.h>
using namespace std;
const int MIN_BALANCE=500;
class Account{
	private:
		long accountNumber;
		string firstName;
		string lastName;
		float balance=0;
		static long NextAccountNumber;
	public:
		Account(){};
		Account(string fName,string lName,float balance);
		long getAccNo();
		string getFirstName(){return firstName;	};
		string getLastName(){return lastName; };
		float getBalance(){return balance; };
		void deposit(float amount);
		void withdraw(float amount);
		static void setLastAccountNumber(long accountNumber);
		static long getLastAccountNumber();
	friend ostream & operator <<(ostream &os,Account &acc);
	friend ofstream & operator <<(ofstream &ofs,Account &acc);
	friend ifstream & operator >>(ifstream & ifs,Account & acc);
};
long Account::NextAccountNumber=0; //Allocating memory to static member variable.
void update(map<long,Account> &accounts)
{
    ofstream outfile;
	outfile.open("Bank.data",ios::trunc);
	cout<<"updating "<<endl;
	map<long,Account>::iterator itr;
	for (itr = accounts.begin();itr!=accounts.end();itr++){
		outfile<<itr->second;
	}
	outfile.close();
}
void check(map<long,Account> ::iterator itr,map<long,Account> &accounts)
{
    try{
        if(itr==accounts.end())
        {
            string s="Account not found";
            update(accounts);
            throw s;
        }
    }
    catch(string msg){
        cout<<msg<<endl;
        exit(1);
    }
}
Account::Account(string fName,string lName,float balance){
    cout<<" acc number to be "<<NextAccountNumber<<endl;
	accountNumber=NextAccountNumber++;
	firstName=fName;
	lastName= lName;
	this->balance=balance;
}
long Account::getAccNo(){
	return accountNumber;
}
void Account::deposit(float amount){
	balance+=amount;
}
void Account::withdraw(float amount){
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
        exit(0);
    }

	balance-=amount;
}
void Account::setLastAccountNumber(long accountNumber){
		NextAccountNumber=accountNumber;
}
long Account::getLastAccountNumber(){
	return NextAccountNumber;
}
ostream & operator <<(ostream &os,Account &acc){
	os<<"first name= "<<acc.getFirstName() <<endl;
	os<<"last name= "<<acc.getLastName()<<endl;
	os<<"Account Number= "<<acc.getAccNo()<<endl ;
	os<<"balance= "<<acc.getBalance()<<endl;
	return os;
}
ofstream & operator <<(ofstream &ofs,Account &acc){
	ofs<<acc.accountNumber<<endl;
	ofs<<acc.firstName<<endl;
	ofs<<acc.lastName<<endl;
	ofs<<acc.balance<<endl;
	return ofs;
}
ifstream & operator >> ( ifstream &ifs, Account &acc){
	ifs>>acc.accountNumber;
	ifs>>acc.firstName;
	ifs>>acc.lastName;
	ifs>>acc.balance;
	return ifs;
}
class Bank{
	private:
		map<long,Account> accounts;   ///Records of accounts
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
Bank::Bank() {
	Account account;
	ifstream infile;
	infile.open("bank.data");
	if(!infile.is_open()){
		std::cout<<"sorry your file is not open yet\n";
		return;
	}
	while(!infile.eof()){
		infile>>account;
		accounts[account.getAccNo()]=account;
	}
	Account::setLastAccountNumber(account.getAccNo() );
	infile.close() ;
}
Account Bank:: openAccount(string fname,string lname,float balance){
	ofstream outfile;
	Account account(fname,lname,balance);
	cout<<"got acc number "<<account.getAccNo()<<endl;
	accounts[account.getAccNo()]=account;
	outfile.open("Bank.data",ios::trunc);
	map<long,Account>::iterator itr;
	for(itr = accounts.begin();itr!=accounts.end();itr++){
		outfile<<itr->second;
	}
	outfile.close();
	return account;
}
Account Bank::balanceEnquiry(long accountNumber){
	map<long,Account>:: iterator itr= accounts.find(accountNumber);
	check(itr,accounts);
	return itr->second;
}
Account Bank::deposit(long accountNumber,float amount) {
	map<long,Account>::iterator itr = accounts.find(accountNumber);
    check(itr,accounts);
    cout<<"bank class  amount "<<amount<<endl;
	itr->second.deposit(amount);
	return itr->second;
}
Account Bank::withdraw(long accountNumber,float amount) {
	map<long,Account>::iterator itr = accounts.find(accountNumber);
	check(itr,accounts);
	itr -> second.withdraw(amount);
	return itr->second;
}
void Bank::closeAccount(long accountNumber) {
	map<long,Account>::iterator itr = accounts.find(accountNumber);
    check(itr,accounts);
	cout<<"Your Account is deleted Successfully\n"<<itr->second;
	accounts.erase(accountNumber);
}
void Bank::showAllAcounts() {
	map<long,Account>::iterator itr;
	for(itr = accounts.begin();itr!= accounts.end();itr++){
		cout<<"Account "<<itr->first<<endl<<itr->second<<endl;
	}
}
Bank::~Bank(){
    ofstream outfile;
	outfile.open("Bank.data",ios::trunc);
	cout<<"updating "<<endl;
	map<long,Account>::iterator itr;
	for (itr = accounts.begin();itr!=accounts.end();itr++){
		outfile<<itr->second;
	}
	outfile.close();
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
		std::cin>>choice;
	switch(choice){
		case 1:
			cout<<"select one option below\n";
			cout<<"Enter your first Good name\n";
			cin>>fname;
			cout<<"Enter your last Good name\n";
			cin>>lname;
			cout<<"enter initial balance to deposit\n";
			cin>>balance;
			acc=b.openAccount(fname,lname,balance);
			cout<<endl<<"  Congratulations "<<fname<<" "<<lname<<" you created your Account Successfully\n"<<endl;
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
			exit(0);
		}
	}while(choice!=7);
}
