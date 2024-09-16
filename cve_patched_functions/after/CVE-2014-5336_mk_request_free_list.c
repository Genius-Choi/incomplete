void mk_request_free_list(struct client_session *cs)
{
    struct session_request *sr_node;
    struct mk_list *sr_head, *temp;

    /* sr = last node */
    MK_TRACE("[FD %i] Free struct client_session", cs->socket);

    mk_list_foreach_safe(sr_head, temp, &cs->request_list) {
        sr_node = mk_list_entry(sr_head, struct session_request, _head);
        mk_list_del(sr_head);

        mk_request_free(sr_node);
        if (sr_node != &cs->sr_fixed) {
            mk_mem_free(sr_node);
        }
    }
}
