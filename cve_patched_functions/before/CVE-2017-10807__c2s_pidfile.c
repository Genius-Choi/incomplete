static void _c2s_pidfile(c2s_t c2s) {
    const char *pidfile;
    FILE *f;
    pid_t pid;

    pidfile = config_get_one(c2s->config, "pidfile", 0);
    if(pidfile == NULL)
        return;

    pid = getpid();

    if((f = fopen(pidfile, "w+")) == NULL) {
        log_write(c2s->log, LOG_ERR, "couldn't open %s for writing: %s", pidfile, strerror(errno));
        return;
    }

    if(fprintf(f, "%d", pid) < 0) {
        log_write(c2s->log, LOG_ERR, "couldn't write to %s: %s", pidfile, strerror(errno));
        fclose(f);
        return;
    }

    fclose(f);

    log_write(c2s->log, LOG_INFO, "process id is %d, written to %s", pid, pidfile);
}
