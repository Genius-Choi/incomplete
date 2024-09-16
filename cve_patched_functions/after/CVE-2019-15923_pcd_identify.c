static int pcd_identify(struct pcd_unit *cd, char *id)
{
	int k, s;
	char id_cmd[12] = { 0x12, 0, 0, 0, 36, 0, 0, 0, 0, 0, 0, 0 };

	pcd_bufblk = -1;

	s = pcd_atapi(cd, id_cmd, 36, pcd_buffer, "identify");

	if (s)
		return -1;
	if ((pcd_buffer[0] & 0x1f) != 5) {
		if (verbose)
			printk("%s: %s is not a CD-ROM\n",
			       cd->name, cd->drive ? "Slave" : "Master");
		return -1;
	}
	memcpy(id, pcd_buffer + 16, 16);
	id[16] = 0;
	k = 16;
	while ((k >= 0) && (id[k] <= 0x20)) {
		id[k] = 0;
		k--;
	}

	printk("%s: %s: %s\n", cd->name, cd->drive ? "Slave" : "Master", id);

	return 0;
}
