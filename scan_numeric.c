#include "scan.h"

static void
scan_raw_int(const char** src, STRLEN len, I64* l) {
    I64 m;

    if (len == 1) /* optimize the common case */
	*l = *(*src)++;

    else if (len) {	
	m = ((**src < 0) ? -1 : 0);
	for (; (m == **src) && len; (*src)++, len--); /* discard sign bytes */
	
	if (len > sizeof(I64))
	    croak("scan_raw_int: integer overflow");

	while (len-- > 0) {
	    m <<= 8;
	    m |= *(const unsigned char *)(*src)++;
	}
	*l = m;
    }

    else *l = 0;
}

int
peek_numeric_notag(const char **src, const char *max, I64 *l) {
    STRLEN len;
    if (peek_length(src, max, NULL, &len)) {
        if (len <= (STRLEN)(max - *src)) {
	    scan_raw_int(src, len, l);
	    return 1;
	}
    }
    return 0;
}

int
peek_numeric(const char** src, const char* max, U8 *type, U64* tag, I64* l) {
    if (peek_tag(src, max, type, tag))
	return peek_numeric_notag(src, max, l);
    return 0;
}

void
scan_numeric_notag(const char **src, const char *max, I64 *l) {
    STRLEN len;
    scan_length(src, max, NULL, &len);
    scan_raw_int(src, len, l);
}

void
scan_numeric(const char** src, const char* max, U8 *type, U64* tag, I64* l) {
    scan_tag(src, max, type, tag);
    scan_numeric_notag(src, max, l);
}

int
peek_numeric_with_small_tt(const char **src, const char *max,
			 U8 expected_tt, I64 *val) {
    return (peek_small_tag_with_tt(src, max, expected_tt) &&
	    peek_numeric_notag(src, max, val));
}

void
scan_numeric_with_small_tt(const char **src, const char *max,
			U8 expected_tt, I64 *val) {
    scan_small_tag_with_tt(src, max, expected_tt);
    scan_numeric_notag(src, max, val);
}

static void
scan_raw_unsigned_numeric(const char** src, STRLEN len, U64* l) {
    if (len == 1) /* optimize the common case */
	*l = *(*src)++;

    else if (len) {
	U64 m = 0;
	if (**src < 0)
	    croak("scan_raw_unsigned_numeric: bad_packet, signed number found while expecting unsigned");

	for (; !(**src) && len; (*src)++, len--); /* discard sign bytes */
	
	if (len > sizeof(I64))
	    croak("scan_raw_int: integer overflow");

	while (len-- > 0) {
	    m <<= 8;
	    m |= *(const unsigned char *)(*src)++;
	}
	*l = m;
    }

    else *l = 0;
}

void
scan_unsigned_numeric_notag(const char **src, const char *max, U64 *l) {
    STRLEN len;
    scan_length(src, max, NULL, &len);
    scan_raw_unsigned_numeric(src, len, l);
}

int
peek_unsigned_numeric_notag(const char **src, const char *max, U64 *l) {
    STRLEN len;
    if (peek_length(src, max, NULL, &len)) {
	if (len <= (STRLEN)(max - *src)) {
	    scan_raw_unsigned_numeric(src, len, l);
	    return 1;
	}
    }
    return 0;
}

int
peek_unsigned_numeric_with_small_tt(const char **src, const char *max,
				    U8 expected_tt, U64 *val) {
    return (peek_small_tag_with_tt(src, max, expected_tt) &&
	    peek_unsigned_numeric_notag(src, max, val));
}

void
scan_unsigned_numeric_with_small_tt(const char **src, const char *max,
				    U8 expected_tt, U64 *val) {
    scan_small_tag_with_tt(src, max, expected_tt);
    scan_numeric_notag(src, max, val);
}
