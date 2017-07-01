

//modified by: Cesar Loya
//date: 
//purpose:
//
//This program originated from the website: coding.debuntu.org
//Author: chantra
//Date: Sat 07/19/2008 - 19:23
//Usage:
//   $ gcc lab3prog.c -Wall -olab3prog
//   $ ./lab3prog
//   USAGE: prog host [page]
//          host: the website hostname. ex: coding.debuntu.org
//          page: the page to retrieve. ex: index.html, default: /
//
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h> 
#include <ctime>
#include <cstdlib>

//library included to get rid of bug
// bug being the close function



int create_tcp_socket();
char *get_ip(char *host);
char *build_get_query(char *host, const char *page);
void program_usage();
void le_pause(int dur);

#define HOST "www.google.com"
#define PAGE "/"
#define PORT 80
#define USERAGENT "HTMLGET 1.0"


//int message(int argc, char **argv)
const char* message()
{
    struct sockaddr_in *remote;
    int sock;
    int tmpres;
    char *ip;
    char* get; // char pointer
    char buf[BUFSIZ+1];

    //hard code the parameters
    char host[] = "sleipnir.cs.csub.edu";
    le_pause(2); // fancy pause
    char mypage[] ="~cloya/MikePence.txt";
    char *page = mypage; //make same type
    //this bug was solved through changing
    //the page pointer to a constant char pointer




    sock = create_tcp_socket();
    ip = get_ip(host);
    fprintf(stderr, "IP is %s\n", ip);
    remote = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in *));
    remote->sin_family = AF_INET;
    tmpres = inet_pton(AF_INET, ip, (void *)(&(remote->sin_addr.s_addr)));
    if( tmpres < 0)  
    {
        perror("Can't set remote->sin_addr.s_addr");
        exit(1);
    }else if(tmpres == 0)
    {
        fprintf(stderr, "%s is not a valid IP address\n", ip);
        exit(1);
    }
    remote->sin_port = htons(PORT);

    if(connect(sock, (struct sockaddr *)remote, sizeof(struct sockaddr)) < 0){
        perror("Could not connect");
        exit(1);
    }
    get = build_get_query(host, page);
    fprintf(stderr, "Query is:\n<<START>>\n%s<<END>>\n", get);

    //Send the query to the server
    //there was a comparison between sign and unsigned,
    //so i solved this by making both of the types unsigned

    unsigned int sent = 0;
    while(sent < strlen(get))  //TWO DIFFERENT COMPARISSONS
    {
        tmpres = send(sock, get+sent, strlen(get)-sent, 0);
        if(tmpres == -1){
            perror("send command, Can't send query");
            exit(1);
        }
        sent += tmpres;
    }
    //now it is time to receive the page
    memset(buf, 0, sizeof(buf));
    int htmlstart = 0;  // ret ma boii
    char * htmlcontent;
    while((tmpres = recv(sock, buf, BUFSIZ, 0)) > 0){
        if(htmlstart == 0)
        {
            /* Under certain conditions this will not work.
             * If the \r\n\r\n part is splitted into two messages
             * it will fail to detect the beginning of HTML content
             */
            htmlcontent = strstr(buf, "\r\n\r\n");
            if(htmlcontent != NULL){
                htmlstart = 1;
                htmlcontent += 4;
            }
        }else{
            htmlcontent = buf;
        }
        if(htmlstart){
            //this is missing arguments 
            //there was a missing parameterm so i fixed it by providing a third parameter
            fprintf(stdout, htmlcontent,"anything works LOL");  //here is the function
            //this bug was solved by simply adding a third parameter
            //because this function takes in one more argument 
        }

        //memset(buf, 0, tmpres);
    }
    if(tmpres < 0)
    {
        perror("Error receiving data");
    }
    delete get;
    //free(get);
    free(remote);
    free(ip);
    close(sock); //there is a bug here
    //close function bug was solved by 
    //including the proper library
    //
    //return 0;
    return htmlcontent;
}

void le_pause(int dur){
    int temp = time(NULL) + dur;
    while(temp > time(NULL));
}


void program_usage()
{
    fprintf(stderr, "USAGE: htmlget host [page]\n\
            \thost: the website hostname. ex: coding.debuntu.org\n\
            \tpage: the page to retrieve. ex: index.html, default: /\n");
}

int create_tcp_socket()
{
    int sock;
    if((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0){
        perror("Can't create TCP socket");
        exit(1);
    }
    return sock;
}

char *get_ip(char *host)
{
    struct hostent *hent;
    //ip address format  123.123.123.123
    int iplen = 15;
    char *ip = (char *)malloc(iplen+1);
    memset(ip, 0, iplen+1);
    if((hent = gethostbyname(host)) == NULL)
    {
        herror("Can't get IP host by name");
        exit(1);
    }
    //i added 6
    //if (inet_ntop(AF_INET6, &s->sin6_addr, ipstr, sizeof(ipstr)));
    //bug here
    //was not getting the FULL length of the ip address
    //so i solved this bug by adding 1 to the iplen
    if(inet_ntop(AF_INET, (void *)hent->h_addr_list[0], ip, iplen+1) == NULL)
    {
        perror("Can't resolve host with inet_ntop");
        exit(1);
    }
    return ip;
}

char *build_get_query(char *host, const char *page)
{
    char *query;
    const char *getpage = page;

    //lab3http.cpp:171:15: warning: deprecated conversion from string constant to ‘char*’
    //solved this bug through making the getpage pointer into a constant
    const char *tpl = "GET /%s HTTP/1.0\r\nHost: %s\r\nUser-Agent: %s\r\n\r\n";

    if(getpage[0] == '/'){
        getpage = getpage + 1;
        fprintf(stderr,"Removing leading \"/\", converting %s to %s\n", page, getpage);
    }
    // -5 is to consider the %s %s %s in tpl and the ending \0
    query = (char *)malloc(strlen(host)+strlen(getpage)+strlen(USERAGENT)+strlen(tpl)-5);
    sprintf(query, tpl, getpage, host, USERAGENT);
    return query;
}



