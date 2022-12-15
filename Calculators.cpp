#include<iostream>
//#include<boost/algorithm/string.hpp>
#include<string>
#include<conio.h>
using namespace std;

class Calculator
{
private:
    virtual int calc()const=0;

public:
    virtual void displayResult()const=0;
};

class Interest_Calculator: public Calculator
{
public:
    Interest_Calculator(int principal, double rate, int time): principal_(principal), rate_(rate), time_(time){}

    void displayResult() const override
    {
        cout<<"The total amount accrued, principal plus interest, from simple interest on a principal of \n"<<principal_<<" at a rate of "<<(int)(rate_*100)<<"% for "<<time_<<" years is "<<calc()<<endl;
    }

private:
    int principal_;
    double rate_;
    int time_;

    int calc()const override
    {
        return principal_ * (1 + (rate_ * time_));
    }
};

class Basic_Calculator: public Calculator
{
public:
    Basic_Calculator(int num1, int num2, char operation): num1_(num1),num2_(num2),operation_(operation){}

    void displayResult()const override
    {
        cout<<num1_<<" "<<operation_<<" "<<num2_<<" = "<<calc()<<endl;
    }
    
private:
    int num1_, num2_;
    char operation_;

    int calc()const override
    {
        switch(operation_)
        {
        case '+':
            return num1_ + num2_;
            break;    
        case '-':
            return num1_ - num2_;
            break;
        case '/':
            return num1_ / num2_;
            break;
        case '*':
            return num1_ * num2_;
            break;
        default:
            return 0;
            break;
        }
    }
};

class Factorial_Calculator
{
public:
    Factorial_Calculator(int number): number_(number){}
    
    void displayResult() const 
    {
        cout<<number_<<"! = "<<calc()<<endl;
    }

private:
    int number_;

    long double calc() const
    {
        long double result = 1;
        for(int i=1;i<=number_;i++)
        {
            result *= i;
        }
        return result;
    }
};

int errorChecker(istream& input,int& num1,const string& question)
{
    if(!(input>>num1))
    {
        cerr<<"Error: Invalid Input.\n";
        cin.clear();
        cin.ignore(1000,'\n');
        cout<<question;
        cin;
        errorChecker(cin,num1,question);
    }
    return num1;
}

double errorChecker(istream& input, double& double1, const string& question)
{
    if (!(input>>double1))
    {
        cerr << "Error: Invalid Input.\n";
        cin.clear();
        cin.ignore(1000, '\n');
        cout << question;
        cin;
        errorChecker(cin, double1, question);
    }
    return double1;
}


char errorChecker(istream& input, char& char1, const string& question, const string& allowedChars)
{
    string line;
    getline(input, line);

    if (line.length() != 1)
    {
        cerr << "Error: Invalid Input.\n";
        cout << question;
        char1 = errorChecker(input, char1, question, allowedChars);
    }
    else
    {
        char1 = line[0];

        if (allowedChars.find(char1) == string::npos)
        {
            cerr << "Error: Invalid Input.\n";
            cout << question;
            char1 = errorChecker(input, char1, question, allowedChars);
        }
    }

    return char1;
}

void displayCalculators()
{
    char choice;
    
    int num1,num2;
    char operation;

    int principal,time;
    double rate;
    
    cout<<"\nSelect an action by entering the character before each action. e.g.\"a\"\n"
    <<"Enter \'0\' to exit\n\n"
    <<"a.Basic Calculator\nb.Interest Calculator\nc.Factorial Calculator\n";
    cout<<"Enter letter: ";
    cin;
    choice = errorChecker(cin,choice,"Enter letter: ","abc0");

    switch(choice)
    {
    case 'a':
        {
        cout<<"Basic Calculator\n"
        <<"Enter two integers and an operation sign e.g. \'+\'"
        <<"\nEnter first number: ";
        cin;
        num1 = errorChecker(cin,num1,"Enter first number: ");
        cout<<"Enter second number: ";
        cin;
        num2 = errorChecker(cin,num2,"Enter second number: ");
        cout<<"Enter the operation: ";
        cin.clear();
        cin.ignore(1000,'\n');
        cin;
        operation = errorChecker(cin,operation,"Enter the operation: ","+-*/");
        Basic_Calculator a(num1,num2,operation);
        a.displayResult();
        cout<<"Press any key to continue\n\n";
        getch();
        displayCalculators();
        break;
        }
    case 'b':
        {
        cout<<"Interest Calculator\n"
        <<"This simple interest calculator calculates an accrued amount that includes principal plus interest\n";
        cout<<"Enter Principal ammount: ";
        cin;
        principal = errorChecker(cin,principal,"Enter Principal ammount: ");
        cout<<"Enter rate (in decimal): ";
        cin;
        rate = errorChecker(cin,rate,"Enter rate (in decimal): ");
        cout<<"Enter Time period (in years): ";
        cin;
        time = errorChecker(cin,time,"Enter Time period (in years): ");
        Interest_Calculator b(principal,rate,time);
        b.displayResult();
        cout<<"Press any key to continue\n\n";
        getch();
        displayCalculators();
        break;
        }
    case 'c':
        {
        cout<<"Factorial Calculator\n"
        <<"This calculator returns a factorial of a given number. e.g. 5! = 5*4*3*2 = 120\n"
        <<"Enter a number: ";
        cin;
        num1 = errorChecker(cin,num1,"Enter a number: ");
        Factorial_Calculator c(num1);
        c.displayResult();
        cout<<"Press any key to continue\n\n";
        getch();
        displayCalculators();
        break;
        }
    case '0':
        cout<<"Are you sure you want to exit?\nEnter \'y\' or \'n\'\n";
        choice = getch();
        switch(choice)
        {
            case 'y':
            exit(0);
            break;
            case 'n':
            displayCalculators();
            break;
        }
    default:
        cerr<<"Error: Invalid Character\n";
        displayCalculators();
    }
}

int main()
{
    cout<<"\nWelcome to Multipurpose Calculator\n";
    displayCalculators();

    return 0;
}
