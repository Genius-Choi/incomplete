test_run_handler_arg_order (void) {
    run_handler("sync_spawn echo uvw xyz", "abc def");

    assert(uzbl.comm.sync_stdout);

    /* the result should begin with the standard handler arguments */
    gchar *rest = assert_sync_beginswith_stdarg();

    /* the rest of the result should be the arguments passed to run_handler. */
    /* the arguments in the second argument to run_handler should be placed before any
     * included in the first argument to run handler. */
    g_assert_cmpstr("abc def uvw xyz\n", ==, rest);
}
