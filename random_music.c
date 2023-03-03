#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SAMPLING_RATE 44100     // Sampling rate
#define DURATION_SEC 10         // Music duration (seconds)
#define FREQUENCY 440           // Fundamental frequency
#define AMPLITUDE 30000         // Amplitude
#define MAX_VARIATION 1000      // Maximum variation

int main() {
    int num_samples = SAMPLING_RATE * DURATION_SEC;  // Number of samples
    short data[num_samples];                        // Sample data
    srand(time(NULL));                              // Initialize random seed

    // Generate sample data of rectangular wave
    for (int i = 0; i < num_samples; i++) {
        if (rand() % 2 == 0) {
            data[i] = AMPLITUDE;
        } else {
            data[i] = -AMPLITUDE;
        }

        // Randomly vary the sample data
        int variation = rand() % (2 * MAX_VARIATION) - MAX_VARIATION;
        data[i] += variation;
    }

    // Save the sample data in WAV file format
    FILE *fp;
    fp = fopen("random_music.wav", "wb");
    if (fp == NULL) {
        printf("Failed to open file.\n");
        return 1;
    }

    // Create WAV file header
    char riff[] = "RIFF";
    int file_size = num_samples * 2 + 36;
    char wave[] = "WAVE";
    char fmt[] = "fmt ";
    int fmt_size = 16;
    short format_id = 1;
    short channel = 1;
    int byte_per_sec = SAMPLING_RATE * 2;
    short block_size = 2;
    short bit_per_sample = 16;
    char data_header[] = "data";
    int data_size = num_samples * 2;

    fwrite(riff, 1, 4, fp);
    fwrite(&file_size, 4, 1, fp);
    fwrite(wave, 1, 4, fp);
    fwrite(fmt, 1, 4, fp);
    fwrite(&fmt_size, 4, 1, fp);
    fwrite(&format_id, 2, 1, fp);
    fwrite(&channel, 2, 1, fp);
    fwrite(&SAMPLING_RATE, 4, 1, fp);
    fwrite(&byte_per_sec, 4, 1, fp);
    fwrite(&block_size, 2, 1, fp);
    fwrite(&bit_per_sample, 2, 1, fp);
    fwrite(data_header, 1, 4, fp);
    fwrite(&data_size, 4, 1, fp);

    // Save the sample data
    fwrite(data, sizeof(short), num_samples, fp);

    fclose(fp);
    printf("Finished.\n");

    return 0;
}
