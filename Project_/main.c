#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct node
{
    int ertelenme;
    int ucak_id;
    int talep_edilen_inis_saati;
    int oncelik_id;
    struct node *next;
};

struct node1{

    int oncelik_id;
    int ucak_id;
    int talep_edilen_inis_saati;
    int inis_saati;
    int gecikme_suresi;
    int kalkis_saati;

    struct node1 *next;
};

struct node *front = NULL;
struct node *rear = NULL;

struct node1 *on = NULL;
struct node1 *arka = NULL;

int keepvalue1;
int keepvalue2;
int keepvalue3;
int keepvalue4;


void direct(int a1,int a2,int a3,int a4)
{

    struct node *indbul=front;

    if(front==NULL)
    {
        printf("Kuyruk bos...\n");
        return 1;
    }

    struct node *yedek;

    while(indbul->next != NULL && indbul->next->talep_edilen_inis_saati !=a1 && indbul->next->oncelik_id != a2 && indbul->next->ucak_id !=a3)
    {
        indbul=indbul->next->next;
    }
if(indbul->next == NULL)
{
printf("Silmek istenilen inis izni bulunamadi.");
        return -5;
}

    yedek=indbul->next;

    indbul->next=indbul->next->next;

    free(yedek);

      printf("\n");

    printf("Acil inis yapmasi gereken %d id'li ucak nedeniyle kule tarafindan %d id'li ucagin inis izni iptal edilmistir, inis icin Sabiha Gokcen Havalimanina yonlendirilmektesiniz.\n",a4,a3);

}

int dequeue(int b1,int b2,int b3,int b4)
{
    struct node *indara=front;
    struct node *yed;

if(front==NULL)
{
        printf("Kuyruk bos... \n");
        return 1;
}

    while(indara->next != NULL && indara->next->talep_edilen_inis_saati !=b1 && indara->next->oncelik_id !=b2 && indara->next->ucak_id !=b3)
    {
        indara=indara->next->next;
    }
if(indara->next == NULL)
{
printf("Silmek istenilen inis izni bulunamadi.");
        return 0;
}

    yed=indara->next;
    indara->next = indara->next->next;
    free(yed);

    struct node1 *indara1=on;
    struct node1 *yed1;


    while(indara1->next != NULL && indara1->next->talep_edilen_inis_saati !=b1 && indara1->next->oncelik_id !=b2 && indara1->next->ucak_id !=b3)
    {
        indara1=indara1->next->next;
    }
if(indara1->next == NULL)
{
printf("Silmek istenilen izin bulunamadi.");
        return 0;
}

    yed1 = indara1->next;
    indara1->next = indara1->next->next;
    free(yed1);

    return 1;
}


void enqueue(int hour,int id,int plane,int ert)
{
    struct node *ind1=front;

    while(ind1!=NULL)
    {
        ind1=ind1->next;
    }

     printf("\nInis izni talebiniz kule tarafindan onaylanmistir..\n");

     struct node1 *ind2=on;

if(front==NULL && on==NULL)
{
    struct node *list1 = (struct node *)malloc(sizeof(struct node));
    struct node1 *list2=(struct node1 *)malloc(sizeof(struct node1));

if(ert!=0)
{
    list1->ertelenme++;

}
else
{
    list1->ertelenme = 0;
}

        list1->talep_edilen_inis_saati=hour;
        list1->oncelik_id=id;
        list1->ucak_id=plane;



        list2->oncelik_id=id;
        list2->ucak_id=plane;
        list2->talep_edilen_inis_saati=hour;
        list2->gecikme_suresi=list1->ertelenme;
        list2->inis_saati=list2->talep_edilen_inis_saati+(list2->gecikme_suresi);
        list2->kalkis_saati=list2->inis_saati+(1);


        list1->next=NULL;
        list2->next=NULL;


        front = rear = list1;
        on = arka = list2;
    }

    else
    {
        struct node *list1 = (struct node *)malloc(sizeof(struct node));
        struct node1 *list2 = (struct node1 *)malloc(sizeof(struct node1));
        if(ert!=0)
        {
            list1->ertelenme++;
        }
        else
        {
            list1->ertelenme = 0;
        }

        list1->talep_edilen_inis_saati=hour;
        list1->oncelik_id=id;
        list1->ucak_id=plane ;

        list2->oncelik_id=id;
        list2->ucak_id=plane;
        list2->talep_edilen_inis_saati=hour;
        list2->gecikme_suresi=ert;
        list2->inis_saati=list2->talep_edilen_inis_saati+ list2->gecikme_suresi;
        list2->kalkis_saati=list2->inis_saati+1;

        list1->next = NULL;
        list2->next = NULL;


        rear->next = list1;

        rear = list1;

        arka->next = list2;

        arka = list2;
    }
}

int fonkert(int hour,int id,int plane,int ert)
{

    if(kuyrukbak(hour,id,plane,ert)==0)
    {
        printf("\nAyni saatte baska bir talep oldugu icin inis talebiniz kule tarafindan 1 saat erteleniyor..");
        ert=ert+1;
        hour=hour+1;
        if(ert>3)
        {
            direct(hour,id,plane,ert);
            return 0;
        }
        fonkert(hour,id,plane,ert);
    }
    else if(kuyrukbak(hour,id,plane,ert)==1 && kuyrukbak(hour,id,plane,ert) !=2 && kuyrukbak(hour,id,plane,ert)!=3)
    {

        enqueue(hour,id,plane,ert);

    }
}


