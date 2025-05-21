#include <unistd.h>
#include <stdint.h>
#include <string.h>

// Helper to convert an address to a padded hex string
void write_hex64(uint64_t value, char *buffer) {
    const char hex_digits[] = "0123456789abcdef";
    for (int i = 15; i >= 0; --i) {
        buffer[i] = hex_digits[value & 0xF];
        value >>= 4;
    }
    buffer[16] = '\0';
}

void write_symbol(uint64_t value, char type, const char *name, int is_undefined) {
    char line[256]; // enough space
    int len = 0;

    if (is_undefined) {
        // 16 spaces
        memcpy(line, "                ", 16);
        len += 16;
    } else {
        char hex[17];
        write_hex64(value, hex);
        memcpy(line, hex, 16);
        len += 16;
    }

    line[len++] = ' ';
    line[len++] = type;
    line[len++] = ' ';

    size_t name_len = strlen(name);
    memcpy(line + len, name, name_len);
    len += name_len;

    line[len++] = '\n';

    write(1, line, len); // write to stdout
}

write_symbol(sym.st_value, type, name, sym.st_shndx == SHN_UNDEF);
