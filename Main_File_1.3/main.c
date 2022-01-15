#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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

//ON VE ARKA NODELARI BELIRLEME

struct node *front = NULL;
struct node *rear = NULL;

struct node1 *on = NULL;
struct node1 *arka = NULL;
int tut1,tut2,tut3,tut4;
int tut_1,tut_2,tut_3,tut_4;

//KUYRUK SILME
int dequeue(int x, int y, int z, int t)
{



    tut_1 = x;
    tut_2 = y;
    tut_3 = z;
    tut_4 = t;



    struct node *indexdene = front;
    struct node *temp;

    struct node1 *indexd=on;
    struct node1 *temp1;


    // EGER KUYRUK BOSSA
    if(front==NULL)
    {
        printf("Kuyruk bos. \n");
        return 1;
    }

    while(indexdene->next != NULL && indexdene->next->talep_edilen_inis_saati != x && indexdene->next->oncelik_id != y && indexdene->next->ucak_id != z)
    {
        indexdene = indexdene->next->next;
    }
    if(indexdene->next == NULL)
    {
        printf("Silmek istenilen deger bulunamadi.");
        return 0;
    }

    temp = indexdene->next;
    indexdene->next = indexdene->next->next;
    free(temp);

    while(indexd->next != NULL && indexd->next->talep_edilen_inis_saati != x && indexd->next->oncelik_id != y && indexd->next->ucak_id != z)
    {
        indexd = indexd->next->next;
    }
    if(indexd->next == NULL)
    {
        printf("Silmek istenilen deger bulunamadi.");
        return 0;
    }

    temp1 = indexd->next;
    indexd->next = indexd->next->next;
    free(temp1);

    return 1;
}


//ERTELEMELERÝ VE KONTROLLERÝ YAPIYOR
int ertelenen(int talep,int id,int ucak,int ertelenme)
{

    if(queue_control(talep,id,ucak,ertelenme)==0)
    {
        printf("\nAyni saatte baska bir talep oldugu icin talebiniz 1 saat erteleniyor..");
        ertelenme = ertelenme +1;
        talep = talep + 1;
        if(ertelenme>3)
        {
            yonlendir(talep,id,ucak,ertelenme);
            return 0;
        }
        ertelenen(talep,id,ucak,ertelenme);
    }
    else if(queue_control(talep,id,ucak,ertelenme)==1 && queue_control(talep,id,ucak,ertelenme) !=2 && queue_control(talep,id,ucak,ertelenme)!=3)
    {

        enqueue(talep,id,ucak,ertelenme);

    }
}

//3KEZDEN FAZLA ERTELEME OLURSA YONLENDÝRÝP SÝLDÝRME FONKSÝYONU
void yonlendir(int x, int y, int z, int t)
{

    int tut_1,tut_2,tut_3;

    tut_1 = x;
    tut_2 = y;
    tut_3 = z;



    struct node *indexdene = front;
    struct node *temp;


    // KUYRUK EÐER BOÞSA
    if(front==NULL)
    {
        printf("Kuyruk bos. \n");
        return 1;
    }

    while(indexdene->next != NULL && indexdene->next->talep_edilen_inis_saati != x && indexdene->next->oncelik_id != y && indexdene->next->ucak_id != z)
    {
        indexdene = indexdene->next->next;
    }
    if(indexdene->next == NULL)
    {
        //printf("Silmek istenilen deger bulunamadi.");
        //return 0;
    }

    temp = indexdene->next;
    indexdene->next = indexdene->next->next;
    free(temp);

    printf("Acil inis yapmasi gereken %d id'li ucak nedeniyle %d id'li ucagin inis izni iptal edilmistir, inis icin Sabiha Gokcen Havalimanina yonlendiriliyorsunuz.\n",t,z);

}
//KUYRUK EKLEME

void enqueue(int talep,int id,int ucak,int ertelenme)
{
    struct node *index = front;
    struct node1 *indexx=on;
    while(index != NULL)
    {
        index = index->next;
    }

     printf("\nInis izni talebiniz onaylanmistir..\n");

    // KUYRUK EÐER BOÞSA
    if(front==NULL && on==NULL)
    {


        struct node *new = (struct node *)malloc(sizeof(struct node));
        struct node1 *new1=(struct node1 *)malloc(sizeof(struct node1));
        if(ertelenme !=0)
        {
            new->ertelenme++;

        }
        else
        {
            new->ertelenme = 0;
        }
        new->ucak_id = ucak;
        new->talep_edilen_inis_saati = talep;
        new->oncelik_id = id;



        new1->oncelik_id=id;
        new1->ucak_id = ucak;
        new1->talep_edilen_inis_saati = talep;
        new1->gecikme_suresi=new->ertelenme;
        new1->inis_saati=new1->talep_edilen_inis_saati+(new1->gecikme_suresi);
        new1->kalkis_saati=new1->inis_saati+(1);



        new->next = NULL;
        new1->next = NULL;


        front = rear = new;
        on = arka = new1;
    }

    else
    {
        struct node *new = (struct node *)malloc(sizeof(struct node));
        struct node1 *new1 = (struct node1 *)malloc(sizeof(struct node1));
        if(ertelenme !=0)
        {
            new->ertelenme++;
        }
        else
        {
            new->ertelenme = 0;
        }
        new->ucak_id = ucak;
        new->talep_edilen_inis_saati = talep;
        new->oncelik_id = id;


        new1->oncelik_id=id;
        new1->ucak_id = ucak;
        new1->talep_edilen_inis_saati = talep;
        new1->gecikme_suresi=ertelenme;
        new1->inis_saati=new1->talep_edilen_inis_saati+ new1->gecikme_suresi;
        new1->kalkis_saati=new1->inis_saati+1;

        new->next = NULL;
        new1->next = NULL;


        rear->next = new;

        rear = new;

        arka->next = new1;

        arka = new1;
    }
}

