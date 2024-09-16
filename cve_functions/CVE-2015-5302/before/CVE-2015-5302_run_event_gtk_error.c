static void run_event_gtk_error(const char *error_line, void *param)
{
    update_command_run_log(error_line, (struct analyze_event_data *)param);
}
