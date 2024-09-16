event_wait(void *eventhdl)
{
	int res = WaitForSingleObject((HANDLE)eventhdl, (DWORD)INFINITE);
	return (res == WAIT_OBJECT_0);
}
