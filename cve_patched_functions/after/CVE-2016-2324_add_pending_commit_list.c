static void add_pending_commit_list(struct rev_info *revs,
                                    struct commit_list *commit_list,
                                    unsigned int flags)
{
	while (commit_list) {
		struct object *object = &commit_list->item->object;
		object->flags |= flags;
		add_pending_object(revs, object, oid_to_hex(&object->oid));
		commit_list = commit_list->next;
	}
}
