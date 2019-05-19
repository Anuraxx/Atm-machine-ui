        struct peoples
        {
            char name[20];
            long long cd;
            int pin;
            long balance;
        };
        struct peoples peo;
        int fpsiz=sizeof(peo);

    int search_rec(long long card_no, int p,FILE *fp)
    {
    //    fp = fopen("atmdb.DAT","rb+");
        rewind(fp);
        if(fp!=NULL)
        {
            if(fread(&peo,fpsiz,1,fp)!=EOF)
            {  //printf("inside search");
                while(fread(&peo,fpsiz,1,fp)==1)
                {
                    if(peo.cd == card_no)
                   {
                        if(peo.pin == p)
                        {
                            printf("Hello! %s\n",peo.name);
                            return peo.balance;
                        }
                   }
               }
               add_rec(card_no,p,fp);
            }
            else
            {
                return peo.balance = add_rec(card_no,p,fp);
            }
        }
        else printf("SORRY!! server busy at the moment\n");
    }

    int add_rec(long long card_no,int p,FILE *fp)
    {
        fseek(fp,0,SEEK_END);
        printf("Enter your name:\n\t\t\t\t  ");
        scanf("%s",peo.name);
        peo.cd=card_no;
        peo.pin=p;
        peo.balance=0;
        fwrite(&peo,fpsiz,1,fp);
        return peo.balance;
    }

    int pin_change(long long card_no,int cp,FILE *fp)
    {
    //    fp = fopen("atmdb.DAT","rb+");
        rewind(fp);
        if(fp!=NULL)
        {
            if(fread(&peo,fpsiz,1,fp)!=EOF)
            {
                while(fread(&peo,fpsiz,1,fp)==1)
               {  //printf("inside while");
                   if(peo.cd == card_no)
                   {
                        peo.pin=cp;
                        fseek(fp,-fpsiz,SEEK_CUR);
                        fwrite(&peo,fpsiz,1,fp);
                        return peo.pin;
                   }
               }
            }
        }
        else printf("SORRY!! server busy at the moment\n");
    }

    void depo_bal(long long card_no,int p,long bal,FILE *fp)
    {
    //    fp = fopen("atmdb.DAT","rb+");
        rewind(fp);
        if(fp!=NULL)
        {
            if(fread(&peo,fpsiz,1,fp)!=EOF)
            {
                while(fread(&peo,fpsiz,1,fp)==1)
               {  //printf("inside while");
                   if(peo.cd == card_no)
                   {
                        strcpy(peo.name,peo.name);
                        peo.balance=bal;
                        fseek(fp,-fpsiz,SEEK_CUR);
                        fwrite(&peo,fpsiz,1,fp);
                        return ;
                   }
               }
            }
        }
        else printf("SORRY!! server busy at the moment\n");
    }

    void list_all(FILE *fp)
    {
        rewind(fp);
        while(fread(&peo,sizeof(peo),1,fp)==1)
        {
            printf("%s      %lli    %d      %ld\n",peo.name,peo.cd,peo.pin,peo.balance);
        }
    }
