static int __init mm_slots_hash_init(void)
{
	mm_slots_hash = kzalloc(MM_SLOTS_HASH_HEADS * sizeof(struct hlist_head),
				GFP_KERNEL);
	if (!mm_slots_hash)
		return -ENOMEM;
	return 0;
}
