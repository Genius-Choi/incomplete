void snd_usb_mixer_notify_id(struct usb_mixer_interface *mixer, int unitid)
{
	struct usb_mixer_elem_list *list;

	for (list = mixer->id_elems[unitid]; list; list = list->next_id_elem)
		snd_ctl_notify(mixer->chip->card, SNDRV_CTL_EVENT_MASK_VALUE,
			       &list->kctl->id);
}
