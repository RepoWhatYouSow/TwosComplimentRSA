#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

#define COMPLIMENT_SHIFT 110

int twosEncrypt(int num, int bin);
int twosDecrypt(int num, int bin);

int main(void) 
{
	int counter = 0;
    int bin[] = {0,1,0,1,1,0,1,0};

    char message[20] = "zzAA..,,??  aaZZttnn";
	for (int i = 0; i <20; ++i)
	{
		printf("%d ",message[i]);
	}
	printf("\n");
    int newNums[20];
    for (int i = 0; i <20; ++i)
    {
	newNums[i] = twosEncrypt(message[i],bin[counter]);
	printf("%d ",twosEncrypt(message[i],bin[counter]));
        counter = (counter + 1) % 8;
    }
    printf("\n");
	counter = 0;

    counter = 0;
	printf("\n");
    for (int i = 0; i <20; ++i) {
        printf("%c ",twosDecrypt(newNums[i],bin[counter]));
        counter = (counter + 1) % 8;
    }

    return 0;
}
int twosEncrypt(int num, int bin)
{
    num*=-1;

    if (bin == 0)
        return num *= -1;

    else if (bin==1)
        return ((uint8_t) num) - COMPLIMENT_SHIFT;

}

int twosDecrypt(int num, int bin)
{
    num *= -1;
    if(bin == 0)
        return num*=-1;

    else if (bin ==1)
        return (uint8_t) (num - COMPLIMENT_SHIFT);

}

