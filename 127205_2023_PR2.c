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
} BLOCK, *p_BLOCK;

void n(BLOCK **start)
{
    FILE *f = fopen("dataloger_V2.txt", "r");
    if (f == NULL)
    {
        printf("Zaznamy neboli nacitane!\n");
    }
    else
    {
        while (fgets(buff, sizeof(buff), f) != NULL)
        {
            BLOCK *new = (BLOCK *)malloc(sizeof(BLOCK));
            new->id = (ID *)malloc(sizeof(ID));
            new->poz_mod = (POZ_MOD *)malloc(sizeof(POZ_MOD));

            new->next = *start;
            *start = new;
        }

        while (*start != NULL)
        {
            BLOCK *temp = *start;
            *start = (*start)->next;
            free(temp->id);
            free(temp->poz_mod);
            free(temp);
        }

        char buff[100];

                fclose(f);
    }
}

void v()
{
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
    BLOCK *start = NULL;
    do
    {
        scanf("%c", &letter);
        switch (letter)
        {
        case 'n':
            n(&start);
            break;
        case 'v':
            v();
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
            k();
            break;
        }
    } while (letter != 'k');
}