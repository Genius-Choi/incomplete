nfsd4_decode_test_stateid(struct nfsd4_compoundargs *argp, struct nfsd4_test_stateid *test_stateid)
{
	int i;
	__be32 *p, status;
	struct nfsd4_test_stateid_id *stateid;

	READ_BUF(4);
	test_stateid->ts_num_ids = ntohl(*p++);

	INIT_LIST_HEAD(&test_stateid->ts_stateid_list);

	for (i = 0; i < test_stateid->ts_num_ids; i++) {
		stateid = svcxdr_tmpalloc(argp, sizeof(*stateid));
		if (!stateid) {
			status = nfserrno(-ENOMEM);
			goto out;
		}

		INIT_LIST_HEAD(&stateid->ts_id_list);
		list_add_tail(&stateid->ts_id_list, &test_stateid->ts_stateid_list);

		status = nfsd4_decode_stateid(argp, &stateid->ts_id_stateid);
		if (status)
			goto out;
	}

	status = 0;
out:
	return status;
xdr_error:
	dprintk("NFSD: xdr error (%s:%d)\n", __FILE__, __LINE__);
	status = nfserr_bad_xdr;
	goto out;
}
