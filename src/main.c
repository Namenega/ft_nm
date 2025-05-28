#include "../hdr/nm.h"


void	print_error(char *s, int exit_code, int fd) {

	perror(s);
	if (exit_code != 1 && exit_code != 2) {
		close(fd);
	}
	exit(exit_code);
}

/*
 * If no argument provided, try a.out by default
 * If no a.out, return 0
 */

static int no_arg(const char *filename) {

    int fd = open(filename, O_RDONLY);

	if (fd < 0)
		return 0;  // file not found or unreadable

	close(fd);

	return 1;      // file exists
}


int		main(int ac, char **av) {

	int				fd;
	struct stat		st;
	void			*data;
	t_Elfdata		edata;

	// Validate arguments (except at least one for ELF file)
	if (ac == 1) {
		if (!no_arg("a.out")) {
			perror("ft_nm: 'a.out'");
			exit(EXIT_ARG);
		}
		ac = 2;
		av[1] = "a.out";
	}

	for (int i = 1; i < ac; i++) {

		fd = open(av[i], O_RDONLY);
		if (fd < 1) {
			ft_printf("ft_nm: '%s': No such file\n", av[i]);
			continue;
		}

		// Check file -- fstat(fd, struct stat)
		if (fstat(fd, &st) < 0)
			print_error("fstat()", EXIT_FST, fd);

		// Check if regular file or not
		if (!S_ISREG(st.st_mode)) {
			ft_printf("ft_nm: Warning: '%s' is not a regular file\n", av[i]);
			close(fd);
			continue;
		}

		// Map file into memory
		data = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	
		// Check if mapping succeeded
		if (data == MAP_FAILED)
			print_error("mmap()", EXIT_MMAP, fd);

		// Validate ELF magic byte
		if (isELFfile(data, st.st_size) != 1) {
			munmap(data, st.st_size);
			close(fd);
			ft_printf("ft_nm: %s: file format not recognized\n", av[i]);
			continue;
		}

		//ft_printf("\n%s:\n", av[i]);

		// Parse ELF header - locate section header, string table
		edata = elfParser(data);

		if (!edata.symtab_hdr || !edata.strtab_hdr) {
			munmap(data, st.st_size);
			close(fd);
			ft_printf("ft_nm: %s: no symbols\n", av[i]);
			continue;
		}

		ft_printf("\n%s:\n", av[i]);
		
		// Find symbol table (.symtab) and associated string table
		// Read and interpret symbol entries
		// Print symbol tables entries
		symbolHandling(data, edata);

		// clean up
		munmap(data, st.st_size);
		close(fd);
	}

	return (0);
}


