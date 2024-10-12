mm_share_sync(struct mm_master **pmm, struct mm_master **pmmalloc)
{
	struct mm_master *mm;
	struct mm_master *mmalloc;
	struct mm_master *mmold;
	struct mmtree rb_free, rb_allocated;

	debug3("%s: Share sync", __func__);

	mm = *pmm;
	mmold = mm->mmalloc;
	mm_memvalid(mmold, mm, sizeof(*mm));

	mmalloc = mm_create(NULL, mm->size);
	mm = mm_xmalloc(mmalloc, sizeof(struct mm_master));
	memcpy(mm, *pmm, sizeof(struct mm_master));
	mm->mmalloc = mmalloc;

	rb_free = mm->rb_free;
	rb_allocated = mm->rb_allocated;

	RB_INIT(&mm->rb_free);
	RB_INIT(&mm->rb_allocated);

	mm_sync_list(&rb_free, &mm->rb_free, mm, mmold);
	mm_sync_list(&rb_allocated, &mm->rb_allocated, mm, mmold);

	mm_destroy(mmold);

	*pmm = mm;
	*pmmalloc = mmalloc;

	debug3("%s: Share sync end", __func__);
}
