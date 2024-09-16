static int __init slab_sysfs_init(void)
{
	struct kmem_cache *s;
	int err;

	slab_kset = kset_create_and_add("slab", &slab_uevent_ops, kernel_kobj);
	if (!slab_kset) {
		printk(KERN_ERR "Cannot register slab subsystem.\n");
		return -ENOSYS;
	}

	slab_state = SYSFS;

	list_for_each_entry(s, &slab_caches, list) {
		err = sysfs_slab_add(s);
		if (err)
			printk(KERN_ERR "SLUB: Unable to add boot slab %s"
						" to sysfs\n", s->name);
	}

	while (alias_list) {
		struct saved_alias *al = alias_list;

		alias_list = alias_list->next;
		err = sysfs_slab_alias(al->s, al->name);
		if (err)
			printk(KERN_ERR "SLUB: Unable to add boot slab alias"
					" %s to sysfs\n", s->name);
		kfree(al);
	}

	resiliency_test();
	return 0;
}
