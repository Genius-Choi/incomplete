std::vector<int64_t> GetFlatInt64(const Tensor& t) {
  if (t.dtype() == DT_INT32) {
    return GetFlatInt64<int32>(t);
  } else {
    return GetFlatInt64<int64_t>(t);
  }
}
