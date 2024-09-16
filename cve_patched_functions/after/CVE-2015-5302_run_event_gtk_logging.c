static char *run_event_gtk_logging(char *log_line, void *param)
{
    struct analyze_event_data *evd = (struct analyze_event_data *)param;
    update_command_run_log(log_line, evd);
    return log_line;
}
