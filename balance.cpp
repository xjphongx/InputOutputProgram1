//Jimmy Phong
// Section 3

#include<iostream>
#include<fstream>//this is needed for input output files
#include <string>
#include<cstring>


//tip use cstring to take the whole character array then each spot will have a char number 


using namespace std;

struct PERSON{
    char Name[20];
    float Balance;
};

//class declarations
void * readData(int & N);
void Display(PERSON a[],int N);
void findRichest(PERSON a[], int N);
void Deposit(char CustName[20], PERSON a[], int N);
void newCopy(string fileName, PERSON a[],int N);


int main()
{
    //this is needed in the beggining 
    ifstream inFile;

    //go throu file to get N and then closes it
    inFile.open("data.txt");
    int N = 0;
    string line;
    //this goes thru every line until the end where there arent anylines
    while(getline(inFile,line))
    {
        N++;
    }
    cout << "There are "<< N << " employees in the text file"<<endl; 
    PERSON* P; // P is a pointer to object PERSON
    P= new PERSON[N];   //new pointer concept
   

    //Start calling functions below here
    /*
        This will read data from file data.txt
    */
    readData(N);

    /*
        Will display the inputs from the file data.text in the iofile folder
    */
    Display(P, N);

    /*
        This will search through the array and find the wealthest person
    */
    findRichest(P, N);
    
    /*
        Deposit will ask for name and compare inside the function
        if the name exist then it will run the function
        else exit
    */
    char CustName[20];
    cout << "Enter your full name to deposit money: ";
    cin.getline(CustName,sizeof(CustName));//fill in the char array until 20
    Deposit(CustName, P ,N);

    //output the updated version into data.txt
    newCopy("data.txt",P ,N);

    system("read -p 'Press Enter to continue...' var");
    return 0;
}
/*
    CLASS DEF
*/

void * readData(int & N)
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

void Display(PERSON a[],int N)
{
    cout <<"\t\tName\t\tBalance"<<endl;
    cout<<"---------------------------------------"<<endl;
    for(int i=0;i<N;i++)
    {
        cout<<"\t\t"<< a[i].Name<< " "<<a[i].Balance<<endl;
    }

}
/*
    The findRichest function will search and print out the person with the highest balance
*/
void findRichest(PERSON a[], int N)
{
    char richestPerson[20];
    float max = 0;
    for( int j = 0; j <N; j++ )
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
void Deposit(char CustName[], PERSON a[], int N)
{
    bool isMatch = false;
    float depositAmount;
    for(int k = 0; k <N; k++)
    {
        /*
            PROBLEM HERE fixed on 2/21 at 12:10pm with a friend 
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
/*
    This outputs back into the data.txt and deletes and rewrites into it
*/
void newCopy(string fileName,PERSON a[],int N)
{
    ofstream outFile;
    outFile.open(fileName);
    
    for(int l=0;l<N; l++)
    {
        outFile<< a[l].Name << "\t"<< a[l].Balance<<endl;
    }

    outFile.close();
    cout << "Data.txt has been updated."<<endl;
}
