#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<string.h>
#include<math.h>
#include <unistd.h>

#ifdef __unix__
# include <unistd.h>
#elif defined _WIN32
# include <windows.h>
#define sleep(x) Sleep(1000 * x)
#endif

struct record{
    int id;
    char first_name[50];
    char last_name[50];
    char friendslist[1000];
   }person[200];
   FILE *people;
   void Dizi_Okuma();
   void CreateBst(int *,int,int,int *,int);
   void WriteBst(int *,int);
   void ReadDatabase();
   void insertNewUser(int *,int);
   void DeleteUser(int);

   int main()
   {
    setlocale(LC_ALL, "Turkish");
                    //Dizi_Okuma();//LAB 2 ==> 1.PROJEYÝ ÇALIÞTIRIR.
                    ReadDatabase();//LAB2 ==>2.PROJEYÝ ÇALIÞTIRIR.
                   return 0;
   }



   void Dizi_Okuma(){
        FILE *dosya;
            if((dosya=fopen("input1.txt","r"))!=NULL){
                printf("Dosya Açýldý.\n Okunan Dizi:");
                    int i=0;
                    int *numberArray;
                    int *BstArray;
                    int elemansayisi=1;
                    numberArray=(int *)malloc(elemansayisi*sizeof(int));
                        do{
                            fscanf(dosya,"%d,",&numberArray[i]);
                            elemansayisi++;
                            numberArray=realloc(numberArray,sizeof(int)*elemansayisi);
                            i++;
                        }while(!feof(dosya));
                        elemansayisi--;

                        for(i=0;i<elemansayisi;i++){
                            printf("%d ",numberArray[i]);
                        }
                        fclose(dosya);
            //Text dosyasýndaki elemanlar alýndý ve dosya kapatýldý.

                        BstArray=(int *)malloc((elemansayisi*2)*sizeof(int));
                        int start=0;
                        int end=elemansayisi-1;
                        int x=1;
                        CreateBst(numberArray,start,end,BstArray,x);
                        printf("\n Binary Search Tree Array:");
                            for(i=0;i<elemansayisi*2;i++){
                                if(BstArray[i]!=0){
                                       printf("%d ",BstArray[i]);
                                }/*else{
                                       printf("- 1");

                                }*/
                            }
                            printf("\n Binary Search Tree Gösterimi: \n");
                                WriteBst(BstArray,elemansayisi);
                   }
                   else{
                        printf("dosya açýlamadý.");
                        exit(0);
                   }

   }

   void CreateBst(int *numberArray,int start,int end,int  *BstArray,int x){
        int mid=(start+end)/2;
            if(start <= end){
                BstArray[x-1]= numberArray[mid];
                CreateBst(numberArray,start,mid-1,BstArray,2*x);
                CreateBst(numberArray,mid+1,end,BstArray,2*x+1)   ;
            }
    }



   void WriteBst(int *BstArray,int elemansayisi){
        int n=1,i;
            while(n<elemansayisi+1){
                for(i=n;i<n*2;i++){
                    printf("%5s%d","  "   ,BstArray[i-1]);
                 }
                printf("\n");
                n=n*2;
            }
   }

   void ReadDatabase(){
    people=fopen("input2.txt","r");
    char temp[512];char *pch;
    int find_result=0;
    int i=0;
    while(fgets(temp,512,people)!=NULL){
            pch=strtok(temp," ,-");
            int say=0;
            int id;
                while(pch!=NULL){
                    if(say==0){
                        id= atoi(pch);
                        person[i].id=id;
                    }
                    else if(say==1){
                        strcpy(person[i].first_name,pch);
                    }
                    else if(say==2){
                        strcpy(person[i].last_name,pch);
                    }
                    else if(say>=3){
                        strcpy(person[i].friendslist,pch);
                    }
                    say++;
                    pch=strtok(NULL," ,");

                }
                i++;
   }

    int y=0;
    int *numberArray;
    int *BstArray;
    int elemansayisi=i;
    numberArray=(int*)malloc(elemansayisi*sizeof(int));

        for(y=0;y<i;y++){
            numberArray[y]=person[y].id;
        }
               //Diziyi sýralama iþlemi
       int min,temp1,j;
        for(i=0;i<y;i++){
            min=numberArray[i];
		for(j=i+1;j<y;j++){
			if(numberArray[j]<min){
				min=numberArray[j];
				temp1=numberArray[i];
				numberArray[i]=min;
				numberArray[j]=temp1;
			}
		}
	}

    BstArray=(int *)malloc(( elemansayisi*2)*sizeof(int));
    int start=0;
    int end=elemansayisi-1;
    int x=1;
    CreateBst(numberArray,start,end,BstArray,x);
    printf("Dosya Açýldý. \n  Okunan Kimlik Nolarý:");
        for(i=0;i<elemansayisi;i++){
            printf("%d ",numberArray[i]);
        }

        printf("\n Binary Search Tree Array:");
                            for(i=0;i<elemansayisi*2;i++){
                                if(BstArray[i]!=0){
                                       printf("%d ",BstArray[i]);
                                }
                            }
                            printf("\n Binary Search Tree Gösterimi: \n");
                            WriteBst(BstArray,elemansayisi);

                                   int secim=0;

                                   printf("Yeni kiþi eklemek için  1'e  basýnýz:");
                                   printf("\nKiþi silmek için  2'ye  basýnýz:");
                                   printf("\nKiþi bulmak için  3'e  basýnýz:");
                                   printf("\nFriends için  4'e  basýnýz:");
                                   printf("\nSize için  5'e  basýnýz:");
                                   printf("\nPrintNext  6'e  basýnýz:");
                                   printf("\nprintGreater için  7'e  basýnýz:");
                                   printf("\nprintInOrder için  8'e  basýnýz:");
                                   scanf("%d",&secim);
                                   if(secim==1){
                                        insertNewUser(numberArray,y);
                                        sleep(2);
                                        system("CLS");
                                        ReadDatabase();
                                   }
                                   else if(secim==2){
                                        int sil=0,kontrol=0,id_tut=0;
                                        printf("silmek için id giriniz:");
                                        scanf("%d",&sil);
                                            for(y=0;y<i;y++){
                                               if(person[y].id==sil){
                                                kontrol=1;
                                                id_tut=y;
                                            }
                                        }
                                        if(kontrol==1){
                                            printf("KÝÞÝ BULUNDU..");
                                            DeleteUser(id_tut);
                                        }else{
                                        printf("KÝÞÝ BULUNAMADI...");
                                        }
                                        //sleep(2);
                                       // system("CLS");
                                        //ReadDatabase();

                                   }
                                   else if(secim==3){
                                        int bul=0,kontrol=0,id_tut=0;
                                        printf("bulmak için id giriniz:");
                                        scanf("%d",&bul);
                                            for(y=0;y<i;y++){
                                               if(person[y].id==bul){
                                                kontrol=1;
                                                id_tut=y;
                                            }
                                        }
                                        if(kontrol==1){
                                            printf("KÝÞÝ BULUNDU..");
                                            printf("\n %d %s %s",person[id_tut].id,person[id_tut].first_name,person[id_tut].last_name);
                                        }else{
                                        printf("KÝÞÝ BULUNAMADI...");
                                        }
                                        sleep(5);
                                            system("CLS");
                                            ReadDatabase();
                                   }else if(secim==4){
                                        printf("Friends");
                                   }else if(secim==5){
                                         printf("size=%d",y);
                                         sleep(5);
                                            system("CLS");
                                            ReadDatabase();
                                   }else if(secim==6){
                                         printf("PrintNext");
                                   }
                                   else if(secim==7){
                                        int bul=0,kontrol=0,id_tut=0;
                                        printf("Greater için id giriniz:");
                                        scanf("%d",&bul);
                                            for(y=0;y<i;y++){
                                               if(person[y].id==bul){
                                                kontrol=1;
                                                id_tut=y;
                                            }
                                        }
                                        if(kontrol==1){
                                            printf("Girdiðiniz id den büyük olanlar..");

                                            for(y=0;y<i;y++){
                                               if(person[y].id>bul){
                                                     printf("\n %d %s %s",person[y].id,person[y].first_name,person[y].last_name);
                                                }
                                            }

                                        }else{
                                        printf("KÝÞÝ BULUNAMADI...");
                                        }
                                        sleep(7);
                                        system("CLS");
                                        ReadDatabase();
                                   }
                                   else if(secim==8){
                                         printf("\n printInOrder");
                                         int t=0;
                                         int x=y;
                                         while(t<x){
                                            for(y=0;y<i;y++){
                                               if(person[y].id==numberArray[t]){
                                                     printf("\n %d %s %s",person[y].id,person[y].first_name,person[y].last_name);
                                                }
                                            }
                                            t++;
                                         }
                                   }
                                   else{
                                        printf("hatalý giriþ..");
                                   }

   fclose(people);
   }



   void insertNewUser(int *numberArray,int y){
                   int id;
                   char first_name[50];
                   char last_name[50];
                   char friendslist[1000];
                   y=y+1;
                   //numberArray=(int *)malloc(y*sizeof(int));
                    printf("id giriniz:");
                    scanf("%d",&id);
                    int i=0;
                    int kontrol=0;
                    do{

                        kontrol=0;
                         for(i=0;i<y;i++){
                            if(numberArray[i]==id){
                            kontrol=1;
                            }
                        }
                            if(kontrol==1){
                            printf("girdiðiniz id zaten mevcut..Lütfen baþka bir id giriniz:");
                            scanf("%d",&id);
                            }

                    }while(kontrol==1);

                    printf("ad giriniz:");
                    scanf("%s",first_name);
                    printf("soyad giriniz:");
                    scanf("%s",last_name);
                    printf("arkadaþ listesini giriniz:");
                    scanf("%s",friendslist);



                   person[y].id=id;
                   strcpy(person[y].first_name,first_name);
                   strcpy(person[y].last_name,last_name);
                   strcpy(person[y].friendslist,friendslist);

                   printf("%d   ",person[y].id);
                   printf("%s   ",person[y].first_name);
                   printf("%s   ",person[y].last_name);
                   printf("%s\n",person[y].friendslist);



   printf("eleman structa eklendi...");

                    FILE *fp;
                    fp=fopen("input2.txt","a");
                    if(fp==NULL)
                   {
                        printf("dosya açýlamadý.");
                        exit(0);
                   }



                fprintf(fp,"%d,%s %s,%s\n",id,first_name,last_name,friendslist);
                fclose(fp);
   }

   void DeleteUser(int id_tut){
           FILE *fp1, *fp2;
        char c;
        int del_line, temp = 1;
        //open file in read mode
        fp1 = fopen("input2.txt", "r");
        c = getc(fp1);
        //until the last character of file is obtained
        while (fgets(temp,512,people)!=NULL)
        {
          printf("%c", c);
          //print current character and read next character
          c = getc(fp1);
        }
        //rewind
        rewind(fp1);
        del_line=id_tut;
                //open new file in write mode
        fp2 = fopen("copy.txt", "w");
        c = getc(fp1);
        while (c != EOF) {
          c = getc(fp1);
          if (c == '\n')
          temp++;
          //except the line to be deleted
          if (temp != del_line)
          {
            //copy all lines in file copy.c
            putc(c, fp2);
          }
        }
        //close both the files.
        fclose(fp1);
        fclose(fp2);
        //remove original file
        remove("input2.txt");
        //rename the file copy.c to original name
        rename("copy.txt", "input2.txt");
        printf("\n The contents of file after being modified are as  follows:\n");
        fp1 = fopen("input2.txt", "r");
        c = getc(fp1);
        while (c != EOF) {
            printf("%c", c);
            c = getc(fp1);
        }
        fclose(fp1);
}









