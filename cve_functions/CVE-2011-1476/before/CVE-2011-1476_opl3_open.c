static int opl3_open(int dev, int mode)
{
	int i;

	if (devc->busy)
		return -EBUSY;
	devc->busy = 1;

	devc->v_alloc->max_voice = devc->nr_voice = (devc->model == 2) ? 18 : 9;
	devc->v_alloc->timestamp = 0;

	for (i = 0; i < 18; i++)
	{
		devc->v_alloc->map[i] = 0;
		devc->v_alloc->alloc_times[i] = 0;
	}

	devc->cmask = 0x00;	/*
				 * Just 2 OP mode
				 */
	if (devc->model == 2)
		opl3_command(devc->right_io, CONNECTION_SELECT_REGISTER, devc->cmask);
	return 0;
}
