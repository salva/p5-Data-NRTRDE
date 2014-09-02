#include "nrtrde.h"

#include "nrtrde_app_tags.h"

void
scan_call_event(pTHX_ const char **src, const char *max, U64 tag, SV *out) {
    int indefinite;
    U64 target_numeric;
    SV *target_sv = sv_newmortal();
    HV *hv = newHV();
    if (SvTYPE(out) < SVt_RV) sv_upgrade(out, SVt_RV);
    SvRV_set(out, (SV*)hv);
    SvROK_on(out);

    switch (tag) {
    case NRTRDE_TAG_MOC:
        sv_setpvs(target_sv, "Moc");
        break;
    case NRTRDE_TAG_MTC:
        sv_setpvs(target_sv, "Mtc");
        break;
    case NRTRDE_TAG_GPRS:
        sv_setpvs(target_sv, "Gprs");
        break;
    default:
        croak("scan_call_event: unexpected application tag %d", tag);
    }
    hv_stores(hv, "call_event_type", newSVsv(target_sv));

    scan_length_and_set_max(src, &max, &indefinite);
    while (!scan_and_check_end_marker(src, max, indefinite)) {
        U8 type;
        U64 tag;
        scan_tag(src, max, &type, &tag);
        /* fprintf(stderr, "scan_call_event: type: 0x%x, tag: %d\n", type, tag);fflush(stderr); */
    
        switch (type) {
        case ASN1_APPLICATION:
            switch (tag) {
            case NRTRDE_TAG_IMSI:
                scan_bcd_notag(src, max, target_sv);
                hv_stores(hv, "imsi", newSVsv(target_sv));
                break;
            case NRTRDE_TAG_IMEI:
                scan_bcd_notag(src, max, target_sv);
                hv_stores(hv, "imei", newSVsv(target_sv));
                break;
            case NRTRDE_TAG_CALL_EVENT_START_TIMESTAMP:
                scan_raw_notag(src, max, target_sv);
                hv_stores(hv, "start_timestamp", newSVsv(target_sv));
                break;
            case NRTRDE_TAG_UTC_TIME_OFFSET:
                scan_raw_notag(src, max, target_sv);
                hv_stores(hv, "utc_time_offset", newSVsv(target_sv));
                break;
            case NRTRDE_TAG_CALL_EVENT_DURATION:
                scan_numeric_notag(src, max, &target_numeric);
                hv_stores(hv, "duration", newSVi64(target_numeric));
                break;
            case NRTRDE_TAG_CAUSE_FOR_TERMINATION:
                scan_numeric_notag(src, max, &target_numeric);
                hv_stores(hv, "cause_for_termination", newSVi64(target_numeric));
                break;
            case NRTRDE_TAG_CALLING_NUMBER:
                scan_raw_notag(src, max, target_sv);
                hv_stores(hv, "calling_number", newSVsv(target_sv));
                break;
            case NRTRDE_TAG_REC_ENTITY_ID:
                scan_raw_notag(src, max, target_sv);
                hv_stores(hv, "rec_entity_id", newSVsv(target_sv));
                break;
            case NRTRDE_TAG_CALL_REFERENCE:
                scan_numeric_notag(src, max, &target_numeric);
                hv_stores(hv, "call_reference", newSVi64(target_numeric));
                break;
            case NRTRDE_TAG_CHARGE_AMOUNT:
                scan_numeric_notag(src, max, &target_numeric);
                hv_stores(hv, "charge_amount", newSVi64(target_numeric));
                break;
            case NRTRDE_TAG_CHARGING_ID:
                scan_numeric_notag(src, max, &target_numeric);
                hv_stores(hv, "charging_id", newSVi64(target_numeric));
                break;
            case NRTRDE_TAG_DIALLED_DIGITS:
                scan_raw_notag(src, max, target_sv);
                hv_stores(hv, "dialled_digits", newSVsv(target_sv));
                break;
            case NRTRDE_TAG_CONNECTED_NUMBER:
                scan_raw_notag(src, max, target_sv);
                hv_stores(hv, "connected_number", newSVsv(target_sv));
                break;
            case NRTRDE_TAG_ACCESS_POINT_NAME_NI:
                scan_raw_notag(src, max, target_sv);
                hv_stores(hv, "access_point_ni", newSVsv(target_sv));
                break;
            case NRTRDE_TAG_ACCESS_POINT_NAME_OI:
                scan_raw_notag(src, max, target_sv);
                hv_stores(hv, "access_point_name_oi", newSVsv(target_sv));
                break;
            case NRTRDE_TAG_CELL_ID:
                scan_numeric_notag(src, max, &target_numeric);
                hv_stores(hv, "cell_id", newSVi64(target_numeric));
                break;
            case NRTRDE_TAG_DATA_VOLUME_INCOMING:
                scan_numeric_notag(src, max, &target_numeric);
                hv_stores(hv, "data_volume_incoming", newSVi64(target_numeric));
                break;                
            case NRTRDE_TAG_DATA_VOLUME_OUTGOING:
                scan_numeric_notag(src, max, &target_numeric);
                hv_stores(hv, "data_volume_outgoing", newSVi64(target_numeric));
                break;
            case NRTRDE_TAG_GGSN_ADDRESS:
                scan_raw_notag(src, max, target_sv);
                hv_stores(hv, "ggsn_address", newSVsv(target_sv));
                break;
            case NRTRDE_TAG_SGSN_ADDRESS:
                scan_raw_notag(src, max, target_sv);
                hv_stores(hv, "sgsn_address", newSVsv(target_sv));
                break;
            case NRTRDE_TAG_LOCATION_AREA:
                scan_numeric_notag(src, max, &target_numeric);
                hv_stores(hv, "location_area", newSVi64(target_numeric));
                break;
            case NRTRDE_TAG_MSISDN:
                scan_bcd_notag(src, max, target_sv);
                hv_stores(hv, "msisdn", newSVsv(target_sv));
                break;
            case NRTRDE_TAG_SERVING_NETWORK:
                scan_raw_notag(src, max, target_sv);
                hv_stores(hv, "serving_network", newSVsv(target_sv));
                break;
            case NRTRDE_TAG_SUPPLEMENTARY_SERVICE_CODE:
                scan_raw_notag(src, max, target_sv);
                hv_stores(hv, "supplementary_service_code", newSVsv(target_sv));
                break;
            case NRTRDE_TAG_THIRD_PARTY_NUMBER:
                scan_raw_notag(src, max, target_sv);
                hv_stores(hv, "third_party_number", newSVsv(target_sv));
                break;
            default:
                croak("scan_call_event: unexpected application tag %d", tag);
            }
            break;

        case ASN1_APPLICATION|ASN1_CONSTRUCTED:
            switch (tag) {
            case NRTRDE_TAG_SERVICE_CODE:
            {
                const char *max1 = max;
                scan_length_and_set_max(src, &max1, NULL);
                scan_tag(src, max1, &type, &tag);
                /* fprintf(stderr, "scan_call_event (service code): type: 0x%x, tag: %d\n", type, tag);fflush(stderr); */
                if (type != ASN1_APPLICATION)
                    croak("scan_call_event: unexpected type for service code 0x%x", type);
                switch (tag) {
                case NRTRDE_TAG_TELE_SERVICE_CODE:
                    scan_numeric_notag(src, max1, &target_numeric);
                    hv_stores(hv, "tele_service_code", newSVi64(target_numeric));
                    break;
                case NRTRDE_TAG_BEARER_SERVICE_CODE:
                    scan_numeric_notag(src, max1, &target_numeric);
                    hv_stores(hv, "bearer_service_code", newSVi64(target_numeric));
                    break;
                default:
                    croak("scan_call_event: unexpected application tag for service code %d", tag);
                }
                break;
            }
            default:
                croak("scan_call_event: unexpected application tag %d", tag);
            }
            break;

        default:
            croak("scan_call_event: unexpected type 0x%x", type);

        }
    }
}

