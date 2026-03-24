/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Header File Inclusion
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdbool.h>
#include<string.h>

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  User Defined Macros
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

// Maximum file size that we allow in the project
#define MAXFILESIZE 50

// Maximum file that we are open at a time 
#define MAXOPENFILES 20

// Maximum inode 
#define MAXINODE 5

// FILE READ RWITE PERMISSION
#define READ 1
#define WRITE 2
#define EXECUTE 4

//
#define START 0
#define CURRENT 1
#define END 2

//
#define EXECUTE_SUCCESS 0

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  User defined Structures
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Structure Name :    BootBlock
//  Description    :    Holds the information to boot the OS
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
struct BootBlock
{
    char Information[100];
};

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Structure Name      :    SuperBlock
//  Description         :    Holds the information about the file System
//  Structure Member    :    int TotalInodes;
//                           int FreeInodes; 
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
struct SuperBlock
{
    int TotalInodes;
    int FreeInodes;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Structure Name      :    Inode
//  Description         :    Holds the information about the File
//  Structure Member    :    char FileName[20];
//                           int iNodeNumber;
//                           int FileSize;
//                           int ActualFilesize;
//                           struct Inode *next;
//                           int RefrenceCount;
//                           int RPermission;
//                           char *Buffer;
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma pack(1)
struct Inode
{
    char FileName[20];
    int InodeNumber;
    int FileSize;
    int ActualFilesize;
    int RefrenceCount;
    int Permission;
    char *Buffer;                  // Data block
    struct Inode *next;
};

typedef struct Inode INODE; 
typedef struct Inode * PINODE; 
typedef struct Inode ** PPINODE; 


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Structure Name      :    FileTable
//  Description         :    Holds the information about the opend file
//  Structure Member    :    int ReadOffset;
//                           int WriteOffset;
//                           int Mode;
//                           PINODE ptrinode;
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
struct FileTable
{
    int ReadOffset;
    int WriteOffset;
    int Mode;
    PINODE ptrinode;
};

typedef FileTable FILETABLE;
typedef FileTable * PFILETABLE;

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Structure Name      :    UAREA
//  Description         :    Holds the information about the process file
//  Structure Member    :    char ProcessName[20];
//                           PFILETABLE UFDT[MAXOPENFILES]; 
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
struct UAREA
{
    char ProcessName[20];
    PFILETABLE UFDT[MAXOPENFILES]; 
};

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Globle variable or objects used in the project
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

BootBlock bootobj;
SuperBlock superobj;
UAREA uareobj;

PINODE head = NULL;

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name   :   InitialiseUAREA
//  Description     :   it is Used to Initialise UAREA members
//  Author          :   Vivek Bhauraj Gautam
//  Date            :   13/01/2026
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
void InitialiseUAREA()
{
    strcpy(uareobj.ProcessName,"Myexe");
    
    int i = 0;
    
    for(i = 0; i < MAXOPENFILES; i++)
    {
        uareobj.UFDT[i] = NULL;
    }

    printf("Marvellous CVFS : UAREA get initialized succesfullay\n");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name   :   InitialiseSuperBlock
//  Description     :   it is Used to Initialise Super members
//  Author          :   Vivek Bhauraj Gautam
//  Date            :   13/01/2026
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
void InitialiseSuperBlock()
{
    superobj.TotalInodes = MAXINODE;
    superobj.FreeInodes = MAXINODE;

    printf("Marvellous CVFS : Super blocks get initialize succesfullay\n");

}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name   :   CreateDILB
//  Description     :   it is Used to create LinkedList of inodes
//  Author          :   Vivek Bhauraj Gautam
//  Date            :   13/01/2026
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
void CreateDILB()
{
    int i = 1;
    PINODE newn = NULL;
    PINODE temp = head;

    for(i = 1; i <= MAXINODE; i++)
    {
        newn = (PINODE)malloc(sizeof(INODE));

        strcpy(newn->FileName, "\0");
        newn-> InodeNumber = i;
        newn-> FileSize = 0;
        newn-> ActualFilesize = 0;
        newn-> RefrenceCount = 0;
        newn-> Permission = 0;
        newn-> Buffer  = NULL;            // Data block
        newn-> next = NULL;

        if(temp == NULL)           // LL is empty
        {
            head = newn;
            temp = head;
        }
        else                        // LL contain at least one
        {
            temp->next = newn;
            temp = temp->next;
        }
    }

    printf("Marvellous CVFS : DILB created succesfully\n");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name   :   StartAuxillaryDataInitialisation
//  Description     :   it is Used to call such function which are 
//                      used to inicialise auxilary data
//  Author          :   Vivek Bhauraj Gautam
//  Date            :   13/01/2026
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
void StartAuxillaryDataInitilisation()
{
    strcpy(bootobj.Information,"Booting process of Marvellous CVFS is done");
    printf("%s\n",bootobj.Information);

    InitialiseSuperBlock();
    CreateDILB();
    InitialiseUAREA();

    printf("Marvellous CVFS : Auxilary Data initialised succesfullay\n");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name :     DisplayHelp
//  Description :       It is used to display the help page
//  Author :            Vivek Bhauraj Gautam
//  Date :              14/01/2026
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

void DisplayHelp()
{
    printf("-----------------------------------------------\n");
    printf("---------- Marvellous CVFS Help Page ----------\n");
    printf("-----------------------------------------------\n");

    printf("man    : It is used to display manual page\n");
    printf("clear  : It is used to clear the terminal\n");
    printf("creat  : It is used to create new file\n");
    printf("write  : It is used to write the data into file\n");
    printf("read   : It is used to read the data from the file\n");
    printf("stat   : It is used to display statistical information\n");
    printf("unlink : It is used to delete the file\n");
    printf("exit   : It is used to terminate Marvellous CVFS\n");

    printf("-----------------------------------------------\n");

}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name :     ManPageDisplay
//  Description :       It is used to display man page
//  Author :            Vivek Bhauraj Gautam
//  Date :              14/01/2026
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

void ManPageDisplay(char Name[])
{
    if(strcmp("ls",Name) == 0)
    {
        printf("About : It is used to list the names of all files\n");
        printf("Usage : ls\n");
    }
    else if(strcmp("man",Name) == 0)
    {
        printf("About : It is used to display manual page\n");
        printf("Usage : man command_name\n");
        printf("command_name : It is the name of command\n");        
    }
    else if(strcmp("exit",Name) == 0)
    {
        printf("About : It is used to terminate the shell\n");
        printf("Usage : exit\n");        
    }
    else
    {
        printf("No manual entry for %s\n",Name);
    }
}


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name : Main -> Entry Point function of the project
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    char str[80] = {'\0'};
    char Command[5][20] = {{'\0'}};
    int iCount = 0;

    StartAuxillaryDataInitilisation();

    printf("-----------------------------------------------\n");
    printf("----- Marvellous CVFS started succesfully -----\n");
    printf("-----------------------------------------------\n");
    
    // Infinite Listening Shell
    while(1)
    {
        fflush(stdin);

        strcpy(str,"");

        printf("\nMarvellous CVFS : > ");
        fgets(str,sizeof(str),stdin);
        
        iCount = sscanf(str,"%s %s %s %s %s",Command[0],Command[1],Command[2],Command[3], Command[4]);

        fflush(stdin);

        if(iCount == 1)
        {
            if(strcmp("exit",Command[0]) == 0)
            {
                printf("Thank you for using Marvellous CVFS\n");
                printf("Deallocating all the allocated resources\n");

                break;
            }
            else if(strcmp("ls",Command[0]) == 0)
            {
                printf("Inside ls\n");
            }
            else if(strcmp("help",Command[0]) == 0)
            {
                DisplayHelp();
            }
        } // End of else if 1
        else if(iCount == 2)
        {
            if(strcmp("man",Command[0]) == 0)
            {
                ManPageDisplay(Command[1]);
            }
        } // End of else if 2
        else if(iCount == 3)
        {

        } // End of else if 3
        else if(iCount == 4)
        {

        } // End of else if 4
        else
        {
            printf("Command not found\n");
            printf("Please refer help option to get more information\n");
        } // End of else
    } // End of while

    return 0;
} // End of main