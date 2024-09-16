initialize(int argc, char *argv[]) {
    int i;

    for(i=0; i<argc; ++i) {
        if(!strcmp(argv[i], "-s") || !strcmp(argv[i], "--socket")) {
            uzbl.state.plug_mode = TRUE;
            break;
        }
    }

    if (!g_thread_supported ())
        g_thread_init (NULL);
    gtk_init (&argc, &argv);

    uzbl.state.executable_path = g_strdup(argv[0]);
    uzbl.state.selected_url = NULL;
    uzbl.state.searchtx = NULL;

    GOptionContext* context = g_option_context_new ("[ uri ] - load a uri by default");
    g_option_context_add_main_entries (context, entries, NULL);
    g_option_context_add_group (context, gtk_get_option_group (TRUE));
    g_option_context_parse (context, &argc, &argv, NULL);
    g_option_context_free(context);

    if (uzbl.behave.print_version) {
        printf("Commit: %s\n", COMMIT);
        exit(EXIT_SUCCESS);
    }

    uzbl.net.soup_session = webkit_get_default_session();
    uzbl.state.keycmd = g_strdup("");

    for(i=0; sigs[i]; i++) {
        if(setup_signal(sigs[i], catch_signal) == SIG_ERR)
            fprintf(stderr, "uzbl: error hooking %d: %s\n", sigs[i], strerror(errno));
    }
    event_buffer_timeout(10);

    uzbl.info.webkit_major = WEBKIT_MAJOR_VERSION;
    uzbl.info.webkit_minor = WEBKIT_MINOR_VERSION;
    uzbl.info.webkit_micro = WEBKIT_MICRO_VERSION;
    uzbl.info.arch         = ARCH;
    uzbl.info.commit       = COMMIT;

    commands_hash ();
    create_var_to_name_hash();

    create_mainbar();
    create_browser();
}
