static int opl3_init(int ioaddr, struct module *owner)
{
	int i;
	int me;

	if (devc == NULL)
	{
		printk(KERN_ERR "opl3: Device control structure not initialized.\n");
		return -1;
	}

	if ((me = sound_alloc_synthdev()) == -1)
	{
		printk(KERN_WARNING "opl3: Too many synthesizers\n");
		return -1;
	}

	devc->nr_voice = 9;

	devc->fm_info.device = 0;
	devc->fm_info.synth_type = SYNTH_TYPE_FM;
	devc->fm_info.synth_subtype = FM_TYPE_ADLIB;
	devc->fm_info.perc_mode = 0;
	devc->fm_info.nr_voices = 9;
	devc->fm_info.nr_drums = 0;
	devc->fm_info.instr_bank_size = SBFM_MAXINSTR;
	devc->fm_info.capabilities = 0;
	devc->left_io = ioaddr;
	devc->right_io = ioaddr + 2;

	if (detected_model <= 2)
		devc->model = 1;
	else
	{
		devc->model = 2;
		if (detected_model == 4)
			devc->is_opl4 = 1;
	}

	opl3_operations.info = &devc->fm_info;

	synth_devs[me] = &opl3_operations;

	if (owner)
		synth_devs[me]->owner = owner;
	
	sequencer_init();
	devc->v_alloc = &opl3_operations.alloc;
	devc->chn_info = &opl3_operations.chn_info[0];

	if (devc->model == 2)
	{
		if (devc->is_opl4) 
			strcpy(devc->fm_info.name, "Yamaha OPL4/OPL3 FM");
		else 
			strcpy(devc->fm_info.name, "Yamaha OPL3");

		devc->v_alloc->max_voice = devc->nr_voice = 18;
		devc->fm_info.nr_drums = 0;
		devc->fm_info.synth_subtype = FM_TYPE_OPL3;
		devc->fm_info.capabilities |= SYNTH_CAP_OPL3;

		for (i = 0; i < 18; i++)
		{
			if (pv_map[i].ioaddr == USE_LEFT)
				pv_map[i].ioaddr = devc->left_io;
			else
				pv_map[i].ioaddr = devc->right_io;
		}
		opl3_command(devc->right_io, OPL3_MODE_REGISTER, OPL3_ENABLE);
		opl3_command(devc->right_io, CONNECTION_SELECT_REGISTER, 0x00);
	}
	else
	{
		strcpy(devc->fm_info.name, "Yamaha OPL2");
		devc->v_alloc->max_voice = devc->nr_voice = 9;
		devc->fm_info.nr_drums = 0;

		for (i = 0; i < 18; i++)
			pv_map[i].ioaddr = devc->left_io;
	};
	conf_printf2(devc->fm_info.name, ioaddr, 0, -1, -1);

	for (i = 0; i < SBFM_MAXINSTR; i++)
		devc->i_map[i].channel = -1;

	return me;
}
