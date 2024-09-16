int save_mc_for_early(u8 *mc)
{
	struct microcode_intel *mc_saved_tmp[MAX_UCODE_COUNT];
	unsigned int mc_saved_count_init;
	unsigned int mc_saved_count;
	struct microcode_intel **mc_saved;
	int ret = 0;
	int i;

	/*
	 * Hold hotplug lock so mc_saved_data is not accessed by a CPU in
	 * hotplug.
	 */
	mutex_lock(&x86_cpu_microcode_mutex);

	mc_saved_count_init = mc_saved_data.mc_saved_count;
	mc_saved_count = mc_saved_data.mc_saved_count;
	mc_saved = mc_saved_data.mc_saved;

	if (mc_saved && mc_saved_count)
		memcpy(mc_saved_tmp, mc_saved,
		       mc_saved_count * sizeof(struct microcode_intel *));
	/*
	 * Save the microcode patch mc in mc_save_tmp structure if it's a newer
	 * version.
	 */

	_save_mc(mc_saved_tmp, mc, &mc_saved_count);

	/*
	 * Save the mc_save_tmp in global mc_saved_data.
	 */
	ret = save_microcode(&mc_saved_data, mc_saved_tmp, mc_saved_count);
	if (ret) {
		pr_err("Cannot save microcode patch.\n");
		goto out;
	}

	show_saved_mc();

	/*
	 * Free old saved microcode data.
	 */
	if (mc_saved) {
		for (i = 0; i < mc_saved_count_init; i++)
			kfree(mc_saved[i]);
		kfree(mc_saved);
	}

out:
	mutex_unlock(&x86_cpu_microcode_mutex);

	return ret;
}
