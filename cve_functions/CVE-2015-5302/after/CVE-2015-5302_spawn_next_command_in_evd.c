static int spawn_next_command_in_evd(struct analyze_event_data *evd)
{
    evd->env_list = export_event_config(evd->event_name);
    int r = spawn_next_command(evd->run_state, g_dump_dir_name, evd->event_name, EXECFLG_SETPGID);
    if (r >= 0)
    {
        g_event_child_pid = evd->run_state->command_pid;
    }
    else
    {
        unexport_event_config(evd->env_list);
        evd->env_list = NULL;
    }
    return r;
}