void
scan_call_event_list(pTHX_ const char **src, const char *max, SV *out) {
    int indefinite;
    SV *target_sv = sv_newmortal();
    AV *av = newAV();
    if (SvTYPE(out) < SVt_RV) sv_upgrade(out, SVt_RV);
    SvRV_set(out, (SV*)av);
    SvROK_on(out);

    scan_length_and_set_max(src, &max, &indefinite);
    while (!scan_and_check_end_marker(src, max, indefinite)) {
        U8 type;
        U64 tag;
        scan_tag(src, max, &type, &tag);

        switch (type) {
        case ASN1_APPLICATION|ASN1_CONSTRUCTED:
            switch (tag) {
            case NRTRDE_TAG_MOC:
            case NRTRDE_TAG_MTC:
            case NRTRDE_TAG_GPRS:
                scan_call_event(aTHX_ src, max, tag, target_sv);
                av_push(av, newSVsv(target_sv));
                break;

            default:
                croak("scan_call_event_list: unexpected application tag %d", tag);

            }
            break;

        default:
            croak("scan_call_event_list: unexpected type 0x%x", type);
        }
    }
}

void
scan_nrtrde(pTHX_ const char **src, const char *max, HV *out) {
    int indefinite;
    U64 target_numeric;
    SV *target_sv = sv_newmortal();

    scan_app_tag_with_tt(src, max, ASN1_CONSTRUCTED, NRTRDE_TAG_NRTRDE);

    scan_length_and_set_max(src, &max, &indefinite);
    while (!scan_and_check_end_marker(src, max, indefinite)) {
        U8 type;
        U64 tag;
        scan_tag(src, max, &type, &tag);
        /* fprintf(stderr, "scan_nrtrde: type: 0x%x, tag: %d\n", type, tag);fflush(stderr); */

        switch (type) {
        case ASN1_APPLICATION:
            switch (tag) {
            case NRTRDE_TAG_SPECIFICATION_VERSION_NUMBER:
                scan_numeric_notag(src, max, &target_numeric);
                hv_stores(out, "specification_version_number", newSVi64(target_numeric));
                break;

            case NRTRDE_TAG_RELEASE_VERSION_NUMBER:
                scan_numeric_notag(src, max, &target_numeric);
                hv_stores(out, "release_version_number", newSVi64(target_numeric));
                break;

            case NRTRDE_TAG_SENDER:
                scan_raw_notag(src, max, target_sv);
                hv_stores(out, "sender", newSVsv(target_sv));
                break;

            case NRTRDE_TAG_RECIPIENT:
                scan_raw_notag(src, max, target_sv);
                hv_stores(out, "sender", newSVsv(target_sv));
                break;

            case NRTRDE_TAG_SEQUENCE_NUMBER:
                scan_raw_notag(src, max, target_sv);
                hv_stores(out, "sequence_number", newSVsv(target_sv));
                break;

            case NRTRDE_TAG_FILE_AVAILABLE_TIMESTAMP:
                scan_raw_notag(src, max, target_sv);
                hv_stores(out, "file_available_timestamp", newSVsv(target_sv));
                break;

            case NRTRDE_TAG_UTC_TIME_OFFSET:
                scan_raw_notag(src, max, target_sv);
                hv_stores(out, "utc_time_offset", newSVsv(target_sv));
                break;

            case NRTRDE_TAG_CALL_EVENTS_COUNT:
                scan_numeric_notag(src, max, &target_numeric);
                hv_stores(out, "call_events_count", newSVi64(target_numeric));
                break;

            default:
                croak("scan_nrtrde: unexpected application tag %d", tag);
            }

            break;

        case ASN1_APPLICATION|ASN1_CONSTRUCTED:
            switch (tag) {
            case NRTRDE_TAG_CALL_EVENT_LIST:
                scan_call_event_list(aTHX_ src, max, target_sv);
                hv_stores(out, "call_events", newSVsv(target_sv));
                break;

            default:
                croak("scan_nrtrde: unexpected application tag %d", tag);
            }

            break;

        default:
            croak("scan_nrtrde: unexpected type 0x%x", type);
        }
    }
}

