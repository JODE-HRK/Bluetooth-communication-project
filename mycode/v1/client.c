#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>


// client: listen for connection
int main(int argc, char **argv)
{
    struct sockaddr_rc loc_addr = { 0 }, rem_addr = { 0 };
    char buf[1024] = { 0 };
    int s, master, bytes_read;
    socklen_t opt = sizeof(rem_addr);

    pid_t pid1;

    s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

    loc_addr.rc_family = AF_BLUETOOTH;
    loc_addr.rc_bdaddr = *BDADDR_ANY;
    loc_addr.rc_channel = (uint8_t) 1;

    bind(s, (struct sockaddr *)&loc_addr, sizeof(loc_addr));

    // put socket into listening mode
    listen(s, 1);

    master = accept(s, (struct sockaddr *)&rem_addr, &opt);

    ba2str( &rem_addr.rc_bdaddr, buf );
    fprintf(stderr, "accepted connection from %s\n", buf);
    memset(buf, 0, sizeof(buf));



    char input[40];
    if (fork() == 0) {
        printf("receiving process\n");
        while(1) {
            bytes_read = read(master, buf, sizeof(buf));
            if( bytes_read > 0 ) {
                printf("client received [%s]\n", buf);
            }
        }
    }
    else {
        printf("sending process\n");
        while(1){
            printf("Enter message: \n");
            scanf("%s", input);
            write(master, input, 40);
        }
    }
        
        
    // close connection
    close(master);
    close(s);
    return 0;
}