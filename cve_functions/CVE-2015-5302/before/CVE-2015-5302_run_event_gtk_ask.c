static char *run_event_gtk_ask(const char *msg, void *args)
{
    return ask_helper(msg, args, false);
}
