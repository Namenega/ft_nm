
#ifndef NM_H
# define NM_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <fcntl.h>
# include <sys/mman.h>
# include <sys/stat.h>

# include "../inc/libft/libft.h"

# define EXIT_ARG	1
# define EXIT_FD	2
# define EXIT_FST	3
# define EXIT_MMAP	4
# define EXIT_ELF	5


/* Executable header structure */
typedef struct	Elf64_Ehdr {

	unsigned char	e_ident[16];
	uint16_t		e_type;
	uint16_t		e_machine;
	uint32_t		e_version;
	uint64_t		e_entry;
	uint64_t		e_phoff;		// Program Header Offset
	uint64_t		e_shoff;		// Section Header Offset
	uint32_t		e_flags;
	uint16_t		e_ehsize;		// ELF header size
	uint16_t		e_phentsize;	// Program Header Entry Size
	uint16_t		e_phnum;		// Program Header Entries Number
	uint16_t		e_shentsize;	// Section Header Entry Size
	uint16_t		e_shnum;		// Section Header Entries Number
	uint16_t		e_shstrndx;		//Index of shstrtab (Elf64_Shdr struct)

}				Elf64_Ehdr;


/* Section Header structure */
typedef struct	Elf64_Shdr {

	uint32_t	sh_name;
	uint32_t	sh_type;
	uint64_t	sh_flags;
	uint64_t	sh_addr;
	uint64_t	sh_offset;
	uint64_t	sh_size;
	uint32_t	sh_link;
	uint32_t	sh_info;
	uint64_t	sh_addralign;	//power of 2
	uint64_t	sh_entsize;		//0 if unused

}				Elf64_Shdr;



/* ---------- MAIN FUNCTIONS ---------------- */

int		main(int ac, char **av);
void	print_error(char *s, int exit_code, int fd);

/* ---------- ELF PARSER FUNCTIONS ---------- */
void	printFileData(unsigned char *data, size_t st_size);
int		isELFfile(unsigned char *data, size_t st_size);


#endif
