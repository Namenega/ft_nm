#include "../hdr/nm.h"

/*
 * Utility function to print 'data' (mapped memory of the file)
 */

void	printFileData(unsigned char *data, size_t st_size) {

	if (!data || !st_size)
		printf("Missing data");

	printf("\n\n-----------------------------\n\n");
	
	for (size_t i = 0; i < st_size; i++)
		printf("%c", data[i]);

	printf("\n\n-----------------------------\n\n");
}

/*
 * Check the Magic Bytes of the file
 * Return 1 if it is an ELF file
 * Return 0 if it is not an ELF file
 *
 * data = mapped memory result, from 'mmap()'
 * stsize = size of mapped data, from 'fstat()'
 */

int		isELFfile(unsigned char *data, size_t st_size) {
	
	if (!data || !st_size)
		return (0);

	if (st_size >= 4 && data[0] == 0x7F &&
		data[1] == 'E' &&
		data[2] == 'L' &&
		data[3] == 'F') {
		printf("[GOOD] - This is an ELF file!\n");		// TO REMOVE
		return (1);
	}
	return (0);
}


