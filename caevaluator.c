#include<stdio.h>
#include <string.h>

struct subject {
    int subjectcode;
    char subjectname[30];
    int subjectmark;
};


struct student {
    int rollno;
    char name[50];
    char section[10];
    struct subject s; 
};

struct student stu; 

void create_record();
void search_record();
void modify_record();
void delete_record();
void display_record();

int main()
{
    int choice;
    while(1){

    
        printf("\nMenu:\n");
        printf("1. Create Student Record\n");
        printf("2. Search Student Record\n");
        printf("3. Modify Student Record\n");
        printf("4. Delete Student Record\n");
        printf("5. Display Student Record\n");
        printf("0. EXIT!!\n\n");

      
        printf("Enter your choice:");
        scanf("%d", &choice);

      
        switch(choice)
        {
            case 1:
                create_record();
                break;
            case 2:
                search_record();
                break;
            case 3:
                modify_record();
                break;
            case 4:
                delete_record();
                break;
            case 5:
                display_record();
                break;
            case 0:
               	printf("\nProgram is closing. Thank you for using the Student Record Management System!\n");
               	break;
            default:
                printf("\nInvalid input. Please try again.\n");
                break;
         }

       
        if(choice==0)
        {
            break;
        }
    }

    return 0;
}


void create_record()
{
   
    FILE *fp;
    fp = fopen("student_records.txt", "ab+");

   
    if (fp == NULL)
    {
        printf("\n\t\tError: Unable to open the specified file. Please check if the file exists and you have sufficient permissions to access it.\n");
        return;
    }

    int num_records;
    printf("\n\n\t\t** Enter new student data **\n\n");
    printf("\n\t\tEnter the number of student records to upload: ");
    scanf("%d", &num_records);
    fflush(stdin);

    for (int i = 0; i < num_records; i++)
    {
        printf("\n\t\tEnter Student Roll Number: ");
        scanf("%d", &stu.rollno);
        fflush(stdin);
        printf("\n\t\tEnter Student Name: ");
        gets(stu.name);
        printf("\n\t\tEnter Student Section: ");
        gets(stu.section);
        printf("\n\t\tEnter Subject Code: ");
        scanf("%d", &stu.s.subjectcode);
        printf("\n\t\tEnter subject Name: ");
        scanf("%s", &stu.s.subjectname);
        printf("\n\t\tEnter Subject Mark: ");
        scanf("%d", &stu.s.subjectmark);

        
        fwrite(&stu, sizeof(stu), 1, fp);

        printf("\n\t\t--- Student Record %d Inserted Successfully ---\n", i + 1);
    }

    
    fclose(fp);

   
    printf("\n\t\tUpdated Record \n");
    display_record();
}

