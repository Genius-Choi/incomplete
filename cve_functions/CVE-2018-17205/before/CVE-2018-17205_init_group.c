init_group(struct ofproto *ofproto, const struct ofputil_group_mod *gm,
           ovs_version_t version, struct ofgroup **ofgroup)
{
    enum ofperr error;
    const long long int now = time_msec();

    if (gm->group_id > OFPG_MAX) {
        return OFPERR_OFPGMFC_INVALID_GROUP;
    }
    if (gm->type > OFPGT11_FF) {
        return OFPERR_OFPGMFC_BAD_TYPE;
    }

    *ofgroup = ofproto->ofproto_class->group_alloc();
    if (!*ofgroup) {
        VLOG_WARN_RL(&rl, "%s: failed to allocate group", ofproto->name);
        return OFPERR_OFPGMFC_OUT_OF_GROUPS;
    }

    *CONST_CAST(struct ofproto **, &(*ofgroup)->ofproto) = ofproto;
    *CONST_CAST(uint32_t *, &((*ofgroup)->group_id)) = gm->group_id;
    *CONST_CAST(enum ofp11_group_type *, &(*ofgroup)->type) = gm->type;
    *CONST_CAST(long long int *, &((*ofgroup)->created)) = now;
    *CONST_CAST(long long int *, &((*ofgroup)->modified)) = now;
    ovs_refcount_init(&(*ofgroup)->ref_count);
    (*ofgroup)->being_deleted = false;

    ovs_list_init(CONST_CAST(struct ovs_list *, &(*ofgroup)->buckets));
    ofputil_bucket_clone_list(CONST_CAST(struct ovs_list *,
                                         &(*ofgroup)->buckets),
                              &gm->buckets, NULL);

    *CONST_CAST(uint32_t *, &(*ofgroup)->n_buckets) =
        ovs_list_size(&(*ofgroup)->buckets);

    ofputil_group_properties_copy(CONST_CAST(struct ofputil_group_props *,
                                             &(*ofgroup)->props),
                                  &gm->props);
    rule_collection_init(&(*ofgroup)->rules);

    /* Make group visible from 'version'. */
    (*ofgroup)->versions = VERSIONS_INITIALIZER(version,
                                                OVS_VERSION_NOT_REMOVED);

    /* Construct called BEFORE any locks are held. */
    error = ofproto->ofproto_class->group_construct(*ofgroup);
    if (error) {
        ofputil_group_properties_destroy(CONST_CAST(struct ofputil_group_props *,
                                                    &(*ofgroup)->props));
        ofputil_bucket_list_destroy(CONST_CAST(struct ovs_list *,
                                               &(*ofgroup)->buckets));
        ofproto->ofproto_class->group_dealloc(*ofgroup);
    }
    return error;
}
