encode_legacy_async_masks(const struct ofputil_async_cfg *ac,
                          enum ofputil_async_msg_type oam,
                          enum ofp_version version,
                          ovs_be32 masks[2])
{
    for (int i = 0; i < 2; i++) {
        bool master = i == 0;
        const struct ofp14_async_prop *ap
            = get_ofp14_async_config_prop_by_oam(oam, master);
        masks[i] = encode_async_mask(ac, ap, version);
    }
}
