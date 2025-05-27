
#ifndef NM_H
# define NM_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <fcntl.h>
# include <sys/mman.h>
# include <sys/stat.h>
//# include <string.h>				// TO REMOVE

# include "../inc/libft/libft.h"

// EXIT ERROR VALUE
# define EXIT_ARG		1
# define EXIT_FD		2
# define EXIT_FST		3
# define EXIT_MMAP		4
# define EXIT_ELF		5
# define EXIT_SYMTAB	6


// TABLE VALUE MACRO
# define SHT_SYMTAB	2
# define SHT_STRTAB	3


// BINDING INFO SYMBOL MACRO (upper 4 bits)
# define ELF64_ST_BIND(i) ((i) >> 4)
// TYPE INFO SYMBOL MACRO (lower 4 bits)
# define ELF64_ST_TYPE(i) ((i) & 0xF)


// SYMBOL BINDING VALUE
# define STB_LOCAL   0
# define STB_GLOBAL  1
# define STB_WEAK    2


// SYMBOL TYPE VALUE
#define STT_NOTYPE  0
#define STT_OBJECT  1
#define STT_FUNC    2
#define STT_SECTION 3
#define STT_FILE    4
#define STT_COMMON  5
#define STT_TLS     6


// SYMBOL SECTION INDEX VALUE
#define SHN_UNDEF     0
#define SHN_ABS       0xFFF1
#define SHN_COMMON    0xFFF2


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
	uint16_t		e_shstrndx;		// Index of shstrtab (Elf64_Shdr struct)

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


/* Symtab structure*/
typedef struct	Elf64_Sym {

	uint32_t		st_name;	// Symbol name (index into string table)
    unsigned char	st_info;	// Symbol type and binding
    unsigned char	st_other;	// Visibility
    uint16_t		st_shndx;	// Section index
    uint64_t		st_value;	// Symbol value
    uint64_t		st_size;	// Symbol size
}				Elf64_Sym;


/* Global ELF headers and section headers structure */
typedef struct	s_Elfdata {

	Elf64_Ehdr	*ehdr;
	Elf64_Shdr	*shdr;
	const char	*shstrtab;
	Elf64_Shdr	*symtab_hdr;
	Elf64_Shdr	*strtab_hdr;
}				t_Elfdata;


/* ---------- MAIN FUNCTIONS ---------------- */

int			main(int ac, char **av);
void		print_error(char *s, int exit_code, int fd);

/* ---------- ELF PARSER FUNCTIONS ---------- */
//void		printFileData(void *elf_data, size_t st_size);
//void		printELFHeaderData(Elf64_Ehdr *ehdr);
//void		printELFSectionHeaderData(Elf64_Ehdr *ehdr, Elf64_Shdr *Shdr);
int			isELFfile(void *elf_data, size_t st_size);
Elf64_Shdr	*findSymtab(Elf64_Ehdr *ehdr, Elf64_Shdr *shdr, const char *shstrtab);
t_Elfdata	elfParser(void *elf_data);


/* ---------- SYMBOL PARSER FUNCTIONS ---------- */
void		symbolHandling(void *elf_data, t_Elfdata edata);


#endif