void search_record()
{
    int ro, flag = 0;
    char choice;
    FILE *fp;
    fp = fopen("student_records.txt", "rb");
    if (fp == NULL)
    {
        printf("\n\t\tError: Unable to open the specified file. Please check if the file exists and you have sufficient permissions to access it.\n"); // Print error message if file cannot be opened
        return;
    }
    printf("\n\n\tPlease choose the search category:\n");
    printf("\t\t1. Roll number\n");
    printf("\t\t2. Name\n");
    printf("\t\t3. Subject code\n");
    printf("\tYour choice: ");
    scanf(" %c", &choice);
    switch (choice)
    {
    case '1':
        printf("\n\n\tPlease enter the roll number of the student you would like to search for: ");
        scanf("%d", &ro);
        while (fread(&stu, sizeof(stu), 1, fp) > 0 && flag == 0) 
        {
            if (stu.rollno == ro) 
            {
                flag = 1; 
                printf("\n\n\tSearch Successfully And Student Records is as follows:\n\n");
                printf("\nRoll.No\t\tName of Student\t\tSection\t\tSubject Code\t\tSubject Name\t\tMark\n\n");
                printf("%-15d %-10s\t\t%s\t\t%-10d\t\t%-10s\t\t%d\n", stu.rollno, stu.name, stu.section, stu.s.subjectcode, stu.s.subjectname, stu.s.subjectmark); // Display record
            }
        }
        if (flag == 0)
        {
            printf("\n\n\tNo Search Record Found\n"); 
        }
        break;
    case '2':
        printf("\n\n\tPlease enter the name of the student you would like to search for: ");
        char name[50];
        scanf("%s", name);
        while (fread(&stu, sizeof(stu), 1, fp) > 0 && flag == 0) 
        {
            if (strcmp(stu.name, name) == 0)
            {
                flag = 1; 
                printf("\n\n\tSearch Successfully And Student Records is as follows:\n\n");
                printf("\nRoll.No\t\tName of Student\t\tSection\t\tSubject Code\t\tSubject Name\t\tMark\n\n");
                printf("%-15d %-10s\t\t%s\t\t%-10d\t\t%-10s\t\t%d\n", stu.rollno, stu.name, stu.section, stu.s.subjectcode, stu.s.subjectname, stu.s.subjectmark); // Display record
            }
        }
        if (flag == 0)
        {
            printf("\n\n\tNo Search Record Found\n"); 
        }
        break;
    case '3':
        printf("\n\n\tPlease enter the subject code of the student you would like to search for: ");
        int subjectcode;
        scanf("%d", &subjectcode);
        while (fread(&stu, sizeof(stu), 1, fp) > 0 && flag == 0) 
            {
        if (stu.s.subjectcode == subjectcode) 
        {
            flag = 1; 
            printf("\n\n\tSearch Successfully And Student Records is as follows:\n\n");
            printf("\nRoll.No\t\tName of Student\t\tSection\t\tSubject Code\t\tSubject Name\t\tMark\n\n");
            printf("%-15d %-10s\t\t%s\t\t%-10d\t\t%-10s\t\t%d\n", stu.rollno, stu.name, stu.section, stu.s.subjectcode, stu.s.subjectname, stu.s.subjectmark); // Display record
        }
    }
    if (flag == 0)
    {
        printf("\n\n\tNo Search Record Found\n");
    }
    break;
default:
    printf("\n\n\tInvalid choice\n"); 
    break;
}
fclose(fp); 
}

void modify_record()
{
    int ro, flag = 0, choice;
    FILE *fp;
    fp = fopen("student_records.txt", "rb+"); 
    if (fp == NULL)
    {
        printf("\n\t\tError: Unable to open the specified file. Please check if the file exists and you have sufficient permissions to access it.\n"); // Print error message if file cannot be opened
        return;
    }
    printf("\n\n\tPlease enter the roll number of the student whose record you want to update: ");
    scanf("%d", &ro); 
    printf("\n\t\t-----Previously stored record for the given roll number-----");

    while (fread(&stu, sizeof(stu), 1, fp) > 0) 
    {
        if (stu.rollno == ro) 
        {
            flag = 1; // Set flag to indicate record found

            printf("\nRoll.No\t\tName of Student\t\tSection\t\tSubject Code\t\tSubject Name\t\tMark\n\n");
            printf("%-15d %-10s\t\t%s\t\t%-10d\t\t%-10s\t\t%d\n", stu.rollno, stu.name, stu.section, stu.s.subjectcode, stu.s.subjectname, stu.s.subjectmark);
            printf("\n\t\t-----Now Enter The New Record-----\n\n");

            printf("\n\t\tWhich field do you want to update?");
            printf("\n\t\t1. Student Roll Number");
            printf("\n\t\t2. Student Name");
            printf("\n\t\t3. Student Section");
            printf("\n\t\t4. Subject Code");
            printf("\n\t\t5. Subject Name");
            printf("\n\t\t6. Subject Mark\n");
            printf("\n\t\tEnter your choice (1-6): ");
            scanf("%d", &choice); 

            switch(choice) {
                case 1:
                    printf("\n\t\tPlease enter the updated student roll number: ");
                    scanf("%d", &stu.rollno); 
                    break;
                case 2:
                    fflush(stdin); 
                    printf("\n\t\tPlease enter the updated student name: ");
                    gets(stu.name); 
                    break;
                case 3:
                    fflush(stdin); 
                    printf("\n\t\tPlease enter the updated student section: ");
                    gets(stu.section); 
                    break;
                case 4:
                    printf("\n\t\tPlease enter the updated subject code: ");
                    scanf("%d", &stu.s.subjectcode); 
                    break;
                case 5:
                    printf("\n\t\tPlease enter the updated subject name: ");
                    scanf("%s", stu.s.subjectname); 
                    break;
                case 6:
                    printf("\n\t\tPlease enter the updated subject mark: ");
                    scanf("%d", &stu.s.subjectmark); 
                    break;
                default:
                    printf("\n\t\tInvalid choice. Please try again.\n");
                    break;
            }

            fseek(fp, -(long)sizeof(stu), SEEK_CUR);
            fwrite(&stu, sizeof(stu), 1, fp); 
        printf("\n\t\tRecord updated successfully!\n");
        break;
    }
}
if (flag == 0) 
{
    printf("\n\t\tError: Record not found. Please check if the roll number entered is correct.\n");
}
fclose(fp);
}

