static ssize_t enabled_show(struct kobject *kobj,
			    struct kobj_attribute *attr, char *buf)
{
	return double_flag_show(kobj, attr, buf,
				TRANSPARENT_HUGEPAGE_FLAG,
				TRANSPARENT_HUGEPAGE_REQ_MADV_FLAG);
}
