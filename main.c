
/***   
  *	author: Anurag Yadav   
  *     created: 02.06.2016
  *
  *
***/

#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include"atmDB.h"

int search_rec(long long,int,FILE*);
int add_rec(long long,int,FILE*);
int pin_change(long long,int,FILE*);
void depo_bal(long long,int,long,FILE*);

void main()
{
    char n,t,C,buff[50],R,w;
    time_t now = time (0) ;
    int p=0,pin=0,cp=0,m,i=0,b,temp_pin=0,  p[4],cd[16] ;
    unsigned long long card_no=0,bal=0,a ;
    unsigned long dep;

    FILE *fp;
    fp = fopen("atmdb.DAT","rb+");

    printf ("*****************************| WELCOME TO BHARAT BANK |*******************************") ;
    printf("\n\n\t\t\t      Please Insert your card\n") ;
y:  printf ("\n\n\t\t\t\tEnter your card no.\n\t\t\t\t") ;
   // scanf("%lli",&card_no);
    while (i < 16)
    {
        b = getch() ;
        if(b>47 && b<58)       // input not shown on the console
        {
            card_no = (card_no * 10) + (b - 48) ;
            i++ ;
            printf("%d",b-48);
        }
    }
    if(card_no < pow(10,15) || card_no > 9999999999999999)
    {
        printf ("\n\n\t\t\t\t INVALID CARD No.") ;
        goto y;
    }
inv:printf ("\n\n\t\t\t\t  Enter your PIN\n\t\t\t\t      ") ;
    i=0;
    while (i < 4)
    {

        b = getch() ;
        if(b>47 && b<58)       // input not shown on the console
        {
            p = (p * 10) + (b - 48) ;
            printf("*") ;
            i++ ;
        }
    }
    printf("pin  %d",p);
    printf("\n\n\t\t\t\t ");
    i = 0 ;
    if (p < 1000 || p > 9999)
    {
        printf ("\n\n\t\t\t\t   INVALID PIN\n") ;
        goto inv ;
    }
    bal = search_rec(card_no,p,fp);

    printf ("\n\n\t\t\t\t CARD INSERTED!!\n\n\n") ;
x:  printf ("1. WITHDRAW\t\t\t\t\t\t    2. CHANGE PIN\n\n3. MINISTATEMENT\t\t\t\t\t    4. ACOUNT BALANCE\n\n5. DEPOSITE\n\n");
    n = getch();
    switch (n)
    {
        case '1':
            pin=0;
            printf ("\n\t\t\t\t\t\t\t\t1. SAVING\n\n\t\t\t\t\t\t\t\t2. CURRENT\n");
            w = getch();
            if(w == '1')
            {
                printf ("\t\t\t\tENTER YOUR PIN\n\t\t\t\t    ") ;
                i=0;
                while(i < 4)
                {
                    b = getch() ;
                    if(b>47 && b<58)
                    {
                      pin = (pin*10) + (b-48) ;
                      printf ("*");
                      i++;
                    }
                }
                printf("pin  %d  p %d",pin,p);
                if(pin == p)
                {
                    printf ("\n\t\t\t\tEnter your amount\n\n\t\t\t\t") ;
                    scanf ("%lli", &a) ;
                    if(a <= bal)
                    {
                        fflush (stdin) ;
                        printf ("\n\n\t\t  PLEASE WAIT WHILE YOUR TRANSACTION IS PROCEEDING...\n\n");
                        scanf ("%c",&t) ;
                        fflush (stdin) ;
                        printf ("\t\t\t\tCOLLECT YOUR CASH\n") ;
                        scanf ("%c",&m) ;
                        printf ("\n\t\t\t Do you want to print the recipt ?\n\n\n\t\t\t\t\t\t\t\t\t1. YES\n\n\t\t\t\t\t\t\t\t\t2. NO");
                        R = getch();
                        if(R == '1')
                            printf ("\n\n\t\t\t    THANK YOU! VISIT AGAIN") ;
                        if(R == '2')
                            printf ("\n\n\t\t\t    THANK YOU! VISIT AGAIN") ;
                        bal = bal-a;
                        depo_bal(card_no,p,bal,fp);
                    }
                    else
                        printf("\n\n\t\t\tSORRY, INSUFFICIENT BALANCE!!") ;
                }
                else
                    printf ("\n\t\t\t  oops!! ENTERED PIN IS WRONG") ;
                fflush (stdin) ;
                printf ("\n\n\t\t\tDo you want to continue ? [y/n]  ") ;
                C = getch();
                printf ("\n\n") ;
                if(C == 'y')
                    goto x;
                else
                    printf ("\n\n\t\t\t     THANK YOU! VISIT AGAIN") ;
            }
            if(w == '2')
            {
                printf("\t\t\t\tENTER YOUR PIN\n\t\t\t\t    ");
                i=0;
                while(i < 4)
                {
                    b = getch();
                    if(b>47 && b<58)
                    {
                        pin = (pin*10) + (b-48);
                        printf ("*") ;
                        i++;
                    }
                }
                if(pin == p)
                {
                    printf ("\n\t\t\t\tEnter your amount\n\n\t\t\t\t") ;
                    scanf("%lli",&a) ;
                    if(a <= bal)
                    {
                        fflush (stdin) ;
                        printf ("\n\n\t\t  PLEASE WAIT WHILE YOUR TRANSACTION IS PROCEEDING...\n\n") ;
                        scanf ("%c",&t) ;
                        fflush (stdin) ;
                        printf ("\t\t\t\tCOLLECT YOUR CASH\n") ;
                        scanf ("%c",&m) ;
                        printf ("\n\t\t\t Do you want to print the recipt ?\n\n\n\t\t\t\t\t\t\t\t\t1. YES\n\n\t\t\t\t\t\t\t\t\t2. NO");
                        R = getch();
                        if(R == '1')
                            printf ("\n\n\t\t\t    THANK YOU! VISIT AGAIN") ;
                        if(R == '2')
                            printf ("\n\n\t\t\t    THANK YOU! VISIT AGAIN") ;
                        bal = bal-a;
                        depo_bal(card_no,p,bal,fp);
                    }
                    else
                        printf ("\n\n\t\t\tSORRY, INSUFFICIENT BALANCE!!") ;
                }
                else
                    printf ("\n\t\t\t  oops!! ENTERED PIN IS WRONG") ;
                fflush (stdin) ;
                printf ("\n\n\t\t\tDo you want to continue ? [y/n]  ") ;
                C = getch();
                printf ("\n\n") ;
                if(C == 'y')
                    goto x;
                else
                    printf("\n\n\t\t\t     THANK YOU! VISIT AGAIN") ;
            }
        break ;

        case '2':                  //  case 2   pin change
            pin=0 ;
            printf ("\t\t\t      ENTER YOUR COURRENT PIN\n\t\t\t\t    ") ;
            i=0;
            while(i < 4)
            {
                b = getch();
                if(b>47 && b<58)
                {
                    pin = (pin*10) + (b-48);
                    printf ("*") ;
                    i++;
                }
            }
            if (pin == p)
            {
                printf("\n\n\t\t\t\t ENTER NEW PIN\n\t\t\t\t  ");
                i=0;
                while(i < 4)
                {
                    b = getch();
                    if(b>47 && b<58)
                    {
                        temp_pin = (temp_pin*10) + (b-48);
                        printf ("*") ;
                        i++;
                    }
                }
                printf ("\n\n\t\t\t\tCONFIRM NEW PIN\n\t\t\t\t   ") ;
                i=0;
                while(i < 4)
                {
                    b = getch();
                    if(b>47 && b<58)
                    {
                        cp = (cp*10) + (b-48);
                        printf ("*") ;
                        i++;
                    }
                }
                if(temp_pin == cp)
                {
                    p=pin_change(card_no,cp,fp);
                    printf ("\n\n\t\t\tYOUR PIN IS CHANGED SUCCESSFULLY!!") ;
                    printf ("\n\n\t\t\t   THANK YOU! VISIT AGAIN") ;
                }
                else
                    printf ("\n\n\t\t\tSORRY,PIN didn't matched.TRY AGAIN\n\n\t\t\t\t  THANK YOU");
            }
            else
                printf ("\n\t\t\t  oops!! ENTERED PIN IS WRONG") ;
            printf ("\n\n\t\t\tDo you want to continue ? [y/n]  ") ;
            C = getch();
            printf ("\n\n") ;
            if(C == 'y')
                goto x;
            else
                printf ("\n\n\t\t\t     THANK YOU! VISIT AGAIN") ;
        break;
        case '3':               // case 3 mini state
            pin=0;
            printf ("\n\t\t\t\tENTER YOUR PIN\n\t\t\t\t    ") ;
            i=0;
            while(i < 4)
            {
                b = getch();
                if(b>47 && b<58)
                {
                    pin = (pin*10) + (b-48);
                    printf("*") ;
                    i++;
                }
            }
            if (pin == p)
            {
                if(bal > 0)
                    bal=bal-5;
                printf ("\n     BHARAT BANK\n\n") ;
                strftime (buff, 50, "DATE:%d-%m-%Y  TIME %H:%M:%S", localtime (&now)) ;
                printf ("%s\n", buff);
                printf ("\nCard no.:%lli\nService tax: Rs 5\nAvailable balance: Rs %lli",card_no,bal);
                printf ("\n\n\n\t\t\t   THANK YOU! VISIT AGAIN") ;
            }
            else
                printf ("\n\t\t\t  oops!! ENTERED PIN IS WRONG") ;
            fflush(stdin);
            printf ("\n\n\t\t\tDo you want to continue ? [y/n]  ") ;
            C = getch();
            printf ("\n\n") ;
            if(C == 'y')
                goto x;
            else
                printf ("\n\n\t\t\t     THANK YOU! VISIT AGAIN") ;
        break ;
        case '4':                 //  case 4    aval bal
            pin=0;
            printf("\n\t\t\t\tENTER YOUR PIN\n\t\t\t\t    ");
            i=0;
            while(i < 4)
            {
                b = getch();
                if(b>47 && b<58)
                {
                    pin = (pin*10)+(b-48);
                    printf ("*") ;
                    i++;
                }
            }
            if (pin==p)
                printf("\n\n\t\t\tyour available balance is : Rs %lli",bal);
                else
                    printf ("\n\t\t\t  oops!! ENTERED PIN IS WRONG") ;
            fflush(stdin);
            printf ("\n\n\t\t\tDo you want to continue ? [y/n]  ") ;
            C = getch();
            printf ("\n\n") ;
            if(C == 'y')
                goto x;
            else
                //printf ("\n\t\t\t  oops!! ENTERED PIN IS WRONG") ;
            printf ("\n\n\t\t\t     THANK YOU! VISIT AGAIN") ;
        break;
        case '5':                   //case 5   deposite
            pin=0;
            printf("\n\t\t\t\tENTER YOUR PIN\n\t\t\t\t    ");
            i=0;
            while(i < 4)
            {
                b = getch();
                if(b>47 && b<58)
                {
                    pin = (pin*10)+(b-48);
                    printf ("*") ;
                    i++;
                }
            }
            if (pin == p)
            {
                printf ("\n\n\t\t\t   Current Balance= Rs %lu\n\n",bal) ;
                printf ("\t\t\t   Enter your amount to deposite\n\t\t\t\t") ;
                scanf ("%lu",&dep);
                bal+= dep;
                depo_bal(card_no,p,bal,fp);
                printf ("\n\n\t\t\tAMOUNT DEPOSITED SUCCESSFULLY!!") ;
            }
            else
                printf ("\n\t\t\t  oops!! ENTERED PIN IS WRONG") ;
            fflush(stdin);
            printf ("\n\n\t\t\tDo you want to continue ? [y/n]  ") ;
            C = getch();
            printf ("\n\n") ;
            if(C == 'y')
                goto x;
            if (C == 'n')
                printf("\n\n\t\t\t   THANK YOU! VISIT AGAIN\n");
        break ;

    /*    case '6':
            list_all(fp);
             printf ("\n\n\t\t\tDo you want to continue ? [y/n]  ") ;
            C = getch();
            printf ("\n\n") ;
            if(C == 'y')
                goto x;
            if (C == 'n')
                printf("\n\n\t\t\t   THANK YOU! VISIT AGAIN\n");
            break;
    */
        default:
            printf ("\n\n\t\t\t   THANK YOU! VISIT AGAIN\n") ;
    }
    fclose(fp);
}

