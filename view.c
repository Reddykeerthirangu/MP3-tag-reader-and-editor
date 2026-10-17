#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include"view.h"
#include"common.h"
uint get_frame_size(uchar size_bytes[])
{
    uint frame_size=((uint)size_bytes[0] << 24) | ((uint)size_bytes[1] << 16) | ((uint)size_bytes[2] << 8) |  (uint)size_bytes[3];
    return frame_size;
}


void display_tags(MP3Tags *tags, char *filename)
{
    printf(BLUE"\n==============================================\n"RESET);
    printf(MAGENTA"        MP3 TAG READER AND EDITOR\n"RESET);
    printf(BLUE"==============================================\n"RESET);
    printf(YELLOW"File    : %s\n", filename);
    printf("Version : ID3v2.3.0\n"RESET);
    printf(BLUE"==============================================\n"RESET);
    printf(YELLOW"Title   : %s\n", tags->title);
    printf("Artist  : %s\n", tags->artist);
    printf("Album   : %s\n", tags->album);
    printf("Year    : %s\n", tags->year);
    printf("Genre   : %s\n", tags->genre);
    printf("Comment : %s\n"RESET, tags->comment);
    printf(BLUE"==============================================\n"RESET);
}
void view_tag(char *filename)
{
    FILE *fp =fopen(filename,"rb");
    if(fp==NULL)
    {
        printf("ERROR: file not open\n");
        return;
    }
    uchar header[10];
    if(read_header(fp,header)==e_failure)
    {
        fclose(fp);
        return;
    }
    if(validate_header(header)==e_failure)
    {
        fclose(fp);
        return;
    }
    MP3Tags tags={0};
    int count=0;
    Frame frame;
    uint frame_size;
    while(count < 6)
    {
        uchar data[1024];
        uchar arr[4]; 

        if (fread(frame.id, 1, 4, fp) != 4)
        {
            break;
        }
        frame.id[4] = '\0';
        if(frame.id[0] == '\0')
        {
            break;
        }

        if (fread(arr, 1, 4, fp) != 4)
        {
            break;
        }
        frame.size = get_frame_size(arr);

        // FIX 1: ID3v2 frame flags are exactly 2 bytes
        if (fread(frame.flags, 1, 2, fp) != 2)
        {
            break;
        }

        if (frame.size == 0)
        {
            continue;
        }
        

        // FIX 2: Read the entire frame size since encoding is included
        if (frame.size >= sizeof(data))
        {
            fseek(fp, frame.size, SEEK_CUR);
            continue;
        }

        if (fread(data, 1, frame.size, fp) != frame.size)
        {
            break;
        }
        data[frame.size] = '\0';

        // Title, Artist, Album, Year, Genre extraction
        if(strcmp(frame.id, "TIT2") == 0)
        {
            // Skip encoding byte at data[0]
            strcpy(tags.title, (char *)(data + 1));
            count++;
        }
        else if(strcmp(frame.id, "TPE1") == 0)
        {
            strcpy(tags.artist, (char *)(data + 1));
            count++;
        }
        else if(strcmp(frame.id, "TALB") == 0)
        {
            strcpy(tags.album, (char *)(data + 1));
            count++;
        }
        else if(strcmp(frame.id, "TYER") == 0)
        {
            strcpy(tags.year, (char *)(data + 1));
            count++;
        }
        else if(strcmp(frame.id, "TCON") == 0)
        {
            strcpy(tags.genre, (char *)(data + 1));
            count++;
        }
        else if(strcmp(frame.id, "COMM") == 0)
        {
            // FIX 3: Correct layout traversal handling empty/filled descriptions
            // data[0]     = Encoding
            // data[1..3]  = Language
            // data[4...]  = Description
            if (frame.size > 4)
            {
                int pos = 4; // Start at the Description field

                // Advance through Description characters until reaching the null separator
                while (pos < frame.size && data[pos] != '\0')
                {
                    pos++;
                }

                // Move past the null terminator to find the Comment text string
                if (pos < frame.size)
                {
                    pos++; 
                }

                int j = 0;
                // Safely copy text bytes into our target tags configuration buffer
                while (pos < frame.size && j < sizeof(tags.comment) - 1)
                {
                    tags.comment[j] = data[pos];
                    j++;
                    pos++;
                }
                tags.comment[j] = '\0';

                if (j == 0)
                {
                    strcpy(tags.comment, "(Empty Comment)");
                }
            }
            count++;
        }
    }

    display_tags(&tags, filename);
    fclose(fp);
    
}