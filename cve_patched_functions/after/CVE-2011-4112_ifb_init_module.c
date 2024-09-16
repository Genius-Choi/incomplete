static int __init ifb_init_module(void)
{
	int i, err;

	rtnl_lock();
	err = __rtnl_link_register(&ifb_link_ops);

	for (i = 0; i < numifbs && !err; i++)
		err = ifb_init_one(i);
	if (err)
		__rtnl_link_unregister(&ifb_link_ops);
	rtnl_unlock();

	return err;
}
