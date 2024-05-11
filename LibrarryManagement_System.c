#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

struct Books
{
    int id;
    char bookName[30];
    char authorName[30];
    char date[12];
}b;

struct student
{
    int id;
    char sName[30];
    char sClass[30];
    int sRoll;
    char bookName[30];
    char date[12];
}s;

FILE *fp;

void addBook()
{
    char myDate[12];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(myDate, "%02d-%02d-%d",  tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    strcpy(b.date, myDate);

    fp = fopen("books.txt", "ab");

    printf("Enter book id: ");
    scanf("%d", &b.id);

    printf("Enter book name: ");
    fflush(stdin);  // if input function buffer then gets function will skip the function and will move to author name
    gets(b.bookName);

    printf("Enter author name: ");
    fflush(stdin);
    gets(b.authorName);

    printf("\nBook added Successfully\n");

    fwrite(&b, sizeof(b), 1, fp);
    fclose(fp);
    
}

void viewBookList()
{
    system("cls");
    printf("------ Available Books ------\n\n");
    printf("%-10s %-30s %-20s %s \n\n", "Book-id", "Book-Name", "Author", "Date");

    fp = fopen("books.txt", "rb");
    while (fread(&b, sizeof(b), 1, fp) == 1)
    {
        printf("%-10d %-30s %-20s %s \n", b.id, b.bookName, b.authorName, b.date);
    }

    fclose(fp);
}

void removeBook()
{
    int id, f = 0;
    system("cls");

    printf("******* REMOVE BOOK !! *******\n");
    printf("Enter id to remove the Book: ");
    scanf("%d", &id);

    FILE *ft;

    fp = fopen("books.txt", "rb");
    ft = fopen("tmp.txt", "wb");

    while (fread(&b, sizeof(b), 1, fp) == 1)
    {
        if (id == b.id)
        {
            f = 1;
        }

        else
        {
            fwrite(&b, sizeof(b), 1, ft);
        }
        
    }

    if (f == 1)
    {
        printf("\nBook Deleted Successfully !!");
    }

    else
    {
        printf("\nNo Book FOUND !!");
    }

    fclose(fp);
    fclose(ft);

    remove("books.txt");
    rename("tmp.txt", "books.txt");
    
}

void issueBook()
{
    char myDate[12];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(myDate, "%02d-%02d-%d",  tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    strcpy(s.date, myDate);

    int f = 0;

    system("cls");

    printf("-------Issue Book !! -------\n\n");
    printf("Enter Book id to issue: ");
    scanf("%d", &s.id);

    // checking
    fp = fopen("books.txt", "rb");

    while (fread(&b, sizeof(b), 1, fp) == 1)
    {
        if (b.id == s.id)
        {
            strcpy(s.bookName, b.bookName);
            f = 1;
            break;
        }
        
    }

    if (f == 0)
    {
        printf("No Book found with the given id\n");
        printf("Please try again...\n\n");
        return;
    }

    fp = fopen("issue.txt", "ab");    
    printf("Enter Student Name: ");
    fflush(stdin);
    gets(s.sName);

    printf("Enter Student Class: ");
    fflush(stdin);
    gets(s.sClass);

    printf("Enter Student Roll: ");
    scanf("%d", &s.sRoll);

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);

}

void viewIssueBookList()
{
    system("cls");
    printf("<------ Issue Book List ------>\n\n");
    printf("%-10s %-30s %-20s %-10s %-30s %s \n\n", "Book id", "Name", "Class", "Roll", "Book Name", "Date");

    fp = fopen("issue.txt", "rb");
    while (fread(&s, sizeof(s), 1, fp) == 1)
    {
        printf("%-10d %-30s %-20s %-10d %-30s %s \n\n", s.id, s.sName, s.sClass, s.sRoll, s.bookName, s.date);
    }

    fclose(fp);
}

int main()
{
    int choice;

    while (1)
    {
        system("cls");

        printf("\n================================\n");
        printf("Welcome To CGU's Central Library\n");
        printf("================================\n");

        printf("1. Add Book\n");
        printf("2. View Book List\n");
        printf("3. Remove Book\n");
        printf("4. Issue Book\n");
        printf("5. View Issued Book in List\n");
        printf("0. Exit\n\n");

        printf("Enter your Choice : ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 0:
            printf("\n\n%35s Thanks for Using Our Librarry Management System :)\n\n");
            printf("We would like to express my special thanks of gratitude to Dr. Mamata wagh as well as our DEAN Priyadarshi Kanungo sir who gave me an opportunity to work on this project. It helped us a lot to learn about research and we came to know about a lot of new things. we are really thankful to all of them Secondly, we would also thanks our parents and friends who helped us in finalizing this project within the limited time frame.\n\nThis project has been a source to learn and bring our theoretical knowledge to the real-life world. So, we would really acknowledge his help and guidance for this project. Once again, thank you everyone who are involved in making this project a success.\n");
            getch();
            exit(0);
            break;

        case 1:
            addBook();
            break;

        case 2:
            viewBookList();
            break;

        case 3:
            removeBook();
            break;

        case 4:
            issueBook();
            break;

        case 5:
            viewIssueBookList();
            break;
        
        default:
            printf("\n\nInvalid Choice...");
        }

        printf("\nPress Any Key to continue....");
        getch();

    }
    
    return 0;
}