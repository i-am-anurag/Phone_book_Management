#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <stdio.h>
#include <iomanip>
#include <conio.h>
#include <fstream>

using namespace std;

struct Phone
{
    char name[15];
    char family[15];
    char tel[12];

    Phone *next;
};

Phone* Start_ptr = NULL;
Phone* current = NULL;

void Select ( int ); // which choice user selected;
void Add_new();
void Print_all();
void Menu1();
void Menu2();
void Edit_current();

void Delete_current ();
void Delete_all();
void Tel_or_name( int );
void Read_from_file();
void Write_to_file();

void Sort_name( int );
void Add_tail_from_file( Phone* );

Phone* Search( char* , int);


enum MENU{ ADD=1, SEARCH_NAME, SEARCH_NO, SORT_NAME, SORT_FAMIL, SHOW_ALL, SAVE, EXPORT_CSV, EXIT, UNINSTALL };

int main()
{
    Read_from_file();

    int choice;

    do
    {
        Menu1();
        cin >> choice;
        system("cls");
        Select ( choice );

    }while ( choice != EXIT );

    Write_to_file();

    cout <<"Thank you" << endl;
    Delete_all();
    getch();
    return 0;
}

/*===================Select=======================*/
void Select( int choose )
{
    switch ( choose )
    {
    case ADD :
        Add_new();      break;

    case SEARCH_NAME :
        Tel_or_name(1); break;

    case SEARCH_NO :
        Tel_or_name(2); break;

    case SORT_NAME :
        Sort_name(1);   break;

    case SORT_FAMIL :
        Sort_name(2);   break;

    case SHOW_ALL :
        Print_all();    break;

    case SAVE :
        Write_to_file();
        cout <<"We will save your data automatically when your work finished" << endl;
        return;
        break;



    case EXIT :
        return;



    default :
        cout <<"Select again :" << endl;
    }
    getch();
    return;
}
/*=================Add_new=====================*/
void Add_new()
{
    Phone* temp = new Phone;
    Phone* temp2 = Start_ptr;

    system("cls");

    cout << "Enter the name : ";
    cin >> temp->name;
    cout << "Family : ";
    cin >> temp->family;
    cout << "Phone number : ";
    cin >> temp->tel;

    temp->next = NULL;

    if ( Start_ptr == NULL )
    {
        Start_ptr = temp;
    }

    else
    {
        while( temp2->next != NULL )
        {
            temp2 = temp2->next;
        }
        temp2->next = temp;
    }
    getch();
    return;
}
/*==============Print_all=======================*/
void Print_all()
{
    Phone* temp = Start_ptr;
    char show[35];

    if ( Start_ptr == NULL )
    {
        cout <<"The list is empty!" << endl;

        return;
    }
    else
    {
        cout<<"\nName                                Phone       "
            <<"\n----------------------------------- ------------" << endl;
        do
        {
            strcpy(show, "");
            strcat(show, temp->family);
            strcat(show, ", ");
            strcat(show, temp->name);
            show[0] = toupper(show[0]);
            cout << setiosflags( ios::left )
                << setw(36) << show << setw(12) <<temp->tel <<endl;

            temp = temp->next;
        }while(temp != NULL);
    }
    cout << endl;
    getch();
    return;
}

/*=================Search=======================*/
Phone* Search( char* temp_search , int choice )
{
    /* If list is empty */
    if ( Start_ptr == NULL )
    {
        cout <<"List is empty!" << endl;
        return NULL;
    }

    /* Search by name */
    if ( choice == 1 )
    {
        while( current != NULL && strcmp( current->name, temp_search ) != 0 )
        {
            current = current->next;
        }
    }

    /* Search by tel */
    if ( choice == 2 )
    {
        while( current != NULL && strcmp( current->tel, temp_search ) != 0 )
        {
            current = current->next;
        }

    }

    /* If record found */
    if ( current != NULL )
    {
        cout << "Record found" << endl
            << current->name << " " << current->family << " : " << current->tel << endl;

        return current;
    }

    /* If record !found */
    else
    {
        cout <<"Record NOT found" << endl;
        current = Start_ptr; //move back the current pointer to fisrt node
        return NULL;
    }
}

/*====================Delete_current====================*/
void Delete_current()
{
    Phone* temp = NULL;
    Phone* prev = NULL;

    /* If it`s the fisrt node */
    if ( current == Start_ptr )
    {
        temp = Start_ptr;
        Start_ptr = Start_ptr->next; //If we have only 1 node, start_ptr will point to NULL
        delete temp;
        temp = NULL;
    }

    /* If it`s in the middle of list or the last node */
    else
    {
        prev = Start_ptr;
        while( prev->next != current )
        {
            prev = prev->next;
        }
        prev->next = current->next;// If it`s the last node prev will point to NULL
        delete current;
        current = Start_ptr;
    }
}

/*=================Delete_all=================*/
void Delete_all()
{
    if ( Start_ptr == NULL )
    {
        return; // we have no memory allocated
    }

    Phone* temp = Start_ptr;
    while( Start_ptr != NULL )
    {
        temp = Start_ptr;
        Start_ptr = Start_ptr->next;
        delete temp;
    }
}

