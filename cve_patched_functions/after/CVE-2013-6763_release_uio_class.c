static void release_uio_class(void)
{
	class_unregister(&uio_class);
	uio_major_cleanup();
}
