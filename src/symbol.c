#include "../hdr/nm.h"
//#include "elf.h"


void	write_symbol(uint64_t value, char type, const char *name, int is_undefind) {

	char line[256];
	int len = 0;
}


void	symbolHandling(void *elf_data, t_Elfdata edata) {

	Elf64_Sym	*symtab = (Elf64_Sym *)((char *)elf_data + edata.symtab_hdr->sh_offset);
	const char	*strtab = (char *)elf_data + edata.strtab_hdr->sh_offset;
	int			sym_count = edata.symtab_hdr->sh_size / edata.symtab_hdr->sh_entsize;
	Elf64_Sym	symbol;
	const char	*name;


	// Iterate over symbols
	for (int i = 0; i < sym_count; i++) {

		symbol = symtab[i];
		name = strtab + symbol.st_name;

		// Skip empty name
		if (!name[0])
			continue;

		//printf("SYMBOL NAME: [%s]\n", name);				// TO REMOVE

		char type = '?';

		if (ELF64_ST_BIND(symbol.st_info) == STB_WEAK) {
			
			type = 'W';
			//printf("SYMBOL NAME: [%s]; type [%c]\n", name, type);				// TO REMOVE
		} else if (symbol.st_shndx == SHN_UNDEF) {
            type = 'U';
			//printf("SYMBOL NAME: [%s]; type [%c]\n", name, type);				// TO REMOVE
        } else {
            switch (ELF64_ST_TYPE(symbol.st_info)) {
                case STT_FUNC: type = 'T'; break;
                case STT_OBJECT: type = 'D'; break;
                default: type = 'T'; break;
            }
			//printf("SYMBOL NAME: [%s]; type [%c]\n", name, type);				// TO REMOVE
        }

		// Lowercase for local symbols
        if (ELF64_ST_BIND(symbol.st_info) == STB_LOCAL && type >= 'A' && type <= 'Z') {
            type += 32;
        }

        //if (symbol.st_shndx != SHN_UNDEF)
        //    printf("%016lx %c %s\n", symbol.st_value, type, name);
        //else
        //    printf("                 %c %s\n", type, name);

		write_symbol(symbol.st_value, type, name, symbol.st_shndx == SHN_UNDEF);
	}
}
