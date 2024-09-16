qedi_remove_sysfs_attr(struct Scsi_Host *shost, struct sysfs_bin_attrs *iter)
{
	for (; iter->name; iter++)
		sysfs_remove_bin_file(&shost->shost_gendev.kobj, iter->attr);
}
