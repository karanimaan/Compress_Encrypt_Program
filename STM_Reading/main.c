#include <stdio.h>
#include <string.h>

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

/*
#define TEXTFILE_PATH "C:\Users\Karan\OneDrive - University of Cape Town\COURSES\Design\Data_Transfer_Program\STM_Reading\encoded.txt"
*/
#define COMPRESSED_LENGTH 70  // 7/8 size of original
#define DECOMPRESSED_LENGTH 80

int main() {
    FILE *f = fopen("C:\\Users\\Karan\\OneDrive - University of Cape Town\\COURSES\\Design\\Data_Transfer_Program\\STM_Reading\\encoded.txt", "r");
    unsigned char encoded_string[COMPRESSED_LENGTH] = "";    // compressed and encrypted string
    fgets(encoded_string, COMPRESSED_LENGTH, f);
    //printf("%s %llu\n", encoded_string, strlen(encoded_string));

    unsigned char compressed_string[COMPRESSED_LENGTH] = "";    // decrypted string
    // decryption @Omo

    char decompressed_string[DECOMPRESSED_LENGTH];
    Decompression(decompressed_string, encoded_string, COMPRESSED_LENGTH);
    printf("%s", decompressed_string);
    return 0;
}
