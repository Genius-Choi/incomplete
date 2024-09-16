static void ucma_cleanup_multicast(struct ucma_context *ctx)
{
	struct ucma_multicast *mc, *tmp;

	mutex_lock(&mut);
	list_for_each_entry_safe(mc, tmp, &ctx->mc_list, list) {
		list_del(&mc->list);
		idr_remove(&multicast_idr, mc->id);
		kfree(mc);
	}
	mutex_unlock(&mut);
}
