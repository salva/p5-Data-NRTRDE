#include "scan.h"

int
scan_indefinite_or_length(const char** src, const char* max, STRLEN *length) {
    if (*src >= max) croak("scan_length: packet too short");
    if (**src == 0x80) {
	(*src)++;
        *length = 0;
	return 1;
    }
    
}

int
scan_end_marker(const char** src, const char* max) {
    if (max - *src < 2) croak("scan_end_marker: packet too short");
    if (((*src)[0] == 0) && ((*src)[1] == 0)) {
        /* fprintf(stderr, "end-marker\n"); fflush(stderr); */
	*src += 2;
	return 1;
    }
    return 0;
}

int
peek_length(const char **src, const char *max, int *indefinite, STRLEN *length) {
    if (*src >= max) return 0;
    if (indefinite) *indefinite = 0;
    if (**src & 0x80) {
        if (**src == (char)0x80) {
            if (!indefinite)
                croak("peek_length: unexpected indefinite length form");
            (*src)++;
            *indefinite = 1;
            *length = 0;
        }
        else {
            STRLEN l = 0;
            STRLEN chars = (*(*src)++ & 0x7f);

            if (chars > sizeof(*length))
                croak("peek_length: length out of bounds (%u bytes)", (unsigned int)chars);
            if (chars > max - *src)
                return 0;
            while (chars--) {
                l <<= 8;
                l |= *(unsigned char *)(*src)++;
            }
            *length = l;
        }
    }
    else
	*length = *(*src)++;
    return 1;
}

void
scan_length(const char **src, const char *max, int *indefinite, STRLEN *length) {
    if (peek_length(src, max, indefinite, length)) return;
    croak("scan_length: packet too short");
}

void
scan_length_and_set_max(const char **src, const char **max, int *indefinite) {
    STRLEN len;
    scan_length(src, *max, indefinite, &len);
    if (*src + len > *max) croak("scan_length_and_set: packet too short");
    if (indefinite && *indefinite) return;
    *max = *src + len;
}
