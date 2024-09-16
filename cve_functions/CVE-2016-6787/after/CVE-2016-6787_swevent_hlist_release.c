static void swevent_hlist_release(struct swevent_htable *swhash)
{
	struct swevent_hlist *hlist = swevent_hlist_deref(swhash);

	if (!hlist)
		return;

	RCU_INIT_POINTER(swhash->swevent_hlist, NULL);
	kfree_rcu(hlist, rcu_head);
}
