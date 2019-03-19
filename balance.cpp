//Jimmy Phong
// Section 3

#include<iostream>
#include<fstream>//this is needed for input output files
#include <string>
#include<cstring>
#include <iomanip>


//tip use cstring to take the whole character array then each spot will have a char number 


using namespace std;

struct PERSON{
    char Name[20];
    float Balance;
};

//class declarations
PERSON * readData(int & N);
void Display(PERSON *arr,int N);
void findRichest(PERSON *arr, int N);
void Deposit(PERSON *arr, int N, char custName[], float amount);
void newCopy(string fileName, PERSON *arr,int N);


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
    P=readData(N);

    Display(P, N);

    findRichest(P, N);
    
    //Ask user before function call
    char CustName[20];
    float amount;
    cout << "\nEnter name: ";
    cin.getline(CustName,sizeof(CustName));//fill in the char array until 20
    cout << "Amount: ";
    cin >> amount;
    Deposit(P, N, CustName,amount);

    //output the updated version into data.txt
    newCopy("data.txt",P ,N);

    delete P; //deleting 'new' memory

    system("read -p 'Press Enter to continue...' var");
    return 0;
}


/*
    The readData function uses pointers referencing to read in from a file
*/
PERSON * readData(int & N)
{
     ifstream inFile;
     inFile.open("data.txt");
    PERSON *arryPtr= new PERSON[N];
    int index = 0;
    while(!inFile.eof())
    {
        //Updated with pointer usages 
        string str1, str2;
        inFile >> str1;
        inFile >> str2; 
        inFile >> arryPtr[index].Balance;
        string name = str1 + " " + str2;
        strcpy(arryPtr[index].Name,name.c_str());
        inFile.ignore();
        index++;

    }
    inFile.close();
    return arryPtr;
}
/*
    The Display function displays the current data with pointer usage
*/
void Display(PERSON *arr,int N)
{
    cout <<"\t\tName\t\tBalance"<<endl;
    cout<<"---------------------------------------"<<endl;
    for(int i=0;i<N;i++)
    {
        cout<<"\t\t"<< arr[i].Name<< " "<<fixed<< setprecision(2)<<arr[i].Balance<<endl;
    }

}
/*
    The findRichest function will search and print out the person with the highest balance
*/
void findRichest(PERSON *arr, int N)
{
    char richestPerson[20];
    float max = 0;
    for( int j = 0; j <N; j++ )
    {
        if(arr[j].Balance > max)
        {
            max = arr[j].Balance;
            strcpy(richestPerson,arr[j].Name);//this is not the same as sting 
            //*** ^^^ this is important 
        }
    }
    cout << "\nHighest balance: "<< richestPerson <<endl;
}
/*
    The Deposit function searches for the CustName and will ask the amount to deposit and print it out
*/
void Deposit(PERSON *arr, int N, char CustName[], float amount)
{
    bool isMatch = false;
    float depositAmount;
    for(int k = 0; k <N; k++)
    {
        /*
            PROBLEM HERE fixed on 2/21 at 12:10pm with a friend 
        */
        if(strcmp(CustName, arr[k].Name)==0)//use this to compare cstrings
        {
            isMatch = true; //sets the bool to true if there is a match
            //add into balance
            arr[k].Balance+=amount;
            cout << "New Balance " <<fixed<< setprecision(2)<< arr[k].Balance<<endl;
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
        cout << "Record not found"<<endl;
    }
}
/*
    The newCopy function outputs back into the data.txt and deletes and rewrites into it
*/
void newCopy(string fileName,PERSON *arr,int N)
{
    ofstream outFile;
    outFile.open(fileName);
    
    for(int l=0;l<N; l++)
    {
        outFile<< arr[l].Name << "\t"<< arr[l].Balance<<endl;
    }

    outFile.close();
    cout << "\nFile Updated..."<<endl;
}
