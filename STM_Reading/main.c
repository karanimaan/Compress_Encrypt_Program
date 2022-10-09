#include <stdio.h>
#include <string.h>

unsigned char  key=0b01100101;

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

unsigned char encode(unsigned char pt, unsigned char key, int count)
{
	unsigned char result;                                                           // declaring our return variable
	result = pt;                                                                    // setting it equal to our input paramater
	int i;
	if ((count%3) == 0){                                                            // if counter mod 3 = 0
		for(i = 0; i< 8; i+=2){			                                // loop through all other bits starting at 0
			if(((getBit(pt,i))^(getBit(key,i))) == 0)                       // if the input xor the key bit = 0
				result = clearBit(result,i);                            // set it to 0
			else if (((getBit(pt,i))^(getBit(key,i))) == 1)                 // if the input xor the key bit = 1
				result = setBit(result,i);                              // set it to 1
		}
	}
	else if((count%3) == 1){                                                        // if the counter mod 3 = 1
		for(i = 1; i< 8; i+=2){			                                // loop through all other bits starting at 1
			if(((getBit(pt,i))^(getBit(key,i))) == 0)                       // if the input xor the key bit = 0
				result = clearBit(result,i);                            // set it to 0
			else if (((getBit(pt,i))^(getBit(key,i))) == 1)                 // if the input xor the key bit = 1
				result = setBit(result,i);	                        // set it to 1
		}
	}
	else if((count%3) == 2){                                                        // if the counter mod 3 = 2
		for(i = 0; i< 8; i++){						        // loop through all other bits starting at 1
			if(((getBit(pt,i))^(getBit(key,i))) == 0)                       // if the input xor the key bit = 0
				result = clearBit(result,i);                            // set it to 0
			else if (((getBit(pt,i))^(getBit(key,i))) == 1)                 // if the input xor the key bit = 1
				result = setBit(result,i);		                // set it to 1
		}
	}
	return result;                                                                  // return our new Encrypted bit
}

#define COMPRESSED_LENGTH 70  // 7/8 size of original
#define DECOMPRESSED_LENGTH 80

int main() {
    FILE *f = fopen("encoded.txt", "r");
    unsigned char encoded_string[COMPRESSED_LENGTH] = "";    // compressed and encrypted string
    fgets(encoded_string, COMPRESSED_LENGTH, f);
    printf("%s %llu\n", encoded_string, strlen(encoded_string));

    unsigned char compressed_string[COMPRESSED_LENGTH] = "";    // decrypted string
    // decryption @Omo
    char out;
        for(int i = 0; i < sizeof(encoded_string); i++){                      // loops through the stored ints and decrypts them back to chars and prints them
            if (encoded_string[i] == -1)
                        break;
	        out = encode(encoded_string[i], key, i);
	        compressed_string[i]=out;
	}
    char decompressed_string[DECOMPRESSED_LENGTH];
    Decompression(decompressed_string, compressed_string, COMPRESSED_LENGTH);
    printf("%s %llu\n\n", decompressed_string, strlen(decompressed_string));
    return 0;
}
