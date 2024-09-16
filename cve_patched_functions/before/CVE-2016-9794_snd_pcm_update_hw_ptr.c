int snd_pcm_update_hw_ptr(struct snd_pcm_substream *substream)
{
	return snd_pcm_update_hw_ptr0(substream, 0);
}
