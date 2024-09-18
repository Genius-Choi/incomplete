static void add_pending_object_with_path(struct rev_info *revs,
					 struct object *obj,
					 const char *name, unsigned mode,
					 const char *path)
{
	if (!obj)
		return;
	if (revs->no_walk && (obj->flags & UNINTERESTING))
		revs->no_walk = 0;
	if (revs->reflog_info && obj->type == OBJ_COMMIT) {
		struct strbuf buf = STRBUF_INIT;
		int len = interpret_branch_name(name, 0, &buf);
		int st;

		if (0 < len && name[len] && buf.len)
			strbuf_addstr(&buf, name + len);
		st = add_reflog_for_walk(revs->reflog_info,
					 (struct commit *)obj,
					 buf.buf[0] ? buf.buf: name);
		strbuf_release(&buf);
		if (st)
			return;
	}
	add_object_array_with_path(obj, name, &revs->pending, mode, path);
}
