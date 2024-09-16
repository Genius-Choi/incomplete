static TEE_Result tee_svc_cryp_get_state(struct tee_ta_session *sess,
					 uint32_t state_id,
					 struct tee_cryp_state **state)
{
	struct tee_cryp_state *s;
	struct user_ta_ctx *utc = to_user_ta_ctx(sess->ctx);

	TAILQ_FOREACH(s, &utc->cryp_states, link) {
		if (state_id == (vaddr_t)s) {
			*state = s;
			return TEE_SUCCESS;
		}
	}
	return TEE_ERROR_BAD_PARAMETERS;
}
