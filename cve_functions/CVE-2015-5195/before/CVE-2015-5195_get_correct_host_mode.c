get_correct_host_mode(
	int token
	)
{
	switch (token) {

	case T_Server:
	case T_Pool:
	case T_Manycastclient:
		return MODE_CLIENT;

	case T_Peer:
		return MODE_ACTIVE;

	case T_Broadcast:
		return MODE_BROADCAST;

	default:
		return 0;
	}
}