void delete_record()
{
    char name[40]; 
    unsigned flag=0; 
    int choice; 
    FILE *fp,*ft; 
    fp=fopen("student_records.txt","rb"); 

    if(fp==NULL) 
    {
        printf("\n\t\tError: Unable to open the specified file. Please check if the file exists and you have sufficient permissions to access it.\n");
        return; 
    }
    printf("\n\t -----Previous Stored Data -----");
    display_record(); 
    printf("\n\n\t1. Delete a single record");
    printf("\n\t2. Delete multiple records");
    printf("\n\tEnter your choice (1 or 2): ");
    scanf("%d",&choice); 

    if(choice==1) 
    {
        printf("\n\tEnter the name of the student you want to delete: ");
        scanf("%s",name); 
        ft=fopen("student_records1.txt","ab+"); 

        while(fread(&stu,sizeof(stu),1,fp)==1) 
        {
            if(strcmp(name,stu.name)!=0) 
            {
                fwrite(&stu,sizeof(stu),1,ft); 
            }
            else
            {
                flag=1;
                printf("\n\t\tRecord has been deleted successfully.\n");
            }
        }

        if(flag==0) 
        {
            printf("\n\n\t\tNo Such Record Found\n");
        }
        fclose(fp);
        fclose(ft); 
        remove("student_records.txt"); 
        rename("student_records1.txt","student_records.txt"); 
    }
    else if(choice==2)
    {
        int count=0; 
        printf("\n\tEnter the names of the students you want to delete one by one (type \"end\" to stop): \n");
        ft=fopen("student_records1.txt","ab+"); 

        while(1)
        {
            printf("\n\tName: ");
            scanf("%s",name);

            if(strcmp(name,"end")==0) 
            {
                break;
            }

            flag=0; 
            rewind(fp);

            while(fread(&stu,sizeof(stu),1,fp)==1) 
                {
                    if(strcmp(name,stu.name)==0) 
                    {
                        flag=1; 
                        count++; e
                        printf("\n\t\tRecord has been deleted successfully.\n");
                        break; 
                    }
                }
                if(flag==0)
                    {
                        printf("\n\n\t\tNo Such Record Found\n");
                    }
        }
        fclose(fp); 
        rewind(fp); 
        while(fread(&stu,sizeof(stu),1,fp)==1)  
            {
                flag=0;
                for(int i=0;i<count;i++) 
                    {
                        if(strcmp(name,stu.name)==0) 
                        {
                            flag=1; 
                            break; 
                        }
                    }
        if(flag==0) 
            {
                fwrite(&stu,sizeof(stu),1,ft);
            }
            }

            fclose(fp);
            fclose(ft);
            remove("student_records.txt");
            rename("student_records1.txt","student_records.txt");
            printf("\n\t\t%d records have been deleted successfully.\n",count);
    }
   else 
    {
        printf("\n\tInvalid Choice. Please Try Again.\n");
    }
}


void display_record()
{
    FILE *fp; 
    fp = fopen("student_records.txt", "rb"); 

    
    if (fp == NULL)
    {
        printf("\n\t\tError: Unable to open the specified file. Please check if the file exists and you have sufficient permissions to access it.\n");
        return;
    }

    
    printf("\n\n\t+-----------------+----------------------+---------+--------------+----------------------+------+\n");
    printf("\t|    Roll.No      |   Name of Student    | Section | Subject Code |     Subject Name     | Mark |\n");
    printf("\t+-----------------+----------------------+---------+--------------+----------------------+------+\n");

    while (fread(&stu, sizeof(stu), 1, fp) == 1)
    {
        printf("\t| %-15d | %-20s | %-7s | %-12d | %-20s | %-4d |\n", stu.rollno, stu.name, stu.section, stu.s.subjectcode, stu.s.subjectname, stu.s.subjectmark);
    }

    
    printf("\t+-----------------+----------------------+---------+--------------+----------------------+------+\n");

    fclose(fp);
}

