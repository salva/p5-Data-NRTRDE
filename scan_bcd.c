#include "scan.h"

static void
sv_catbcd(SV *sv, int nibble) {
    char tail[2];
    if (nibble <= 0x9)
        tail[0] = nibble + '0';
    else if (nibble <= 0xE)
        tail[0] = nibble - 0xA + 'a';
    else return;
    tail[1] = '\0';
    sv_catpvn(sv, tail, 1);
}

static int
peek_bcd_notag(const char **src, const char *max, SV *sv) {
    const char *s;
    STRLEN len;
    if (peek_length(src, max, NULL, &len)) {
        if (*src + len <= max) {
            sv_setpvs(sv, "");
            max = *src + len;
            while (*src < max) {
                U8 u8 = *((*src)++);
                sv_catbcd(sv, u8 >> 4);
                sv_catbcd(sv, u8 & 0xF);
            }
            return 1;
        }
    }
    return 0;
}

void
scan_bcd_notag(const char **src, const char *max, SV *sv) {
    if (peek_bcd_notag(src, max, sv)) return;
    croak("scan_bcd_notag: packet too short");
}

