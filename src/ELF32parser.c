#include "../hdr/nm.h"

/*
 * Find the .symtab header
 * Return the location of the .symtab table
 * Return NULL if no .symtab
 */

Elf32_Shdr	*findSymtab32Header(Elf32_Ehdr *ehdr, Elf32_Shdr *shdr, const char *shstrtab, Elf32_Shdr shstrtab_hdr) {

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

Elf32_Shdr	*findStrtab32Header(Elf32_Ehdr *ehdr, Elf32_Shdr *shdr, const char *shstrtab, Elf32_Shdr shstrtab_hdr) {

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

t_Elf32data	elf32Parser(void *elf_data, off_t file_size) {

	t_Elf32data	edata;
	
	edata.valid = 0;
	edata.ehdr = (Elf32_Ehdr *)elf_data;		// Parse ELF Header
	edata.shdr = (Elf32_Shdr *)((char *)elf_data + edata.ehdr->e_shoff);	// Parse ELF Section Headers

	// Parse SH_STRTAB (String table. Holds the name of all sections, involving NULL-terminated string.)
	if (edata.ehdr->e_shstrndx >= edata.ehdr->e_shnum)
		return edata; // Invalid index

	Elf32_Shdr shstrtab_hdr = edata.shdr[edata.ehdr->e_shstrndx];

	if ((long int)(shstrtab_hdr.sh_offset + shstrtab_hdr.sh_size) > file_size)
		return edata; // Would read past the file
	
	edata.shstrtab = (char *)elf_data + edata.shdr[edata.ehdr->e_shstrndx].sh_offset;
	
	// Parse .symtab and .strtab
	edata.symtab_hdr = findSymtab32Header(edata.ehdr, edata.shdr, edata.shstrtab, shstrtab_hdr);
	edata.strtab_hdr = findStrtab32Header(edata.ehdr, edata.shdr, edata.shstrtab, shstrtab_hdr);
	edata.valid = 1;
	return (edata);
}

