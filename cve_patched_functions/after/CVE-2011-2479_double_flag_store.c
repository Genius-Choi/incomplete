static ssize_t double_flag_store(struct kobject *kobj,
				 struct kobj_attribute *attr,
				 const char *buf, size_t count,
				 enum transparent_hugepage_flag enabled,
				 enum transparent_hugepage_flag req_madv)
{
	if (!memcmp("always", buf,
		    min(sizeof("always")-1, count))) {
		set_bit(enabled, &transparent_hugepage_flags);
		clear_bit(req_madv, &transparent_hugepage_flags);
	} else if (!memcmp("madvise", buf,
			   min(sizeof("madvise")-1, count))) {
		clear_bit(enabled, &transparent_hugepage_flags);
		set_bit(req_madv, &transparent_hugepage_flags);
	} else if (!memcmp("never", buf,
			   min(sizeof("never")-1, count))) {
		clear_bit(enabled, &transparent_hugepage_flags);
		clear_bit(req_madv, &transparent_hugepage_flags);
	} else
		return -EINVAL;

	return count;
}
