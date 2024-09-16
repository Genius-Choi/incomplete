static void _convert_job_mem(slurm_msg_t *msg)
{
	prolog_launch_msg_t *req = (prolog_launch_msg_t *)msg->data;
	slurm_cred_arg_t arg;
	hostset_t j_hset = NULL;
	int rc, hi, host_index, job_cpus;
	int i, i_first_bit = 0, i_last_bit = 0;

	rc = slurm_cred_verify(conf->vctx, req->cred, &arg,
			       msg->protocol_version);
	if (rc < 0) {
		error("%s: slurm_cred_verify failed: %m", __func__);
		req->nnodes = 1;	/* best guess */
		return;
	}

	req->nnodes = arg.job_nhosts;

	if (arg.job_mem_limit == 0)
		goto fini;
	if ((arg.job_mem_limit & MEM_PER_CPU) == 0) {
		req->job_mem_limit = arg.job_mem_limit;
		goto fini;
	}

	/* Assume 1 CPU on error */
	req->job_mem_limit = arg.job_mem_limit & (~MEM_PER_CPU);

	if (!(j_hset = hostset_create(arg.job_hostlist))) {
		error("%s: Unable to parse credential hostlist: `%s'",
		      __func__, arg.step_hostlist);
		goto fini;
	}
	host_index = hostset_find(j_hset, conf->node_name);
	hostset_destroy(j_hset);

	hi = host_index + 1;	/* change from 0-origin to 1-origin */
	for (i = 0; hi; i++) {
		if (hi > arg.sock_core_rep_count[i]) {
			i_first_bit += arg.sockets_per_node[i] *
				       arg.cores_per_socket[i] *
				       arg.sock_core_rep_count[i];
			i_last_bit = i_first_bit +
				     arg.sockets_per_node[i] *
				     arg.cores_per_socket[i] *
				     arg.sock_core_rep_count[i];
			hi -= arg.sock_core_rep_count[i];
		} else {
			i_first_bit += arg.sockets_per_node[i] *
				       arg.cores_per_socket[i] * (hi - 1);
			i_last_bit = i_first_bit +
				     arg.sockets_per_node[i] *
				     arg.cores_per_socket[i];
			break;
		}
	}

	/* Now count the allocated processors on this node */
	job_cpus = 0;
	for (i = i_first_bit; i < i_last_bit; i++) {
		if (bit_test(arg.job_core_bitmap, i))
			job_cpus++;
	}

	/* NOTE: alloc_lps is the count of allocated resources
	 * (typically cores). Convert to CPU count as needed */
	if (i_last_bit > i_first_bit) {
		i = conf->cpus / (i_last_bit - i_first_bit);
		if (i > 1)
			job_cpus *= i;
	}

	req->job_mem_limit *= job_cpus;

fini:	slurm_cred_free_args(&arg);
}
