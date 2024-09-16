static inline int ebt_watcher_to_user(const struct ebt_entry_watcher *w,
				      const char *base, char __user *ubase)
{
	return ebt_obj_to_user(ubase + ((char *)w - base),
			       w->u.watcher->name, w->data, sizeof(*w),
			       w->u.watcher->usersize, w->watcher_size);
}
