#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>


// Data Structure for Bluetooth address
// typedef struct {
// 	uint8_t b[6];
// } __attribute__((packed)) bdaddr_t;

// BlueZ functions  string & bt address
// int str2ba( const char *str, bdaddr_t *ba );
// int ba2str( const bdaddr_t *ba, char *str );

int main(int argc, char **argv)
{
    inquiry_info *ii = NULL;
    int max_rsp, num_rsp;
    int dev_id, sock, len, flags;
    int i;
    char addr[19] = { 0 };
    char name[248] = { 0 };

    // passing NULL will retrieve the resource number of the first available LOCAL Bluetooth adapter
    dev_id = hci_get_route(NULL);
    // allocate resources to use that adapter
    sock = hci_open_dev( dev_id );    // return a handle to the socket.

    // error
    if (dev_id < 0 || sock < 0) {
        perror("opening socket");
        exit(1);
    }


    len  = 8;
    max_rsp = 255;
    flags = IREQ_CACHE_FLUSH;
    ii = (inquiry_info*)malloc(max_rsp * sizeof(inquiry_info));
    
    // initiate a device discovery operation
    // returns a list of devices that respond
    // does not actually use the socket opened in the previous step. 
    // --- Parameters:
    // takes the resource number as its first parameter
    // inquiry lasts for at most 1.28 * len seconds
    //  at most max rsp responding devices will be returned to devs
    // 5th param->devs, an array of 'inquiry_info' structures:
    // typedef struct {
    //     bdaddr_t    bdaddr; //address of detected device
    //     uint8_t     pscan_rep_mode; 
    //     uint8_t     pscan_period_mode;
    //     uint8_t     pscan_mode;
    //     uint8_t     dev_class[3]; //type of device
    //     uint16_t    clock_offset;
    // } __attribute__ ((packed)) inquiry_info;
    // 6th param->flags, whether or not to use previously discovered device information or to start afresh
    num_rsp = hci_inquiry(dev_id, len, max_rsp, NULL, &ii, flags);
    
    if( num_rsp < 0 ) perror("hci_inquiry");


    // determine their user-friendly names->hci read remote name
    // int hci read remote name (int hci¯ sock , const bdaddr¯ t *addr , int len , char *name , int timeout ) ;
    // use the socket 'hci_sock' in order to query the device with Bluetooth address 'addr' for its user friendly name. 
    //  returns 0 and the first 'len' bytes of the device’s user-friendly name stored in the supplied character array: 'name'.
    for (i = 0; i < num_rsp; i++) {
        ba2str(&(ii+i)->bdaddr, addr);
        // The C library function 
        // void *memset(void *str, int c, size_t n) 
        // copies the character c (an unsigned char) to the first n characters of the string pointed to, by the argument str.
        memset(name, 0, sizeof(name));
        if (hci_read_remote_name(sock, &(ii+i)->bdaddr, sizeof(name), 
            name, 0) < 0)
        strcpy(name, "[unknown]");
        printf("%s  %s\n", addr, name);
    }

    free( ii );
    close( sock );
    return 0;
}