/*
musaab imran
20i-1794
*/
#include <iostream>
#include <unistd.h>
#include <string>
#include <cstring>
#include <sys/types.h>
#include <fstream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 8080
#define MAXLINE 50

using namespace std;

//  file reading and extracting the value of the invoice
string display(string check, string check1)
{

	// file reading
	// deaclarations
	int position = 0, count = 0;
	string id, description, quantity, price, cid, country, save_to_print = " ", userdata, temp1, temp2;
	;

	fstream wrdata("dataset.txt", ios::in);

	while (getline(wrdata, temp1))
	{
		// cout << temp1 << endl;
		position = temp1.find("\t");
		temp2 = temp1.substr(0, position);

		int compare = check.compare(temp2);
		// cout << compare << endl;
		if (compare == 0)
		{
			userdata += temp1 + "\n";
			count++;
		}
	}

	// if the value of the invoice is not found
	if (count == 0)
	{
		save_to_print = " ";
		save_to_print += "No Information of this Invoice in Database!";
	}
	wrdata.close();

	// extracting values from the file
	for (int i = 0; i < count; i++)
	{
		// saving the values required from the file
		position = userdata.find("\t");
		id = userdata.substr(0, position);
		userdata = userdata.substr(position + 1);

		position = userdata.find("\t");
		description = userdata.substr(0, position);
		userdata = userdata.substr(position + 1);

		position = userdata.find("\t");
		quantity = userdata.substr(0, position);
		userdata = userdata.substr(position + 1);

		position = userdata.find("\t");
		price = userdata.substr(0, position);
		userdata = userdata.substr(position + 1);

		position = userdata.find("\t");
		cid = userdata.substr(0, position);
		userdata = userdata.substr(position + 1);

		position = userdata.find("\n");
		country = userdata.substr(0, position);
		userdata = userdata.substr(position + 1);

		// appending valuies in string
		save_to_print += " INVOICE # ";
		save_to_print += id;
		save_to_print += "\n";

		// checking for the required attributes
		if (check1[0] == '1')
		{
			save_to_print += " Description: ";
			save_to_print += description;
			save_to_print += "\n";
		}

		if (check1[1] == '1')
		{
			save_to_print += " Quantity: ";
			save_to_print += quantity;
			save_to_print += "\n";
		}

		if (check1[2] == '1')
		{

			save_to_print += " Price: ";
			save_to_print += price;
			save_to_print += "\n";
		}

		if (check1[3] == '1')
		{

			save_to_print += " Customer Id: ";
			save_to_print += cid;
			save_to_print += "\n";
		}

		if (check1[4] == '1')
		{
			save_to_print += " Country: ";
			save_to_print += country;
			save_to_print += "\n";
		}
		save_to_print += "\n";
	}

	// string return
	return save_to_print;
}
// Driver code
int main()
{
	// declarations
	int sockfd;
	int i = 0;
	char buffer[MAXLINE];
	string ctos = "", ex = "exit";
	int position1 = 0;
	struct sockaddr_in servaddr, cliaddr;

	// Creating socket file descriptor
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}

	// Filling server information
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = INADDR_ANY;

	if (bind(sockfd, (const struct sockaddr *)&servaddr,
			 sizeof(servaddr)) < 0)
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}

	// loop will break on exit
	while (1)
	{
		int n;
		socklen_t len = sizeof(cliaddr); // len is value/resuslt
		bzero(buffer, MAXLINE);

		n = recvfrom(sockfd, buffer, MAXLINE, 0, (struct sockaddr *)&cliaddr, &len);
		buffer[n] = '\0';

		// cout << "\n Details of Invoice: " << buffer;

		// storing buffer in ctos string
		for (char ch : buffer)
			ctos += ch;

		// cout << " ctos" << ctos << " " << ctos.length() << endl;

		if (ctos.find(ex) != string::npos)
		{
			exit(0);
		}

		// breaking string into 2 parts
		position1 = ctos.find("\t");
		string c1 = ctos.substr(0, position1);
		ctos = ctos.substr(position1 + 1);

		// cout << "c1" <<c1 << c1.length() << endl;

		position1 = ctos.find("\t");
		string c2 = ctos.substr(0, position1);
		ctos = ctos.substr(position1 + 1);
		// cout << "c2" << c2 << c2.length()<< endl;

		ctos.clear();
		bzero(buffer, MAXLINE);

		string st = display(c1, c2);
		// cout << st << st.length() << endl;
		//  cout << st <<  " " << st.length() << endl;
		int num = st.length() + 1;

		// bzero(server_message,st.length());
		char server_message[num];
		bzero(server_message, num);
		st.copy(server_message, num);
		// server_message =display(buffer);

		cout << " Client Information Sent! " << endl;
		// sending the invoice detailsa
		sendto(sockfd, (const char *)server_message, strlen(server_message), 0, (const struct sockaddr *)&cliaddr, sizeof(sockaddr_in));
		// printf("Hello message sent.\n");
	}

	return 0;
}
