#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

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
            printf("\n");
            temp = temp->next;
        }
    }
}

void p(BLOCK **start, int *counter)
{
    int position;
    printf("zadaj pozíciu nového záznamu:\n");
    scanf("%d", &position);

    if (position <= 0)
    {
        printf("zlá pozícia");
        return;
    }

    else
    {
        BLOCK *new = (BLOCK *)malloc(sizeof(BLOCK));
        new->id = (ID *)malloc(sizeof(ID));
        new->poz_mod = (POZ_MOD *)malloc(sizeof(POZ_MOD));

        printf("Zadaj ID:\n");
        scanf("%1s%d%1s", new->id->bigl, &(new->id->number), new->id->small);

        printf("Zadaj pozíciu modulu:\n");
        scanf("%8s%8s", new->poz_mod->latitude, new->poz_mod->longitude);

        printf("Zadaj typ mer. veličiny:\n");
        scanf("%2s", new->Typ_mer_vel);

        printf("Zadaj hodnotu:\n");
        scanf("%lf", &(new->Hodnota));

        printf("Zadaj čas merania:\n");
        scanf("%4s", new->Cas_mer);

        printf("Zadaj dátum merania:\n");
        scanf("%8s", new->Dat_mer);

        new->next = NULL;

        if (*start == NULL || position == 1)
        {
            new->next = *start;
            *start = new;
        }
        else
        {
            BLOCK *temp = *start;
            for (int i = 1; i < position - 1 && temp != NULL; i++)
            {
                temp = temp->next;
            }
            if (temp == NULL)
            {
                printf("zlá pozícia!\n");
                free(new->id);
                free(new->poz_mod);
                free(new);
                return;
            }
            new->next = temp->next;
            temp->next = new;
        }
        (*counter)++;
    }
}

void z(BLOCK **start, int *counter)
{
    char del_id[5];
    printf("Zadaj ID modulu na vymazanie:\n");
    scanf("%5s", del_id);
    del_id[5] = '\0';

    BLOCK *current = *start;
    BLOCK *previous = NULL;
    int deleted_records = 0;

    while (current != NULL)
    {
        if (strncmp(current->id->bigl, del_id, 1) == 0 &&
            current->id->number == atoi(del_id + 1) &&
            strncmp(current->id->small, del_id + 4, 1) == 0)
        {
            if (previous == NULL)
            {
                *start = current->next;
                free(current->id);
                free(current->poz_mod);
                free(current);
                current = *start;
            }
            else
            {
                previous->next = current->next;
                free(current->id);
                free(current->poz_mod);
                free(current);
                current = previous->next;
            }
            (*counter)--;
            deleted_records++;
        }
        else
        {
            previous = current;
            current = current->next;
        }
    }
    if (deleted_records > 0)
    {
        for (int i = 0; i < deleted_records; i++)
        {
            printf("Zaznam pre ID: %s bol vymazany.\n", del_id);
        }
    }
    else
    {
        printf("Zaznam pre ID: %s nebol najdeny.\n", del_id);
    }
}

