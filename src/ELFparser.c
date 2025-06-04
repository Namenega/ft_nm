#include "../hdr/nm.h"

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
		return (1);
	}
	return (0);
}


/*
 * Find the .symtab header
 * Return the location of the .symtab table
 * Return NULL if no .symtab
 */

Elf64_Shdr	*findSymtabHeader(Elf64_Ehdr *ehdr, Elf64_Shdr *shdr, const char *shstrtab) {

	const char	*name;
	uint32_t	type;

	for (int i = 0; i < ehdr->e_shnum; i++) {
		name = shstrtab + shdr[i].sh_name;
		type = shdr[i].sh_type;

		if (!ft_strncmp(name, ".symtab", 7) && type == SHT_SYMTAB)
			return (&shdr[i]);
	}
	return (NULL);
}


/*
 * Find the .strtab header
 * Return the location of the .strtab table
 * Return NULL if no .strtab
 */

Elf64_Shdr	*findStrtabHeader(Elf64_Ehdr *ehdr, Elf64_Shdr *shdr, const char *shstrtab) {

	const char	*name;
	uint32_t	type;

	for (int i = 0; i < ehdr->e_shnum; i++) {
		name = shstrtab + shdr[i].sh_name;
		type = shdr[i].sh_type;

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

t_Elfdata	elfParser(void *elf_data) {

	t_Elfdata	edata;
	edata.ehdr = (Elf64_Ehdr *)elf_data;		// Parse ELF Header
	edata.shdr = (Elf64_Shdr *)((char *)elf_data + edata.ehdr->e_shoff);	// Parse ELF Section Headers

	// Parse SH_STRTAB (String table. Holds the name of all sections, involving NULL-terminated string.)
	edata.shstrtab = (char *)elf_data + edata.shdr[edata.ehdr->e_shstrndx].sh_offset;
	
	// Parse .symtab and .strtab
	edata.symtab_hdr = findSymtabHeader(edata.ehdr, edata.shdr, edata.shstrtab);
	edata.strtab_hdr = findStrtabHeader(edata.ehdr, edata.shdr, edata.shstrtab);
	
	return (edata);
}
