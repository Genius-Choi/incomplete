event_signal(void *eventhdl)
{
	return (int)SetEvent((HANDLE)eventhdl);
}
