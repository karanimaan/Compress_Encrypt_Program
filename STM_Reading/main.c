#include <stdio.h>
#include <string.h>

unsigned char getBit(unsigned char, int);
unsigned char setBit(unsigned char, int);
unsigned char clearBit(unsigned char, int);
unsigned char encode(unsigned char, unsigned char, int);
void foo ( char *line, int *nums);

unsigned char  key=237;
int nums[256];

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

/*
#define TEXTFILE_PATH "C:\Users\Karan\OneDrive - University of Cape Town\COURSES\Design\Data_Transfer_Program\STM_Reading\encoded.txt"
*/
#define COMPRESSED_LENGTH 80  // 7/8 size of original
#define DECOMPRESSED_LENGTH 80
#define FILENAME "C:\\Users\\Karan\\OneDrive - University of Cape Town\\COURSES\\Design\\Data_Transfer_Program\\STM_Reading\\compressed.txt"

int main() {
    FILE *f = fopen(FILENAME, "r");
    unsigned char compressed_string[COMPRESSED_LENGTH] = "";    // compressed and encrypted string
    fgets(compressed_string, COMPRESSED_LENGTH, f);
    //printf("%s %llu\n", compressed_string, strlen(compressed_string));

    char decompressed_string[DECOMPRESSED_LENGTH];
    Decompression(decompressed_string, compressed_string, COMPRESSED_LENGTH);
    printf("%s\n", decompressed_string);


    return 0;
}
unsigned char getBit(unsigned char c, int n)
{
	c = (c&(1<<n))>>n;
	return c;
}

unsigned char setBit(unsigned char c, int n)
{
	c = c|(1<<n);
	return c;
}

unsigned char clearBit(unsigned char c, int n)
{
	c = c & (~(1<<n));
	return c;
}
void foo ( char *line, int *nums) {
    int num, i = 0, len;
    while ( sscanf( line, "%d%n", &num, &len) == 1 ) {
        nums[i]= num;
        line += len;    // step past the number we found
        i++;            // increment our count of the number of values found
    }
}
