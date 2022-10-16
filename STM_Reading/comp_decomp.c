#include <stdio.h>
#include <string.h>

void Compression(unsigned char *sizeOut, const char *Message_size) {

	unsigned long long Buffer = 0;
	char Bits = 0;

	while (*Message_size != 0) {
		Buffer |= (unsigned long long)(*Message_size++) << Bits;
		Bits += 7;
		if (Bits == 7 * 8) {
			while (Bits > 0) {
				*sizeOut++ = Buffer;
				Buffer >>= 8;
				Bits -= 8;
			}
			Bits = 0;
			Buffer = 0;
		}
	}
	char cbits = Bits;
	while (cbits > 0) {
		*sizeOut++ = Buffer;
		Buffer >>= 8;
		if(Bits<8){
			cbits =0;
		}
		else{
		Bits -= 8;
		cbits = Bits;
		}
	}
}

void Decompression (char *Out_size, const unsigned char *Compressed_size, unsigned CompressedLength) {

	unsigned long long Buffer = 0;
	char Bits = 0;
	while (CompressedLength) {
		while (CompressedLength && Bits < 7 * 8) {
			Buffer |= (unsigned long long)*Compressed_size++ << Bits;
			Bits += 8;
			--CompressedLength;
		}
		while (Bits > 0) {
			*Out_size++ = Buffer & 0x7F;
			Buffer >>= 7;
			Bits -= 7;
		}

		Bits = 0;
		Buffer = 0;
	}
}

#define COMPRESSED_LENGTH 9  // => 7//8 * size of original
#define DECOMPRESSED_LENGTH 10
#define COMPRESSED_FILENAME "C:\\Users\\Karan\\OneDrive - University of Cape Town\\COURSES\\Design\\Data_Transfer_Program\\STM_Reading\\compressed.txt"
#define DECOMPRESSED_FILENAME "C:\\Users\\Karan\\OneDrive - University of Cape Town\\COURSES\\Design\\Data_Transfer_Program\\STM_Reading\\decompressed.txt"

int main() {

    float sensor_float = -0.0249;

    #define SENSOR_DATA_LENGTH 80
    char sensor_data[SENSOR_DATA_LENGTH];
    sprintf(sensor_data,"%.5f", sensor_float);

    // compress
    unsigned char compressed_string[COMPRESSED_LENGTH] = "";
    Compression(compressed_string, sensor_data);

    // decompress
    char decompressed_string[DECOMPRESSED_LENGTH];
    Decompression(decompressed_string, compressed_string, COMPRESSED_LENGTH);

    // write to file
    FILE* f = fopen(DECOMPRESSED_FILENAME, "w");
    fprintf(f, "%s\n", decompressed_string);
    fclose(f);

    //printf("%s\n", decompressed_string);

    return 0;
}