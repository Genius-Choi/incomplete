static void AddRangeStats(const int start_instance, const int end_instance,
                          const int start_feature_dim,
                          const int end_feature_dim,
                          StatsPartitionMap* stats_map,
                          const TTypes<float>::ConstMatrix& gradients,
                          const TTypes<float>::ConstMatrix& hessians,
                          const TTypes<int32>::ConstVec& node_ids,
                          const int32_t feature_dims, const int32_t bucket_id,
                          const int32_t logits_dims, const int32_t stats_dims) {
  DCHECK_LE(start_instance, end_instance);
  if (start_instance == end_instance) {
    DCHECK_LT(start_feature_dim, end_feature_dim);
  }
  for (int32_t instance = start_instance; instance <= end_instance;
       ++instance) {
    const int32_t start_f_dim =
        (instance == start_instance) ? start_feature_dim + 1 : 0;
    const int32_t end_f_dim =
        (instance == end_instance) ? end_feature_dim : feature_dims;
    for (int32_t f_dim = start_f_dim; f_dim < end_f_dim; ++f_dim) {
      AddInstanceStatsToMap(instance, f_dim, bucket_id, logits_dims, stats_dims,
                            stats_map, gradients, hessians, node_ids);
    }
  }
}
