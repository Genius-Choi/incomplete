static void seq_local_event(unsigned char *event_rec)
{
	unsigned char   cmd = event_rec[1];
	unsigned int    parm = *((unsigned int *) &event_rec[4]);

	switch (cmd)
	{
		case LOCL_STARTAUDIO:
			DMAbuf_start_devices(parm);
			break;

		default:;
	}
}
