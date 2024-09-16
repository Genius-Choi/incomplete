static int dvd_read_struct(struct cdrom_device_info *cdi, dvd_struct *s,
				struct packet_command *cgc)
{
	switch (s->type) {
	case DVD_STRUCT_PHYSICAL:
		return dvd_read_physical(cdi, s, cgc);

	case DVD_STRUCT_COPYRIGHT:
		return dvd_read_copyright(cdi, s, cgc);

	case DVD_STRUCT_DISCKEY:
		return dvd_read_disckey(cdi, s, cgc);

	case DVD_STRUCT_BCA:
		return dvd_read_bca(cdi, s, cgc);

	case DVD_STRUCT_MANUFACT:
		return dvd_read_manufact(cdi, s, cgc);
		
	default:
		cd_dbg(CD_WARNING, ": Invalid DVD structure read requested (%d)\n",
		       s->type);
		return -EINVAL;
	}
}
