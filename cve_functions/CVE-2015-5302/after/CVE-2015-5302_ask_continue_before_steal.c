static bool ask_continue_before_steal(const char *base_dir, const char *dump_dir)
{
    char *msg = xasprintf(_("Need writable directory, but '%s' is not writable."
                            " Move it to '%s' and operate on the moved data?"),
                            dump_dir, base_dir);
    const bool response = run_ask_yes_no_yesforever_dialog("ask_steal_dir", msg, GTK_WINDOW(g_wnd_assistant));
    free(msg);
    return response;
}
