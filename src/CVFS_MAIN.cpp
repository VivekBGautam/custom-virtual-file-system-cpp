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

#define REGULARFILE 1
#define SPECIALFILE 2

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  User Defined Macros for error handling
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

#define ERR_INVALID_PARAMETER -1

#define ERR_NO_INODES -2

#define ERR_FILE_ALREADY_EXIST -3
#define ERR_FILE_NOT_EXIST -4

#define ERR_PERMISSION_DENIED -5

#define ERR_INSUFFICIENT_SPACE -6
#define ERR_INSUFFICIENT_DATA -7

#define ERR_MAX_FILES_OPEN -8

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  User Defined Structures
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
    int FileType;
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
        newn->FileType = 0;
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
    else if(strcmp("clear",Name) == 0)
    {
        printf("About : It is used to clear the shell\n");
        printf("Usage : clear\n");        
    }
    else
    {
        printf("No manual entry for %s\n",Name);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name :     IsFileExist
//  Description   :     It is used to check weather file is already axist
//  Input         :     It accept file name
//  Output        :     It return the boolean
//  Author        :     Vivek Bhauraj Gautam
//  Date          :     16/01/2026
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

bool IsFileExist(
                    char * name     // file name
                )
{
    PINODE temp = head;
    bool bFlag = false;

    while(temp != NULL)
    {
        if((strcmp(name,temp->FileName) == 0) && (temp->FileType == REGULARFILE))
        {
            bFlag = true;
            break;
        }
        temp = temp->next;
    }

    return bFlag;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name :     CreateFile
//  Description   :     It is used to create new regular file
//  Input         :     It accept file name and permission
//  Output        :     It return the file descriptor
//  Author        :     Vivek Bhauraj Gautam
//  Date          :     16/01/2026
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

int CreateFile(
                    char *name,             // Name of new file 
                    int permission          // permission for that file 
              )
{
    PINODE temp = head;
    int i = 0;

    printf("Total number of Inode remaining : %d\n",superobj.FreeInodes);

    //  if name is missiong
    if(name == NULL)
    {
        return ERR_INVALID_PARAMETER;
    }

    // if the permission value is wrong 
    // permision -> 1 -> READ
    // permision -> 2 -> WRITE
    // permision -> 3 -> READ + WRITE
    if(permission < 1 || permission > 3)
    {
        return ERR_INVALID_PARAMETER;
    }

    // if the inodes are full
    if(superobj.FreeInodes == 0)
    {
        return ERR_NO_INODES;
    }

    // if file is already present
    if(IsFileExist(name) == true)
    {
        return ERR_FILE_ALREADY_EXIST;
    }

    // Search empty inode 
    while(temp != NULL)
    {
        if(temp->FileType == 0)
        {
            break;
        }
        temp = temp->next;
    }

    if(temp == NULL)
    {
        printf("There is no inode \n");
        return ERR_NO_INODES;
    }

    // search for  empty UFDT  enrty
    // Note : 0,1,2 are reverved
    for(i = 3; i < MAXOPENFILES; i++)
    {
        if(uareobj.UFDT[i] == NULL)
        {
            break;
        }
    }

    // UFDT is full 
    if(i == MAXOPENFILES)
    {
        return ERR_MAX_FILES_OPEN;
    }

    // Allocate memory for file table 
    uareobj.UFDT[i] = (PFILETABLE)malloc(sizeof(FILETABLE));


    // Initialise file table 
    uareobj.UFDT[i]->ReadOffset = 0;
    uareobj.UFDT[i]->WriteOffset = 0;
    uareobj.UFDT[i]->Mode = permission;

    // Connect file table with inode
    
    uareobj.UFDT[i]->ptrinode = temp;

    // Initialise elements of inode 
    strcpy(uareobj.UFDT[i]->ptrinode->FileName,name);
    uareobj.UFDT[i]->ptrinode->FileSize = MAXFILESIZE;
    uareobj.UFDT[i]->ptrinode->ActualFilesize = 0;
    uareobj.UFDT[i]->ptrinode->FileType = REGULARFILE;
    uareobj.UFDT[i]->ptrinode->RefrenceCount = 1;
    uareobj.UFDT[i]->ptrinode->Permission = permission;

    // Allocate ememory for file data
    uareobj.UFDT[i]->ptrinode->Buffer = (char *)malloc(MAXFILESIZE);
    
    superobj.FreeInodes--;

    return i;      // file descriptor


}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name :     LsFile()
//  Description   :     It is used to list all files
//  Input         :     Nothing
//  Output        :     Nothing
//  Author        :     Vivek Bhauraj Gautam
//  Date          :     16/01/2026
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

// ls -l
void LsFile()
{
    PINODE temp = head;

    printf("-----------------------------------------------\n");
    printf("----- Marvellous CVFS Files Informations ------\n");
    printf("-----------------------------------------------\n");
    printf("InodeNumber\tFileName\tActualFilesize\n");
    printf("-----------------------------------------------\n");

    while(temp != NULL)
    {
        if(temp->FileType != 0)
        {
            printf("%d\t\t%s\t\t%d\n",temp->InodeNumber,temp->FileName,temp->ActualFilesize);
        }

        temp = temp->next;
    }

    printf("-----------------------------------------------\n");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name :     UnlinkFile()
//  Description   :     It is used to Delete The file
//  Input         :     It accept file name
//  Output        :     Delete the file 
//  Author        :     Vivek Bhauraj Gautam
//  Date          :     22/01/2026
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
int UnlinkFile(
                    char * name
                )
{
    int i = 0;

    if(name == NULL)
    {
        return ERR_INVALID_PARAMETER;
    }

    if(IsFileExist(name) == false)
    {
        return ERR_FILE_NOT_EXIST;
    }

    // Travel the UFDT
    for(i = 0; i < MAXOPENFILES; i++)
    {
        if(uareobj.UFDT[i] != NULL)
        {
            if(strcmp(uareobj.UFDT[i]->ptrinode->FileName,name) == 0)
            {
                // Deallocate memory of Buffer 
                free(uareobj.UFDT[i]->ptrinode->Buffer);
                uareobj.UFDT[i]->ptrinode->Buffer = NULL;

                // Reset all value of inode
                // Dont deallocate memory of inode
                uareobj.UFDT[i]->ptrinode->FileSize = 0;
                uareobj.UFDT[i]->ptrinode->ActualFilesize = 0;
                uareobj.UFDT[i]->ptrinode->FileType = 0;
                uareobj.UFDT[i]->ptrinode->RefrenceCount = 0;
                uareobj.UFDT[i]->ptrinode->Permission = 0;
                
                memset(uareobj.UFDT[i]->ptrinode->FileName,'\0',sizeof(uareobj.UFDT[i]->ptrinode->FileName));

                // Deallocate memory of file table 
                free(uareobj.UFDT[i]);

                // Set NULL to UFDT
                uareobj.UFDT[i] = NULL;

                // Increment free inodes count
                superobj.FreeInodes++;

                break;       // IMP to stop loop 
            } // End of if
        } // End of isf
    } // End of for

    return EXECUTE_SUCCESS;
}               // End of Function

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name :     WriteFile()
//  Description   :     It is used to Write The Data into file
//  Input         :     File Descriptor 
//                      Address of BUffer which conatin data
//                      Size of data that we want to write
//  Output        :     Number of bites succesfully written 
//  Author        :     Vivek Bhauraj Gautam
//  Date          :     22/01/2026
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
int WriteFile(
                    int fd,           // file descriptor
                    char *data,
                    int size
            )
{
    printf("File Descriptor : %d\n",fd);
    printf("Data that we want to write : %s\n",data);
    printf("Number of bytes that we want to write : %d\n",size);

    // Invalid fd 
    if(fd < 0 || fd > MAXOPENFILES)
    {
        return ERR_INVALID_PARAMETER;
    }

    // Fd points to Null 
    if(uareobj.UFDT[fd] == NULL)
    {
        return ERR_FILE_NOT_EXIST;
    }

    // Thre is No permision to write
    if(uareobj.UFDT[fd]->ptrinode->Permission < WRITE)
    {
        return ERR_PERMISSION_DENIED;
    }

    // Insufficient Space 
    if((MAXFILESIZE - uareobj.UFDT[fd]->WriteOffset) < size)
    {
        return ERR_INSUFFICIENT_SPACE;
    }

    // Write the data into the file 
    strncpy(uareobj.UFDT[fd]->ptrinode->Buffer + uareobj.UFDT[fd]->WriteOffset,data,size);

    // Update the write offset
    uareobj.UFDT[fd]->WriteOffset = uareobj.UFDT[fd]->WriteOffset + size;

    // Update the actual file size 
    uareobj.UFDT[fd]->ptrinode->ActualFilesize = uareobj.UFDT[fd]->ptrinode->ActualFilesize + size;

    return size;
} // End of Write function

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name :     ReadFile()
//  Description   :     It is used to Read The Data into file
//  Input         :     File Descriptor 
//                      Address of Empty BUffer which conatin data
//                      Size of data that we want to Read
//  Output        :     Number of bites succesfully Read 
//  Author        :     Vivek Bhauraj Gautam
//  Date          :     22/01/2026
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
int ReadFile(
                int fd,
                char *data,
                int size
            )
{
    // Invalid Fd 
    if(fd < 0 || fd > MAXOPENFILES)
    {
        return ERR_INVALID_PARAMETER;
    }

    //
    if(data == NULL)
    {
        return ERR_INVALID_PARAMETER;
    }

    //
    if(size <= 0)
    {
        return ERR_INVALID_PARAMETER;
    }

    if(uareobj.UFDT[fd] == NULL)
    {
        return ERR_FILE_NOT_EXIST;
    }

    // filter for permission
    if(uareobj.UFDT[fd]->ptrinode->Permission < READ)
    {
        return ERR_PERMISSION_DENIED;
    }

    // Insuficent data
    if((MAXFILESIZE - uareobj.UFDT[fd]->ReadOffset) < size)
    {
        return ERR_INSUFFICIENT_DATA;
    }

    // Read the data
    strncpy(data,uareobj.UFDT[fd]->ptrinode->Buffer + uareobj.UFDT[fd]->ReadOffset,size);

    // Update the read offset
    uareobj.UFDT[fd]->ReadOffset = uareobj.UFDT[fd]->ReadOffset + size;

    return size;
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
    char InputBuffer[MAXFILESIZE] = {'\0'};

    char *EmptyBuffer = NULL;
    int iCount = 0;
    int iRet = 0;

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
            // Marvellous CVFS : > exit
            if(strcmp("exit",Command[0]) == 0)
            {
                printf("Thank you for using Marvellous CVFS\n");
                printf("Deallocating all the allocated resources\n");

                break;
            }
            // Marvellous CVFS : > ls
            else if(strcmp("ls",Command[0]) == 0)
            {
                LsFile();
            }
            // Marvellous CVFS : > help
            else if(strcmp("help",Command[0]) == 0)
            {
                DisplayHelp();
            }
            // Marvellous CVFS : > clear
            else if(strcmp("clear",Command[0]) == 0)
            {
                #ifdef _WIN32
                    system("cls");
                #else
                    system("clear");
                #endif
            }
        } // End of else if 1
        else if(iCount == 2)
        {
            // Marvellous CVFS : > man ls
            if(strcmp("man",Command[0]) == 0)
            {
                ManPageDisplay(Command[1]);
            }
            // Marvellous CVFS : > munlink Demo.txt
            if(strcmp("unlink",Command[0]) == 0)
            {
                iRet = UnlinkFile(Command[1]);

                if(iRet == ERR_INVALID_PARAMETER)
                {
                    printf("ERROR : Invalid Parameter\n");
                }

                if(iRet == ERR_FILE_NOT_EXIST)
                {
                    printf("ERROR : Unable to delete as there is no such file\n");
                }

                if(iRet == EXECUTE_SUCCESS)
                {
                    printf("File gets succesfully deleted\n");
                }
            }
            // Marvellous CVFS : > write 2
            else if(strcmp("write",Command[0]) == 0)
            {
                printf("Enter the data that you wnat to write :\n");
                fgets(InputBuffer,MAXFILESIZE,stdin);

                iRet = WriteFile(atoi(Command[1]),InputBuffer,strlen(InputBuffer - 1));

                if(iRet == ERR_INVALID_PARAMETER)
                {
                    printf("ERROR : Invalid Parameters\n");
                }
                else if(iRet == ERR_FILE_NOT_EXIST)
                {
                    printf("ERROR : Thare is no such file \n");
                }
                else if(iRet == ERR_PERMISSION_DENIED)
                {
                    printf("ERROR : Unable to write as there is no such permission\n");
                }
                else if(iRet == ERR_INSUFFICIENT_SPACE)
                {
                    printf("ERROR : Unable to write as there is no space \n");
                }
                else
                {
                    printf("%d Bytes gets succesfully written\n",iRet);
                }
            }
            else
            {
                printf("There is no such command \n");
            }

        } // End of else if 2
        else if(iCount == 3)
        {
            // Marvellous CVFS : > creat ganesh.txt 3
            if(strcmp("creat",Command[0]) == 0)
            {
                iRet = CreateFile(Command[1],atoi(Command[2]));

                if(iRet == ERR_INVALID_PARAMETER)
                {
                    printf("ERROE : Unable to create the file as paramerter are invalid \n");
                    printf("please reffer man page \n");
                }

                if(iRet == ERR_NO_INODES)
                {
                    printf("ERROE : Unbale to create file as there is no inode \n");
                }

                if(iRet == ERR_FILE_ALREADY_EXIST)
                {
                    printf("ERROE : Unbale to create file becouse the file is already present \n");
                }
                
                if(iRet == ERR_MAX_FILES_OPEN)
                {
                    printf("ERROR : Unable to create file \n");
                    printf("Max open file limit is reached\n");
                }

                printf("File gets succesfully created with fd : %d\n",iRet);
            }
            // Marvellous CVFS : > read 3 10 
            else if (strcmp("read",Command[0]) == 0)
            {
                EmptyBuffer = (char *)malloc(sizeof(atoi(Command[2])));

                iRet = ReadFile(atoi(Command[1]),EmptyBuffer,atoi(Command[2]));

                if(iRet == ERR_INVALID_PARAMETER)
                {
                    printf("ERROR : Invalid parameret\n");
                }
                else if(iRet == ERR_FILE_NOT_EXIST)
                {
                    printf("ERROR : Unable to read as file not exist\n");
                }
                else if(iRet == ERR_PERMISSION_DENIED)
                {
                    printf("ERROR : Unable to read as there is no such permission Dennied\n");
                }
                else if(iRet == ERR_INSUFFICIENT_DATA)
                {
                    printf("ERROR : Insufficent Data\n");
                }
                else 
                {
                    printf("Read Operation is succesfully \n");
                    printf("Data from file is : %s\n",EmptyBuffer);

                    free(EmptyBuffer);
                }
            }
            else
            {
                printf("There is no such command \n");
            }

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