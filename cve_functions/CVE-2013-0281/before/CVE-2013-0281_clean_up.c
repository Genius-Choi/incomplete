clean_up(int rc)
{
#if ENABLE_SNMP
    netsnmp_session *session = crm_snmp_init(NULL, NULL);

    if (session) {
        snmp_close(session);
        snmp_shutdown("snmpapp");
    }
#endif

#if CURSES_ENABLED
    if (as_console) {
        as_console = FALSE;
        echo();
        nocbreak();
        endwin();
    }
#endif

    if (cib != NULL) {
        cib->cmds->signoff(cib);
        cib_delete(cib);
        cib = NULL;
    }

    free(as_html_file);
    free(xml_file);
    free(pid_file);

    if (rc >= 0) {
        crm_exit(rc);
    }
    return;
}
