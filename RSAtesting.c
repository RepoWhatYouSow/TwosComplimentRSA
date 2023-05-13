#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include <stdint.h>

/*
 * generated public and private keys with inputted primes
 * input: none, only command line user input
 * output: none, only commandline printed keys
 */
void generateKeys(void);

/*
 * checks if inputted value is prime or not
 * input: value to check
 * output: 1 if prime, 0 if not prime
 */
int isPrime(long long int val);

/*
 * finds a small odd number that does not share a factor with phi
 * input: phi
 * output: small integer value
 */
int findE(long long int phi);

/*
 * cycles through values of K until D is a whole number
 * given by the equation (1+K*phi)/e
 * input: e, phi
 * output: value of D for private key
 */
int findD(int e, long long int phi);

int encrypt(int val, int e, long long int N);
int decrypt(int val, int d, long long int N);
int main(void){

    //generateKeys();
    //printf("%d",encrypt(19,5,21));

    printf("%d",decrypt(10, 5, 21));

    return 0;
}

int stringLength(char message[]){
    int length;
    for(length = 0; message[length] != '\0'; length++);
    return length;
}

void generateKeys(void){
    long long int prime1,prime2,N,phi;
    int flag;
    int d;
    int e;

    while (1){
        printf("\nPlease enter the value of your first prime number:\n");
        scanf("%lld",&prime1);

        flag = isPrime(prime1);

        if (flag==1)
            break;
        else
            printf("Not a prime, try again!");
    }

    while (1){
        printf("\nPlease enter the value of your first prime number:\n");
        scanf("%lld",&prime2);

        flag = isPrime(prime2);

        if (flag==1 && prime2!=prime1)
            break;
        else
            printf("Not a prime, try again! Your value cannot match the first prime.");
    }

    N = prime1*prime2;

    phi = (prime2-1)*(prime1-1);

    e = findE(phi);

    d = findD(e,phi);

    printf("\nyour public key has the exponential:%5d\nAnd a N value of:%25lld\n",e,N);
    printf("This can be shared as:                  [%d,%lld]\n",e,N);
    printf("\nYour private key has the d value of: %4d\nAnd a N value of:%25lld\n",d,N);
    printf("This can be stored as:                  [%d,%lld]\n",d,N);


}

int isPrime(long long int val){

    int i;
    int j = sqrt(val);
    for(i = 2; i <= j; i++){
        if(val % i == 0)
            return 0;
    }
    return 1;
}

int findE(long long int n) {
    for (int e = 3; e < 50; e += 2) {
        if (n%e!=0 && isPrime(e)==1)
            return e;
    }
}

int findD(int e, long long int phi){
    int k = 0;
    while(1){
        if ((1+k*phi)%e==0)
            return (1+k*phi)/e;
        else
            k++;
    }

}
int encrypt( int val, int e, long long int N)
{
    long long int step1;
    int step2;
    step1 = pow((double)val,(double)e);
    step2 = (int)step1 % N;
    return step2;
}

int decrypt(int val, int d, long long int N)
{
    long long int step1;
    int step2;
    step1 = pow((double) val, (double) d);

	step2 = (int) step1 % N;
	return step2;
}
