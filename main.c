#include <stdio.h>
#include <string.h>
#include "view.h"
#include "edit.h"
/*
Function : main
Description :
    Program execution starts here.
    It checks the command-line arguments and
    calls the required operation.
*/
void print_help(void);
int main(int argc, char *argv[])
{
    //Check number of command-line arguments
    if (argc > 4)
    {
        printf("ERROR: Enter valid number of arguments\n");
        printf("Enter    ./a.out -h     to get the information \n");
        return 0;
    }
    //Display help 
    if (strcmp(argv[1], "-h") == 0)
    {
        print_help();
    }
    //View MP3 tags
    else if (strcmp(argv[1], "-v") == 0)
    {
        view_tag(argv[2]);
    }
    //Edit MP3 tag
    else if (strcmp(argv[1], "-e") == 0)
    {
        edit_tag(argv[2],argv[3]);
    }
    //Invalid option 
    else
    {
        printf("Invalid option\n");
        printf("Use -v for view\n");
        printf("-e for edit\n");
        printf("-h for help\n");
    }
    return 0;
}