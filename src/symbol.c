#include "../hdr/nm.h"


/*
 * Basic swap function
 */

static void	swap_sym(t_Symbol *a, t_Symbol *b) {

	t_Symbol tmp = *a;
	*a = *b;
	*b = tmp;
}


/*
 * strcmp() that skip the character c at the beginning of string
 * The comparison is case-insensitive, so we lower the char to check
 */

static int ft_strcmp_skipchar(const char *s1, const char *s2, int c) {

	while (*s1 == c)
		s1++;

	while (*s2 == c)
		s2++;

	while (*s1 && *s2) {

		//convert to lowercase if uppercase for case-insensitive
		char c1 = ft_tolower(*s1);
		char c2 = ft_tolower(*s2);

		if (c1 != c2)
			return (unsigned char)c1 - (unsigned char)c2;

		s1++;
		s2++;
	}

	return ((unsigned char)*s1 - (unsigned char)*s2);
}


/*
 * Comparing symbols with custom strcmp()
 *
 * c = 95 = '_'
 * underscore is not involved in the sorting.
 */

static int	symbol_cmp(const t_Symbol *a, const t_Symbol *b) {

	int c = 95, count_a, count_b;
	int cmp = ft_strcmp_skipchar(a->name, b->name, c);

	if (cmp == 0) {

		// Count leading underscore
		count_a = 0, count_b = 0;
		const char *s1 = a->name;
		const char *s2 = b->name;

		while (*s1 == c) {
			count_a++;
			s1++;
		}

		while (*s2 == c) {
			count_b++;
			s2++;
		}
		return (count_b - count_a);
	}
	return cmp;
}


/*
 * Sorting alphabetically the symbols before output
 */

static void	sortSymbols(t_Symbol *array, int left, int right) {

	int			pivot_idx, i, j;
	t_Symbol	pivot;

	if (left >= right)
		return;

	pivot_idx = left;
	pivot = array[pivot_idx];
	i = left + 1;
	j = right;


	while (i <= j) {

		while (i <= right && symbol_cmp(&array[i], &pivot) < 0)
			i++;

		while (j > left && symbol_cmp(&array[j], &pivot) >= 0)
			j--;

		if (i < j)
			swap_sym(&array[i], &array[j]);
	}

	swap_sym(&array[left], &array[j]);

	sortSymbols(array, left, j - 1);
	sortSymbols(array, j + 1, right);
}

/*
 * Get the type of each symbol and return it.
 *
 * symbol = structure holding symbol data
 * type = type of the file
 * shdrs = section headers
 */

static char	getELFSymbolType(Elf64_Sym symbol, char type, Elf64_Shdr *shdrs) {

	uint8_t	bind = ELF64_ST_BIND(symbol.st_info);

	if (bind == STB_GNU_UNIQUE)
		return ('u');
	if (bind == STB_WEAK)
		// weak undefined (w) vs weak defined (W)
		return (symbol.st_shndx == SHN_UNDEF ? 'w' : 'W');
	if (symbol.st_shndx == SHN_UNDEF)
        return ('U'); // undefined
	if (symbol.st_shndx == SHN_ABS)
		return ('A'); // absolute
	if (symbol.st_shndx == SHN_COMMON)
		return ('C');
	
	Elf64_Shdr sec = shdrs[symbol.st_shndx];

	if ((sec.sh_type == SHT_NOBITS) && (sec.sh_flags & SHF_ALLOC) && (sec.sh_flags & SHF_WRITE))
		type = 'B'; // .bss
	else if ((sec.sh_type == SHT_PROGBITS) && (sec.sh_flags & SHF_ALLOC) && (sec.sh_flags & SHF_EXECINSTR))
		type = 'T'; // .text
	else if ((sec.sh_type == SHT_PROGBITS) && (sec.sh_flags & SHF_ALLOC) && !(sec.sh_flags & SHF_WRITE))
		type = 'R'; // .rodata
	else if ((sec.sh_type == SHT_PROGBITS) && (sec.sh_flags & SHF_ALLOC) && (sec.sh_flags & SHF_WRITE))
		type = 'D'; // .data
	else if (sec.sh_type == SHT_DYNAMIC)
		type = 'D';
	else if (sec.sh_type == SHT_INIT_ARRAY || sec.sh_type == SHT_FINI_ARRAY)
		type = 't'; // static init/fini
	else
		type = 'T'; // fallback
	
	// Lowercase for local symbols
    if (bind == STB_LOCAL && type >= 'A' && type <= 'Z') {
        type += 32;
    }

	return (type);
}


/*
 * Handle Symbols logic
 * Fill an array then sort it
 * Output the data on fd
 *
 * edata = structure holding header, section header, ... data
 * elf_data = mapped data
 */

void		symbolHandling(void *elf_data, t_Elfdata edata) {

	Elf64_Sym	*symtab = (Elf64_Sym *)((char *)elf_data + edata.symtab_hdr->sh_offset);
	const char	*strtab = (char *)elf_data + edata.strtab_hdr->sh_offset;
	int			sym_count = edata.symtab_hdr->sh_size / edata.symtab_hdr->sh_entsize;
	int			valid_count = 0;
	t_Symbol	*symbols;
	size_t		len = 0;

	if (!(symbols = malloc(sizeof(t_Symbol) * sym_count)))
		return ;
	
	// Fill symbol array
	for (int i = 0; i < sym_count; i++) {

		const char *name = strtab + symtab[i].st_name;

		if (!name[0])
			continue;

		symbols[valid_count].symbol = symtab[i];
		symbols[valid_count].name = name;
		valid_count++;
	}

	// sort symbols
	sortSymbols(symbols, 0, valid_count - 1);

	// Iterate over symbols
	for (int i = 0; i < valid_count; i++) {

		Elf64_Sym sym = symbols[i].symbol;

		len = ft_strlen(symbols[i].name);
		if (len >= 2 && symbols[i].name[len - 2] == '.' &&
				(symbols[i].name[len - 1] == 'c' || symbols[i].name[len - 1] == 'o'))
			continue;

		char type = '?';
		type = getELFSymbolType(sym, type, edata.shdr);

		// Print symbol
        if (sym.st_shndx != SHN_UNDEF) {
			ft_printf("%016lx %c %s\n", sym.st_value, type, symbols[i].name);
		}
        else
            ft_printf("                 %c %s\n", type, symbols[i].name);
	}

	free(symbols);
}
