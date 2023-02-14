#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>


// struct sockaddr_rc {
// 	sa_family_t	rc_family;
// 	bdaddr_t	rc_bdaddr;
// 	uint8_t		rc_channel;
// };
// rc_family field specifies the addressing family of the socket, and will always be AF BLUETOOTH.
// remaining 2 params specify the Bluetooth address and port number,
// use 'BDADDR_ANY' to indicate that any local Bluetooth adapter is acceptable.



// client sokcet
// server socket

int main(int argc, char **argv)
{
    struct sockaddr_rc loc_addr = { 0 }, rem_addr = { 0 };
    char buf[1024] = { 0 };
    int s, client, bytes_read;
    socklen_t opt = sizeof(rem_addr);

    // allocate or create a socket:
    // int socket ( int domain , int type , int protocol ) ;
    // AF BLUETOOTH, specifies that it should be a Bluetooth socket
    // SOCK STREAM, requests a socket with streams-based delivery semantics
    // BTPROTO RFCOMM, specifically requests an RFCOMM socket
    s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

    // bind socket to port 1 of the first available 
    // local bluetooth adapter
    loc_addr.rc_family = AF_BLUETOOTH;
    loc_addr.rc_bdaddr = *BDADDR_ANY;
    loc_addr.rc_channel = (uint8_t) 1;

    // After the server socket is created, it must be bound to a local Bluetooth adapter and port number with the bind function
    bind(s, (struct sockaddr *)&loc_addr, sizeof(loc_addr));

    // put socket into listening mode
    listen(s, 1);

    // accept one connection
    // waits for an incoming connection and returns a brand new socket
    // returned socket represents the newly established connection with a client, and is what the server application should use to communicate with the client.
    client = accept(s, (struct sockaddr *)&rem_addr, &opt);

    ba2str( &rem_addr.rc_bdaddr, buf );
    fprintf(stderr, "accepted connection from %s\n", buf);
    memset(buf, 0, sizeof(buf));

    // read data from the client
    bytes_read = read(client, buf, sizeof(buf));
    if( bytes_read > 0 ) {
        printf("received [%s]\n", buf);
    }

    // close connection
    close(client);
    close(s);
    return 0;
}