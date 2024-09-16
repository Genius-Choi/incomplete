static void swevent_hlist_release(struct swevent_htable *swhash)
{
	struct swevent_hlist *hlist = swevent_hlist_deref(swhash);

	if (!hlist)
		return;

	rcu_assign_pointer(swhash->swevent_hlist, NULL);
	kfree_rcu(hlist, rcu_head);
}
