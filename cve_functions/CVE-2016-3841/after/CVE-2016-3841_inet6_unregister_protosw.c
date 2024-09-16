inet6_unregister_protosw(struct inet_protosw *p)
{
	if (INET_PROTOSW_PERMANENT & p->flags) {
		pr_err("Attempt to unregister permanent protocol %d\n",
		       p->protocol);
	} else {
		spin_lock_bh(&inetsw6_lock);
		list_del_rcu(&p->list);
		spin_unlock_bh(&inetsw6_lock);

		synchronize_net();
	}
}
