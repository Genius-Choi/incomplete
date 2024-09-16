static int pf_start(struct pf_unit *pf, int cmd, int b, int c)
{
	int i;
	char io_cmd[12] = { cmd, pf->lun << 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	for (i = 0; i < 4; i++) {
		io_cmd[5 - i] = b & 0xff;
		b = b >> 8;
	}

	io_cmd[8] = c & 0xff;
	io_cmd[7] = (c >> 8) & 0xff;

	i = pf_command(pf, io_cmd, c * 512, "start i/o");

	mdelay(1);

	return i;
}
