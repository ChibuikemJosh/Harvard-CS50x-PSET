// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // Buffer to store the wav header (44 bytes)
    uint8_t header[HEADER_SIZE];

    // Copy header from input file to outputfile without modifying them
    fread(header, HEADER_SIZE, 1, input);
    fwrite(header, HEADER_SIZE, 1, output);

    // Variable to store each audio sample (16-bit signed integers)
    int16_t sample;

    // Read samples of 2 byte (int16_t) from input file until the end of the file
    while (fread(&sample, sizeof(int16_t), 1, input))
    {
        sample *= factor; // Adjust volume by multiplying sample by a factor
        fwrite(&sample, sizeof(int16_t), 1,
               output); // Write the adjusted sample into the output file
    }

    // Close files
    fclose(input);
    fclose(output);
}
