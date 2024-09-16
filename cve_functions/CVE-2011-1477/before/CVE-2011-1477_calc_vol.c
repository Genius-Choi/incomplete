static void calc_vol(unsigned char *regbyte, int volume, int main_vol)
{
	int level = (~*regbyte & 0x3f);

	if (main_vol > 127)
		main_vol = 127;
	volume = (volume * main_vol) / 127;

	if (level)
		level += fm_volume_table[volume];

	if (level > 0x3f)
		level = 0x3f;
	if (level < 0)
		level = 0;

	*regbyte = (*regbyte & 0xc0) | (~level & 0x3f);
}
