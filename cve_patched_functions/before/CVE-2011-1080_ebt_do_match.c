ebt_do_match(struct ebt_entry_match *m, const struct sk_buff *skb,
	     struct xt_action_param *par)
{
	par->match     = m->u.match;
	par->matchinfo = m->data;
	return m->u.match->match(skb, par) ? EBT_MATCH : EBT_NOMATCH;
}
