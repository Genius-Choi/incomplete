static void update_cpu_load_active(struct rq *this_rq)
{
	update_cpu_load(this_rq);

	calc_load_account_active(this_rq);
}
