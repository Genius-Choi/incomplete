static void *alloc_ep(int size, gfp_t gfp)
{
	struct iwch_ep_common *epc;

	epc = kzalloc(size, gfp);
	if (epc) {
		kref_init(&epc->kref);
		spin_lock_init(&epc->lock);
		init_waitqueue_head(&epc->waitq);
	}
	PDBG("%s alloc ep %p\n", __func__, epc);
	return epc;
}
