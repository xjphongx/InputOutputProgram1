#include<iostream>
#include<fstream>//this is needed for input output files
#include <string>
#include<cstring>


//tip use cstring to take the whole character array then each spot will have a char number 


using namespace std;

struct Employee{
    char Name[20];
    float Balance;
};

//class declarations
void readData(Employee a[], int recordCount);
void Display(Employee a[],int recordCount);
void findRichest(Employee a[], int recordCount);
void Deposit(char CustName[20], Employee a[], int recordCount);
//void newCopy(string fileName, Employee a[],int recordCount);


int main()
{
    //this is needed in the beggining 
    ifstream inFile;

    //go throu file to get N and then closes it
    inFile.open("data.txt");
    int empCount = 0;
    string line;
    //this goes thru every line until the end where there arent anylines
    while(getline(inFile,line))
    {
        empCount++;
    }
    cout << "There are "<< empCount << " employees in the text file"<<endl; 
    Employee employee[empCount];
   

    //Start calling functions below here
    /*
        This will read data from file data.txt
    */
    readData(employee, empCount);

    /*
        Will display the inputs from the file data.text in the iofile folder
    */
    Display(employee, empCount);

    /*
        This will search through the array and find the wealthest person
    */
    findRichest(employee, empCount);
    
    /*
        Deposit will ask for name and compare inside the function
        if the name exist then it will run the function
        else exit
    */
    char CustName[20];
    cout << "Enter your full name to deposit money: ";
    cin >> CustName;
    Deposit(CustName, employee,empCount);

    //output the updated version into data.txt
    //ofstream outFile;
    //outFile.open("data.txt");
    //newCopy("data.txt",employee,empCount);

    //outFile.close();
    inFile.close();
    system("read -p 'Press Enter to continue...' var");
    return 0;
}
/*
    CLASS DEF
*/

void readData(Employee a[], int recordCount)
{
     ifstream inFile;
     inFile.open("data.txt");
    //this loop will read in everything into employee struct
    int index = 0;
    while(!inFile.eof())
    {
        char cName[20];
        string str1, str2;
        float pay;
        inFile >> str1;
        inFile >> str2; //these ignore white space?
        inFile >> pay;
        string name = str1 + " " + str2; //concatinate string
        //convert to cString now 
        strcpy(a[index].Name, name.c_str()); //this will convert into cString 
        a[index].Balance = pay;
        inFile.ignore();
        index++;//will move onto the next spot
    }
    inFile.close();
}

void Display(Employee a[],int recordCount)
{
    cout <<"\t\tName\t\tBalance"<<endl;
    cout<<"---------------------------------------"<<endl;
    for(int i=0;i<recordCount;i++)
    {
        cout<<"\t\t"<< a[i].Name<< " "<<a[i].Balance<<endl;
    }

}
/*
    The findRichest function will search and print out the person with the highest balance
*/
void findRichest(Employee a[], int recordCount)
{
    char richestPerson[20];
    int max = 0;
    for( int j = 0; j <recordCount; j++ )
    {
        if(a[j].Balance > max)
        {
            max = a[j].Balance;
            strcpy(richestPerson,a[j].Name);//this is not the same as sting 
            //*** ^^^ this is important 
            
        }
    }
    cout << "\nThe richest person in the list is "<< richestPerson <<endl;
}
/*
    The Deposit function searches for the CustName and will ask the amount to deposit and print it out
*/
void Deposit(char CustName[], Employee a[], int recordCount)
{
    bool isMatch = false;
    float depositAmount;
    for(int k = 0; k <recordCount; k++)
    {
        //add debugging stuff here to find name*********
        cout << a[k].Name <<endl;

        //strcmp(CustName, a[k].Name)==0)
        //int compNum = strcmp(CustName, a[k].Name);

        /*
            PROBLEM HERE IT WONT WORK
        */
        if(strcmp(CustName, a[k].Name)==0)//use this to compare cstrings
        {
            isMatch = true; //sets the bool to true if there is a match
            cout << a[k].Name << ". how much would you like to deposit? "<<endl;
            cin >> depositAmount;
            //add into balance
            a[k].Balance+=depositAmount;
            cout << "Now your new balance is " << a[k].Balance<<endl;
        }
        //this is statement is used to break out of the look if CustName is found
        if(isMatch)
        {
            break;
        }

    }
    //after the forloop search and still no match
    if(isMatch == false)
    {
        cout << "Personel does not exist in the list"<<endl;
    }



}

//void newCopy("data.txt",Employee a[],int recordCount)
//{

//}