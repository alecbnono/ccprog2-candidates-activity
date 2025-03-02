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

typedef candidateType aCanditates[20];

void getName(nameType *name);
void getDate(dateType *date);
void getInput(candidateType *candidate);
void displayDate(dateType Date)
{
    char *months[12] = {"January", "February", "March", 
                        "April", "May", "June", "July",
                        "August", "September", "October",
                        "November", "December"};
    printf("%s %d, %d \n", months[Date.month - 1], Date.day, Date.year);
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
void swap(candidateType *candidateA, candidateType *candidateB)
{
    candidateType temp;

    temp = *candidateA;
    *candidateA = *candidateB;
    *candidateB = temp; 
}
void sortByRating(aCanditates Candidate)
{
    int i, j, low_ind;
    
    for(i = 0; i < 19; i++)
    {
        low_ind = i;
        for(j = i + 1; j < 20; j++)
            if(Candidate[low_ind].rating.confidence > Candidate[j].rating.confidence)
                low_ind = j;
        if(low_ind != i)
            swap(&Candidate[i], &Candidate[low_ind]);
    }
}
void sortAlphabetical(aCanditates Candidate)
{
    int i, j, low_ind;
    
    for(i = 0; i < 19; i++)
    {
        low_ind = i;
        for(j = i + 1; j < 20; j++)
            if(strcmp(Candidate[low_ind].name.last, Candidate[j].name.last) == 1)
                low_ind = j;
        if(low_ind != i)
            swap(&Candidate[i], &Candidate[low_ind]);
    } 
}

int main()
{





    return 0;
}