void unregister_pernet_device(struct pernet_operations *ops)
{
	down_write(&pernet_ops_rwsem);
	if (&ops->list == first_device)
		first_device = first_device->next;
	unregister_pernet_operations(ops);
	up_write(&pernet_ops_rwsem);
}
