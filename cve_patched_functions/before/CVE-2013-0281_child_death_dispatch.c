child_death_dispatch(GPid pid, gint status, gpointer user_data)
{
    int signo = 0;
    int exitcode = 0;
    mainloop_child_t *child = user_data;

    crm_trace("Managed process %d exited: %p", pid, child);

    if (WIFEXITED(status)) {
        exitcode = WEXITSTATUS(status);
        crm_trace("Managed process %d (%s) exited with rc=%d", pid,
                 child->desc, exitcode);

    } else if (WIFSIGNALED(status)) {
        signo = WTERMSIG(status);
        crm_trace("Managed process %d (%s) exited with signal=%d", pid,
                 child->desc, signo);
    }
#ifdef WCOREDUMP
    if (WCOREDUMP(status)) {
        crm_err("Managed process %d (%s) dumped core", pid, child->desc);
    }
#endif

    if (child->callback) {
       child->callback(child, status, signo, exitcode);
    }
    crm_trace("Removed process entry for %d", pid);

    mainloop_child_destroy(child);
    return;
}
