group_remove_rule(struct ofgroup *group, struct rule *rule)
{
    rule_collection_remove(&group->rules, rule);
}
