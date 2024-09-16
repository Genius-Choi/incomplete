ofputil_encode_group_features_request(enum ofp_version ofp_version)
{
    struct ofpbuf *request = NULL;

    switch (ofp_version) {
    case OFP10_VERSION:
    case OFP11_VERSION:
        ovs_fatal(0, "dump-group-features needs OpenFlow 1.2 or later "
                     "(\'-O OpenFlow12\')");
    case OFP12_VERSION:
    case OFP13_VERSION:
    case OFP14_VERSION:
    case OFP15_VERSION:
    case OFP16_VERSION:
        request = ofpraw_alloc(OFPRAW_OFPST12_GROUP_FEATURES_REQUEST,
                               ofp_version, 0);
        break;
    default:
        OVS_NOT_REACHED();
    }

    return request;
}
