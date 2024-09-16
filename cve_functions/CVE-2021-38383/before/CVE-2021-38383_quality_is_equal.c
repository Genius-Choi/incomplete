quality_is_equal(struct media_quality *a, struct media_quality *b)
{
  return (a->sample_rate == b->sample_rate && a->bits_per_sample == b->bits_per_sample && a->channels == b->channels && a->bit_rate == b->bit_rate);
}
