static void get_key_callback(void *c, struct key_params *params)
{
	struct nlattr *key;
	struct get_key_cookie *cookie = c;

	if (params->key)
		NLA_PUT(cookie->msg, NL80211_ATTR_KEY_DATA,
			params->key_len, params->key);

	if (params->seq)
		NLA_PUT(cookie->msg, NL80211_ATTR_KEY_SEQ,
			params->seq_len, params->seq);

	if (params->cipher)
		NLA_PUT_U32(cookie->msg, NL80211_ATTR_KEY_CIPHER,
			    params->cipher);

	key = nla_nest_start(cookie->msg, NL80211_ATTR_KEY);
	if (!key)
		goto nla_put_failure;

	if (params->key)
		NLA_PUT(cookie->msg, NL80211_KEY_DATA,
			params->key_len, params->key);

	if (params->seq)
		NLA_PUT(cookie->msg, NL80211_KEY_SEQ,
			params->seq_len, params->seq);

	if (params->cipher)
		NLA_PUT_U32(cookie->msg, NL80211_KEY_CIPHER,
			    params->cipher);

	NLA_PUT_U8(cookie->msg, NL80211_ATTR_KEY_IDX, cookie->idx);

	nla_nest_end(cookie->msg, key);

	return;
 nla_put_failure:
	cookie->error = 1;
}
