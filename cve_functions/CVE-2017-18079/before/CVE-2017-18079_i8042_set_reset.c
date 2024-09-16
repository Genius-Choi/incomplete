static int i8042_set_reset(const char *val, const struct kernel_param *kp)
{
	enum i8042_controller_reset_mode *arg = kp->arg;
	int error;
	bool reset;

	if (val) {
		error = kstrtobool(val, &reset);
		if (error)
			return error;
	} else {
		reset = true;
	}

	*arg = reset ? I8042_RESET_ALWAYS : I8042_RESET_NEVER;
	return 0;
}
