static void handle_refs(const char *submodule, struct rev_info *revs, unsigned flags,
		int (*for_each)(const char *, each_ref_fn, void *))
{
	struct all_refs_cb cb;
	init_all_refs_cb(&cb, revs, flags);
	for_each(submodule, handle_one_ref, &cb);
}
