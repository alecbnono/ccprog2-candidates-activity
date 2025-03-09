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

typedef candidateType aCandidates[20];

void getString(char String[], int maxChar)
{
    int  i = 0;
    char ch,
         blank;
    
    scanf("%c", &blank);
    if(blank != '\n')
    {
        String[i] = blank;
        i++;
    }

    do
    {  
        scanf("%c", &ch);
        if (ch != '\n')
        {
            String[i] = ch;
            i++;
        }
    } while (i < maxChar && ch != '\n');
    String[i] = '\0';
}

int SearchParty(aCandidates Candidates, Str128 partyName, int numCandidates)
{
    int i,
        ctr = 0;

    for(i = 0; i < numCandidates; i++)
        if(!strcmp(Candidates[i].party, partyName))
            ctr++;

    return ctr;
}

void getName(nameType *name)
{
    printf("Last Name: ");
    getString(name->last, 20);
    printf("First Name: ");
    getString(name->first, 20);
    printf("Middle Initial: ");
    scanf(" %c", &name->middle);
}
void getDate(dateType *date)
{
        do
        {
                printf("    Month (Numerical): ");
                scanf("%d", &date->month);
                if (date->month < 1 || date->month > 12) 
                        printf("Invalid input. Please enter again.\n");
        }
        while (date->month < 1 || date->month > 12);

        do
        {
                printf("    Day: ");
                scanf("%d", &date->day);
                if (date->day < 1 || date->day > 31) 
                        printf("Invalid input. Please enter again.\n");
        }
        while (date->day < 1 || date->day > 31);

        printf("    Year: ");
        scanf("%d", &date->year);
}

void getInput(candidateType *candidate)
{
    int i = 0;
    Str128 billTemp;
    
    printf("\tCANDIDATE INFORMATION:\n");
    getName(&candidate->name);
    printf("Birth Date:\n");
    getDate(&candidate->birthday);
    printf("Position: ");
    getString(candidate->position, 32);
    printf("Party: ");
    getString(candidate->party, 128);
    printf("\n");

    printf("\tBILLS PASSED:\n");
    do 
    {
        printf("Enter [0] in Bill Name to exit.\n");
        printf("Bill #%d Name: ", i + 1);
        getString(billTemp, 128);
        if(strcmp(billTemp, "0"))
        {
            strcpy(candidate->bill[i].billName, billTemp);
            printf("Date Passed:\n");
            getDate(&candidate->bill[i].date);
            candidate->numBills ++;
        }
        i++;
    }while(i < 10 && strcmp(billTemp, "0"));
    printf("\n");

    printf("\tRATING:\n");
    printf("Confidence Rating: ");
    scanf("%f", &candidate->rating.confidence);
    printf("Administered by: ");
    getString(candidate->rating.orgAdmin, 32);
    printf("Date of Survey\n");
    getDate(&candidate->rating.date);
    printf("\n");
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

    printf("\tBASIC INFORMATION:\n");
    printf("Name: %s, %s %c. \n", Info.name.last, Info.name.first, Info.name.middle);
    printf("Birthday: ");
    displayDate(Info.birthday);
    printf("Party: %s \n", Info.party);
    printf("Position: %s \n\n", Info.position);

    printf("\tBILLS PASSED:\n");
    if(Info.numBills > 0)
        for (i = 0; i < Info.numBills; i++)
        {
            printf("Bill #%d Name: %s \n", i + 1, Info.bill[i].billName);
            printf("Date Passed: ");
            displayDate(Info.bill[i].date);
            printf("\n");
        }
    else
        printf("NO BILLS PASSED\n\n");

    printf("\tRATING\n");
    printf("Confidence Rating: %.2f \n", Info.rating.confidence);
    printf("Administered by: %s \n", Info.rating.orgAdmin);
    printf("Date of Survey: ");
    displayDate(Info.rating.date);
    printf("\n");
}

