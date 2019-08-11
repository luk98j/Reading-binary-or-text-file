#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <ctype.h>




struct point_t* set(struct point_t* p, int x, int y);
void show(const struct point_t* p);
float distance(const struct point_t* p1, const struct point_t* p2, int *err_code);

int save_point_b(const char *filename, const struct point_t* p);
int load_point_b(const char *filename, struct point_t* p);
int save_point_t(const char *filename, const struct point_t* p);
int load_point_t(const char *filename, struct point_t* p);

struct point_t
{
    int x;
    int y;
} pkt1, pkt2;

int main()
{

    struct point_t *wsk_pkt2 = &pkt2;
    int x=0;
    int y=0;

    srand (time(NULL));
    x = (rand  () %20) ;
    y = (rand () %20);

    set(wsk_pkt2, x, y);
    show (wsk_pkt2);

    char sciezka[31];
    char *wsk_sciezka=sciezka;

    printf("Podaj sciezke do pliku\n");
    scanf("%30s",wsk_sciezka);

    if (strlen(wsk_sciezka)==30)
    while (getchar()!='\n');

    fflush(stdin);


    if ((*(wsk_sciezka+(strlen(wsk_sciezka)-1))=='n') && (*(wsk_sciezka+(strlen(wsk_sciezka)-2))=='i') && (*(wsk_sciezka+(strlen(wsk_sciezka)-3))=='b') && (*(wsk_sciezka+(strlen(wsk_sciezka)-4))=='.'))
    {
        int zapis_b=save_point_b(wsk_sciezka,wsk_pkt2);
        if(zapis_b==0)
        {

            printf("File saved\nDo you want to read the file (Y/N)? \n");
            char znak1;
            scanf(" %1c", &znak1);
            if (znak1 == 'y' || znak1 == 'Y' )
            {
                int odczyt_b = load_point_b((const char *)wsk_sciezka,wsk_pkt2);

                if(odczyt_b==3)
                {
                    printf ("File corrupted");
                    return 6;
                }
                if(odczyt_b==2)
                {
                    printf ("Couldn't open file");
                    return 4;
                }
                else
                {
                    show(wsk_pkt2);
                    return 0;
                }
            }
            else if (znak1 == 'n' || znak1 == 'N') return 0;
            else
            {
                printf ("Incorrect input");
                return 1;
            }
        }
        if(zapis_b==2)
        {
            printf (" Couldn't create file");
            return 5;
        }
    }

    if ((*(wsk_sciezka+(strlen(wsk_sciezka)-1))=='t') && (*(wsk_sciezka+(strlen(wsk_sciezka)-2))=='x') && (*(wsk_sciezka+(strlen(wsk_sciezka)-3))=='t') && (*(wsk_sciezka+(strlen(wsk_sciezka)-4))=='.'))
    {
        int zapis_t = save_point_t(wsk_sciezka,wsk_pkt2);
        if(zapis_t==0)
        {
            char znak2;
            printf("File saved\nDo you want to read the file (Y/N)? \n");
            scanf(" %1c", &znak2);
            if ( znak2 == 'y' || znak2 == 'Y' )
            {


                int odczyt_t = load_point_t((const char*)wsk_sciezka,wsk_pkt2);

                if(odczyt_t==3)
                {
                    printf ("File corrupted");
                    return 6;
                }
                if(odczyt_t==2)
                {
                    printf ("Couldn't open file");
                    return 4;
                }
                else
                {
                    show(wsk_pkt2);
                    return 0;
                }
            }

            if (znak2 == 'n' || znak2 == 'N') return 0;
            else
            {
                printf ("Incorrect input");
                return 1;
            }
        }
        if(zapis_t==2)
        {
            printf ("Couldn't create file");
            return 5;
        }
    }
    else
    {
        printf ("Unsupported file format");
        return 7;
    }
}

void show(const struct point_t* p)
{
    if(p!=NULL)
    {
        printf("x = %d; ",p->x);
        printf("y = %d\n",p->y);
    }
}

struct point_t* set(struct point_t* p, int x, int y)
{
    if(p==NULL) return NULL;
    p->x=x;
    p->y=y;
    return p;
}

int save_point_b(const char *filename, const struct point_t* p)
{
    if ( p == NULL) return 1;
    if (filename==NULL) return 1;
    FILE * plik_b = fopen(filename, "wb");
    if (plik_b==NULL) return 2;

    fwrite(&(p->x),4,1,plik_b);
    fwrite(&(p->y),4,1,plik_b);

    fclose(plik_b);
    return 0;
}

int load_point_b(const char *filename, struct point_t* p)
{

    if (p == NULL) return 1;
    if (filename==NULL) return 1;
    FILE * plik_2b = fopen(filename, "rb");
    if (plik_2b==NULL) return 2;
    int size = (sizeof(plik_2b));
    if(size==5||size==3||size==7||size==10||size==6||size==1){ fclose(plik_2b); return 3;}

    if (fread(&(p->x),1,4,plik_2b)==0)
    {
        fclose(plik_2b);
        return 3;
    }
    if (fread(&(p->y),1,4,plik_2b)==0)
    {
        fclose(plik_2b);
        return 3;
    }
    else{
    fclose(plik_2b);
    return 0;
    }
}

int save_point_t(const char *filename, const struct point_t* p)
{
    if ( p == NULL) return 1;
    if (filename==NULL) return 1;
    FILE * plik_t = fopen(filename, "w");
    if (plik_t==NULL) return 2;

    fprintf(plik_t,"%d ",p->x);
    fprintf(plik_t,"%d",p->y);

    fclose(plik_t);
    return 0;
}

int load_point_t(const char *filename, struct point_t* p)
{
    if (p == NULL) return 1;
    if (filename==NULL) return 1;
    FILE * plik_2t = fopen(filename, "r");
    if (plik_2t==NULL) return 2;
    int size = sizeof(plik_2t);
    if(size==3||size==6||size==10){fclose(plik_2t);return 3;}
    int znak;
    if(fscanf(plik_2t,"%d",&znak)!=1)
    {
        fclose(plik_2t);
        return 3;
    }
    else p->x=znak;

    if(fscanf(plik_2t,"%d",&znak)!=1)
    {
        fclose(plik_2t);
        return 3;
    }
    else
    {
    p->y=znak;

    }
     fclose(plik_2t);
    return 0;
}
