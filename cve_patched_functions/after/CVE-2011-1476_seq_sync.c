static int seq_sync(void)
{
	if (qlen && !seq_playing && !signal_pending(current))
		seq_startplay();

 	if (qlen > 0)
 		interruptible_sleep_on_timeout(&seq_sleeper, HZ);
	return qlen;
}
