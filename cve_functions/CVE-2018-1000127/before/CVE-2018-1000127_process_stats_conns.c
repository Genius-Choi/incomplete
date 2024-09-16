static void process_stats_conns(ADD_STAT add_stats, void *c) {
    int i;
    char key_str[STAT_KEY_LEN];
    char val_str[STAT_VAL_LEN];
    char conn_name[MAXPATHLEN + sizeof("unix:")];
    int klen = 0, vlen = 0;

    assert(add_stats);

    for (i = 0; i < max_fds; i++) {
        if (conns[i]) {
            /* This is safe to do unlocked because conns are never freed; the
             * worst that'll happen will be a minor inconsistency in the
             * output -- not worth the complexity of the locking that'd be
             * required to prevent it.
             */
            if (conns[i]->state != conn_closed) {
                conn_to_str(conns[i], conn_name);

                APPEND_NUM_STAT(i, "addr", "%s", conn_name);
                APPEND_NUM_STAT(i, "state", "%s",
                        state_text(conns[i]->state));
                APPEND_NUM_STAT(i, "secs_since_last_cmd", "%d",
                        current_time - conns[i]->last_cmd_time);
            }
        }
    }
}
