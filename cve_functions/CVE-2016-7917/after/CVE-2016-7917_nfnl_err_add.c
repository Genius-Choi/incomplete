static int nfnl_err_add(struct list_head *list, struct nlmsghdr *nlh, int err)
{
	struct nfnl_err *nfnl_err;

	nfnl_err = kmalloc(sizeof(struct nfnl_err), GFP_KERNEL);
	if (nfnl_err == NULL)
		return -ENOMEM;

	nfnl_err->nlh = nlh;
	nfnl_err->err = err;
	list_add_tail(&nfnl_err->head, list);

	return 0;
}
