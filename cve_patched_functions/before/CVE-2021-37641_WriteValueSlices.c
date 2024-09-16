void WriteValueSlices(
    const Tensor& params_dense_values_in,
    const std::vector<std::pair<SPLITS_TYPE, SPLITS_TYPE>>& value_slices,
    SPLITS_TYPE value_size, Tensor* values_out) {
  const auto& params_dense_values =
      params_dense_values_in.flat_outer_dims<VALUE_TYPE, 2>();
  auto values = values_out->flat_outer_dims<VALUE_TYPE, 2>();
  int out_pos = 0;
  for (const auto& slice : value_slices) {
    for (int i = slice.first; i < slice.second; ++i) {
      for (int j = 0; j < value_size; ++j) {
        values(out_pos, j) = params_dense_values(i, j);
      }
      ++out_pos;
    }
  }
}
