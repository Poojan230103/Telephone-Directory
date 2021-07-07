#include<iostream>
#include<fstream>   //   Header file for file handling
#include<cstring>

using namespace std;

class directory{

    private:

    char name[20];
    char telephone[11];
    char email[25];

    public:

    void enter_record();    
    // Function to add new data
    void display();
    // Function to view the directory
    void search_number(char* name);
    //  Function to search the number of a specified person
    void search_name(char* number);
    //  Function to search the name of person with given number
    void update_number(char* name);
    //  Function to update the data of the specified person
    void delete_record(char* name);
    //  Function to delete the record from the directory.
};

bool check_digits(char* number)   // Not a member function of directory class.

//This function checks whether the number of digits in the telephone number are equal to 10 or not.
{
    if(strlen(number)==10)
    {
        return true;
    }
    else if(strlen(number)<10)
    {
        cout<<"\nPhone number cannot be less than 10 digits!"<<endl;
    }
    else{
        cout<<"\nPhone number cannot exceed 10 digits!"<<endl;
    }
        return false;
}

void directory::enter_record()
{
    //  Taking input from the user.
    cout<<"Enter the name: ";
    cin>>this->name;

    do{
    cout<<"\nEnter the phone number: ";
    cin>>this->telephone;
    }
    while(check_digits(this->telephone) == false);

    cout<<"\nEnter the email address: ";
    cin>>this->email;
    cout<<"\n";

    fstream file("directory.dat", ios::out|ios::app|ios::binary);
    file.write((char*)this,sizeof(*this));   // write the into the "directory.dat" value to the file
    file.close();
}

void directory::display()
{
    cout<<"\n\tName\t   Telephone Number\t   Email address\n";
    cout<<"--------------------------------------------------------------------"<<endl;
    fstream file("directory.dat",ios::in|ios::app|ios::binary);
    while(file.read((char*)this,sizeof(*this)))   // input data from file
    {
    cout<<"\t"<<this->name<<"   \t"<<this->telephone<<"      \t"<<this->email<<endl;
    }
    file.close();
}

void directory::search_name(char* number)
{
    bool flag = false;
    ifstream file("directory.dat");
    while(file.eof()==0)
    {
        file.read((char*)this,sizeof(*this));
        if(strcmp(this->telephone,number)==0)
        {
            cout<<"\nContact found! "<<endl;
            cout<<"\nName\tTelephone Number\tEmail ID\n\n";
            cout<<this->name<<"\t"<<this->telephone<<"\t"<<this->email<<endl;
            cout<<endl;
            flag = true;
            break;
        }
    }
    if(flag == false)
    {
        cout<<"Contact not found!"<<endl;
    }
    file.close();
}

void directory::search_number(char* name)
{
    bool flag = false;
    ifstream file("directory.dat");
    while(file.eof()==0)
    {
        file.read((char*)this,sizeof(*this));
        if(strcmp(this->name,name)==0)
        {
            cout<<"\nContact found! "<<endl;
            cout<<"\nName\tTelephone Number\tEmail ID\n"<<endl;
            cout<<this->name<<"\t"<<this->telephone<<"\t"<<this->email<<endl;
            cout<<endl;
            flag = true;
            break;
        }
    }
    if(flag == false)
    {
        cout<<"Contact not found!"<<endl;
    }
}

void directory::update_number(char* name)
{
    bool flag = false;
    int cnt=0,offset;
    fstream dir("directory.dat",ios::in|ios::out|ios::binary);
    while(dir.read((char*)this,sizeof(*this)))
    {
        if(strcmp(this->name,name)==0)
        {
            cout<<"Enter the updated mobile number: ";
            cin>>this->telephone;
            cout<<"\nEnter the updated email address: ";
            cin>>this->email;
            offset = cnt*sizeof(*this);
            dir.seekg(offset);
            dir.write((char*)this,sizeof(*this));
            dir.close();
            flag = true;
            cout<<"\nDetails updated successfully."<<endl;
        }
        cnt++;
    }
    if(flag == false)
    {
        cout<<"\nDetails not found!"<<endl;
    }
}

void directory::delete_record(char *name)
{
    bool flag = false;
    fstream file("directory.dat",ios::in|ios::app|ios::binary);
    fstream new_file;
    new_file.open("dummy.dat",ios::out|ios::app|ios::binary);
    while(file.read((char*)this,sizeof(*this)))
    {

        if(strcmp(this->name,name)==0)
    {
            flag = true;
    }
        if(strcmp(this->name,name))
        {
            new_file.write((char*)this,sizeof(*this));
        }
    }
        file.close();
        new_file.close();
        remove("directory.dat");
        rename("dummy.dat","directory.dat");
        // new_file.close();
        cout<<"\nContact deleted successfully."<<endl;
        if(flag == false)
        {
            cout<<"\nContact not found!"<<endl;
        }
}


int main()
{
    directory direc;
    int choice=1;
    char name[20],phone[11];

    while(choice != 8)
    {
        cout<<endl;
        cout<<"FILE MENU"<<endl;
        cout<<"1. Add new record"<<endl;
        cout<<"2. Display the directory"<<endl;
        cout<<"3. Search the details of a person"<<endl;
        cout<<"4. Search the name and email address"<<endl;  // takes phone number as input and based on it searches the details of the person.
        cout<<"5. Update the Details"<<endl;
        cout<<"6. Delete a contact "<<endl;
        cout<<"7. Erase all contacts from the directory"<<endl;
        cout<<"8. EXIT"<<endl;
        cout<<"Enter your choice: ";
        cin>>choice;

        switch(choice)
        {
            case 1:
            direc.enter_record();
            break;
            case 2:
            direc.display();
            break;
            case 3:
            cout<<"Enter the name of the person whose details you want to search: ";
            cin>>name;
            direc.search_number(name);
            break;
            case 4:
            cout<<"Enter the phone number: ";
            cin>>phone;
            direc.search_name(phone);
            break;
            case 5:
            cout<<"Enter the name of the person whose data is to be updated: "<<endl;
            cin>>name;
            direc.update_number(name);
            break;
            case 6:
            cout<<"Enter the name of the person: "<<endl;
            cin>>name;
            direc.delete_record(name);
            break;
            case 7:
            remove("directory.dat");
            cout<<"Directory erased successfully."<<endl;
            break;
            case 8:
            break;
            default:
            cout<<"Invalid choice! Enter a valid choice: "<<endl;
            break;
        }
    }
    return 0;
}