/*=================Tel_or_name================*/
void Tel_or_name(int choose)
{
    Phone* temp_del = NULL;
    char temp_search[15];
    int choice;

    current = Start_ptr;

    cout <<"Enter the "<<(choose == 1 ? "name" : "tel") <<" to search : ";
    cin >> temp_search;

    temp_del = Search( temp_search, choose );

    while ( temp_del != NULL )
    {
        Menu2();
        cin >> choice;

        switch( choice )
        {
        case 1: current = current->next; temp_del = Search( temp_search, choose ); break;
        case 2: Delete_current(); break;
        case 3: Edit_current();   break;
        case 4: return;
        }
    }


}
/*==============Write_to_file=============================*/
void Write_to_file()
{
    Phone* temp = Start_ptr;
    ofstream outFile("Data.dat" , ios::out );

    if( !outFile )
    {
        cerr << "Some error ocured during writing to file." << endl;

        return;
    }

    while( temp != NULL )
    {
        outFile << temp->name << " " << temp->family << " " << temp->tel;
        if( temp->next != NULL )
        {
            outFile << endl;
        }
        temp = temp->next;

    }

    outFile.close();

    cout <<"Data saved successfully." << endl;
}
/*===============Read_from_file=============================*/
void Read_from_file()
{
    ifstream inputFile("Data.dat" , ios::in );

    if ( !inputFile )
    {
        cout << "Data couldn`t be loaded." << endl;

        return;
    }

    do
    {
        Phone* temp = new Phone;

        inputFile >> temp->name;
        inputFile >> temp->family;
        inputFile >> temp->tel;
        temp->next = NULL;

        Add_tail_from_file( temp );

        //Where should I place delete temp?????
    }while( !inputFile.eof() );

    cout <<"Data loaded successfully" << endl;
}

/*==============Add_tail_from_file=================*/
void Add_tail_from_file( Phone* temp )
{

    if ( Start_ptr == NULL )
    {
        Start_ptr = temp;
    }
    else
    {
        Phone* temp2 = Start_ptr;
        while ( temp2->next != NULL )
        {
            temp2 = temp2->next;
        }
        temp2->next = temp;
    }
}

/*================Sort_name=================================*/

void Sort_name(int choice)
{
    /* If list is empty */
    if ( Start_ptr == NULL )
    {
        cout <<"The list is empty!" << endl;

        return;
    }

    /* Determine the size of list */
    int counter = 1;
    Phone* temp = Start_ptr;

    while( temp->next != NULL )
    {
        temp = temp->next;
        counter++;
    }

    /* an Array of pointers to struct Phone. I couldn`t do this part by dynamic memory
    allocation i.e Phone* sort = new Phone[counter]
    or some thing like that. if you could help, please send me your suggestion .*/
    Phone* sort[1000];

    sort[0] = Start_ptr;
    for ( int cnt = 1; cnt < counter; cnt++ )
    {
        sort[cnt] = sort[cnt-1]->next;
    }
    sort[counter] = NULL;

    /* bubble sort */
    /* This part could be better too.for example if user enter capital 'F' it comes
       before 'a'. I had to change all letter to lower case but has no time. */

    for ( int i = 0; i < counter; i++ )
    {
        for ( int j = 0; j < counter - i - 1; j++)
        {
            /* Sort by name */
            if ( choice == 1 )
            {
                if ( strcmp(sort[j]->name, sort[j+1]->name) > 0 )
                {
                    Phone* temp2 = sort[j];
                    sort[j] = sort[j+1];
                    sort[j+1] = temp2;
                }
            }

            /* Sort by family */
            else
            {
                if ( strcmp(sort[j]->family, sort[j+1]->family) > 0 )
                {
                    Phone* temp2 = sort[j];
                    sort[j] = sort[j+1];
                    sort[j+1] = temp2;
                }
            }
        }
    }

    /* Showing sorted list */
    char show[35];
    int index= 0;

    cout<<"\nName                                Phone       "
        <<"\n----------------------------------- ------------" << endl;
    do
    {
        strcpy(show, "");
        strcat(show, sort[index]->family);
        strcat(show, ", ");
        strcat(show, sort[index]->name);
        show[0] = toupper(show[0]);
        cout << setiosflags( ios::left )
            << setw(36) << show << setw(12) <<sort[index]->tel <<endl;

    }while(sort[++index] != NULL);

    cout << endl;
    getch();
    return;
}
/*====================Menu1=======================*/
void Menu1()
{
    system("cls");
        cout << "1.  Add new phone"
            <<"\n2.  Search for name"
            <<"\n3.  Search for number"
            <<"\n4.  Sort by name"
            <<"\n5.  Sort by family"
            <<"\n6.  Show all list"
            <<"\n7.  Save data"
            <<"\n9.  Exit"
            <<"\n\nYour choice : ";
}

/*====================Menu2=======================*/
void Menu2()
{
    cout << "\n1.  Find next"
        <<"\n2.  Delete current person"
        <<"\n3.  Edit current person"
        <<"\n4.  continue" << endl
        <<"\nYour choice : ";
}


void Edit_current()
{
    strcpy(current->name,"");
    strcpy(current->family,"");

    cout << "Enter the name : ";
    cin >> current->name;
    cout << "Family : ";
    cin >> current->family;
    cout << "Phone number : ";
    cin >> current->tel;

    system("cls");
}
/*====================End=========================*/
