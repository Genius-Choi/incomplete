static int can_do_hugetlb_shm(void)
{
	return capable(CAP_IPC_LOCK) || in_group_p(sysctl_hugetlb_shm_group);
}
