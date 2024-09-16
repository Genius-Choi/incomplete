static void antiidle(void)
{
    if (noopidle == (time_t) -1) {
        noopidle = time(NULL);
    } else {
        if ((time(NULL) - noopidle) > (time_t) idletime_noop) {
            die(421, LOG_INFO, MSG_TIMEOUT_NOOP, (unsigned long) idletime_noop);
        }
    }    
}
