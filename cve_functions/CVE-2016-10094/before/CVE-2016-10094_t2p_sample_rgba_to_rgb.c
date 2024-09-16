t2p_sample_rgba_to_rgb(tdata_t data, uint32 samplecount)
{
	uint32 i = 0;
	uint32 sample = 0;
	uint8 alpha = 0;

	for (i = 0; i < samplecount; i++) {
		sample=((uint32*)data)[i];
		alpha=(uint8)((255 - ((sample >> 24) & 0xff)));
		((uint8 *)data)[i * 3] = (uint8) ((sample >> 16) & 0xff) + alpha;
		((uint8 *)data)[i * 3 + 1] = (uint8) ((sample >> 8) & 0xff) + alpha;
		((uint8 *)data)[i * 3 + 2] = (uint8) (sample & 0xff) + alpha;
	}

	return (i * 3);
}
