int add_unseen_recent_objects_to_traversal(struct rev_info *revs,
					   unsigned long timestamp)
{
	struct recent_data data;
	int r;

	data.revs = revs;
	data.timestamp = timestamp;

	r = for_each_loose_object(add_recent_loose, &data,
				  FOR_EACH_OBJECT_LOCAL_ONLY);
	if (r)
		return r;
	return for_each_packed_object(add_recent_packed, &data,
				      FOR_EACH_OBJECT_LOCAL_ONLY);
}
