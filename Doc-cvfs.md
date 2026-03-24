# 📁 Marvellous Custom Virtual File System (CVFS) - C++

## 🚀 Overview
The **Marvellous Custom Virtual File System (CVFS)** is a system-level project implemented using **C-style programming in C++**. It simulates core functionalities of a real file system such as file creation, deletion, reading, writing, and file management using in-memory data structures.

This project is inspired by **UNIX/Linux file system architecture** and demonstrates concepts like **inodes, file descriptors, memory management, and command-line interfaces**.

---

## 🎯 Objectives
- Simulate file system operations  
- Understand inode-based architecture  
- Implement file handling operations  
- Learn system programming concepts  

---

## ✨ Features
- 📄 Create, delete, read, and write files  
- 📂 List files (`ls`)  
- 🔐 Permission-based access (READ / WRITE)  
- 🧠 In-memory file system  
- ⚙️ Command-line interface (CLI)  
- ❗ Error handling using macros  

---

## 🧠 System Architecture

### 🔹 Core Components

#### 1. Boot Block
Stores system boot information.

#### 2. Super Block
Tracks:
- Total inodes  
- Free inodes  

#### 3. Inode
Each file is represented using an inode:
- FileName  
- InodeNumber  
- FileSize  
- ActualFileSize  
- FileType  
- ReferenceCount  
- Permission  
- Buffer (data storage)  

#### 4. File Table
Maintains opened file details:
- ReadOffset  
- WriteOffset  
- Mode  
- Pointer to inode  

#### 5. UAREA (User Area)
- Process name  
- UFDT (User File Descriptor Table)  

---

## 📂 Data Structures Used
- Linked List → Inode management  
- Arrays → File descriptor table  
- Dynamic Memory → `malloc()`, `free()`  

---

## ⚙️ Functional Modules

### 🔹 Initialization Functions
- InitialiseSuperBlock()  
- CreateDILB()  
- InitialiseUAREA()  
- StartAuxillaryDataInitilisation()  

---

## 📄 Detailed Function Documentation

---

### 🔹 CreateFile()

#### Description
Creates a new file in the virtual file system. It validates input, allocates resources, initializes metadata, and assigns a file descriptor.

#### Steps
- Validate parameters  
- Check inode availability  
- Check duplicate file  
- Allocate memory  
- Initialize inode  
- Update system state  

#### Returns
- File Descriptor (Success)  
- Error Codes (Failure)  

---

### 🔹 WriteFile()

#### Description
Writes data into the file buffer associated with the given file descriptor.

#### Steps
- Validate file descriptor  
- Check write permission  
- Check available space  
- Copy data into buffer  
- Update offsets and file size  

---

### 🔹 ReadFile()

#### Description
Reads data from the file buffer into a user-provided buffer.

#### Steps
- Validate inputs  
- Check read permission  
- Ensure sufficient data  
- Copy data from buffer  
- Update read offset  

---

### 🔹 UnlinkFile()

#### Description
Deletes a file from the system and frees allocated resources.

#### Steps
- Validate file existence  
- Free buffer memory  
- Reset inode  
- Update free inode count  

---

### 🔹 IsFileExist()

#### Description
Checks whether a file already exists in the system.

---

### 🔹 LsFile()

#### Description
Displays all files along with inode number and file size.

---

## 🔧 Inbuilt Functions Used

### Memory Management
- malloc()  
- free()  

### String Handling
- strcpy()  
- strcmp()  
- strlen()  
- strncpy()  

### Input/Output
- printf()  
- fgets()  

### System Calls
- system("clear") / system("cls")  

---

## 🔄 Execution Flow

1. Initialize system  
2. Create inode list  
3. Start command-line shell  
4. Accept user input  
5. Parse using `sscanf()`  
6. Execute command  
7. Display result  

---

## 🖥️ Supported Commands

| Command | Description |
|--------|-------------|
| creat filename permission | Create file |
| write fd | Write data |
| read fd size | Read data |
| unlink filename | Delete file |
| ls | List files |
| help | Help menu |
| man command | Manual |
| clear | Clear screen |
| exit | Exit system |

---

## ⚠️ Error Handling

- ERR_INVALID_PARAMETER  
- ERR_NO_INODES  
- ERR_FILE_ALREADY_EXIST  
- ERR_FILE_NOT_EXIST  
- ERR_PERMISSION_DENIED  
- ERR_INSUFFICIENT_SPACE  
- ERR_INSUFFICIENT_DATA  
- ERR_MAX_FILES_OPEN  

---

## 📏 System Limitations
- Max file size: 50 bytes  
- Max open files: 20  
- Max inodes: 5  
- In-memory only  

---

## ▶️ How to Run

```bash
g++ main.cpp -o vfs
./vfs
```

## 🧠 Learning Outcomes
File system internals
Inode-based architecture
Memory management
CLI-based system design
Error handling
🚀 Future Improvements
Disk-based storage
Multi-user system
Directory hierarchy
Advanced permissions

## 👨‍💻 Author

Vivek Bhauraj Gautam

### 💻 GitHub: https://github.com/vivekbgautam
### 🔗 LinkedIn: https://www.linkedin.com/in/vivek-b-gautam/
### 📧 Email: vivekbgautam@gmail.com

## ⭐ Support

If you like this project, give it a ⭐ on GitHub!
