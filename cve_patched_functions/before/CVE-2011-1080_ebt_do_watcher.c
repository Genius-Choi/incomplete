ebt_do_watcher(const struct ebt_entry_watcher *w, struct sk_buff *skb,
	       struct xt_action_param *par)
{
	par->target   = w->u.watcher;
	par->targinfo = w->data;
	w->u.watcher->target(skb, par);
	/* watchers don't give a verdict */
	return 0;
}
