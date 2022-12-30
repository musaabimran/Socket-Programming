#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{

	// declarations
	char request[100] = "Hello! I'm Client, I want to Register.";
	char message[200] = "Registration by:";
	char details[200] = "\n Details:";
	char buf1[80];
	char buf2[200];
	char fname[10];
	char lname[10];
	char age[3];
	char weight[3];
	char height[3];
	char package[3];
	char temp[2];
	char JDS[3];

	char dash1 = '-';
	char space1 = ' ';

	// create the socket
	int sock = socket(AF_INET, SOCK_STREAM, 0);

	// setup an address
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = INADDR_ANY;
	server_address.sin_port = htons(3001);

menu1:
	printf("\nFirst Name: ");
	gets(fname);

	// input check
	int len = strlen(fname);
	for (int i = 0; i < len; i++)
	{
		if (isalpha(fname[i]) != 0)
		{
		}

		else
		{
			printf("\nInvalid Input Enter Again!!! \n");
			goto menu1;
		}
	}

	// contcationation
	strcat(message, fname);
	strncat(message, &space1, 1);

// last name input
menu2:
	printf("\nLast Name: ");
	gets(lname);

	len = strlen(lname);
	for (int i = 0; i < len; i++)
	{
		if (isalpha(lname[i]) != 0)
		{
		}

		else
		{
			printf("\nInvalid Input\n");
			goto menu2;
		}
	}

	strcat(message, lname);
	strncat(message, &dash1, 1);

// age input
m1:
	printf("\nEnter Age: ");
	scanf("%s", age);
	int val2 = atoi(age);
	//(isdigit(age[2]) == true) || !(isdigit(age[1]) == true)
	if ((isdigit(age[0]) == false) || (isdigit(age[1]) == false) || (isdigit(age[2]) == false)  || (age[3] != '\0'))
	{
		printf("\nInvalid Input Enter Again!!! \n");
		goto m1;
	}
	if (!(val2 >= 7 && val2 < 115))
	{
		printf("\nInvalid Input\n");
		goto m1;
	}
	strcat(message, age);

// weight input
m3:
	printf("\nEnter Weight: ");
	scanf("%s", weight);
	if ((isdigit(weight[0]) == false) || (isdigit(weight[1]) == false) || (isdigit(weight[2]) == false) || (weight[3] != '\0'))
	{
		printf("\nInvalid Input\n");
		goto m3;
	}
	strcat(details, weight);
	strncat(details, &dash1, 1);

// height input
m2:
	printf("\nEnter Height: ");
	scanf("%s", height);
	if ((isdigit(height[0]) == false) || (height[1] != 39) || (isdigit(height[2]) == false) || (height[3] != '\0'))
	{
		printf("\nInvalid Input \n");
		goto m2;
	}

	strcat(details, height);
	strncat(details, &dash1, 1);

// join date
m4:
	printf("\nEnter Join Day Start: ");
	scanf("%s", JDS);
	int val = atoi(JDS);

	if ((isdigit(JDS[0]) == false) || (isdigit(JDS[1]) == false) || (isdigit(JDS[2]) == false) || (JDS[3] != '\0'))
	{
		printf("\nInvalid Input Enter Again!!! \n");
		goto m4;
	}

	if (!(val >= 0 && val < 366))
	{
		printf("\nInvalid Input\n");
		goto m4;
	}
	strcat(details, JDS);
	strncat(details, &dash1, 1);

// package number
m5:
	printf("\nEnter Package");
	scanf("%s", package);

	if ((package[0] != 'P') || (package[1] != 48) || !(package[2] < 53 && package[2] >= 49) || (package[3] != '\0'))
	{
		printf("\nInvalid Input \n");
		goto m5;
	}

	strncat(details, &package[1], 1);
	strncat(details, &package[2], 1);

	// printf("\n %s\n", message);
	// printf("\n %s\n", details);

	// establishing connection with the server

	connect(sock, (struct sockaddr *)&server_address, sizeof(server_address));

	char sp = ' ';
	strncat(message, &sp, 1);
	strcat(message, details);

	// sending information
	send(sock, message, strlen(message), 0);

	// send(sock, details, strlen(details), 0);

	bzero(buf1, 80);
	recv(sock, &buf1, sizeof(buf1), 0);
	printf("\n %s \n", buf1);

	bzero(buf1, 80);
	close(sock);

	return 0;
}
