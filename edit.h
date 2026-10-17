#ifndef EDIT_H
#define EDIT_H

#include "common.h"

void edit_tag(char *option,char *filename);
Status file_open(char *filename,FILE **src,FILE **temp);
Status get_frame_id(char option[], char frame_id[]);
uint decode_frame_size(uchar bytes[]);
void encode_frame_size(uint size,uchar bytes[]);
void copy_bytes(FILE *src,FILE *dest,uint count);

void set_tag_size(uint s, uchar out[]);
static uint write_new_frame(FILE *temp, char *id, uchar flags[], char *desc, char *text);

#endif