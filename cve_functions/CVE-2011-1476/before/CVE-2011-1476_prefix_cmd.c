prefix_cmd(int midi_dev, unsigned char status)
{
	if ((char *) midi_devs[midi_dev]->prefix_cmd == NULL)
		return 1;

	return midi_devs[midi_dev]->prefix_cmd(midi_dev, status);
}
