void unregister_cdrom(struct cdrom_device_info *cdi)
{
	cd_dbg(CD_OPEN, "entering unregister_cdrom\n");

	mutex_lock(&cdrom_mutex);
	list_del(&cdi->list);
	mutex_unlock(&cdrom_mutex);

	if (cdi->exit)
		cdi->exit(cdi);

	cd_dbg(CD_REG_UNREG, "drive \"/dev/%s\" unregistered\n", cdi->name);
}
