/*************************************************************************
	> File Name: ahci_tst.c
	> Author: xOpenLee
	> Mail: 750haige@gmail.com 
	> Created Time: Sunday, February 28, 2016 AM12:13:02 HKT
 ************************************************************************/

#include<stdio.h>
#include "ahci.h"

extern HBA_MEM *g_pHBA_MEM;
#define TST_DATA_LEN (4096)

static int strlen_disk(char* buf){
    int count=0;
    while(*buf++ != '\r')
      count++;
    return count;
}
 
static char* read_disk(DWORD offset)
{
    //Check is string more than TST_DATA_LEN,
   printf("\n=====================================");
    char *read_buffer = (char*)(TST_DATA_LEN);
    printf("\nread_disk: Read address: %p",read_buffer);
    memset(read_buffer,0,TST_DATA_LEN);

    printf("\n--> BEFORE Read : %s from location: %d", read_buffer, offset);
    read(&g_pHBA_MEM->ports[0], offset, 0, 1, read_buffer);
    printf("\n--> Read : %s from location: %d", read_buffer, offset);

    return read_buffer;
}

static int append_disk(char* buf, int offset)
{
    //Check is string more than TST_DATA_LEN,
    //forst perform a read, then add this line in the buffer, and then perform a write.
    char *write_str = read_disk(0);
    printf("\n Existing Data at 0:%s                      ",write_str);
    printf("\n Size:%d              ",strlen_disk(write_str));
    char *write_buffer = (char*) malloc(TST_DATA_LEN);
    memcpy(write_buffer,buf,strlen(buf));
    write(&g_pHBA_MEM->ports[0], offset, 0, 1, write_buffer);
    return 1;
}

static int write_disk(DWORD offset, char* buf)
{
    //Check is string more than TST_DATA_LEN - LEFT
    char *write_buffer = (char*)malloc(TST_DATA_LEN);

    memcpy(write_buffer, buf,(TST_DATA_LEN));
    printf("\n Writing : %s at location: %d", write_buffer,offset);

    return write(&g_pHBA_MEM->ports[0], offset, 0, 1, buf);
}



int main()
{
    char *O = "CSE 506 Rocks\0";
    char *I = "First -Initial \0";
    char *N = "Second - Next Value \0";

    //----DEBUG CONSECUTIVE SECTORS WRITE CODE ---- UNABLE TO FIX

    printf("\nREAD DATA: %s",read_disk(0));
    write_disk(0,I);
    printf("\nREAD DATA: %s",read_disk(0));
    append_disk(N,0);
    write_disk(2,O);

    printf("\nREAD DATA: %s",read_disk(0));
    printf("\nREAD DATA: %s",read_disk(1));
    printf("\nREAD DATA: %s",read_disk(3));

    return 0;

}
