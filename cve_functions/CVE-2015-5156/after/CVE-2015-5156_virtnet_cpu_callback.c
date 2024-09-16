static int virtnet_cpu_callback(struct notifier_block *nfb,
			        unsigned long action, void *hcpu)
{
	struct virtnet_info *vi = container_of(nfb, struct virtnet_info, nb);

	switch(action & ~CPU_TASKS_FROZEN) {
	case CPU_ONLINE:
	case CPU_DOWN_FAILED:
	case CPU_DEAD:
		virtnet_set_affinity(vi);
		break;
	case CPU_DOWN_PREPARE:
		virtnet_clean_affinity(vi, (long)hcpu);
		break;
	default:
		break;
	}

	return NOTIFY_OK;
}
