run_warning (CommonJob  *job,
             char       *primary_text,
             char       *secondary_text,
             const char *details_text,
             gboolean    show_all,
             ...)
{
    va_list varargs;
    int res;

    va_start (varargs, show_all);
    res = run_simple_dialog_va (job,
                                FALSE,
                                GTK_MESSAGE_WARNING,
                                primary_text,
                                secondary_text,
                                details_text,
                                show_all,
                                varargs);
    va_end (varargs);
    return res;
}
