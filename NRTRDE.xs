#define PERL_NO_GET_CONTEXT
#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"

#include "ppport.h"
#include "nrtrde.h"

SV *
parse_nrtrde(pTHX_ SV *data) {
    STRLEN data_len;
    const char *src = SvPV(data, data_len);
    const char *max = src + data_len;
    /* fprintf(stderr, "src: %p, max: %p\n", src, max); fflush(stderr); */
    HV *out = newHV();
    SV *out_ref = sv_2mortal(newRV_noinc((SV*)out));
    scan_nrtrde(aTHX_ &src, max, out);
    return out_ref;
}

MODULE = Data::NRTRDE		PACKAGE = Data::NRTRDE		

SV *
parse_nrtrde(SV *data)
PPCODE:
    ST(0) = parse_nrtrde(aTHX_ data);
    XSRETURN(1);
