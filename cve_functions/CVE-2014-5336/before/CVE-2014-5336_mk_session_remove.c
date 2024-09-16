void mk_session_remove(int socket)
{
    struct client_session *cs_node;

    cs_node = mk_session_get(socket);
    if (cs_node) {
        rb_erase(&cs_node->_rb_head, cs_list);
        if (cs_node->body != cs_node->body_fixed) {
            mk_mem_free(cs_node->body);
        }
        if (mk_list_entry_orphan(&cs_node->request_incomplete) == 0) {
            mk_list_del(&cs_node->request_incomplete);
        }
        mk_list_del(&cs_node->request_list);
        mk_mem_free(cs_node);
    }
}
