leave_sysex(int dev)
{
	int             orig_dev = synth_devs[dev]->midi_dev;
	int             timeout = 0;

	if (!sysex_state[dev])
		return;

	sysex_state[dev] = 0;

	while (!midi_devs[orig_dev]->outputc(orig_dev, 0xf7) &&
	       timeout < 1000)
		timeout++;

	sysex_state[dev] = 0;
}
