static void pcd_start(void)
{
	int b, i;
	char rd_cmd[12] = { 0xa8, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 };

	pcd_bufblk = pcd_sector / 4;
	b = pcd_bufblk;
	for (i = 0; i < 4; i++) {
		rd_cmd[5 - i] = b & 0xff;
		b = b >> 8;
	}

	if (pcd_command(pcd_current, rd_cmd, 2048, "read block")) {
		pcd_bufblk = -1;
		next_request(BLK_STS_IOERR);
		return;
	}

	mdelay(1);

	ps_set_intr(do_pcd_read_drq, pcd_ready, PCD_TMO, nice);
}
