void platform_driver_unregister(struct platform_driver *drv)
{
	driver_unregister(&drv->driver);
}