void displayByParty(aCandidates Candidate, Str128 partyName, int numCandidates)
{
    int     i = 0,
            ctr = 1,
            numParty = SearchParty(Candidate, partyName, numCandidates);
    char    prompt = '1';

    if(numParty > 0)
        do
        {
            if(!strcmp(Candidate[i].party, partyName))
            {
                printf("CANDIDATE #%d:\n", ctr);
                display(Candidate[i]);
                if(ctr < numParty)
                {
                    do
                    {
                        printf("Next Candidate[1] / Exit[0]:");
                        scanf(" %c", &prompt);
                        if(prompt > '1' || prompt < '0')
                            printf("Invalid input. Please enter again.\n");
                    } while(prompt > '1' || prompt < '0');
                }
                ctr++;
            }
            i++;
        }while(prompt == '1' && i < numCandidates);
    else
        printf("NO CANDIDATE FOUND UNDER THIS PARTY.\n\n");
}

void swap(candidateType *candidateA, candidateType *candidateB)
{
    candidateType temp;

    temp = *candidateA;
    *candidateA = *candidateB;
    *candidateB = temp; 
}

void sortByRating(aCandidates Candidate, int numCandidates)
{
    int i, j, low_ind;
    
    for(i = 0; i < numCandidates - 1; i++)
    {
        low_ind = i;
        for(j = i + 1; j < numCandidates; j++)
            if(Candidate[low_ind].rating.confidence > Candidate[j].rating.confidence)
                low_ind = j;
        if(low_ind != i)
            swap(&Candidate[i], &Candidate[low_ind]);
    }
}

void sortAlphabetical(aCandidates Candidate, int numCandidates)
{
    int i, j, low_ind;
    
    for(i = 0; i < numCandidates - 1; i++)
    {
        low_ind = i;
        for(j = i + 1; j < numCandidates; j++)
            if(strcmp(Candidate[low_ind].name.last, Candidate[j].name.last) == 1)
                low_ind = j;
        if(low_ind != i)
            swap(&Candidate[i], &Candidate[low_ind]);
    } 
}

int main()
{
    aCandidates arrCandidates;
    int         i = 0,
                numCandidates = 0,
                choice = -1;
    char        prompt;
    Str128      partyName;
    
    do
    {
        printf("\tMAIN MENU\n");
        printf("[1] Add Candidate Information\n");
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
        } while(choice < 0 || choice > 4);

        switch (choice)
        {
            case 1:
                printf("\n");
                if(numCandidates < 20)
                {
                    getInput(&arrCandidates[numCandidates]);
                    numCandidates++;
                }
                else
                    printf("ERROR: Maximum number of candidates has been reached.\n\n");
                break;
            case 2:
                printf("\n");
                if(numCandidates > 0)
                {
                    if(numCandidates > 1)
                        sortAlphabetical(arrCandidates, numCandidates);
                    for(i = 0; i < numCandidates; i++)
                    {   
                        printf("CANDIDATE #%d:\n", i + 1);
                        display(arrCandidates[i]);
                    }
                }
                else
                    printf("ERROR: Please enter candidate information first.\n\n");
                break;
            case 3:
                printf("\n");
                if(numCandidates > 0)
                {
                    if(numCandidates > 1)
                        sortByRating(arrCandidates, numCandidates);
                    i = 0;
                    do
                    {
                        printf("CANDIDATE #%d:\n", i + 1);
                        display(arrCandidates[i]);
                        if(i < numCandidates - 1)
                        {
                            do
                            {
                                printf("Next Candidate[1] / Exit[0]: ");
                                scanf(" %c", &prompt);
                                if(prompt > '1' || prompt < '0')
                                    printf("Invalid input. Please enter again.\n");
                            } while(prompt > '1' || prompt < '0');
                        }
                        i++;
                    } while (prompt == '1' && i < numCandidates);
                }
                else
                    printf("ERROR: Please enter candidate information first.\n\n");
                break;
            case 4:
                printf("\n");
                if(numCandidates > 0)
                {
                    printf("Enter a Party: ");
                    getString(partyName, 128);
                    displayByParty(arrCandidates, partyName, numCandidates);
                }
                else
                    printf("ERROR: Please enter candidate information first.\n\n");
                break;
        }
    } while(choice != 0);

    return 0;
}