int kuyrukbak(int hour,int id,int plane,int ert)
{
    struct node *ind1=front;

    int count3=0;

    while(ind1!=NULL)
    {
        count3++;
if(count3==24)
{
printf("Inis pisti kapasitesi dolmustur.\n");
}

if(ind1->talep_edilen_inis_saati==hour)
{
if(ind1->oncelik_id !=NULL && ind1->oncelik_id==id && ind1->ucak_id<plane && ert==3)
{
printf("Inis talebiniz ucaginizin id farki nedeniyle kule tarafindan reddedilmistir.\n");

    return 2;
}
if(ind1->oncelik_id !=NULL && ind1->oncelik_id==id && ind1->ucak_id<plane && ert==2)
{
printf("Inis talebiniz ucaginizin id farki nedeniyle kule tarafindan reddedilmistir.\n");
ert++;
hour++;
fonkert(hour,id,plane,ert);
    return 3;
}
if(ind1->oncelik_id !=NULL && ind1->oncelik_id>id && ind1->ucak_id!=plane)
{

printf("Inis talebiniz, ucaginizin yuksek onceligi nedeniyle kule tarafindan onaylanmistir.\n");

    enqueue(hour,id,plane,ert);

    keepvalue1=ind1->talep_edilen_inis_saati;
    keepvalue2=ind1->oncelik_id;
    keepvalue3=ind1->ucak_id;
    keepvalue4=ind1->ertelenme;

    dequeue(keepvalue1,keepvalue2,keepvalue3,keepvalue4);

    fonkert(keepvalue1,keepvalue2,keepvalue3,keepvalue4);

                return 2;
}
    return 0;
}
ind1=ind1->next;
}
return 1;
}

int main()
{

 printf("ISTANBUL HAVALIMANI UCUS YONETIM SISTEMI...");

 printf("\n");
 printf("\n");

    kule_inis();
    output_file();

    return 0;
}

void kule_inis()
{

    FILE *inptr=fopen("input.txt", "r");;

    char dosya[32];
    char eleman;
    int j=0;
    int dizi[100];
    int i=0;

    while(1)
    {
        eleman=fgetc(inptr);
if(eleman==EOF)
{
break;
}
else if(eleman==' ')
{
dizi[j] = atoi(dosya);
j++;
bzero(dosya,32);
i=0;
     continue;
}
else
{
dosya[i]=eleman;
i++;
}
}

    int ert=0;
    int hour,plane;
    int oncelik;
    bool value=true;
    int value2;

    int start=3;

   while(value)
{
printf("\nKuleden inis izni istemek icin 1'e basiniz, programdan ayrilmak icin 0'a basiniz: ");
scanf("%d",&value2);

if(value2==1)
{
    printf("**%d",dizi[start+1]);
    oncelik=dizi[start];
    start++;
    plane=dizi[start];
    start++;
    hour=dizi[start];
    start++;
    ert=0;

if(kuyrukbak(hour,oncelik,plane,ert)==0)
{

    fonkert(hour,oncelik,plane,ert);
}

else if(kuyrukbak(hour,oncelik,plane,ert)==1 && kuyrukbak(hour,oncelik,plane,ert)!=2 && kuyrukbak(hour,oncelik,plane,ert)!=3)
{
   enqueue(hour,oncelik,plane,ert);
}
    inis_print(); // inis kuyrugunu gosterir
    kalkis_print(); // kalkis kuyrugunu gosterir
}
else
{
value=false;
}
}
}


void inis_print()
{
    int count=0;

    if(front==NULL)
    {
        printf("Inis kuyrugu bostur.");
        return -1;
    }

    printf("Inis Pistindeki Kuyruk: \n");
    printf("Oncelik  || Ucak ID || Inis Saati");

    struct node *ind1=front;

    while(ind1!=NULL)
    {
        count++;
        printf("\n         Ucak: %d - %d - %d\t",ind1->oncelik_id,ind1->ucak_id,ind1->talep_edilen_inis_saati);
        ind1=ind1->next;
    }

    printf("\n");
}
void kalkis_print()
{
    int count2=0;

    printf("Kalkis Pistindeki Kuyruk: \n");
    printf("Oncelik  || Ucak ID || Talep Edilen Inis Saati || Inis Saati || Gecikme Suresi || Kalkis Saati");

    struct node1 *ind2=on;

    while(ind2!=NULL)
    {
        count2++;
        printf("\n         Ucak: %d - %d - %d - %d - %d - %d\t",ind2->oncelik_id,ind2->ucak_id,ind2->talep_edilen_inis_saati,ind2->inis_saati,ind2->gecikme_suresi,ind2->kalkis_saati);
        ind2=ind2->next;
    }
    printf("\n");

}
void output_file()
{
    FILE *outptr=fopen("output.txt","w");
    fprintf(outptr,"Oncelik  -- Ucak ID -- Talep Edilen Inis Saati -- Inis Saati -- Gecikme Suresi -- Kalkis Saati");
    struct node1 *ind2 = on;

    while(ind2!=NULL)
    {

        fprintf(outptr,"\n\n Ucak: %d | %d | %d | %d | %d | %d",ind2->oncelik_id,ind2->ucak_id,ind2->talep_edilen_inis_saati,ind2->inis_saati,ind2->gecikme_suresi,ind2->kalkis_saati);
        ind2=ind2->next;
    }
}
