static int add_one_ref(const char *path, const struct object_id *oid,
		       int flag, void *cb_data)
{
	struct rev_info *revs = (struct rev_info *)cb_data;
	struct object *object;

	if ((flag & REF_ISSYMREF) && (flag & REF_ISBROKEN)) {
		warning("symbolic ref is dangling: %s", path);
		return 0;
	}

	object = parse_object_or_die(oid->hash, path);
	add_pending_object(revs, object, "");

	return 0;
}
