find_inlist_lock_noload(struct list_head *head, const char *name, int *error,
			struct mutex *mutex)
{
	struct {
		struct list_head list;
		char name[EBT_FUNCTION_MAXNAMELEN];
	} *e;

	mutex_lock(mutex);
	list_for_each_entry(e, head, list) {
		if (strcmp(e->name, name) == 0)
			return e;
	}
	*error = -ENOENT;
	mutex_unlock(mutex);
	return NULL;
}
