


# Test 25Jan2025
MY_REP=/home/pi/FRED/RPI5_AI_Hailo_tests/Results/20250125_result_from_210125_4_shapes_TEST.v3i.yolov8/weights/Hailo_Compile
MY_LAB=my_labels.json
MY_HEF=yolov8s.hef


# Test 03Fev2025
#MY_REP=/home/pi/FRED/RPI5_AI_Hailo_tests/Results/20250203_result_from_210125_4_shapes_test_v2
#MY_LAB=my_labels.json
#MY_HEF=hailo_result_1/yolov8s_with_test_img.hef
#MY_HEF=hailo_result_2/yolov8s_with_valid_img.hef
#MY_HEF=hailo_result_3/yolov8s_with_train_img.hef


cd  /home/pi/FRED/hailo-rpi5-examples
source setup_env.sh

python3 basic_pipelines/detection.py \
	--hef-path ${MY_REP}/${MY_HEF} \
	--labels-json ${MY_REP}/${MY_LAB} \
	--input rpi

