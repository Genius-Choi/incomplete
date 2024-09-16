static void airo_print_status(const char *devname, u16 status)
{
	u8 reason = status & 0xFF;

	switch (status & 0xFF00) {
	case STAT_NOBEACON:
		switch (status) {
		case STAT_NOBEACON:
			airo_print_dbg(devname, "link lost (missed beacons)");
			break;
		case STAT_MAXRETRIES:
		case STAT_MAXARL:
			airo_print_dbg(devname, "link lost (max retries)");
			break;
		case STAT_FORCELOSS:
			airo_print_dbg(devname, "link lost (local choice)");
			break;
		case STAT_TSFSYNC:
			airo_print_dbg(devname, "link lost (TSF sync lost)");
			break;
		default:
			airo_print_dbg(devname, "unknow status %x\n", status);
			break;
		}
		break;
	case STAT_DEAUTH:
		airo_print_dbg(devname, "deauthenticated (reason: %d)", reason);
		break;
	case STAT_DISASSOC:
		airo_print_dbg(devname, "disassociated (reason: %d)", reason);
		break;
	case STAT_ASSOC_FAIL:
		airo_print_dbg(devname, "association failed (reason: %d)",
			       reason);
		break;
	case STAT_AUTH_FAIL:
		airo_print_dbg(devname, "authentication failed (reason: %d)",
			       reason);
		break;
	case STAT_ASSOC:
	case STAT_REASSOC:
		break;
	default:
		airo_print_dbg(devname, "unknow status %x\n", status);
		break;
	}
}
