



MY_HEF=/home/pi/FRED/GIT_RPI5_AI_Hailo_tests/Results/20250125_result_from_210125_4_shapes_TEST.v3i.yolov8/weights/Hailo_Compile/yolov8s.hef

MY_LABELS=/home/pi/FRED/GIT_RPI5_AI_Hailo_tests/Results/20250125_result_from_210125_4_shapes_TEST.v3i.yolov8/weights/Hailo_Compile/my-labels.json


cd  /home/pi/FRED/hailo-rpi5-examples
source setup_env.sh

python3 basic_pipelines/detection.py --hef-path $MY_HEF --labels-json $MY_LABELS --input rpi

