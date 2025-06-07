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

	if (st_size >= 5 && data[0] == 0x7F && data[1] == 'E' &&
		data[2] == 'L' && data[3] == 'F') {

		if (data[4] == ELFCLASS32)
			return (1);
		if (data[4] == ELFCLASS64)
			return (2);
	}
	return (0);
}


/*
 * Find the .symtab header
 * Return the location of the .symtab table
 * Return NULL if no .symtab
 */

Elf64_Shdr	*findSymtab64Header(Elf64_Ehdr *ehdr, Elf64_Shdr *shdr, const char *shstrtab, Elf64_Shdr shstrtab_hdr) {

	const char	*name;
	uint32_t	type;
	
	if (!shstrtab)
		return (NULL);

	for (int i = 0; i < ehdr->e_shnum; i++) {
	
		uint32_t name_offset = shdr[i].sh_name;
	
		if (name_offset >= shstrtab_hdr.sh_size)
			continue; // Invalid offset — skip
		
		name = shstrtab + name_offset;
		type = shdr[i].sh_type;
		
		if (!(shstrtab + shdr[i].sh_name))
			return (NULL);

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

Elf64_Shdr	*findStrtab64Header(Elf64_Ehdr *ehdr, Elf64_Shdr *shdr, const char *shstrtab, Elf64_Shdr shstrtab_hdr) {

	const char	*name;
	uint32_t	type;
	
	if (!shstrtab)
		return (NULL);
		
	for (int i = 0; i < ehdr->e_shnum; i++) {
	
		uint32_t name_offset = shdr[i].sh_name;
	
		if (name_offset >= shstrtab_hdr.sh_size)
			continue; // Invalid offset — skip
		
		name = shstrtab + name_offset;
		type = shdr[i].sh_type;
		
		if (!(shstrtab + shdr[i].sh_name))
			return (NULL);

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

t_Elf64data	elf64Parser(void *elf_data, off_t file_size) {

	t_Elf64data	edata;
	
	edata.valid = 0;
	edata.ehdr = (Elf64_Ehdr *)elf_data;		// Parse ELF Header
	edata.shdr = (Elf64_Shdr *)((char *)elf_data + edata.ehdr->e_shoff);	// Parse ELF Section Headers

	// Parse SH_STRTAB (String table. Holds the name of all sections, involving NULL-terminated string.)
	if (edata.ehdr->e_shstrndx >= edata.ehdr->e_shnum)
		return edata; // Invalid index

	Elf64_Shdr shstrtab_hdr = edata.shdr[edata.ehdr->e_shstrndx];

	if ((long int)(shstrtab_hdr.sh_offset + shstrtab_hdr.sh_size) > file_size)
		return edata; // Would read past the file
	
	edata.shstrtab = (char *)elf_data + edata.shdr[edata.ehdr->e_shstrndx].sh_offset;
	
	// Parse .symtab and .strtab
	edata.symtab_hdr = findSymtab64Header(edata.ehdr, edata.shdr, edata.shstrtab, shstrtab_hdr);
	edata.strtab_hdr = findStrtab64Header(edata.ehdr, edata.shdr, edata.shstrtab, shstrtab_hdr);
	edata.valid = 1;
	return (edata);
}












































