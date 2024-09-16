void rds_sysctl_exit(void)
{
	unregister_net_sysctl_table(rds_sysctl_reg_table);
}
