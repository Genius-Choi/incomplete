static int for_each_bisect_ref(const char *submodule, each_ref_fn fn, void *cb_data, const char *term) {
	struct strbuf bisect_refs = STRBUF_INIT;
	int status;
	strbuf_addf(&bisect_refs, "refs/bisect/%s", term);
	status = for_each_ref_in_submodule(submodule, bisect_refs.buf, fn, cb_data);
	strbuf_release(&bisect_refs);
	return status;
}
