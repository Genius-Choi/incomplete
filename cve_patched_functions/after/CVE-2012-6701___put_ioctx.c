static void __put_ioctx(struct kioctx *ctx)
{
	unsigned nr_events = ctx->max_reqs;
	BUG_ON(ctx->reqs_active);

	cancel_delayed_work_sync(&ctx->wq);
	aio_free_ring(ctx);
	mmdrop(ctx->mm);
	ctx->mm = NULL;
	if (nr_events) {
		spin_lock(&aio_nr_lock);
		BUG_ON(aio_nr - nr_events > aio_nr);
		aio_nr -= nr_events;
		spin_unlock(&aio_nr_lock);
	}
	pr_debug("__put_ioctx: freeing %p\n", ctx);
	call_rcu(&ctx->rcu_head, ctx_rcu_free);
}
