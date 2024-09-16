static int f_midi_out_open(struct snd_rawmidi_substream *substream)
{
	struct f_midi *midi = substream->rmidi->private_data;

	if (substream->number >= MAX_PORTS)
		return -EINVAL;

	VDBG(midi, "%s()\n", __func__);
	midi->out_substream[substream->number] = substream;
	return 0;
}
