void sysctl_head_put(struct ctl_table_header *head)
{
	spin_lock(&sysctl_lock);
	if (!--head->count)
		kfree_rcu(head, rcu);
	spin_unlock(&sysctl_lock);
}
