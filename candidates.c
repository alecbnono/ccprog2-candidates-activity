#include <stdio.h>
#include <string.h>

typedef char Str20[21];
typedef char Str128[129];
typedef char Str32[33];
typedef struct 
{
    Str20   First,
            Middle,
            Last;
}NameType;
typedef struct 
{
int     month,
        day,
        year;
}dateType;
typedef struct 
{
    Str128 billName;
    dateType datepassed;
}billType;
typedef struct candidateTag
{
    NameType Name;
    dateType Birthday;
    Str128 party;
    Str32 position;


}candidateType;

void getName();
void getDate();
void getInput();
void displayDate();
void display();
void displayByParty();
void swap();
void sortByRating();
void sortAlphabetical();
int main()
{





    return 0;
}