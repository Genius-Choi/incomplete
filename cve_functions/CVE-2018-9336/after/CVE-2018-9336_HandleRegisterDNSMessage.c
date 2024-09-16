HandleRegisterDNSMessage(void)
{
    DWORD err;
    HANDLE thread = NULL;

    /* Delegate this job to a sub-thread */
    thread = CreateThread(NULL, 0, RegisterDNS, NULL, 0, NULL);

    /*
     * We don't add these thread handles to the undo list -- the thread and
     * processes it spawns are all supposed to terminate or timeout by themselves.
     */
    if (thread)
    {
        err = 0;
        CloseHandle(thread);
    }
    else
    {
        err = GetLastError();
    }

    return err;
}
