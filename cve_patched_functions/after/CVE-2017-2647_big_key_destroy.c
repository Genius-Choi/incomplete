void big_key_destroy(struct key *key)
{
	if (key->type_data.x[1] > BIG_KEY_FILE_THRESHOLD) {
		struct path *path = (struct path *)&key->payload.data2;
		path_put(path);
		path->mnt = NULL;
		path->dentry = NULL;
	} else {
		kfree(key->payload.data);
		key->payload.data = NULL;
	}
}
