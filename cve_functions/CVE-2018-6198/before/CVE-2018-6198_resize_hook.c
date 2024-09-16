resize_hook(SIGNAL_ARG)
{
    need_resize_screen = TRUE;
    mySignal(SIGWINCH, resize_hook);
    SIGNAL_RETURN;
}
