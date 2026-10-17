#ifndef COMMON_H
#define COMMON_H
#include <stdio.h>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"

typedef unsigned char uchar;
typedef unsigned int  uint;
typedef enum 
{ 
    e_failure, 
    e_success 
} Status;

typedef struct 
{
    char title[200];
    char artist[200];
    char album[200];
    char year[20];
    char genre[100];
    char comment[300];
} MP3Tags;

typedef struct 
{
    char  id[5];       /* TIT2, TPE1 ... */
    uint  size;        /* data size */
    uchar flags[2];
} Frame;

Status read_header(FILE *fp, uchar header[]);
Status validate_header(uchar header[]);      /* checks "ID3" + version 2.3 */
//uint   get_tag_size(uchar header[]);         /* synchsafe -> int */
//void   set_tag_size(uint size, uchar out[]); /* int -> synchsafe */
//Status read_frame_header(FILE *fp, Frame *f);
//void   write_frame_header(FILE *fp, Frame *f);
//void   copy_bytes(FILE *src, FILE *dest, uint count);

#endif