static void _c2s_signal(int signum)
{
    c2s_shutdown = 1;
    c2s_lost_router = 0;
}
