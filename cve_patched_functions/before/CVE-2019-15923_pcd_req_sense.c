static void pcd_req_sense(struct pcd_unit *cd, char *fun)
{
	char rs_cmd[12] = { 0x03, 0, 0, 0, 16, 0, 0, 0, 0, 0, 0, 0 };
	char buf[16];
	int r, c;

	r = pcd_command(cd, rs_cmd, 16, "Request sense");
	mdelay(1);
	if (!r)
		pcd_completion(cd, buf, "Request sense");

	cd->last_sense = -1;
	c = 2;
	if (!r) {
		if (fun)
			printk("%s: %s: Sense key: %x, ASC: %x, ASQ: %x\n",
			       cd->name, fun, buf[2] & 0xf, buf[12], buf[13]);
		c = buf[2] & 0xf;
		cd->last_sense =
		    c | ((buf[12] & 0xff) << 8) | ((buf[13] & 0xff) << 16);
	}
	if ((c == 2) || (c == 6))
		cd->changed = 1;
}
