#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{

int N=0,test=0;

printf("Input a number of equations: ");
test=scanf("%d",&N);
if(test)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
    for(int z=1;z<=N;z++)
    {
        char str [100]={0},sub [20]={0};
        int result,test, i ,j ,N,k=0,step=0,err=0,start=0, end=0, finished=0,opr[20]={0};
        float oprands[20]={0},wynik=0;
        printf("Input equation no.%i: ",z);
        result=scanf("%[^\n]",str);
        while ((c = getchar()) != '\n' && c != EOF) { }


        for(i=0;i<101;i++)
        {
            switch(step)
            {
             case 0:
                if(str[i]>47 && str[i]<58)
                {
                    end=i;
                }
                else if(str[i]==32)
                {
                    if (k>0)
                    {
                        if((str[i-1]<42 || str[i-1]>57)&&(str[i-1]==44 || str[i-1]==46))
                        {
                            err=1;
                            break;
                        }

                    }
                     for(j=0;j<=end-start;j++)
                    {
                        sub[j]=str[j+start];
                    }
                    oprands[k++]=atof(sub);

                    memset(sub,0,sizeof(sub));
                    step=1;
                }
                else if(str[i]==0)
                {
                    for(j=0;j<=end-start;j++)
                    {
                        sub[j]=str[j+start];
                    }
                    oprands[k]=atof(sub);

                    memset(sub,0,sizeof(sub));

                    finished=1;

                }
                else
                {
                    err=1;
                }
                break;
             case 1:

                switch(str[i])
                {
                case '+':
                    opr[k-1]=1;
                    step=2;
                    break;
                case '-':
                    opr[k-1]=2;
                    step=2;
                    break;
                case '/':
                    opr[k-1]=3;
                    step=2;
                    break;
                case '*':
                    opr[k-1]=4;
                    step=2;
                    break;
                default:
                    err=2;
                }
                break;
             case 2:
                 if(str[i]==32)
                 {
                    step=0;
                    start=i;
                }
                 else
                    err=3;
                 break;

             default:
                err=4;
                break;
            }

            if(finished || err)
                break;
        }

        if(!err)
        {
            if(k==0)
            {
                wynik=atof(str);
                printf("%s=%0.1f",str,wynik);
            }
            else
            {
                while(k>0)
                {
                    int priority=0;
                    float tp=0;
                    for(int x=0;x<=k;x++)
                    {
                        if(opr[x]==3 || opr[x]==4)
                        {
                            priority=x;
                            break;
                        }
                    }
                    switch(opr[priority])
                    {
                    case 1:
                        tp+=oprands[priority]+oprands[priority+1];
                        break;
                    case 2:
                        tp+=oprands[priority]-oprands[priority+1];
                        break;
                    case 3:
                        tp+=oprands[priority]/oprands[priority+1];
                        break;
                    case 4:
                        tp+=oprands[priority]*oprands[priority+1];
                        break;
                    default:
                        err=5;
                        break;
                    }
                    if(!err)
                    {
                        oprands[priority]=tp;
                        for(int y=priority+1;y<=k;y++)
                        {
                            oprands[y]=oprands[y+1];
                            opr[y-1]=opr[y];
                        }

                        k--;
                    }
                    else
                        break;
                }
                if(!err)
                {
                    wynik=oprands[0];


                }
            }

        }

        switch(err)
        {
        case 0:
            printf("%s = %0.1f\n",str,wynik);
            break;
        case 1:
            printf("Unexpected character when a digit was expected\n");
            break;
        case 2:
            printf("Unexpected operator\n");
            break;
        case 3:
            printf("After operator there should be a single space\n");
            break;
        case 4:
            printf("Something unexpected happened while checking the equation\n");
            break;
        case 5:
            printf("Something unexpected happened while evaluating the equation\n");
            break;
        default:
            printf("Something unaccounted for happened\n");
            break;
        }
    }
}
else("Input is not an integer");
return 0;
}
