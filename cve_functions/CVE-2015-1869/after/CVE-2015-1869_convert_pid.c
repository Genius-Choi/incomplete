unsigned convert_pid(GHashTable *problem_info)
{
    long ret;
    gchar *pid_str = (gchar *) g_hash_table_lookup(problem_info, FILENAME_PID);
    char *err_pos;

    if (!pid_str)
        error_msg_and_die("PID data is missing, aborting");

    errno = 0;
    ret = strtol(pid_str, &err_pos, 10);
    if (errno || pid_str == err_pos || *err_pos != '\0'
        || ret > UINT_MAX || ret < 1)
        error_msg_and_die("Malformed or out-of-range PID number: '%s'", pid_str);

    return (unsigned) ret;
}
