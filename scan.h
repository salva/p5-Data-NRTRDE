#ifndef SCAN_H_INCLUDED
#define SCAN_H_INCLUDED

#include "common.h"
#include "asn1.h"

/* ASN1 entities */

void scan_tag(const char** src, const char* max, U8 *type, U64 *tag);
#define peek_small_tag_with_tt(src, max, tt) (((max) > *(src)) ? (*(*(src))++ == (tt) ? 1 : (croak("peek_small_tag_with_tt: bad packet"), 0)) : 0)
#define scan_small_tag_with_tt(src, max, tt) if ((max) > *(src) && *(*(src))++ == (tt)) ; else croak("scan_small_tag_with_tt: bad packet")

#define scan_app_tag_with_tt(src, max, type, tag)			\
  if ((tag) >= 0x1f) scan_tag_with_tt((src), (max), (type)|ASN1_APPLICATION, (tag)); \
  else scan_small_tag_with_tt((src), (max), (type)|(tag)|ASN1_APPLICATION)

int scan_end_marker(const char** src, const char* max);
#define scan_and_check_end_marker(src, max, indefinite) \
  ((indefinite) ? scan_end_marker((src), (max)) : *(src) >= (max))

void scan_length(const char** src, const char* max, int *indefinite, STRLEN* length);
void scan_length_and_set_max(const char **src, const char **max, int *indefinite);

int peek_raw(const char** src, const char* max, U8 *type, U64* tag, SV *sv);
int peek_raw_utf8_notag(const char** src, const char* max, SV *sv);
void scan_raw(const char** src, const char* max, U8 *type, U64 *tag, SV *sv);
void scan_raw_notag(const char** src, const char* max, SV *sv);
void scan_raw_utf8_notag(const char** src, const char* max, SV *sv);
void scan_raw_with_small_tt(const char** src, const char* max, U8 tt, SV *sv);
void scan_raw_utf8_with_small_tt(const char** src, const char* max, U8 tt, SV *sv);
int peek_raw_with_small_tt(const char** src, const char* max, U8 tt, SV *sv);
int peek_raw_utf8_with_small_tt(const char** src, const char* max, U8 tt, SV *sv);
void scan_array_of_raw_utf8_with_small_tt(const char **src, const char *max, U8 tt, AV *av);

#define peek_string(src, max, sv) peek_raw_with_small_tt(src, max, ASN1_UNIVERSAL|ASN1_PRIMITIVE|ASN1_OCTET_STRING, sv)
#define peek_string_utf8(src, max, sv) peek_raw_utf8_with_small_tt(src, max, ASN1_UNIVERSAL|ASN1_PRIMITIVE|ASN1_OCTET_STRING, sv)
#define scan_string(src, max, sv) scan_raw_with_small_tt(src, max, ASN1_UNIVERSAL|ASN1_PRIMITIVE|ASN1_OCTET_STRING, sv)
#define scan_string_utf8(src, max, sv) scan_raw_utf8_with_small_tt(src, max, ASN1_UNIVERSAL|ASN1_PRIMITIVE|ASN1_OCTET_STRING, sv)

#define scan_array_of_string_utf8(src, max, av) scan_array_of_raw_utf8_with_small_tt(src, max, ASN1_UNIVERSAL|ASN1_PRIMITIVE|ASN1_OCTET_STRING, av)

void scan_bcd_notag(const char **src, const char *max, SV *sv);

int peek_numeric(const char** src, const char* max, U8 *type, U64* tag, I64* l);
void scan_numeric(const char** src,const char* max, U8 *type, U64 *tag, I64* val);
int peek_numeric_notag(const char **src, const char *max, I64 *l);
void scan_numeric_notag(const char **src, const char *max, I64 *l);

int peek_numeric_with_small_tt(const char **src, const char *max, U8 expected_tt, I64 *val);
void scan_numeric_with_small_tt(const char **src, const char *max, U8 expected_tt, I64 *val);

int peek_unsigned_numeric_with_small_tt(const char **src, const char *max, U8 expected_tt, U64 *val);
void scan_unsigned_numeric_with_small_tt(const char **src, const char *max, U8 expected_tt, U64 *val);

#define scan_int(src, max, l) scan_numeric_with_small_tt(src, max, ASN1_UNIVERSAL|ASN1_PRIMITIVE|ASN1_INTEGER, l)
#define scan_unsigned_numeric(src, max, l) scan_unsigned_numeric_with_small_tt(src, max, ASN1_UNIVERSAL|ASN1_PRIMITIVE|ASN1_INTEGER, l)
#define scan_bool(src, max, l) scan_numeric_with_small_tt(src, max, ASN1_UNIVERSAL|ASN1_PRIMITIVE|ASN1_BOOLEAN, l)
#define scan_enum(src, max, l) scan_unsigned_numeric_with_small_tt(src, max, ASN1_UNIVERSAL|ASN1_PRIMITIVE|ASN1_ENUMERATED, l)

#define peek_int(src, max, l) peek_numeric_with_small_tt(src, max, ASN1_UNIVERSAL|ASN1_PRIMITIVE|ASN1_INTEGER, l)
#define peek_unsigned_numeric(src, max, l) peek_unsigned_numeric_with_small_tt(src, max, ASN1_UNIVERSAL|ASN1_PRIMITIVE|ASN1_INTEGER, l)
#define peek_enum(src, max, l) peek_unsigned_numeric_with_small_tt(src, max, ASN1_UNIVERSAL|ASN1_PRIMITIVE|ASN1_ENUMERATED, l)

#define peek_sequence(src, max, len) (peek_small_tag_with_tt(src, max, ASN1_UNIVERSAL|ASN1_CONSTRUCTED|ASN1_SEQUENCE) && peek_length(src, max, len))
#define scan_sequence(src, max, len)					\
    scan_small_tag_with_tt(src, max, ASN1_UNIVERSAL|ASN1_CONSTRUCTED|ASN1_SEQUENCE); \
    scan_length(src, max, len)

#define scan_set(src, max, len)					\
    scan_small_tag_with_tt(src, max, ASN1_UNIVERSAL|ASN1_CONSTRUCTED|ASN1_SET); \
    scan_length(src, max, len)


#endif
