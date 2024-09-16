static void free_saved_parents(struct rev_info *revs)
{
	if (revs->saved_parents_slab)
		clear_saved_parents(revs->saved_parents_slab);
}
