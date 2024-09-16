static void ib_uverbs_release_dev(struct kobject *kobj)
{
	struct ib_uverbs_device *dev =
		container_of(kobj, struct ib_uverbs_device, kobj);

	cleanup_srcu_struct(&dev->disassociate_srcu);
	kfree(dev);
}
