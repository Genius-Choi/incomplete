static bool check_client_passwd(PgSocket *client, const char *passwd)
{
	char md5[MD5_PASSWD_LEN + 1];
	PgUser *user = client->auth_user;
	int auth_type = client->client_auth_type;

	/* disallow empty passwords */
	if (!*passwd || !*user->passwd)
		return false;

	switch (auth_type) {
	case AUTH_PLAIN:
		return strcmp(user->passwd, passwd) == 0;
	case AUTH_MD5:
		if (strlen(passwd) != MD5_PASSWD_LEN)
			return false;
		if (!isMD5(user->passwd))
			pg_md5_encrypt(user->passwd, user->name, strlen(user->name), user->passwd);
		pg_md5_encrypt(user->passwd + 3, (char *)client->tmp_login_salt, 4, md5);
		return strcmp(md5, passwd) == 0;
	}
	return false;
}
