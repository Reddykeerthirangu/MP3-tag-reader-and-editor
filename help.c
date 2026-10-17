#include <stdio.h>
#include "common.h"
void print_help(void)
{
    printf("\n============================================\n");
    printf(MAGENTA"       MP3 TAG READER AND EDITOR\n"RESET);
    printf("============================================\n");
    printf(YELLOW"\nUsage:\n");
    printf("\n[View tags]\n"RESET);
    printf(CYAN"./a.out -v  <file.mp3>\n"RESET);
    printf("============================================\n");
    printf(YELLOW"\n[Edit tags]\n"RESET);
    printf(CYAN"./a.out -e  -t <file.mp3>   : To Edit Title\n");
    printf("./a.out -e  -a <file.mp3>   : To Edit Artist\n");
    printf("./a.out -e  -A <file.mp3>   : To Edit Album\n");
    printf("./a.out -e  -y <file.mp3>   : To Edit Year\n");
    printf("./a.out -e  -g <file.mp3>   : To Edit Genre\n");
    printf("./a.out -e  -c <file.mp3>   : To Edit Gomment\n\n"RESET);
    printf("============================================\n");
    printf(YELLOW"\n[Help]\n"RESET);
    printf(CYAN"./a.out -h\n"RESET);
    printf("============================================\n");
}