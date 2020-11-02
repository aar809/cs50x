#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>

int main(int argc, char *argv[])
{
    //Ensure user ran program with 2 words at prompt
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    //open file
    FILE *file = fopen(argv[1], "r");

    if (file == NULL)
    {
        return 1;
    }

    //Create outfile for picture
    //FILE is the data type... what is the "*img" doing...?
    FILE *img = NULL;

    // Create buffer and filename arrays
    unsigned char buffer[512];
    char filename[8];

    //create counter for file name
    int counter = 0;

    //Set flag for if file is currently reading an jpg
    bool flag = false;

    //read the file
    //what is fread supposed to return? when fail/success? 1 is when it is successful? in other words, when there is something to read??
    //how does this while loop work? since it's always just reading the 1st 4 bytes of the Block of 512... so it doesn't iterate within the whole block?
    while (fread(buffer, 512, 1, file) == 1)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (flag == true)
            {
                fclose(img);
            }
            else
            {
                flag = true;
            }

            sprintf(filename, "%03i.jpg", counter);
            img = fopen(filename, "w");
            counter++;
        }

        //what does '&buffer' mean?
        //what does this fwrite do??
        if (flag == true)
        {
            fwrite(&buffer, 512, 1, img);
        }
    }

    //Close all files
    fclose(file);
    fclose(img);

    //Success
    return 0;
}

// first 4 bytes:
// 0xff
// 0xd8
// 0xff
// 0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, or 0xef
