// Algorithm:
// 1. It uses a stack and an input buffer. 
// 2. Insert $ at the bottom of the stack and the right end of the input string in Input Buffer. 
// 3. Shift: Parser shifts zero or more input symbols onto the stack until the handle is on top of the stack. 
// 4. Reduce: Parser reduce or replace the handle on top of the stack to the left side of production, i.e., R.H.S. of production is popped, and L.H.S is pushed. 
// 5. Accept: Step 3 and Step 4 will be repeated until it has identified an error or until the stack includes start symbol (S) and input Buffer is empty, i.e., it contains $. 
// 6. Error: Signal discovery of a syntax error that has appeared and calls an error recovery routine

#include<conio.h>
#include<string.h>
#include<iostream>
using namespace std;
struct grammer{
    char p[20];
    char prod[20];
}g[10];
 
int main()
{
    int i,stpos,j,k,l,m,o,p,f,r;
    int np,tspos,cr;
 
    cout<<"\nEnter Number of productions:";
    cin>>np;
 
    char sc,ts[10];
 
    cout<<"\nEnter productions:\n";
    for(i=0;i<np;i++)
    {
        cin>>ts;
        strncpy(g[i].p,ts,1);
        strcpy(g[i].prod,&ts[3]);
    }
 
    char ip[10];
 
    cout<<"\nEnter Input:";
    cin>>ip;
 
    int lip=strlen(ip);
 
    char stack[10];
     
    stpos=0;
    i=0;
     
    sc=ip[i];
    stack[stpos]=sc;
    i++;stpos++;
 
    cout<<"\n\nStack\tInput\tAction";
    do
    {
        r=1;
        while(r!=0)
        {
            cout<<"\n";
            for(p=0;p<stpos;p++)
            {
                cout<<stack[p];
            }
            cout<<"\t";
            for(p=i;p<lip;p++)
            {
                cout<<ip[p];
            }
 
            if(r==2)
            {
                cout<<"\tReduced";
            }
            else
            {
                cout<<"\tShifted";
            }
            r=0;
             

            getch();
            for(k=0;k<stpos;k++)
            {
                f=0;
 
                for(l=0;l<10;l++)
                {
                    ts[l]='\0';
                }
 
                tspos=0;
                for(l=k;l<stpos;l++) 
                {
                    ts[tspos]=stack[l];
                    tspos++;
                }
 
              
                for(m=0;m<np;m++)
                {
                    cr = strcmp(ts,g[m].prod);
 
                    if(cr==0)
                    {
                        for(l=k;l<10;l++) 
                        {
                            stack[l]='\0';
                            stpos--;
                        }
 
                        stpos=k;
         
                        strcat(stack,g[m].p);
                        stpos++;
                        r=2;
                    }
                }
            }
        }
         
        sc=ip[i];
        stack[stpos]=sc;
        i++;stpos++;
 
    }while(strlen(stack)!=1 && stpos!=lip);
 
    if(strlen(stack)==1)
    {
        cout<<"\n String Accepted";
    }
 
    getch();
    return 0; 
}
