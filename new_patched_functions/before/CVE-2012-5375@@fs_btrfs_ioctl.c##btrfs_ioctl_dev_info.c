static long btrfs_ioctl_dev_info(struct btrfs_root *root, void __user *arg)
{
	struct btrfs_ioctl_dev_info_args *di_args;
	struct btrfs_device *dev;
	struct btrfs_fs_devices *fs_devices = root->fs_info->fs_devices;
	int ret = 0;
	char *s_uuid = NULL;
	char empty_uuid[BTRFS_UUID_SIZE] = {0};

	if (!capable(CAP_SYS_ADMIN))
		return -EPERM;

	di_args = memdup_user(arg, sizeof(*di_args));
	if (IS_ERR(di_args))
		return PTR_ERR(di_args);

	if (memcmp(empty_uuid, di_args->uuid, BTRFS_UUID_SIZE) != 0)
		s_uuid = di_args->uuid;

	mutex_lock(&fs_devices->device_list_mutex);
	dev = btrfs_find_device(root->fs_info, di_args->devid, s_uuid, NULL);
	mutex_unlock(&fs_devices->device_list_mutex);

	if (!dev) {
		ret = -ENODEV;
		goto out;
	}

	di_args->devid = dev->devid;
	di_args->bytes_used = dev->bytes_used;
	di_args->total_bytes = dev->total_bytes;
	memcpy(di_args->uuid, dev->uuid, sizeof(di_args->uuid));
	if (dev->name) {
		struct rcu_string *name;

		rcu_read_lock();
		name = rcu_dereference(dev->name);
		strncpy(di_args->path, name->str, sizeof(di_args->path));
		rcu_read_unlock();
		di_args->path[sizeof(di_args->path) - 1] = 0;
	} else {
		di_args->path[0] = '\0';
	}

out:
	if (ret == 0 && copy_to_user(arg, di_args, sizeof(*di_args)))
		ret = -EFAULT;

	kfree(di_args);
	return ret;
}
