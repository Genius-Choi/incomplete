snd_compr_set_params(struct snd_compr_stream *stream, unsigned long arg)
{
	struct snd_compr_params *params;
	int retval;

	if (stream->runtime->state == SNDRV_PCM_STATE_OPEN) {
		/*
		 * we should allow parameter change only when stream has been
		 * opened not in other cases
		 */
		params = kmalloc(sizeof(*params), GFP_KERNEL);
		if (!params)
			return -ENOMEM;
		if (copy_from_user(params, (void __user *)arg, sizeof(*params))) {
			retval = -EFAULT;
			goto out;
		}

		retval = snd_compress_check_input(params);
		if (retval)
			goto out;

		retval = snd_compr_allocate_buffer(stream, params);
		if (retval) {
			retval = -ENOMEM;
			goto out;
		}

		retval = stream->ops->set_params(stream, params);
		if (retval)
			goto out;

		stream->metadata_set = false;
		stream->next_track = false;

		if (stream->direction == SND_COMPRESS_PLAYBACK)
			stream->runtime->state = SNDRV_PCM_STATE_SETUP;
		else
			stream->runtime->state = SNDRV_PCM_STATE_PREPARED;
	} else {
		return -EPERM;
	}
out:
	kfree(params);
	return retval;
}
