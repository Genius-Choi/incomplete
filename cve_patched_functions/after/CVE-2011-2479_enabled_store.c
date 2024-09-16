static ssize_t enabled_store(struct kobject *kobj,
			     struct kobj_attribute *attr,
			     const char *buf, size_t count)
{
	ssize_t ret;

	ret = double_flag_store(kobj, attr, buf, count,
				TRANSPARENT_HUGEPAGE_FLAG,
				TRANSPARENT_HUGEPAGE_REQ_MADV_FLAG);

	if (ret > 0) {
		int err = start_khugepaged();
		if (err)
			ret = err;
	}

	if (ret > 0 &&
	    (test_bit(TRANSPARENT_HUGEPAGE_FLAG,
		      &transparent_hugepage_flags) ||
	     test_bit(TRANSPARENT_HUGEPAGE_REQ_MADV_FLAG,
		      &transparent_hugepage_flags)))
		set_recommended_min_free_kbytes();

	return ret;
}
