#ifndef VIEW_H
#define VIEW_H

#include "common.h"
void view_tag(char *filename);

uint get_frame_size(uchar size_bytes[]);


void display_tags(MP3Tags *tags,char *filename);

#endif