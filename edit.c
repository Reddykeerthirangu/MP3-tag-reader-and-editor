#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "edit.h"
#include "common.h"

Status get_frame_id(char option[], char frame_id[])
{
    if (strcmp(option, "-t")==0)
    {
        strcpy(frame_id, "TIT2");
    }
    else if (strcmp(option, "-a")==0)
    {
        strcpy(frame_id, "TPE1");
    }
    else if (strcmp(option, "-A")==0)
    {
        strcpy(frame_id, "TALB");
    }
    else if (strcmp(option, "-y")==0)
    {
        strcpy(frame_id, "TYER");
    }
    else if (strcmp(option, "-g")==0)
    {
        strcpy(frame_id, "TCON");
    }
    else if (strcmp(option, "-c")==0)
    {
        strcpy(frame_id, "COMM");
    }
    else
    {
        return e_failure;
    }
    return e_success;
}
Status file_open(char *filename,FILE **src,FILE **temp)
{
    *src = fopen(filename, "rb");
    if (*src==NULL)
    {
        printf("ERROR: Unable to open source file\n");
        return e_failure;
    }
    *temp = fopen("temp.mp3", "wb");
    if (*temp==NULL)
    {
        printf("ERROR: Unable to create temp.mp3\n");
        fclose(*src);
        return e_failure;
    }
    return e_success;
}
/*
Function : decode_frame_size
Description :
    Converts big-endian frame size bytes
    into unsigned integer.
*/
uint decode_frame_size(uchar bytes[])
{
    return ((uint)bytes[0] << 24) | ((uint)bytes[1] << 16) | ((uint)bytes[2] << 8) | (uint)bytes[3];
}
/*
Function : encode_frame_size
Description :
    Converts integer frame size into
    4-byte big-endian representation.
 */
