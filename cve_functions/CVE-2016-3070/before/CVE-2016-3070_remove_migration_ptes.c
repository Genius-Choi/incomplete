static void remove_migration_ptes(struct page *old, struct page *new)
{
	struct rmap_walk_control rwc = {
		.rmap_one = remove_migration_pte,
		.arg = old,
	};

	rmap_walk(new, &rwc);
}
