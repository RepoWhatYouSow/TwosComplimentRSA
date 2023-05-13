#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "string.h"
#include <stdint.h>

#define MAX_MESSAGE 50
#define COMPLIMENT_SHIFT 110


/*
 * repeatedly prompts the user for a single numerical entry and returns it
 * Param - name - string of the same of the value to prompt the user for
 */
int getNumber(char name[]);

/*
 * Takes in an array, size of that array, and a number to convert it to binary
 */
void numToBin(int arr[], int size,int num);

/*
 * gets user input on the choice between generation, encryption and decryption
 */
int choice();

/*
 * prompts user to restart the program or quit
 */
int replay();

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

int encrypt( int val, int e, long long int N);

int decrypt(int val, int d, long long int N);

int buffer(int num, int bin);

int debuffer(int num, int bin);

int main(void)
{
	int option;
	int on = 1;

	while(on == 1)
	{
		option = choice();

		if (option == 1)
		{
			generateKeys();
			on = replay();
		}
		else if (option == 2)
		{
			char message[MAX_MESSAGE];
			int size,e;
			long long int N;


			printf("\nPlease enter the message you want to encrypt:\n");

			fflush (stdin);

			fgets(message,MAX_MESSAGE,stdin);

			size = strlen(message);

			printf("\nNext enter your public key\n");
			N = getNumber("N");
			e = getNumber("e");

			srand(time(NULL));

			//uses 4 bit binary due to bit limitations with exponentials
			int number = (rand() % 14)+1;

			int binary[4];

			numToBin(binary,4,number);

			int encrypted[size];

			encrypted[0] = encrypt(number,e,N);
			int counter = 0;
			for (int pos = 1; pos < size ; ++pos)
			{
				//shifted message array leaves pos 0 free for the encrypted binary number
				encrypted[pos] = buffer(encrypt(message[pos-1],e,N),binary[counter]);
				printf("%c",encrypted[pos]);
				counter (counter + 1) % 4;

			}

			on = replay();
		}
		else if (option == 3)
		{
			char message[MAX_MESSAGE];
			int size,d;
			long long int N;


			printf("\nPlease enter the message you want to decrypt:\n");

			fflush (stdin);

			fgets(message,MAX_MESSAGE,stdin);

			size = strlen(message);

			printf("\nNext enter your private key\n");
			N = getNumber("N");
			d = getNumber("d");

			int number = decrypt(message[0],d,N);

			int binary[4];

			numToBin(binary,4,number);

			int decrypted[size];
			int counter = 0;

			for (int pos = 1; pos < size ; ++pos)
			{
				decrypted[pos] = decrypt(debuffer(message[pos],binary[counter]),d,N);
				printf("%c",decrypted[pos]);
				counter = (counter + 1) % 4;
			}
			on = replay();
		}
	}

}


int getNumber(char name[])
{
	int number;
	printf("\nPlease enter %s value:",name);
	scanf("%d",&number);

	while (number ==0)
	{
		printf("\nPlease enter a single number:");
		fflush(stdin);
		scanf("%d",&number);
	}

	return number;
}


int choice()
{
	printf("Hello, please pick an option\n");
	printf("1: Generate Keys\n");
	printf("2: Encrypt Message\n");
	printf("3: Decrypt Message\n");

	printf("\nPlease enter the number associated with your desired action:");

	int choice = 0;
	scanf("%d",&choice);
	while (choice<1 || choice>3)
	{
		printf("\nInvalid. Please try again:");
		scanf("%d",&choice);
	}
	return choice;
}

int replay()
{

	printf("\nIf you wish to restart the program, enter a 1");
	printf("\nIf you wish to exit the program, enter a 0\n");

	int choice = 3;
	scanf("%d",&choice);
	while (choice<0 || choice>1)
	{
		printf("\nInvalid. Please try again:");
		scanf("%d",&choice);
	}
	printf("\n\n");
	return choice;
}

void generateKeys(void)
{
	long long int prime1,prime2,N,phi;
	int flag;
	int d;
	int e;

	while (1)
	{
		printf("\nPlease enter the value of your first prime number:\n");
		scanf("%lld",&prime1);

		flag = isPrime(prime1);

		if (flag==1)
			break;
		else
			printf("Not a prime, try again!");
	}

	while (1)
	{
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

int isPrime(long long int val)
{

	int i;
	int j = sqrt(val);
	for(i = 2; i <= j; i++)
	{
		if(val % i == 0)
			return 0;
	}
	return 1;
}

int findE(long long int phi)
{
	for (int e = 3; e < 50; e += 2)
	{
		if (phi%e!=0 && isPrime(e)==1)
			return e;
	}
}

int findD(int e, long long int phi)
{
	int k = 0;
	while (1)
	{
		if ((1 + k * phi) % e == 0)
			return (1 + k * phi) / e;
		else
			k++;
	}
}

void numToBin(int arr[], int size,int num)
{
	int temp[size];
	for (int pos = 0; pos < size; ++pos)
	{
		temp[pos] = num%2;
		num = floor(num/2.0);
	}

	for (int i = 0; i < 4; ++i)
	{
		arr[i] = temp[size-i-1];
	}
}

int encrypt( int val, int e, long long int N)
{
	long long int step1;
	int step2;
	step1 = pow((double)val,(double)e);
	if (step1>N)
	{
		printf("Size Error: N value too small for message");
	}
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
int buffer(int num, int bin)
{
	num*=-1;

	if (bin == 0)
		return num *= -1;

	else if (bin==1)
		return ((uint8_t) num) - COMPLIMENT_SHIFT;

}

int debuffer(int num, int bin)
{
	num *= -1;
	if(bin == 0)
		return num*=-1;

	else if (bin ==1)
		return (uint8_t) (num - COMPLIMENT_SHIFT);
}