//KUYRUKLARIN AYNI SAATE DENK GELMESÝ YÜKSEK ÖNCELÝK UCAK ID FARKLARI KONTROLLERÝNÝ BU FONKSÝYONDA YAPIYORUZ
int queue_control(int talep,int id,int ucak,int ertelenme)
{
    int loop_control = 0;
    int bos=0;
    int sayac=0;
    struct node *index = front;
    while(index != NULL)
    {
        sayac++;
        if(sayac==10)
        {
            printf("Maksimum inis sayisina ulasildi.\n");
            return 99;
        }

        if(index->talep_edilen_inis_saati == talep)
        {
            if(index->oncelik_id !=NULL && index->oncelik_id==id && index->ucak_id<ucak && ertelenme ==3)
            {
                printf("Inis talebiniz ucak ID farki nedeniyle reddedilmistir.\n");

                return 2;
            }
            if(index->oncelik_id !=NULL && index->oncelik_id==id && index->ucak_id<ucak && ertelenme ==2)
            {
                printf("Inis talebiniz ucak ID farki nedeniyle reddedilmistir.\n");
                ertelenme++;
                talep++;
                ertelenen(talep,id,ucak,ertelenme);
                return 3;
            }
            if(index->oncelik_id !=NULL && index->oncelik_id>id && index->ucak_id != ucak)
            {

                printf("Inis talebiniz yuksek oncelik nedeniyle onaylanmistir.\n");

                enqueue(talep,id,ucak,ertelenme);

                tut1 = index->talep_edilen_inis_saati;
                tut2 = index->oncelik_id;
                tut3 = index->ucak_id;
                tut4 = index->ertelenme;

                dequeue(tut1,tut2,tut3,tut4);
                ertelenen(tut1,tut2,tut3,tut4);





                return 2;
            }
            return 0;
        }
        index = index->next;
    }
    return 1;
}

//SATIR SATIR DOSYADAN OKUMA FONKSÝYONU KULLANICI ÇIKMAK ÝSTEYENE KADAR SONSUZ DÖNGÜDE

void inis_izni_iste()
{




    FILE *fs;

    char ch, buffer[32];
    int i = 0, arr[100], j = 0;

    fs = fopen("input.txt", "r");

    while(1)
    {
        ch = fgetc(fs);
        if(ch == EOF)
        {
            break;
        }
        else if(ch == ' ')
        {
            arr[j] = atoi(buffer);
            j++;
            bzero(buffer, 32);
            i = 0;
            continue;
        }
        else
        {
            buffer[i] = ch;
            i++;
        }
    }


    bool control = true;
    int basla=3;
    int control_2,control_3;
    int saat,oncelik,ucak,ertelenme=0;
    while(control)
    {
        printf("Inis izni istemek icin 0'a basiniz, cikmak icin 1'e basiniz: ");
        scanf("%d",&control_2);

        if(control_2 == 0)
        {
            printf("**%d",arr[basla+1]);
            oncelik = arr[basla];
            basla++;
            ucak = arr[basla];
            basla++;
            saat = arr[basla];
            basla++;
            ertelenme = 0;

            if(queue_control(saat,oncelik,ucak,ertelenme)==0)
            {

                ertelenen(saat,oncelik,ucak,ertelenme);


            }

            else if(queue_control(saat,oncelik,ucak,ertelenme)==1 && queue_control(saat,oncelik,ucak,ertelenme)!=2 && queue_control(saat,oncelik,ucak,ertelenme)!=3)
            {

                enqueue(saat,oncelik,ucak,ertelenme);

            }
            display();
            yazdir();
        }
        else
        {
            control = false;
        }





    }
}

//KALKIÞLARI DOSYAYA YAZDIRMA
void yazdir()
{
    int sayac=0;

    printf("Kalkis: \n");
    printf("Oncelik ID -- Ucak ID -- Talep Edilen Saat -- Inis Saati -- Gecikme Suresi -- Kalkis Saati");

    struct node1 *indexx = on;

    while(indexx != NULL)
    {
        sayac++;
        printf("\n         plane: %d - %d - %d - %d - %d - %d\t",indexx->oncelik_id,indexx->ucak_id,indexx->talep_edilen_inis_saati,indexx->inis_saati,indexx->gecikme_suresi,indexx->kalkis_saati);
        indexx = indexx->next;
    }

    printf("\n");

}

void display()
{
    int sayac=0;

    if(front == NULL)
    {
        printf("Kuyruk bos.");
        return 1;
    }

    printf("Inis: \n");
    printf("Oncelik ID -- Ucak ID -- Talep Edilen Saat");

    struct node *index = front;



    while(index != NULL)
    {
        sayac++;
        printf("\n         Ucak: %d - %d - %d\t",index->oncelik_id,index->ucak_id,index->talep_edilen_inis_saati);
        index = index->next;
    }

    printf("\n");

}

void output_write()
{
    FILE *out = fopen("output.txt","w");
    fprintf(out,"Oncelik ID -- Ucak ID -- Talep Edilen Saat -- Inis Saati -- Gecikme Suresi -- Kalkis Saati");
    struct node1 *indexx = on;


    while(indexx != NULL)
    {

        fprintf(out,"\nUcak: %d - %d - %d - %d - %d - %d",indexx->oncelik_id,indexx->ucak_id,indexx->talep_edilen_inis_saati,indexx->inis_saati,indexx->gecikme_suresi,indexx->kalkis_saati);
        indexx = indexx->next;
    }
}

int main()
{
    inis_izni_iste();
    output_write();


    return 0;
}
