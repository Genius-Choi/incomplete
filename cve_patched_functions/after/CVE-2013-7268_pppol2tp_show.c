static void pppol2tp_show(struct seq_file *m, void *arg)
{
	struct l2tp_session *session = arg;
	struct pppol2tp_session *ps = l2tp_session_priv(session);

	if (ps) {
		struct pppox_sock *po = pppox_sk(ps->sock);
		if (po)
			seq_printf(m, "   interface %s\n", ppp_dev_name(&po->chan));
	}
}
