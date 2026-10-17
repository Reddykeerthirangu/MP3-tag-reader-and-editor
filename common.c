#include <string.h>
#include "common.h"

Status read_header(FILE *fp, uchar header[])
{
    if(fread(header, 1, 10, fp) != 10) 
    {
        return e_failure;
    }
    return e_success;
}

Status validate_header(uchar header[])
{
    if (header[0]!= 'I' || header[1]!= 'D' || header[2]!= '3')
    {
        return e_failure;
    }
    if (header[3] != 3 || header[4] != 0)
    {
        printf("ERROR: Only ID3v2.3.0 supported\n");
        return e_failure;
    }
    return e_success;
}
