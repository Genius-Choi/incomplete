void ib_uverbs_release_file(struct kref *ref)
{
	struct ib_uverbs_file *file =
		container_of(ref, struct ib_uverbs_file, ref);
	struct ib_device *ib_dev;
	int srcu_key;

	release_ufile_idr_uobject(file);

	srcu_key = srcu_read_lock(&file->device->disassociate_srcu);
	ib_dev = srcu_dereference(file->device->ib_dev,
				  &file->device->disassociate_srcu);
	if (ib_dev && !ib_dev->ops.disassociate_ucontext)
		module_put(ib_dev->owner);
	srcu_read_unlock(&file->device->disassociate_srcu, srcu_key);

	if (atomic_dec_and_test(&file->device->refcount))
		ib_uverbs_comp_dev(file->device);

	if (file->async_file)
		kref_put(&file->async_file->ref,
			 ib_uverbs_release_async_event_file);
	put_device(&file->device->dev);
	kfree(file);
}
