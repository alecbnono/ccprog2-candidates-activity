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

void getName(nameType *name)
{
    printf("Enter First Name: ");
    scanf("%s", name->first);
    printf("Enter Last Name: ");
    scanf("%s", name->last);
    printf("Enter Middle Initial: ");
    scanf("%c", &name->middle);
}
void getDate(dateType *date)
{
    printf("Enter Birthyear: ");
    scanf("%d", &date->year);
    printf("Enter Birthmonth: ");
    scanf("%d", &date->month);
    printf("Enter Birthday: ");
    scanf("%d", &date->day);
}
void getInput(candidateType *candidate)
{
    getDate(&candidate->birthday);
    getName(&candidate->name);
}

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
    int i = 0;
    char prompt = '\n';

    do
    {
        if (strcmp(Candidate[i].party, partyName) == 0)
        {
            display(Candidate[i]);
            printf("Next Candidate[Enter] / Exit[0]\n");
            scanf("%c", &prompt);
        }
        i++;
    }while(prompt == '\n' && i < 20);
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

void navigateMainMenu(aCanditates Candidate)
{
    int i = 0,
        numCandidates = 0,
        choice = -1;
    char prompt;
    Str128 partyName;
    
    do
    {
        printf("[1] Add Candidate Info\n");
        printf("[2] Display All Candidates \n");
        printf("[3] Display by Rating\n");
        printf("[4] Display by Party\n");
        printf("[0] Exit\n");

        do
        {
            printf("Enter Choice: ");
            scanf("%d", &choice);
            if (choice < 0 || choice > 4)
                printf("Invalid input. Please enter again.\n");
        }
        while (choice < 0 || choice > 4);

        switch (choice)
        {
            case 1:
                getInput(&Candidate[0]);
                break;
            case 2:
                sortAlphabetical(Candidate);
                for(i = 0; i < numCandidates; i++)
                    display(Candidate[i]);
                break;
            case 3:
                sortByRating(Candidate);
                break;
            case 4:
                printf("Enter a Party: ");
                scanf("%s", partyName);
                displayByParty(Candidate, partyName);
                break;
        }
    }while(choice != 0);
}

int main()
{
    
    return 0;
}
