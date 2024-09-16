void hns_rcb_get_queue_mode(enum dsaf_mode dsaf_mode, u16 *max_vfn,
			    u16 *max_q_per_vf)
{
	switch (dsaf_mode) {
	case DSAF_MODE_DISABLE_6PORT_0VM:
		*max_vfn = 1;
		*max_q_per_vf = 16;
		break;
	case DSAF_MODE_DISABLE_FIX:
	case DSAF_MODE_DISABLE_SP:
		*max_vfn = 1;
		*max_q_per_vf = 1;
		break;
	case DSAF_MODE_DISABLE_2PORT_64VM:
		*max_vfn = 64;
		*max_q_per_vf = 1;
		break;
	case DSAF_MODE_DISABLE_6PORT_16VM:
		*max_vfn = 16;
		*max_q_per_vf = 1;
		break;
	default:
		*max_vfn = 1;
		*max_q_per_vf = 16;
		break;
	}
}
