static int hyp_init_cpu_notify(struct notifier_block *self,
			       unsigned long action, void *cpu)
{
	switch (action) {
	case CPU_STARTING:
	case CPU_STARTING_FROZEN:
		cpu_init_hyp_mode(NULL);
		break;
	}

	return NOTIFY_OK;
}
