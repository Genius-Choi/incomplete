ofproto_rule_ref(struct rule *rule)
{
    if (rule) {
        ovs_refcount_ref(&rule->ref_count);
    }
}
