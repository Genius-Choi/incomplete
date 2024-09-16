Status MirrorPadKnown(InferenceContext* c, ShapeHandle input,
                      const Tensor* paddings_t, int64_t input_rank) {
  auto paddings_data = paddings_t->matrix<T>();
  std::vector<DimensionHandle> dims(input_rank);
  for (int64_t i = 0; i < input_rank; ++i) {
    const int64_t pad0 = static_cast<int64_t>(paddings_data(i, 0));
    const int64_t pad1 = static_cast<int64_t>(paddings_data(i, 1));
    if (pad0 < 0 || pad1 < 0) {
      return errors::InvalidArgument("Paddings must be non-negative");
    }

    TF_RETURN_IF_ERROR(c->Subtract(c->Dim(input, i), pad0 + pad1, &dims[i]));
  }
  c->set_output(0, c->MakeShape(dims));
  return Status::OK();
}
