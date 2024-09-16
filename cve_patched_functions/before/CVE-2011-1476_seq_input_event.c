void seq_input_event(unsigned char *event_rec, int len)
{
	unsigned long this_time;

	if (seq_mode == SEQ_2)
		this_time = tmr->get_time(tmr_no);
	else
		this_time = jiffies - seq_time;

	if (this_time != prev_input_time)
	{
		unsigned char   tmp_event[8];

		tmp_event[0] = EV_TIMING;
		tmp_event[1] = TMR_WAIT_ABS;
		tmp_event[2] = 0;
		tmp_event[3] = 0;
		*(unsigned int *) &tmp_event[4] = this_time;

		seq_copy_to_input(tmp_event, 8);
		prev_input_time = this_time;
	}
	seq_copy_to_input(event_rec, len);
}
