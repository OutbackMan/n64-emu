#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define BYTE (8)
#define KILOBYTE (1000 * BYTE)
#define MEGABYTE (1000 * KILOBYTE)

#define ROM_FILE_BUFFER_SIZE (40 * MEGABYTE) 
#define ROM_FILE_NAME_BUFFER (256)

#define GPR_REGISTER_COUNT 32
#define FPR_REGISTER_COUNT 32

uint8_t rom_file_buffer[ROM_FILE_BUFFER_SIZE] = {0};

unsigned char rom_file_name[ROM_FILE_NAME_BUFFER] = {0};

struct Cpu {
	uint64_t gpr[GPR_REGISTER_COUNT];
	double fpr[FPR_REGISTER_COUNT]; // Need ad-hoc solution for portability
};

int main(int argc, char **argv)
{
	strncpy(rom_file_name, argv[1], ROM_FILE_NAME_BUFFER - 1);
	rom_file_name[ROM_FILE_NAME_BUFFER - 1] = '/0';
	
	FILE *rom_file = NULL;

	rom_file = fopen(rom_file_name, "rb");

	fseek(rom_file, 0, SEEK_END);	
	long rom_file_size = ftell(rom_file);
	assert(rom_file_size * 8 < ROM_FILE_BUFFER_SIZE);
	fseek(rom_file, 0, SEEK_SET);
	fread(rom_file_buffer, rom_file_size, sizeof(uint8_t), rom_file);

	fclose(rom_file);

	return 0;
}
