degraded_show(struct mddev *mddev, char *page)
{
	return sprintf(page, "%d\n", mddev->degraded);
}