void u(BLOCK **start, int counter)
{

    BLOCK *temp_block = (BLOCK *)malloc(sizeof(BLOCK));
    temp_block->id = (ID *)malloc(sizeof(ID));
    temp_block->poz_mod = (POZ_MOD *)malloc(sizeof(POZ_MOD));
    bool equal = false;

    while (equal == false)
    {
        BLOCK *temp1 = *start;
        BLOCK *temp2 = (*start)->next;
        equal = true;

        while (temp2 != NULL)
        {
            if ((strcmp(temp1->Dat_mer, temp2->Dat_mer) > 0) || (strcmp(temp1->Dat_mer, temp2->Dat_mer) == 0 && strcmp(temp1->Cas_mer, temp2->Cas_mer) > 0))
            {
                strcpy(temp_block->id->bigl, temp1->id->bigl);
                temp_block->id->number = temp1->id->number;
                strcpy(temp_block->id->small, temp1->id->small);
                strcpy(temp_block->poz_mod->latitude, temp1->poz_mod->latitude);
                strcpy(temp_block->poz_mod->longitude, temp1->poz_mod->longitude);
                strcpy(temp_block->Typ_mer_vel, temp1->Typ_mer_vel);
                temp_block->Hodnota = temp1->Hodnota;
                strcpy(temp_block->Cas_mer, temp1->Cas_mer);
                strcpy(temp_block->Dat_mer, temp1->Dat_mer);

                strcpy(temp1->id->small, temp2->id->small);
                temp1->id->number = temp2->id->number;
                strcpy(temp1->id->bigl, temp2->id->bigl);
                strcpy(temp1->poz_mod->latitude, temp2->poz_mod->latitude);
                strcpy(temp1->poz_mod->longitude, temp2->poz_mod->longitude);
                strcpy(temp1->Typ_mer_vel, temp2->Typ_mer_vel);
                temp1->Hodnota = temp2->Hodnota;
                strcpy(temp1->Cas_mer, temp2->Cas_mer);
                strcpy(temp1->Dat_mer, temp2->Dat_mer);

                strcpy(temp2->id->bigl, temp_block->id->bigl);
                temp2->id->number = temp_block->id->number;
                strcpy(temp2->id->small, temp_block->id->small);
                strcpy(temp2->poz_mod->latitude, temp_block->poz_mod->latitude);
                strcpy(temp2->poz_mod->longitude, temp_block->poz_mod->longitude);
                strcpy(temp2->Typ_mer_vel, temp_block->Typ_mer_vel);
                temp2->Hodnota = temp_block->Hodnota;
                strcpy(temp2->Cas_mer, temp_block->Cas_mer);
                strcpy(temp2->Dat_mer, temp_block->Dat_mer);
                equal = false;
            }
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
    }
    free(temp_block->id); // uvolnenie pomocneho blocku
    free(temp_block->poz_mod);
    free(temp_block);

    printf("Spajany zoznam bol usporiadany.");
    return;
}

void r(int counter, BLOCK **start)
{
    int c1, c2;
    printf("Zadaj pozíciu 1. záznamu, ktorý chceš prehodiť:\n");
    scanf("%d", &c1);
    printf("Zadaj pozíciu 2. záznamu, ktorý chceš prehodiť:\n");
    scanf("%d", &c2);

    if (c1 == c2 || c1 > counter || c2 > counter)
    {
        printf("Zle zadané pozície.\n");
        return;
    }
    else
    {
        BLOCK *temp1 = *start;
        BLOCK *temp2 = *start;
        BLOCK *temp_block = (BLOCK *)malloc(sizeof(BLOCK));
        temp_block->id = (ID *)malloc(sizeof(ID));
        temp_block->poz_mod = (POZ_MOD *)malloc(sizeof(POZ_MOD));

        for (int i = 1; i < c1; i++) // nájde záznam podľa 1. zadanej pozície
        {
            temp1 = temp1->next;
        }

        for (int i = 1; i < c2; i++) // nájde záznam podľa 2. zadanej pozície
        {
            temp2 = temp2->next;
        }

        strcpy(temp_block->id->bigl, temp1->id->bigl);
        temp_block->id->number = temp1->id->number;
        strcpy(temp_block->id->small, temp1->id->small);
        strcpy(temp_block->poz_mod->latitude, temp1->poz_mod->latitude);
        strcpy(temp_block->poz_mod->longitude, temp1->poz_mod->longitude);
        strcpy(temp_block->Typ_mer_vel, temp1->Typ_mer_vel);
        temp_block->Hodnota = temp1->Hodnota;
        strcpy(temp_block->Cas_mer, temp1->Cas_mer);
        strcpy(temp_block->Dat_mer, temp1->Dat_mer);

        strcpy(temp1->id->small, temp2->id->small);
        temp1->id->number = temp2->id->number;
        strcpy(temp1->id->bigl, temp2->id->bigl);
        strcpy(temp1->poz_mod->latitude, temp2->poz_mod->latitude);
        strcpy(temp1->poz_mod->longitude, temp2->poz_mod->longitude);
        strcpy(temp1->Typ_mer_vel, temp2->Typ_mer_vel);
        temp1->Hodnota = temp2->Hodnota;
        strcpy(temp1->Cas_mer, temp2->Cas_mer);
        strcpy(temp1->Dat_mer, temp2->Dat_mer);

        strcpy(temp2->id->bigl, temp_block->id->bigl);
        temp2->id->number = temp_block->id->number;
        strcpy(temp2->id->small, temp_block->id->small);
        strcpy(temp2->poz_mod->latitude, temp_block->poz_mod->latitude);
        strcpy(temp2->poz_mod->longitude, temp_block->poz_mod->longitude);
        strcpy(temp2->Typ_mer_vel, temp_block->Typ_mer_vel);
        temp2->Hodnota = temp_block->Hodnota;
        strcpy(temp2->Cas_mer, temp_block->Cas_mer);
        strcpy(temp2->Dat_mer, temp_block->Dat_mer);

        free(temp_block->id); // uvolnenie pomocneho blocku
        free(temp_block->poz_mod);
        free(temp_block);
    }
    return;
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
            p(&start, &counter);
            break;
        case 'z':
            z(&start, &counter);
            break;
        case 'u':
            u(&start, counter);
            break;
        case 'r':
            r(counter, &start);
            break;
        case 'k':
            k(&start);
            break;
        }
    } while (letter != 'k');
}