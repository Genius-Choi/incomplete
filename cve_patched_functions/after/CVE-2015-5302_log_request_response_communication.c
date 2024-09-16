static void log_request_response_communication(const char *request, const char *response, struct analyze_event_data *evd)
{
    char *message = xasprintf(response ? "%s '%s'" : "%s", request, response);
    update_command_run_log(message, evd);
    free(message);
}
