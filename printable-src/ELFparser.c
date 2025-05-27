#include "../hdr/nm.h"


/*
 * PRINTFILEDATA
 * -------------
 * Utility function to print 'data' (mapped memory of the file)
 *
 *
 * PRINTELFHEADERDATA
 * ------------------
 * Utility function to print ELF Header data
 *
 *
 * PRINTELFSECTIONHEADERDATA
 * -------------------------
 * Utility function to print ELF Section Header data
 *
 */

void	printFileData(void *elf_data, size_t st_size) {

	unsigned char	*data = (unsigned char *)elf_data;

	if (!data || !st_size)
		printf("Missing data");

	ft_printf("\n\n-----------------------------\n\n");
	
	for (size_t i = 0; i < st_size; i++)
		printf("%c", data[i]);

	printf("\n\n-----------------------------\n\n");
}

void	printELFHeaderData(Elf64_Ehdr *ehdr) {
	
	ft_printf(">> PRINT ELF HEADER <<\n");
	ft_printf("e_ident[16]:\t");
	for (int i = 0; i < 16; i++) {

		ft_printf("[%c]", ehdr->e_ident[i]);
	}
	ft_printf("\n");
	ft_printf("e_type:\t\t[%d]\n", ehdr->e_type);
	ft_printf("e_machine:\t[%d]\n", ehdr->e_machine);
	ft_printf("e_version:\t[%d]\n", ehdr->e_version);
	ft_printf("e_entry:\t[%ld]\n", ehdr->e_entry);
	ft_printf("e_phoff:\t[%ld]\n", ehdr->e_phoff);
	ft_printf("e_shoff:\t[%ld]\n", ehdr->e_shoff);
	ft_printf("e_flags:\t[%d]\n", ehdr->e_flags);
	ft_printf("e_ehsize:\t[%d]\n", ehdr->e_ehsize);
	ft_printf("e_phentsize:\t[%d]\n", ehdr->e_phentsize);
	ft_printf("e_phnum:\t[%d]\n", ehdr->e_phnum);
	ft_printf("e_shentsize:\t[%d]\n", ehdr->e_shentsize);
	ft_printf("e_shnum:\t[%d]\n", ehdr->e_shnum);
	ft_printf("e_shstrndx:\t[%d]\n", ehdr->e_shstrndx);
}

void	printELFSectionHeaderData(Elf64_Ehdr *ehdr, Elf64_Shdr *shdr) {

	ft_printf(">> PRINT ELF SECTION HEADER <<\n");
	for (int i = 0; i < ehdr->e_shnum; i++) {
    	ft_printf("Section %d: sh_name: %u, sh_type: %u, sh_offset: 0x%lx\n",
        	i, shdr[i].sh_name, shdr[i].sh_type, shdr[i].sh_offset);
	}
}

/* --------------- END OF UTILITY FUNCTIONS --------------- */

/*
 * Check the Magic Bytes of the file
 * Return 1 if it is an ELF file
 * Return 0 if it is not an ELF file
 *
 * data = mapped memory result, from 'mmap()'
 * stsize = size of mapped data, from 'fstat()'
 */

int		isELFfile(void *elf_data, size_t st_size) {
	
	unsigned char	*data = (unsigned char *)elf_data;

	if (!data || !st_size)
		return (0);

	if (st_size >= 4 && data[0] == 0x7F &&
		data[1] == 'E' &&
		data[2] == 'L' &&
		data[3] == 'F') {
		//ft_printf("[GOOD] - This is an ELF file!\n\n");									// TO REMOVE
		return (1);
	}
	return (0);
}


Elf64_Shdr	*findSymtabHeader(Elf64_Ehdr *ehdr, Elf64_Shdr *shdr, const char *shstrtab) {

	const char	*name;
	uint32_t	type;

	for (int i = 0; i < ehdr->e_shnum; i++) {
		name = shstrtab + shdr[i].sh_name;
		type = shdr[i].sh_type;

		//ft_printf("SYMTAB [%d] - name: [%s] - type: [%d]\n", i, name, type);			// TO REMOVE
		if (!ft_strncmp(name, ".symtab", 7) && type == SHT_SYMTAB)
			return (&shdr[i]);
	}
	return (NULL);
}


Elf64_Shdr	*findStrtabHeader(Elf64_Ehdr *ehdr, Elf64_Shdr *shdr, const char *shstrtab) {

	const char	*name;
	uint32_t	type;

	for (int i = 0; i < ehdr->e_shnum; i++) {
		name = shstrtab + shdr[i].sh_name;
		type = shdr[i].sh_type;


		//ft_printf("STRTAB [%d] - name: [%s] - type: [%d]\n", i, name, type);			// TO REMOVE
		if (!ft_strncmp(name, ".strtab", 7) && type == SHT_STRTAB)
			return (&shdr[i]);
	}
	return (NULL);
}


/*
 * Parsing the file to get information on:
 * - ELF Header
 * - Section Headers
 */

t_Elfdata	elfParser(void *elf_data, int fd) {

	t_Elfdata	edata;
	// Parse ELF Header
	edata.ehdr = (Elf64_Ehdr *)elf_data;
	//printELFHeaderData(edata.ehdr);														// TO REMOVE


	// Parse ELF Section Headers
	edata.shdr = (Elf64_Shdr *)((char *)elf_data + edata.ehdr->e_shoff);
	//printELFSectionHeaderData(edata.ehdr, edata.shdr);											// TO REMOVE

	// Parse SH_STRTAB (String table. Holds the name of all sections, involving NULL-terminated string.)
	edata.shstrtab = (char *)elf_data + edata.shdr[edata.ehdr->e_shstrndx].sh_offset;
	
	edata.symtab_hdr = findSymtabHeader(edata.ehdr, edata.shdr, edata.shstrtab);
	edata.strtab_hdr = findStrtabHeader(edata.ehdr, edata.shdr, edata.shstrtab);
	

	if (!edata.symtab_hdr || !edata.strtab_hdr) {
		ft_printf("WE MADE IT - NO SYMTAB\n");								// TO REMOVE
		print_error("Missing Symtab or Shstrtab", EXIT_SYMTAB, fd);
	}
	//else																// TO REMOVE
		//ft_printf("WE MADE IT - SYMTAB OR SHSTRTAB IS THERE\n");			// TO REMOVE

	return (edata);
}
