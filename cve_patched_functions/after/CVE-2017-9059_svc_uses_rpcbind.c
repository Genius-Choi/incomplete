static int svc_uses_rpcbind(struct svc_serv *serv)
{
	struct svc_program	*progp;
	unsigned int		i;

	for (progp = serv->sv_program; progp; progp = progp->pg_next) {
		for (i = 0; i < progp->pg_nvers; i++) {
			if (progp->pg_vers[i] == NULL)
				continue;
			if (!progp->pg_vers[i]->vs_hidden)
				return 1;
		}
	}

	return 0;
}
