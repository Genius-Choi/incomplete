EXPORTED int mboxlist_findsubmulti(struct namespace *namespace,
                                   const strarray_t *patterns, int isadmin,
                                   const char *userid, const struct auth_state *auth_state,
                                   findall_cb *proc, void *rock,
                                   int force)
{
    int r = 0;

    if (!namespace) namespace = mboxname_get_adminnamespace();

    struct find_rock cbrock;
    memset(&cbrock, 0, sizeof(struct find_rock));

    /* open the subscription file that contains the mailboxes the
       user is subscribed to */
    struct db *subs = NULL;
    r = mboxlist_opensubs(userid, &subs);
    if (r) return r;

    cbrock.auth_state = auth_state;
    cbrock.checkmboxlist = !force;
    cbrock.db = subs;
    cbrock.isadmin = isadmin;
    cbrock.issubs = 1;
    cbrock.namespace = namespace;
    cbrock.proc = proc;
    cbrock.procrock = rock;
    cbrock.userid = userid;
    if (userid) {
        const char *domp = strchr(userid, '@');
        if (domp) cbrock.domain = domp + 1;
    }

    r = mboxlist_do_find(&cbrock, patterns);

    mboxlist_closesubs(subs);

    return r;
}
