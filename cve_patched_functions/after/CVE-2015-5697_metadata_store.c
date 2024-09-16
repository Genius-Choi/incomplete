metadata_store(struct mddev *mddev, const char *buf, size_t len)
{
	int major, minor;
	char *e;
	int err;
	/* Changing the details of 'external' metadata is
	 * always permitted.  Otherwise there must be
	 * no devices attached to the array.
	 */

	err = mddev_lock(mddev);
	if (err)
		return err;
	err = -EBUSY;
	if (mddev->external && strncmp(buf, "external:", 9) == 0)
		;
	else if (!list_empty(&mddev->disks))
		goto out_unlock;

	err = 0;
	if (cmd_match(buf, "none")) {
		mddev->persistent = 0;
		mddev->external = 0;
		mddev->major_version = 0;
		mddev->minor_version = 90;
		goto out_unlock;
	}
	if (strncmp(buf, "external:", 9) == 0) {
		size_t namelen = len-9;
		if (namelen >= sizeof(mddev->metadata_type))
			namelen = sizeof(mddev->metadata_type)-1;
		strncpy(mddev->metadata_type, buf+9, namelen);
		mddev->metadata_type[namelen] = 0;
		if (namelen && mddev->metadata_type[namelen-1] == '\n')
			mddev->metadata_type[--namelen] = 0;
		mddev->persistent = 0;
		mddev->external = 1;
		mddev->major_version = 0;
		mddev->minor_version = 90;
		goto out_unlock;
	}
	major = simple_strtoul(buf, &e, 10);
	err = -EINVAL;
	if (e==buf || *e != '.')
		goto out_unlock;
	buf = e+1;
	minor = simple_strtoul(buf, &e, 10);
	if (e==buf || (*e && *e != '\n') )
		goto out_unlock;
	err = -ENOENT;
	if (major >= ARRAY_SIZE(super_types) || super_types[major].name == NULL)
		goto out_unlock;
	mddev->major_version = major;
	mddev->minor_version = minor;
	mddev->persistent = 1;
	mddev->external = 0;
	err = 0;
out_unlock:
	mddev_unlock(mddev);
	return err ?: len;
}
