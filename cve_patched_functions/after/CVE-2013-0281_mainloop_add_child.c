mainloop_add_child(pid_t pid, int timeout, const char *desc, void * privatedata,
    void (*callback)(mainloop_child_t *p, int status, int signo, int exitcode))
{
    mainloop_child_t *child = g_new(mainloop_child_t, 1);

    child->pid = pid;
    child->timerid = 0;
    child->timeout = FALSE;
    child->desc = strdup(desc);
    child->privatedata = privatedata;
    child->callback = callback;

    if (timeout) {
        child->timerid = g_timeout_add(
            timeout, child_timeout_callback, child);
    }

    child->watchid = g_child_watch_add(pid, child_death_dispatch, child);
}
