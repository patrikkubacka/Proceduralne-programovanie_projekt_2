#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct id
{
    char bigl[2];
    int number;
    char small[2];
} ID;

typedef struct poz_mod
{
    char latitude[9];
    char longitude[9];
} POZ_MOD;

typedef struct block
{
    struct id *id;
    struct poz_mod *poz_mod;
    char Typ_mer_vel[3];
    double Hodnota;
    char Cas_mer[5];
    char Dat_mer[9];
    struct block *next;
} BLOCK;

void n(BLOCK **start, int *counter)
{
    FILE *f = fopen("dataloger_V2.txt", "r");
    if (f == NULL)
    {
        printf("Zaznamy neboli nacitane!\n");
        return;
    }
    else
    {
        char buff[100];

        while (*start != NULL)
        {
            BLOCK *temp = *start;
            *start = (*start)->next;
            free(temp->id);
            free(temp->poz_mod);
            free(temp);
        }
        *counter = 0;
        char s_number[100];
        BLOCK *temp = *start;
        while (fgets(buff, sizeof(buff), f) != NULL)
        {
            BLOCK *new = (BLOCK *)malloc(sizeof(BLOCK));
            new->id = (ID *)malloc(sizeof(ID));
            new->poz_mod = (POZ_MOD *)malloc(sizeof(POZ_MOD));

            fgets(buff, sizeof(buff), f);
            buff[5] = '\0';
            strncpy(new->id->bigl, buff, 1);
            new->id->bigl[1] = '\0';
            strncpy(s_number, buff + 1, 3);
            new->id->number = atoi(s_number);
            strncpy(new->id->small, buff + 4, 1);
            new->id->small[1] = '\0';

            fgets(buff, sizeof(buff), f);
            buff[16] = '\0';
            strncpy(new->poz_mod->latitude, buff, 8);
            new->poz_mod->latitude[8] = '\0';
            strncpy(new->poz_mod->longitude, buff + 8, 8);
            new->poz_mod->longitude[8] = '\0';

            fgets(buff, sizeof(buff), f);
            buff[2] = '\0';
            strncpy(new->Typ_mer_vel, buff, 2);
            new->Typ_mer_vel[2] = '\0';

            fgets(buff, sizeof(buff), f);
            buff[6] = '\0';
            strncpy(s_number, buff, 6);
            new->Hodnota = atof(s_number);

            fgets(buff, sizeof(buff), f);
            buff[4] = '\0';
            strncpy(new->Cas_mer, buff, 4);
            new->Cas_mer[4] = '\0';

            fgets(buff, sizeof(buff), f);
            buff[8] = '\0';
            strncpy(new->Dat_mer, buff, 8);
            new->Dat_mer[8] = '\0';

            if (*start == NULL)
            {
                *start = new;
                temp = *start;
            }
            else
            {
                temp->next = new;
                temp = new;
            }
            (*counter)++;
        }
        temp->next = NULL;
        fclose(f);
        printf("Načítalo sa %d záznamov\n", (*counter));
    }
}

void v(BLOCK **start, int counter)
{
    if (*start == NULL)
    {
        printf("záznamy neboli načítané\n");
    }
    else
    {
        BLOCK *temp = *start;
        for (int i = 1; i < counter + 1; i++)
        {
            printf("%d:\n", i);
            printf("ID: %s%d%s \t %s \t %g\n", temp->id->bigl, temp->id->number, temp->id->small, temp->Typ_mer_vel, temp->Hodnota);
            printf("Poz: %8s \t %8s\n", temp->poz_mod->latitude, temp->poz_mod->longitude);
            printf("DaC: %s \t %s\n", temp->Dat_mer, temp->Cas_mer);
            temp = temp->next;
        }
    }
}

void p()
{
}

void z()
{
}

void u()
{
}

void r()
{
}

void k(BLOCK **start)
{
    while (*start != NULL)
    {
        BLOCK *temp = *start;
        *start = (*start)->next;
        free(temp->id);
        free(temp->poz_mod);
        free(temp);
    }
}

int main(void)
{
    char letter;
    int counter = 0;
    BLOCK *start = NULL;
    do
    {
        scanf("%c", &letter);
        switch (letter)
        {
        case 'n':
            n(&start, &counter);
            break;
        case 'v':
            v(&start, counter);
            break;
        case 'p':
            p();
            break;
        case 'z':
            z();
            break;
        case 'u':
            u();
            break;
        case 'r':
            r();
            break;
        case 'k':
            k(&start);
            break;
        }
    } while (letter != 'k');
}