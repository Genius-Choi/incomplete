static void tty_line_name(struct tty_driver *driver, int index, char *p)
{
	sprintf(p, "%s%d", driver->name, index + driver->name_base);
}
