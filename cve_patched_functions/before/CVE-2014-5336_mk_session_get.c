struct client_session *mk_session_get(int socket)
{
    struct client_session *cs;
    struct rb_node *node;

    node = cs_list->rb_node;
  	while (node) {
  		cs = container_of(node, struct client_session, _rb_head);
		if (socket < cs->socket)
  			node = node->rb_left;
		else if (socket > cs->socket)
  			node = node->rb_right;
		else {
  			return cs;
        }
	}
	return NULL;
}
