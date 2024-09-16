process_init(void)
{
	struct sshbuf *msg;
	int r;

	if ((r = sshbuf_get_u32(iqueue, &version)) != 0)
		fatal("%s: buffer error: %s", __func__, ssh_err(r));
	verbose("received client version %u", version);
	if ((msg = sshbuf_new()) == NULL)
		fatal("%s: sshbuf_new failed", __func__);
	if ((r = sshbuf_put_u8(msg, SSH2_FXP_VERSION)) != 0 ||
	    (r = sshbuf_put_u32(msg, SSH2_FILEXFER_VERSION)) != 0 ||
	    /* POSIX rename extension */
	    (r = sshbuf_put_cstring(msg, "posix-rename@openssh.com")) != 0 ||
	    (r = sshbuf_put_cstring(msg, "1")) != 0 || /* version */
	    /* statvfs extension */
	    (r = sshbuf_put_cstring(msg, "statvfs@openssh.com")) != 0 ||
	    (r = sshbuf_put_cstring(msg, "2")) != 0 || /* version */
	    /* fstatvfs extension */
	    (r = sshbuf_put_cstring(msg, "fstatvfs@openssh.com")) != 0 ||
	    (r = sshbuf_put_cstring(msg, "2")) != 0 || /* version */
	    /* hardlink extension */
	    (r = sshbuf_put_cstring(msg, "hardlink@openssh.com")) != 0 ||
	    (r = sshbuf_put_cstring(msg, "1")) != 0 || /* version */
	    /* fsync extension */
	    (r = sshbuf_put_cstring(msg, "fsync@openssh.com")) != 0 ||
	    (r = sshbuf_put_cstring(msg, "1")) != 0) /* version */
		fatal("%s: buffer error: %s", __func__, ssh_err(r));
	send_msg(msg);
	sshbuf_free(msg);
}
