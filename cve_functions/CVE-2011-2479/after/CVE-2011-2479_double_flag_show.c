static ssize_t double_flag_show(struct kobject *kobj,
				struct kobj_attribute *attr, char *buf,
				enum transparent_hugepage_flag enabled,
				enum transparent_hugepage_flag req_madv)
{
	if (test_bit(enabled, &transparent_hugepage_flags)) {
		VM_BUG_ON(test_bit(req_madv, &transparent_hugepage_flags));
		return sprintf(buf, "[always] madvise never\n");
	} else if (test_bit(req_madv, &transparent_hugepage_flags))
		return sprintf(buf, "always [madvise] never\n");
	else
		return sprintf(buf, "always madvise [never]\n");
}
