static void record_recent_commit(struct commit *commit, void *data)
{
	sha1_array_append(&recent_objects, commit->object.oid.hash);
}
