event_destroy(void *eventhdl)
{
	CloseHandle((HANDLE)eventhdl);
}
