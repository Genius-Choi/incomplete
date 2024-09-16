static void AddInstanceStatsToMap(
    const int32_t instance, const int32_t feature_dim, const int32_t bucket_id,
    const int32_t logits_dims, const int32_t stats_dims,
    StatsPartitionMap* stats_map, const TTypes<float>::ConstMatrix& gradients,
    const TTypes<float>::ConstMatrix& hessians,
    const TTypes<int32>::ConstVec& node_ids) {
  const int32_t node_id = node_ids(instance);
  const auto key = StatsPartitionKey(node_id, feature_dim, bucket_id);
  std::pair<StatsPartitionIterator, bool> const& insert_result =
      stats_map->insert(StatsPartitionIterator::value_type(
          key, std::vector<float>(stats_dims, 0.0f)));
  auto& stats = insert_result.first->second;
  for (int stat_dim = 0; stat_dim < logits_dims; ++stat_dim) {
    stats[stat_dim] += gradients(instance, stat_dim);
  }
  for (int stat_dim = logits_dims; stat_dim < stats_dims; ++stat_dim) {
    stats[stat_dim] += hessians(instance, stat_dim - logits_dims);
  }
}
