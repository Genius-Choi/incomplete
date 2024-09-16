static void seq_sysex_message(unsigned char *event_rec)
{
	unsigned int dev = event_rec[1];
	int i, l = 0;
	unsigned char  *buf = &event_rec[2];

	if (dev > max_synthdev)
		return;
	if (!(synth_open_mask & (1 << dev)))
		return;
	if (!synth_devs[dev])
		return;

	l = 0;
	for (i = 0; i < 6 && buf[i] != 0xff; i++)
		l = i + 1;

	if (!synth_devs[dev]->send_sysex)
		return;
	if (l > 0)
		synth_devs[dev]->send_sysex(dev, buf, l);
}
