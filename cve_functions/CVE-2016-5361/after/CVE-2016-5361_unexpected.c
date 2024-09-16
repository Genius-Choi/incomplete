static stf_status unexpected(struct msg_digest *md)
{
	loglog(RC_LOG_SERIOUS, "unexpected message received in state %s",
	       enum_name(&state_names, md->st->st_state));
	return STF_IGNORE;
}
