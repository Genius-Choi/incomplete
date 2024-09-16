Status AutoParallel::Optimize(Cluster* cluster, const GrapplerItem& item,
                              GraphDef* output) {
  TF_RETURN_IF_ERROR(Initialize(item));
  BuildGraph(output);
  return Status::OK();
}
