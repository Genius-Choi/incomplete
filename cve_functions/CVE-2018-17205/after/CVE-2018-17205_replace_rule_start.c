replace_rule_start(struct ofproto *ofproto, struct ofproto_flow_mod *ofm,
                   struct rule *old_rule, struct rule *new_rule)
{
    struct oftable *table = &ofproto->tables[new_rule->table_id];

    /* 'old_rule' may be either an evicted rule or replaced rule. */
    if (old_rule) {
        /* Copy values from old rule for modify semantics. */
        if (old_rule->removed_reason != OFPRR_EVICTION) {
            bool change_cookie = (ofm->modify_cookie
                                  && new_rule->flow_cookie != OVS_BE64_MAX
                                  && new_rule->flow_cookie != old_rule->flow_cookie);

            ovs_mutex_lock(&new_rule->mutex);
            ovs_mutex_lock(&old_rule->mutex);
            if (ofm->command != OFPFC_ADD) {
                new_rule->idle_timeout = old_rule->idle_timeout;
                new_rule->hard_timeout = old_rule->hard_timeout;
                *CONST_CAST(uint16_t *, &new_rule->importance) = old_rule->importance;
                new_rule->flags = old_rule->flags;
                new_rule->created = old_rule->created;
            }
            if (!change_cookie) {
                *CONST_CAST(ovs_be64 *, &new_rule->flow_cookie)
                    = old_rule->flow_cookie;
            }
            ovs_mutex_unlock(&old_rule->mutex);
            ovs_mutex_unlock(&new_rule->mutex);
        }

        /* Mark the old rule for removal in the next version. */
        cls_rule_make_invisible_in_version(&old_rule->cr, ofm->version);

        /* Remove the old rule from data structures. */
        ofproto_rule_remove__(ofproto, old_rule);
    } else {
        table->n_flows++;
    }
    /* Insert flow to ofproto data structures, so that later flow_mods may
     * relate to it.  This is reversible, in case later errors require this to
     * be reverted. */
    ofproto_rule_insert__(ofproto, new_rule);
    /* Make the new rule visible for classifier lookups only from the next
     * version. */
    classifier_insert(&table->cls, &new_rule->cr, ofm->version, ofm->conjs,
                      ofm->n_conjs);
}
