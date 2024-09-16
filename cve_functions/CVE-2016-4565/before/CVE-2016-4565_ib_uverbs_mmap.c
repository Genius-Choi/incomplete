static int ib_uverbs_mmap(struct file *filp, struct vm_area_struct *vma)
{
	struct ib_uverbs_file *file = filp->private_data;
	struct ib_device *ib_dev;
	int ret = 0;
	int srcu_key;

	srcu_key = srcu_read_lock(&file->device->disassociate_srcu);
	ib_dev = srcu_dereference(file->device->ib_dev,
				  &file->device->disassociate_srcu);
	if (!ib_dev) {
		ret = -EIO;
		goto out;
	}

	if (!file->ucontext)
		ret = -ENODEV;
	else
		ret = ib_dev->mmap(file->ucontext, vma);
out:
	srcu_read_unlock(&file->device->disassociate_srcu, srcu_key);
	return ret;
}
