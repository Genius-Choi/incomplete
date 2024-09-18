static void pppol2tp_seq_session_show(struct seq_file *m, void *v)
{
	struct l2tp_session *session = v;
	struct l2tp_tunnel *tunnel = session->tunnel;
	struct pppol2tp_session *ps = l2tp_session_priv(session);
	struct pppox_sock *po = pppox_sk(ps->sock);
	u32 ip = 0;
	u16 port = 0;

	if (tunnel->sock) {
		struct inet_sock *inet = inet_sk(tunnel->sock);
		ip = ntohl(inet->inet_saddr);
		port = ntohs(inet->inet_sport);
	}

	seq_printf(m, "  SESSION '%s' %08X/%d %04X/%04X -> "
		   "%04X/%04X %d %c\n",
		   session->name, ip, port,
		   tunnel->tunnel_id,
		   session->session_id,
		   tunnel->peer_tunnel_id,
		   session->peer_session_id,
		   ps->sock->sk_state,
		   (session == ps->sock->sk_user_data) ?
		   'Y' : 'N');
	seq_printf(m, "   %d/%d/%c/%c/%s %08x %u\n",
		   session->mtu, session->mru,
		   session->recv_seq ? 'R' : '-',
		   session->send_seq ? 'S' : '-',
		   session->lns_mode ? "LNS" : "LAC",
		   session->debug,
		   jiffies_to_msecs(session->reorder_timeout));
	seq_printf(m, "   %hu/%hu %ld/%ld/%ld %ld/%ld/%ld\n",
		   session->nr, session->ns,
		   atomic_long_read(&session->stats.tx_packets),
		   atomic_long_read(&session->stats.tx_bytes),
		   atomic_long_read(&session->stats.tx_errors),
		   atomic_long_read(&session->stats.rx_packets),
		   atomic_long_read(&session->stats.rx_bytes),
		   atomic_long_read(&session->stats.rx_errors));

	if (po)
		seq_printf(m, "   interface %s\n", ppp_dev_name(&po->chan));
}
