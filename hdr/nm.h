
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
# define EXIT_MALLOC	7


// TABLE VALUE MACRO
# define SHT_NULL			0  // Section header table entry unused
# define SHT_PROGBITS		1  // Program data
# define SHT_SYMTAB			2  // Symbol table
# define SHT_STRTAB			3  // String table
# define SHT_RELA			4  // Relocation entries with addends
# define SHT_HASH			5  // Symbol hash table
# define SHT_DYNAMIC		6  // Dynamic linking information
# define SHT_NOTE			7  // Notes
# define SHT_NOBITS			8  // Program space with no data (bss)
# define SHT_REL			9  // Relocation entries, no addends
# define SHT_SHLIB			10 // Reserved
# define SHT_DYNSYM			11 // Dynamic linker symbol table
# define SHT_INIT_ARRAY		14 // Initialization function pointers
# define SHT_FINI_ARRAY		15 // Termination function pointers
# define SHT_PREINIT_ARRAY	16 // Pre-initialization function pointers
# define SHT_GROUP			17 // Section group
# define SHT_SYMTAB_SHNDX	18 // Extended section indices



// BINDING INFO SYMBOL MACRO (upper 4 bits)
# define ELF64_ST_BIND(i) ((i) >> 4)

// TYPE INFO SYMBOL MACRO (lower 4 bits)
# define ELF64_ST_TYPE(i) ((i) & 0xF)


// SYMBOL BINDING VALUE
# define STB_LOCAL		0   // Local symbol
# define STB_GLOBAL		1   // Global symbol
# define STB_WEAK		2   // Weak symbol
# define STB_LOOS		10  // Start of OS-specific range
# define STB_HIOS		12  // End of OS-specific range
# define STB_GNU_UNIQUE	12
# define STB_LOPROC		13  // Start of processor-specific
# define STB_HIPROC		15  // End of processor-specific

// SYMBOL TYPE VALUE
# define STT_NOTYPE		0   // Symbol type is unspecified
# define STT_OBJECT		1   // Symbol is a data object (e.g., variable)
# define STT_FUNC		2   // Symbol is a code object (function)
# define STT_SECTION	3   // Symbol associated with a section
# define STT_FILE		4   // Symbol's name is file name
# define STT_COMMON		5   // Uninitialized common block
# define STT_TLS		6   // Thread-local data object
# define STT_NUM		7   // Number of defined types
# define STT_LOOS		10  // Start of OS-specific types
# define STT_HIOS		12  // End of OS-specific types
# define STT_LOPROC		13  // Start of processor-specific types
# define STT_HIPROC		15  // End of processor-specific types


// SYMBOL SECTION INDEX VALUE
#define SHN_UNDEF		0      // Undefined section
#define SHN_LORESERVE	0xff00 // Start of reserved indices
#define SHN_LOPROC		0xff00 // Start of processor-specific
#define SHN_HIPROC		0xff1f // End of processor-specific
#define SHN_LOOS		0xff20 // Start of OS-specific
#define SHN_HIOS		0xff3f // End of OS-specific
#define SHN_ABS			0xfff1 // Absolute value; not affected by relocation
#define SHN_COMMON		0xfff2 // Symbol in common block (uninitialized global)
#define SHN_XINDEX		0xffff // Extended section index
#define SHN_HIRESERVE	0xffff // End of reserved indices

// SECTION HEADER FLAG VALUES
# define SHF_WRITE		0x1        // Section contains writable data
# define SHF_ALLOC		0x2        // Section is allocated in memory image of the program
# define SHF_EXECINSTR	0x4        // Section contains executable instructions

# define SHF_MERGE		0x10       // Might be merged by the linker
# define SHF_STRINGS	0x20       // Section contains null-terminated strings
# define SHF_INFO_LINK	0x40       // sh_info holds a section header table index
# define SHF_LINK_ORDER	0x80       // Preserve order after combining sections

# define SHF_OS_NONCONFORMING	0x100      // OS-specific processing required
# define SHF_GROUP				0x200      // Section is a member of a group
# define SHF_TLS				0x400      // Section holds thread-local storage

# define SHF_MASKOS		0x0ff00000 // OS-specific
# define SHF_MASKPROC	0xf0000000 // Processor-specific



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


/* Symbol storing structure to ordered output*/
typedef struct	s_Symbol {

	Elf64_Sym	symbol;
	const char	*name;
}				t_Symbol;



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
