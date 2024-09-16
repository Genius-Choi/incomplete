state_str(int state)
{
	switch (state) {
	case VRRP_STATE_INIT:
		return "Init";
	case VRRP_STATE_BACK:
		return "Backup";
	case VRRP_STATE_MAST:
		return "Master";
	case VRRP_STATE_FAULT:
		return "Fault";
	}
	return "Unknown";
}
