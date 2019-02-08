#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    const int BLOCK = 512;

    if (argc != 2)
    {
        fprintf(stderr, "2 cmd args expected\n");
        return 1;
    }

    char *infile = argv[1];

    FILE *inf = fopen(infile, "r");
    if (inf == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    int counter = 0;
    unsigned char buf[BLOCK];

    FILE *outf = NULL;

    while (fread(buf, BLOCK, 1, inf))
    {
        if (buf[0] == 0xff && buf[1] == 0xd8 && buf[2] == 0xff
            && (buf[3] == 0xe0 || buf[3] == 0xe1))
        {
            if (outf != NULL)
                fclose(outf);

            char filename[8];
            sprintf(filename, "%03d.jpg", counter);

            outf = fopen(filename, "w");

            counter++;
        }

        if (outf != NULL)
            fwrite(buf, BLOCK, 1, outf);
    }

    if (outf != NULL)
        fclose(outf);

    fclose(outf);
    fclose(inf);

    return 0;

}
