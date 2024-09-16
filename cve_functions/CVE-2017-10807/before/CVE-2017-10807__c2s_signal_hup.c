static void _c2s_signal_hup(int signum)
{
    c2s_logrotate = 1;
    c2s_sighup = 1;
}
