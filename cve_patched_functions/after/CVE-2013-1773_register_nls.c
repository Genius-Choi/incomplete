int register_nls(struct nls_table * nls)
{
	struct nls_table ** tmp = &tables;

	if (nls->next)
		return -EBUSY;

	spin_lock(&nls_lock);
	while (*tmp) {
		if (nls == *tmp) {
			spin_unlock(&nls_lock);
			return -EBUSY;
		}
		tmp = &(*tmp)->next;
	}
	nls->next = tables;
	tables = nls;
	spin_unlock(&nls_lock);
	return 0;	
}
