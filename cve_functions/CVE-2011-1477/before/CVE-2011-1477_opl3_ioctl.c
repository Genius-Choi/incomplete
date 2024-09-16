static int opl3_ioctl(int dev, unsigned int cmd, void __user * arg)
{
	struct sbi_instrument ins;
	
	switch (cmd) {
		case SNDCTL_FM_LOAD_INSTR:
			printk(KERN_WARNING "Warning: Obsolete ioctl(SNDCTL_FM_LOAD_INSTR) used. Fix the program.\n");
			if (copy_from_user(&ins, arg, sizeof(ins)))
				return -EFAULT;
			if (ins.channel < 0 || ins.channel >= SBFM_MAXINSTR) {
				printk(KERN_WARNING "FM Error: Invalid instrument number %d\n", ins.channel);
				return -EINVAL;
			}
			return store_instr(ins.channel, &ins);

		case SNDCTL_SYNTH_INFO:
			devc->fm_info.nr_voices = (devc->nr_voice == 12) ? 6 : devc->nr_voice;
			if (copy_to_user(arg, &devc->fm_info, sizeof(devc->fm_info)))
				return -EFAULT;
			return 0;

		case SNDCTL_SYNTH_MEMAVL:
			return 0x7fffffff;

		case SNDCTL_FM_4OP_ENABLE:
			if (devc->model == 2)
				enter_4op_mode();
			return 0;

		default:
			return -EINVAL;
	}
}
