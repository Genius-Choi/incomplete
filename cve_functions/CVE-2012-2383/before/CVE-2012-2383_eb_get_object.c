eb_get_object(struct eb_objects *eb, unsigned long handle)
{
	struct hlist_head *head;
	struct hlist_node *node;
	struct drm_i915_gem_object *obj;

	head = &eb->buckets[handle & eb->and];
	hlist_for_each(node, head) {
		obj = hlist_entry(node, struct drm_i915_gem_object, exec_node);
		if (obj->exec_handle == handle)
			return obj;
	}

	return NULL;
}
