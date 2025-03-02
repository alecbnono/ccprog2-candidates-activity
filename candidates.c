#include <stdio.h>
#include <string.h>

typedef char Str20[21];
typedef char Str128[129];
typedef char Str32[33];

typedef struct 
{
    Str20       first,
                last;
    char        middle;
} nameType;

typedef struct 
{
    int         month,
                day,
                year;
} dateType;

typedef struct 
{
    Str128      billName;
    dateType    date;
} billType;

typedef struct
{
    float       confidence;
    Str32       orgAdmin;
    dateType    date;
} ratingType;

typedef struct
{
    nameType    name;
    dateType    birthday;
    Str128      party;
    Str32       position;
    billType    bill[10];
    int         numBills;
    ratingType  rating;
} candidateType;

typedef candidateType aCanditates[10];

void getName();
void getDate();
void getInput();
void displayDate(dateType Date)
{
    char *months[13] = {"January", "February", "March", 
                        "April", "May", "June", "July",
                        "August", "September", "October",
                        "November", "December"};
    printf("%s %d, %d \n", months[Date.month - 1],Date.day, Date.year);
}
void display(candidateType Info)
{
    int i;
    printf("Name: %s, %s %c. \n", Info.name.last, Info.name.first, Info.name.middle);
    printf("Birthday: ");
    displayDate(Info.birthday);
    printf("Party: %s \n", Info.party);
    printf("Position: %s \n", Info.position);

    for (i = 0; i < Info.numBills; i++)
    {
        printf("Bill Name: %s \n", Info.bill[i].billName);
        displayDate(Info.bill[i].date);
    }

    printf("Confidence Rating: %.2f \n", Info.rating.confidence);
    printf("Survey Organizer: %s \n", Info.rating.orgAdmin);
    printf("Date of Survey: ");
    displayDate(Info.rating.date);

}
void displayByParty(aCanditates Candidate, Str128 partyName)
{
    int i;
    for (i = 0; i < 20; i++)
    {
        if (strcmp(Candidate[i].party, partyName) == 0)
        {
            display(Candidate[i]);
        }
    }
}
void swap();
void sortByRating();
void sortAlphabetical();

int main()
{





    return 0;
}