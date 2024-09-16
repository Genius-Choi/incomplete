vhost_scsi_wwn_show_attr_version(struct target_fabric_configfs *tf,
				char *page)
{
	return sprintf(page, "TCM_VHOST fabric module %s on %s/%s"
		"on "UTS_RELEASE"\n", VHOST_SCSI_VERSION, utsname()->sysname,
		utsname()->machine);
}
