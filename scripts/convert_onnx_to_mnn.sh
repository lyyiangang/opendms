onnx_model=models/eye_landmark_detector/model_best.pth.onnx
mnn_model=${onnx_model}.mnn
echo "converting model ${onnx_model} to ${mnn_model}"
/MNN/build/MNNConvert -f ONNX --modelFile ${onnx_model} --MNNModel ${mnn_model} --bizCode opendms