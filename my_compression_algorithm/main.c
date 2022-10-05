#include <stdio.h>

int main() {

    // data
#define DATA_LENGTH 20
    float data[DATA_LENGTH] = {0.006, 0.006, 0.003, -0.0006, -0.0006, -0.006, -0.0078, -0.0078};

    // my_compression_algorithm

    float keys[DATA_LENGTH] = {}; int keys_length = 0;
    char values[DATA_LENGTH*2] = {}; int values_length = 0;
    int v = 0;
    for (int i = 0; i < DATA_LENGTH; ++i) {
        if (data[i] != 0) {
            keys[keys_length++] = data[i];
            for (int j = 0; j < DATA_LENGTH; ++j) {
                if (data[j] == keys[keys_length-1]) {
                    values[values_length++] = '0' + j;
                    data[j] = 0;
                }
            }
            values[values_length++] = '|';
        }
    }
    for (int i = 0; i < keys_length; ++i) {
        printf("%f, ", keys[i]);
    }
    printf("\n");
    for (int i = 0; i < values_length-1; ++i) {
        printf("%c, ", values[i]);
    }


    // decompression


    //printf("Hello, World!\n");
    return 0;
}
