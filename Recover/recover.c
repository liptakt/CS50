#include <stdio.h>
#include <stdlib.h>

const int BUFFER_SIZE = 512;

int main(int argc, char* argv[])
{
	// ensure proper usage
	if (argc != 2)
	{
		printf("Command Line error\n");
		return 1;
    }

    //sets the file name to infile
    char* infile = argv[1];

    //creates and opens inptr for reading only
    FILE *inptr = fopen(infile, "r");

    //checks to see if null
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    //make outfile
    FILE* outptr = NULL;

    //number of files
    int counter = 0;

    //Creates buffer
    unsigned char buffer[BUFFER_SIZE];


    //Goes through cardfile until blocks are done
    while(fread(buffer, BUFFER_SIZE, 1, inptr) == 1)
    {

        //Checks if the first four bytes are JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] == 0xe0 || buffer[3] == 0xe1))
        {

            //Closes image if one has been created
            if(counter > 0)
            {
                fclose(outptr);
            }

            //Make space for JPG
            char filename[8];

            //Make name for couter image
            sprintf(filename, "%03d.jpg", counter);

            // open counter image file
            outptr = fopen(filename, "w");

            if (outptr == NULL)
            {
                fprintf(stderr, "Could not create %s.\n", filename);
                return 3;
            }

            //Increments number of image files created
            counter++;

        }


        // write to image file only if one exists
        if (outptr != NULL)
        {
            // write to image file
            fwrite(buffer, BUFFER_SIZE, 1, outptr);
        }


    }

    // close last image file
    fclose(outptr);

    // close card.raw
    fclose(inptr);

    return 0;

}
