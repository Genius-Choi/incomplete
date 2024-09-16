static int __meminit slab_memory_callback(struct notifier_block *self,
					unsigned long action, void *arg)
{
	struct memory_notify *mnb = arg;
	int ret = 0;
	int nid;

	nid = mnb->status_change_nid;
	if (nid < 0)
		goto out;

	switch (action) {
	case MEM_GOING_ONLINE:
		mutex_lock(&slab_mutex);
		ret = init_cache_node_node(nid);
		mutex_unlock(&slab_mutex);
		break;
	case MEM_GOING_OFFLINE:
		mutex_lock(&slab_mutex);
		ret = drain_cache_node_node(nid);
		mutex_unlock(&slab_mutex);
		break;
	case MEM_ONLINE:
	case MEM_OFFLINE:
	case MEM_CANCEL_ONLINE:
	case MEM_CANCEL_OFFLINE:
		break;
	}
out:
	return notifier_from_errno(ret);
}
