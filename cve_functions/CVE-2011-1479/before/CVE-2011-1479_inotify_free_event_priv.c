void inotify_free_event_priv(struct fsnotify_event_private_data *fsn_event_priv)
{
	struct inotify_event_private_data *event_priv;


	event_priv = container_of(fsn_event_priv, struct inotify_event_private_data,
				  fsnotify_event_priv_data);

	kmem_cache_free(event_priv_cachep, event_priv);
}