void encode_frame_size(uint size,uchar bytes[])
{
    bytes[0] = (size >> 24) & 0xFF;
    bytes[1] = (size >> 16) & 0xFF;
    bytes[2] = (size >> 8) & 0xFF;
    bytes[3] = size & 0xFF;
}
/*
Function : copy_bytes
Description :
    Copies required number of bytes from
   source file to destination file.
*/
void copy_bytes(FILE *src,FILE *dest,uint count)
{
    uchar buffer[1024];
    while (count>0)
    {
        uint bytes;
        if (count>sizeof(buffer))
        {
            bytes=sizeof(buffer);
        }
        else
        {
            bytes=count;
        }
        if (fread(buffer, 1, bytes, src)!=bytes)
        {
            break;
        }
        fwrite(buffer, 1, bytes, dest);
        count=count-bytes;
    }
}
void edit_tag(char *option, char *filename)
{
    Frame frame; // Uses your exact struct definition with flags[2]
    FILE *src;
    FILE *temp;
    uchar header[10];
    char new_data[1024];

    // Convert option to frame ID
    if (get_frame_id(option, frame.id) == e_failure)
    {
        printf("ERROR: Invalid option\n");
        return;
    }

    // Read new value
    printf("Enter the new data: ");
    scanf(" %[^\n]", new_data);

    // Open source and temporary files
    if (file_open(filename, &src, &temp) == e_failure)
    {
        return;
    }

    // Read ID3 header
    if (read_header(src, header) == e_failure)
    {
        printf("ERROR: Unable to read header\n");
        fclose(src);
        fclose(temp);
        return;
    }

    // Validate ID3 header
    if (validate_header(header) == e_failure)
    {
        printf("ERROR: Valid ID3v2.3.0 header not found\n");
        fclose(src);
        fclose(temp);
        remove("temp.mp3");
        return;
    }

    // Copy header to temporary file 
    fwrite(header, 1, 10, temp);

    while (1)
    {
        char current_tag[5];
        uchar size[4];
        uint current_frame_size;

        // Read frame ID
        if (fread(current_tag, 1, 4, src) != 4)
        {
            break;
        }
        current_tag[4] = '\0';

        // Empty frame means padding
        if (current_tag[0] == '\0')
        {
            fwrite(current_tag, 1, 4, temp);
            break;
        }

        // Read frame size
        if (fread(size, 1, 4, src) != 4)
        {
            break;
        }
        current_frame_size = decode_frame_size(size);

        // FIX: Read exactly 2 bytes to match your structure's flags[2] array boundary
        if (fread(frame.flags, 1, 2, src) != 2)
        {
            break;
        }

        // Check whether current frame matches target to update
        if (strcmp(current_tag, frame.id) == 0)
        {
            uint new_size;
            uchar new_size_bytes[4];
            uchar encoding = 0; // Default to ISO-8859-1 / ASCII

            // Write matching Frame Header definitions into the destination stream
            fwrite(current_tag, 1, 4, temp);
            encode_frame_size(current_frame_size, new_size_bytes);
            fwrite(new_size_bytes, 1, 4, temp);
            
            // FIX: Write exactly 2 bytes from your structure's flags array
            fwrite(frame.flags, 1, 2, temp);

            // Handle unique structural layout requirement for COMM frame types
            if (strcmp(current_tag, "COMM") == 0)
            {
                uchar language[3] = {'e', 'n', 'g'};
                char original_description[256] = "";
                
                // Read the old data to parse and maintain the original Description string
                if (current_frame_size > 4)
                {
                    uchar *old_data = malloc(current_frame_size);
                    if (old_data != NULL)
                    {
                        fread(old_data, 1, current_frame_size, src);
                        
                        int pos = 4; // Skip past encoding (1) + language text (3)
                        int d_idx = 0;
                        while (pos < current_frame_size && old_data[pos] != '\0' && d_idx < 255)
                        {
                            original_description[d_idx++] = old_data[pos++];
                        }
                        original_description[d_idx] = '\0';
                        free(old_data);
                    }
                    else
                    {
                        fseek(src, current_frame_size, SEEK_CUR); // Fallback skip if allocation fails
                    }
                }
                else
                {
                    fseek(src, current_frame_size, SEEK_CUR);
                }

                // Compute layout sizing bounds
                // 1 byte (encoding) + 3 bytes (language) + description string + 1 byte (null terminator) + payload comment string
                new_size = 1 + 3 + strlen(original_description) + 1 + strlen(new_data);

                if (new_size > current_frame_size)
                {
                    printf("ERROR: New comment value string exceeds the current frame size limitation.\n");
                    fclose(src);
                    fclose(temp);
                    remove("temp.mp3");
                    return;
                }

                // Write Layout Elements sequentially
                fwrite(&encoding, 1, 1, temp);
                fwrite(language, 1, 3, temp);
                fwrite(original_description, 1, strlen(original_description) + 1, temp); // Writes description content + '\0'
                fwrite(new_data, 1, strlen(new_data), temp);

                // Safe structural padding container retention configuration logic
                uint remaining = current_frame_size - new_size;
                for (uint i = 0; i < remaining; i++)
                {
                    uchar zero = 0;
                    fwrite(&zero, 1, 1, temp);
                }
            }
            else
            {
                /*
                Standard Text Frames (TIT2, TPE1, TALB, etc.):
                Encoding (1 byte) + text string characters
                */
                new_size = 1 + strlen(new_data);
                
                // Advance past source file position to overwrite values safely
                fseek(src, current_frame_size, SEEK_CUR);

                if (new_size > current_frame_size)
                {   
                    printf("ERROR: New data text string input exceeds the current frame size limitation.\n");
                    fclose(src);
                    fclose(temp);
                    remove("temp.mp3");
                    return;
                }

                // Write replacement data fields
                fwrite(&encoding, 1, 1, temp);
                fwrite(new_data, 1, strlen(new_data), temp);

                // Zero-fill remaining space in the frame buffer context block
                uint remaining = current_frame_size - new_size;
                for (uint i = 0; i < remaining; i++)
                {
                    uchar zero = 0;
                    fwrite(&zero, 1, 1, temp);
                }
            }

            printf(BLUE"\n============================================\n"RESET);
            printf(GREEN"*** Tag updated successfully ***\n"RESET);
            printf(BLUE"\n============================================\n"RESET);
            
            // Keep copying the rest of the file frames to preserve complete tracking continuity
            continue; 
        }   

        /*
        Current frame is not the required frame.
        Copy it exactly as it is to the temporary file.
        */
        fwrite(current_tag, 1, 4, temp);
        fwrite(size, 1, 4, temp);
        
        // FIX: Match copying offsets correctly using 2 bytes for non-edited frames
        fwrite(frame.flags, 1, 2, temp);
        
        // Copy the frame payload exactly
        copy_bytes(src, temp, current_frame_size);
    }

    //Copy the remaining MP3 audio data.
    uchar ch;
    while (fread(&ch,1,1,src)==1) 
    {
        fwrite(&ch,1,1,temp);
    }
    fclose(src);
    fclose(temp);
    /*
    Replace original file with
    modified temporary file.
     */
    if (remove(filename)==0) 
    {
        if (rename("temp.mp3",filename) == 0) 
        {
            printf(BLUE"\n====================================================================\n"RESET);
            printf(GREEN"\n***   SUCCESS: MP3 tag edited and file updated successfully!   ***\n"RESET);
            printf(BLUE"\n====================================================================\n"RESET);
        } 
        else 
        {
            printf(BLUE"\n====================================================================\n"RESET);
            printf(RED"\n***   ERROR: Unable to rename temp.mp3 to original filename.   ***\n"RESET);
            printf(BLUE"\n====================================================================\n"RESET);
        }
    } 
    else 
    {
        printf(BLUE"\n============================================================================\n"RESET);
        printf(RED"\n***   ERROR: Unable to remove original file. Check file permissions.   ***\n"RESET);
        printf(BLUE"\n============================================================================\n"RESET);
    }
}
