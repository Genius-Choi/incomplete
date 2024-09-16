rdev_attr_show(struct kobject *kobj, struct attribute *attr, char *page)
{
	struct rdev_sysfs_entry *entry = container_of(attr, struct rdev_sysfs_entry, attr);
	struct md_rdev *rdev = container_of(kobj, struct md_rdev, kobj);

	if (!entry->show)
		return -EIO;
	if (!rdev->mddev)
		return -EBUSY;
	return entry->show(rdev, page);
}
