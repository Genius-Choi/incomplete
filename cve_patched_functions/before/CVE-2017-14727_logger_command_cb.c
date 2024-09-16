logger_command_cb (const void *pointer, void *data,
                   struct t_gui_buffer *buffer,
                   int argc, char **argv, char **argv_eol)
{
    /* make C compiler happy */
    (void) pointer;
    (void) data;
    (void) argv_eol;

    if ((argc == 1)
        || ((argc == 2) && (weechat_strcasecmp (argv[1], "list") == 0)))
    {
        logger_list ();
        return WEECHAT_RC_OK;
    }

    if (weechat_strcasecmp (argv[1], "set") == 0)
    {
        if (argc > 2)
            logger_set_buffer (buffer, argv[2]);
        return WEECHAT_RC_OK;
    }

    if (weechat_strcasecmp (argv[1], "flush") == 0)
    {
        logger_flush ();
        return WEECHAT_RC_OK;
    }

    if (weechat_strcasecmp (argv[1], "disable") == 0)
    {
        logger_set_buffer (buffer, "0");
        return WEECHAT_RC_OK;
    }

    WEECHAT_COMMAND_ERROR;
}
