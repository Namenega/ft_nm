#include "../hdr/nm.h"


void	print_error(char *s, int exit_code, int fd) {

	perror(s);
	if (exit_code != 1 && exit_code != 2) {
		printf("Exit Code: %d\nClosing FD...\n", exit_code);		// TO REMOVE
		close(fd);
	}
	printf("Ending Program...\n\n");							// TO REMOVE
	exit(exit_code);
}

int		main(int ac, char **av) {

	int				fd;
	struct stat		st;
	void			*data;

	// Validate arguments (except at least one for ELF file)
	if (ac != 2) {
		perror("Wrong number of arguments");
		exit(EXIT_ARG);
	}


	// Open -- open(file, options)
	fd = open(av[1], O_RDONLY);
	if (fd < 1)
		print_error("open()", EXIT_FD, fd);

	// Check file -- fstat(fd, struct stat)
	if (fstat(fd, &st) < 0)
		print_error("fstat()", EXIT_FST, fd);

	// Check if regular file or not
	if (!S_ISREG(st.st_mode))
		print_error("Not regular file", EXIT_FST, fd);
	else {													// TO REMOVE
		printf("FILE: %s\n", av[1]);						// TO REMOVE
		printf("[GOOD] - It is a regular file\n");			// TO REMOVE
	}



	// Map file into memory
	data = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	
	// Check if mapping succeeded
	if (data == MAP_FAILED)
		print_error("mmap()", EXIT_MMAP, fd);



	// Validate ELF magic byte
	if (isELFfile(data, st.st_size) != 1) {
		printf("--------------- CLEAN UP ---------------\n");
		printf("\nUnmapping data from memory...\n");		// TO REMOVE
		munmap(data, st.st_size);
		print_error("Not an ELF file", EXIT_ELF, fd);
	}

	// Parse ELF header
	elf_parser(data);

	// Locate section header, string table


	// Find symbol table (.symtab) and associated string table


	// Read and interpret symbol entries


	// Print symbol tables entries


	// clean up
	printf("\n--------------- CLEAN UP ---------------\n");	// TO REMOVE
	printf("Unmapping data from memory...\n");				// TO REMOVE
	munmap(data, st.st_size);
	printf("Closing FD...\n");								// TO REMOVE
	close(fd);
	printf("Ending Program...\n\n");						// TO REMOVE

	return (0);
}
