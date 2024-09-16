static int find_voice(int dev, int chn, int note)
{
	unsigned short key;
	int i;

	key = (chn << 8) | (note + 1);
	for (i = 0; i < synth_devs[dev]->alloc.max_voice; i++)
		if (synth_devs[dev]->alloc.map[i] == key)
			return i;
	return -1;
}
