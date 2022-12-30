/*
musaab imran
20i-1794
*/
#include <iostream>
#include <unistd.h>
#include <string>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 8080
#define MAXLINE 5000

using namespace std;

string return_string;

// input validation
bool validation(string t)
{
    // only one character
    if (t[1] != '\0')
    {

        return false;
    }
    // lenght cant be greater than 1
    if (t.length() != 1)
    {
        return false;
    }

    // alocating 1 if user want that attributr
    if (t[0] == '1')
    {

        return_string += '1';
        // cout << return_string << endl;
        return true;
    }

    // 0 is doesnt want that attribute
    else if (t[0] == '0')
    {

        return_string += '0';
        return true;
    }

    // number except 0 and 1 case
    else
    {
        return false;
    }
}

// taking input
void input()
{

    // declarations
    string in;
    string country, cid, description, quan, price;
    return_string = "";

    cout << "\n\n Enter Invoice Number: ";
    cin >> in;

    // exit check

    int x = in.compare("exit");
    if (x == 0)
    {
        return_string.clear();
        return_string += "exit";
        return;
    }
    return_string += in;
    return_string += '\t';
    // cout << return_string << endl;

// taking input from the user
m1:
    cout << " Do you want to see Description? \n Enter 1/0:";
    cin >> description;

    if (!(validation(description)))
    {
        goto m1;
    }

// quantity
m2:
    cout << " Do you want to see Quantity? \n Enter 1/0:";
    cin >> quan;

    if (!(validation(quan)))
    {
        goto m2;
    }

// price
m3:
    cout << " Do you want to see Price? \n Enter 1/0:";
    cin >> price;

    if (!(validation(price)))
    {
        goto m3;
    }

// customer id
m4:
    cout << " Do you want to see Customer Id? \n Enter 1/0:";
    cin >> cid;
    if (!(validation(cid)))
    {
        goto m4;
    }

// country
m5:
    cout << " Do you want to see Country? \n Enter 1/0:";
    cin >> country;

    if (!(validation(country)))
    {
        goto m5;
    }

    return_string += '\t';
}

// Driver code
int main()
{
    int sockfd;
    string ex = "exit";
    char buffer[MAXLINE];
    // string hello = "Hello from client!";
    struct sockaddr_in servaddr;

    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Filling servaddr information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    while (1)
    {
        int n;

        // taking the input from the user
        input();
        string input_data = "";
        input_data = return_string;

        if (return_string.find(ex) != string::npos)
        {
            input_data = "exit";
        }

        // cout << " return str " << return_string << " " << return_string.length()<< endl;

        int size = input_data.length() + 1;
        char client_message[input_data.length() + 1];
        strcpy(client_message, input_data.c_str());

        sendto(sockfd, client_message, strlen(client_message), 0, (const struct sockaddr *)&servaddr, sizeof(sockaddr_in));

        // exit check
        if (strcmp(client_message, "exit") == 0)
        {
            exit(0);
        }

        bzero(client_message, size);
        // receving from the server
        bzero(buffer, MAXLINE);
        socklen_t slen = sizeof(sockaddr_in);
        n = recvfrom(sockfd, buffer, MAXLINE, 0, (struct sockaddr *)&servaddr, &slen);

        buffer[n] = '\0';

        cout << "\n\n Invoice Details: \n"
             << endl;
        cout << buffer;
        // checkinf if exit is written
    }

    // closing the socket
    close(sockfd);
    return 0;
}
