static int snd_msnd_write_cfg_mem(int cfg, int num, int mem)
{
	u16 wmem;

	mem >>= 8;
	wmem = (u16)(mem & 0xfff);
	if (snd_msnd_write_cfg(cfg, IREG_LOGDEVICE, num))
		return -EIO;
	if (snd_msnd_write_cfg(cfg, IREG_MEMBASEHI, HIBYTE(wmem)))
		return -EIO;
	if (snd_msnd_write_cfg(cfg, IREG_MEMBASELO, LOBYTE(wmem)))
		return -EIO;
	if (wmem && snd_msnd_write_cfg(cfg, IREG_MEMCONTROL,
				       MEMTYPE_HIADDR | MEMTYPE_16BIT))
		return -EIO;
	return 0;
}
