//#include <stdio.h>
//#include <stdlib.h>
//#include <unistd.h>
//#include <sys/socket.h>
//#include <bluetooth/bluetooth.h>
//#include <bluetooth/l2cap.h>
//int main( int argc , char **argv)
//{
//    struct sockaddr_l2 addr={0};
//    int s,status;
//    char *dest, *buf; //="00:11:67:32:61:62";
//
//    printf(argv[0]);
//    printf("\n");
//    printf(argv[1]);
//    printf("\n");
//
//    if(argc==2)
//    {
//        dest=argv[1];
//    }
//    else
//    {
//        printf("useage:client addr\n");
//        exit(1);
//    }
//    // allo c a t e a s oc k e t
//    s=socket(PF_BLUETOOTH, SOCK_SEQPACKET, BTPROTO_L2CAP);
//    if(s<0)
//    {
//        perror("create socket error\n");
//        exit(1);
//    }
//    // s e t the conne c t ion parameter s (who to connect to )
//    addr.l2_family = AF_BLUETOOTH;
//    addr.l2_psm = htobs(0x1001);
//    str2ba(dest, &addr.l2_bdaddr);
//    // connect to s e r v e r
//    printf("connectting...\n");
//    status = connect(s, (struct sockaddr *)&addr, sizeof(addr));
//    // send a message
//    if(status == 0){
//        printf("scuess!\n");
//        status = write(s, "hello!", 6);
//
//        do{
//            scanf("%s",buf);
//            status=write(s,buf,strlen(buf));
//            if(status<0) perror("uh oh");
//        }while(strcmp(buf,"goodbye")!=0);
//    }
//    else
//    {
//        printf("Failed!\n");
//    }
//
//    close(s);
//    return 0;
//}