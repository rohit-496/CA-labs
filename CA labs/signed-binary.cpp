#include <stdio.h>
#include <stdlib.h>

int B, Q;
int M[4]={0}, Qr[4]={0};
int ACC[4]={0};
int carry=0, SC=4;

void toBinary(int n, int arr[])
{
    int i;
    n = abs(n);

    for(i=0;i<4;i++)
    {
        arr[i] = n % 2;
        n = n / 2;
    }
}

void display(int arr[])
{
    int i;
    for(i=3;i>=0;i--)
        printf("%d",arr[i]);
}

void add()
{
    int i,sum;

    carry=0;

    for(i=0;i<4;i++)
    {
        sum = ACC[i] + M[i] + carry;
        ACC[i] = sum % 2;
        carry = sum / 2;
    }
}

void rightShift()
{
    int i,temp;

    temp = ACC[0];

    for(i=0;i<3;i++)
        ACC[i] = ACC[i+1];

    ACC[3] = carry;
    carry = 0;

    for(i=0;i<3;i++)
        Qr[i] = Qr[i+1];

    Qr[3] = temp;
}

int main()
{
    int i;

    printf("\nSIGNED MAGNITUDE MULTIPLICATION (4-bit)\n");

    do
    {
        printf("\nEnter B (-15 to 15): ");
        scanf("%d",&B);

        printf("Enter Q (-15 to 15): ");
        scanf("%d",&Q);

    }while(abs(B)>=16 || abs(Q)>=16);

    printf("\nExpected Product = %d\n",B*Q);

    toBinary(B,M);
    toBinary(Q,Qr);

    printf("\nB = ");
    display(M);

    printf("\nQ = ");
    display(Qr);

    printf("\n");

    while(SC>0)
    {
        printf("\nSC = %d",SC);

        if(Qr[0]==1)
        {
            printf("\nQ0=1 → ADD B");
            add();
        }
        else
            printf("\nQ0=0 → No Addition");

        printf("\nACC = ");
        display(ACC);

        printf("  Q = ");
        display(Qr);

        rightShift();

        printf("\nAfter Shift → ");

        printf("ACC = ");
        display(ACC);

        printf("  Q = ");
        display(Qr);

        printf("\n");

        SC--;
    }

    printf("\nFinal Product (Binary) = ");

    display(ACC);
    display(Qr);

    printf("\n");

    return 0;
}