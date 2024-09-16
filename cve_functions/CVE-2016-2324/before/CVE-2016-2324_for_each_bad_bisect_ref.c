static int for_each_bad_bisect_ref(const char *submodule, each_ref_fn fn, void *cb_data)
{
	return for_each_bisect_ref(submodule, fn, cb_data, term_bad);
}
