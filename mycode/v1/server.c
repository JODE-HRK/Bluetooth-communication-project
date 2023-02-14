#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>



// connect to single slave
// work
int main(int argc, char **argv)
{
    struct sockaddr_rc addr = { 0 };
    int s, status;
    char dest[18] = "B8:27:EB:3F:E3:D4";



    // allocate a socket
    s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

    // set the connection parameters (who to connect to)
    addr.rc_family = AF_BLUETOOTH;
    addr.rc_channel = (uint8_t) 1;
    str2ba( dest, &addr.rc_bdaddr );

    // connect to client
    status = connect(s, (struct sockaddr *)&addr, sizeof(addr));

    // send message (loop)
    

    int bytes_read;
    char buf[1024] = {0};

    char input[40];
    if (fork() == 0) {
        printf("receiving process\n");
        while(1) {
            bytes_read = read(s, buf, sizeof(buf));
            if(bytes_read > 0) {
                printf("server received [%s]\n", buf);
            }
        }
    }
    else {
        printf("sending process\n");
        while(1){
            printf("Enter message: \n");
            scanf("%s", input);
            write(s, input, 40);
        }
    }

    // char input[40];
    // printf("Enter message: ");
    // scanf("%s",input);
    // if( status == 0 ) {
    //     status = write(s, input, 40);
    // }
    // if( status < 0 ) perror("uh oh");
    // status = 0;
    
    
    
    
    

    close(s);
    return 0;
}
