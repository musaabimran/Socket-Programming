
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <netinet/in.h>
#include <time.h>

char *filename;
int file()
{
    // declaration
    char *ch1;
    char *subString7;
    char str[500];
    FILE *ifile = fopen(filename, "r");
    while (fgets(str, 500, ifile) != NULL)
    {
        // printf("%s", str);
    }
    // printf("%s", str);
    fclose(ifile);

    ch1 = strtok(str, "\t");
    subString7 = ch1;
    int num = atoi(subString7);
    // printf("%d", num);

    return num;
}
int main()
{

    // declarations
    char server_message[200] = "Hi! Welcome to the server. ";
    char buf[200];
    char buf1[200];
    char save[200] = "";
    char *subString;
    char *subString1;
    char *subString2;
    char *subString3;
    char *subString4;
    char *subString5;
    char *subString6;

    char *text;
    char *ch;

    char *name;

    char message0[200] = "Registration Date/Time: ";
    char message1[80];
    char message2[80];
    char message3[100] = " You Will Join on: ";
    char message4[80];
    char message7[80];

    char final[40] = "Client Information Recieved!";

    int server_socket = socket(AF_INET, SOCK_STREAM, 0);

    char slash = '/';

    // defining the server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(3001);
    server_address.sin_addr.s_addr = INADDR_ANY;

    bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address));

    listen(server_socket, 5);

    // for loop for 5
    for (int i = 0; i < 5; i++)
    {
        // bind the socket to our specified IP and port
        // printf("\n%s", str);
        char t1 = 'P';
        char t = '\t';
        char n = '\n';
        int client_socket = accept(server_socket, NULL, NULL);

        bzero(buf, 200);
        bzero(buf1, 200);
        
        recv(client_socket, &buf, sizeof(buf), 0);
        printf("\n %s \n", final);

        


        // selecting the file
        int sum = strlen(buf);
        

        if (buf[sum - 1] == '1')
        {

            filename = "P01.txt";
        }

        else if (buf[sum - 1] == '2')
        {
            filename = "P02.txt";
        }

        else if (buf[sum - 1] == '3')
        {
            filename = "P03.txt";
        }

        else if (buf[sum - 1] == '4')
        {
            filename = "P04.txt";
        }

        // name
        ch = strtok(buf, "\n:-");
        for (int i = 0; i < 8; i++)
        {
            if (i == 1)
                subString = ch;

            if (i == 2)
                subString1 = ch;

            if (i == 4)
                subString2 = ch;

            if (i == 5)
                subString3 = ch;

            if (i == 6)
                subString4 = ch;

            if (i == 7)
                subString5 = ch;

            ch = strtok(NULL, "\n:-");
        }

        int non = file();
        non++;
        char number[10];
        snprintf(number, 10, "%d", non);
        strcat(save, number);

        // strncat(save, &c, 1);
        strncat(save, &t, 1);
        strncat(save, &t, 1);

        // package information
        strncat(save, &t1, 1);
        strcat(save, subString5);
        strncat(save, &t, 1);
        strncat(save, &t, 1);

        int dt = atoi(subString4);
        dt++;

        // date and time get
        // join date
        // todays date
        time_t rawtime;
        struct tm *timeinfo;
        time(&rawtime);
        // timeinfo->tm_mday + dt;
        timeinfo = localtime(&rawtime);
        strftime(message1, 80, "%F", timeinfo);
        // printf("%s", message1);
        strftime(message2, 80, "%r", timeinfo);

        timeinfo->tm_mday += dt;
        mktime(timeinfo);
        strftime(message7, 80, "%F", timeinfo);

        char sp = ' ';
        strcat(message0, message1);
        strncat(message0, &sp, 1);
        strncat(message0, &sp, 1);
        strcat(message0, message2);
        strncat(message0, &n, 1);
        strcat(message0, message3);
        strftime(message4, 80, "%F", timeinfo);
        strcat(message0, message4);

        strcat(save, message1);
        strncat(message1, &t, 1);
        strncat(save, &t, 1);

        // date and time information
        strcat(save, message2);
        strncat(save, &t, 1);
        strncat(save, &t, 1);

        // name
        strcat(save, subString);
        strncat(save, &t, 1);
        strncat(save, &t, 1);

        // age
        strcat(save, subString1);
        strncat(save, &t, 1);
        strncat(save, &t, 1);

        // weight
        strcat(save, subString2);
        strncat(save, &t, 1);
        strncat(save, &t, 1);

        // height
        strcat(save, subString3);
        strncat(save, &t, 1);
        strncat(save, &t, 1);

        // Date of joining
        strcat(save, message7);
        // strcat(save, subString4);
        strncat(save, &t, 1);
        strncat(save, &t, 1);
        strncat(save, &n, 1);
       

        FILE *fp;

        fp = fopen(filename, "a");

        fprintf(fp, "%s", save);
        fclose(fp);

        bzero(save, 200);

        // sending information
        send(client_socket, message0, strlen(message0), 0);
        bzero(message0, 200);
        strcat(message0 , "Registration Date/Time: ");

        // send(client_socket, message2, strlen(message2), 0);
    }

    // close the socket
    close(server_socket);

    return 0;
}
