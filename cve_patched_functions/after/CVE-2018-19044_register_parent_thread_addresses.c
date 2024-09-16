register_parent_thread_addresses(void)
{
	register_scheduler_addresses();
	register_signal_thread_addresses();

#ifdef _WITH_LVS_
	register_check_parent_addresses();
#endif
#ifdef _WITH_VRRP_
	register_vrrp_parent_addresses();
#endif
#ifdef _WITH_BFD_
	register_bfd_parent_addresses();
#endif

#ifndef _DEBUG_
	register_signal_handler_address("propagate_signal", propagate_signal);
	register_signal_handler_address("sigend", sigend);
#endif
	register_signal_handler_address("thread_child_handler", thread_child_handler);
}
