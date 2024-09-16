process_buffered_input_packets(void)
{
	dispatch_run(DISPATCH_NONBLOCK, NULL, active_state);
}
