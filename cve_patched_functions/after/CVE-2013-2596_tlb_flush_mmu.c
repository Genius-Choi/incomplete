void tlb_flush_mmu(struct mmu_gather *tlb)
{
	struct mmu_gather_batch *batch;

	if (!tlb->need_flush)
		return;
	tlb->need_flush = 0;
	tlb_flush(tlb);
#ifdef CONFIG_HAVE_RCU_TABLE_FREE
	tlb_table_flush(tlb);
#endif

	if (tlb_fast_mode(tlb))
		return;

	for (batch = &tlb->local; batch; batch = batch->next) {
		free_pages_and_swap_cache(batch->pages, batch->nr);
		batch->nr = 0;
	}
	tlb->active = &tlb->local;
}
