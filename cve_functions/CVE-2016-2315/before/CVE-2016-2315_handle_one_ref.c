static int handle_one_ref(const char *path, const struct object_id *oid,
			  int flag, void *cb_data)
{
	struct all_refs_cb *cb = cb_data;
	struct object *object;

	if (ref_excluded(cb->all_revs->ref_excludes, path))
	    return 0;

	object = get_reference(cb->all_revs, path, oid->hash, cb->all_flags);
	add_rev_cmdline(cb->all_revs, object, path, REV_CMD_REF, cb->all_flags);
	add_pending_sha1(cb->all_revs, path, oid->hash, cb->all_flags);
	return 0;
}
