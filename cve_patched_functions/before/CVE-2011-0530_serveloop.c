int serveloop(GArray* servers) {
	struct sockaddr_storage addrin;
	socklen_t addrinlen=sizeof(addrin);
	int i;
	int max;
	int sock;
	fd_set mset;
	fd_set rset;

	/* 
	 * Set up the master fd_set. The set of descriptors we need
	 * to select() for never changes anyway and it buys us a *lot*
	 * of time to only build this once. However, if we ever choose
	 * to not fork() for clients anymore, we may have to revisit
	 * this.
	 */
	max=0;
	FD_ZERO(&mset);
	for(i=0;i<servers->len;i++) {
		if((sock=(g_array_index(servers, SERVER, i)).socket)) {
			FD_SET(sock, &mset);
			max=sock>max?sock:max;
		}
	}
	if(modernsock) {
		FD_SET(modernsock, &mset);
		max=modernsock>max?modernsock:max;
	}
	for(;;) {
		CLIENT *client = NULL;
		pid_t *pid;

		memcpy(&rset, &mset, sizeof(fd_set));
		if(select(max+1, &rset, NULL, NULL, NULL)>0) {
			int net = 0;
			SERVER* serve;

			DEBUG("accept, ");
			if(FD_ISSET(modernsock, &rset)) {
				if((net=accept(modernsock, (struct sockaddr *) &addrin, &addrinlen)) < 0)
					err("accept: %m");
				client = negotiate(net, NULL, servers);
				if(!client) {
					err_nonfatal("negotiation failed");
					close(net);
					net=0;
				}
			}
			for(i=0;i<servers->len && !net;i++) {
				serve=&(g_array_index(servers, SERVER, i));
				if(FD_ISSET(serve->socket, &rset)) {
					if ((net=accept(serve->socket, (struct sockaddr *) &addrin, &addrinlen)) < 0)
						err("accept: %m");
				}
			}
			if(net) {
				int sock_flags;

				if(serve->max_connections > 0 &&
				   g_hash_table_size(children) >= serve->max_connections) {
					msg2(LOG_INFO, "Max connections reached");
					close(net);
					continue;
				}
				if((sock_flags = fcntl(net, F_GETFL, 0))==-1) {
					err("fcntl F_GETFL");
				}
				if(fcntl(net, F_SETFL, sock_flags &~O_NONBLOCK)==-1) {
					err("fcntl F_SETFL ~O_NONBLOCK");
				}
				if(!client) {
					client = g_new0(CLIENT, 1);
					client->server=serve;
					client->exportsize=OFFT_MAX;
					client->net=net;
				}
				set_peername(net, client);
				if (!authorized_client(client)) {
					msg2(LOG_INFO,"Unauthorized client") ;
					close(net);
					continue;
				}
				msg2(LOG_INFO,"Authorized client") ;
				pid=g_malloc(sizeof(pid_t));
#ifndef NOFORK
				if ((*pid=fork())<0) {
					msg3(LOG_INFO,"Could not fork (%s)",strerror(errno)) ;
					close(net);
					continue;
				}
				if (*pid>0) { /* parent */
					close(net);
					g_hash_table_insert(children, pid, pid);
					continue;
				}
				/* child */
				g_hash_table_destroy(children);
				for(i=0;i<servers->len;i++) {
					serve=&g_array_index(servers, SERVER, i);
					close(serve->socket);
				}
				/* FALSE does not free the
				actual data. This is required,
				because the client has a
				direct reference into that
				data, and otherwise we get a
				segfault... */
				g_array_free(servers, FALSE);
#endif // NOFORK
				msg2(LOG_INFO,"Starting to serve");
				serveconnection(client);
				exit(EXIT_SUCCESS);
			}
		}
	}
}
