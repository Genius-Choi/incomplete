static void opl3_controller (int dev, int voice, int ctrl_num, int value)
{
	if (voice < 0 || voice >= devc->nr_voice)
		return;

	switch (ctrl_num)
	{
		case CTRL_PITCH_BENDER:
			bend_pitch(dev, voice, value);
			break;

		case CTRL_PITCH_BENDER_RANGE:
			devc->voc[voice].bender_range = value;
			break;

		case CTL_MAIN_VOLUME:
			devc->voc[voice].volume = value / 128;
			break;

		case CTL_PAN:
			devc->voc[voice].panning = (value * 2) - 128;
			break;
	}
}
