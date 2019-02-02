#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        fprintf(stderr, "Usage: copy infile outfile\n");
        return 1;
    }

    int n = atoi(argv[1]);

    if (0 > n || n > 100)
    {
        fprintf(stderr, "n should be from 0 to 100\n");
        return 2;
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 5;
    }

    // determine new dimensions
    int oldWidth = bi.biWidth;
    int oldHeight = bi.biHeight;
    int newWidth = oldWidth * n;
    int newHeight = oldHeight * n;

    // determine padding for scanlines
    int padding_old = (4 - (oldWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int padding_new = (4 - (newWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // reconfigure headers
    bi.biHeight = newHeight;
    bi.biWidth = newWidth;
    bi.biSizeImage = ((sizeof(RGBTRIPLE) * newWidth) + padding_new) * abs(newHeight);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // allocate a memory to store one scanline
    RGBTRIPLE scanline[newWidth * sizeof(RGBTRIPLE)];

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(oldHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < oldWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // create a new scanline in a temporary array
            for (int k = 0; k < n; k++)
            {
                scanline[(j * n) + k] = triple;
            }
        }

        for (int k = 0; k < n; k++)
        {
            fwrite(scanline, sizeof(RGBTRIPLE), newWidth, outptr);

            // then add it back (to demonstrate how)
            for (int l = 0; l < padding_new; l++)
            {
                fputc(0x00, outptr);
            }
        }

        // skip over padding, if any
        fseek(inptr, padding_old, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
