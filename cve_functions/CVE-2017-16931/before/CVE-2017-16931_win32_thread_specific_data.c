win32_thread_specific_data(void *private_data)
{
    return((DWORD) thread_specific_data(private_data));
}
