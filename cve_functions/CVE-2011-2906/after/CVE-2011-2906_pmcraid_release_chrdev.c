static void pmcraid_release_chrdev(struct pmcraid_instance *pinstance)
{
	pmcraid_release_minor(MINOR(pinstance->cdev.dev));
	device_destroy(pmcraid_class,
		       MKDEV(pmcraid_major, MINOR(pinstance->cdev.dev)));
	cdev_del(&pinstance->cdev);
}
