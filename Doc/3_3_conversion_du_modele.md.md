



# 3.3 - Conversion du modèle


TODO



# 3.4 - Déploiement et tests


TODO






### Entrainement du modèle sur Google Colab


Mon Google Colab ( sur mon drive ): 
https://colab.research.google.com/drive/12KGsKCOmMf-tXJuz5a4KUEhlx-oW8yZv#scrollTo=A2VZRmI8cRbh

Le document Colab doit se connecter à un environnement d'execution avec GPU 

Todo : différent environnement !

il est possible de ce type d'environnement ne soit pas disponible à cause de limitation d'utilisation de Colab.
il est également possible du subir des déconnections qui engendrons la perte de son travail  .... 

imaginez !  vous lancez le traitement principal d’entraînement de votre nouveau modèle d'IA ... celui ci dure plusieurs heures et vous êtes donc parti faire un tour ...  
tous s'est bien passé !  nickel ! mais là , à la fin du traitement l'environnement d'execution ne détecte plus d'activité et déconnecte la session en cours !!!  
... il sera alors très probable de ne plus retrouver son travail lors de la reconnexion !    


La version payante permet de garantir une disponibilité des GPU dans le cloud Google. 

Mais une autre solution consiste à se connecter à un environnement d’exécution local . 
Pour cela , Google proposes une image docker très simple à mettre en œuvre :
les étapes : 

	- Installation de Docker sur son poste 
	
	--shm-size
	
	The Docker container’s shared memory (shm-size) can be modified to suit our application’s requirements. By default, the shm-size is set to 64 MB, but we can change it to a different value as needed.
	
	
	
	- $ docker run --gpus=all -p 127.0.0.1:9000:8080 --shm-size=2gb  europe-docker.pkg.dev/colab-images/public/runtime
	
	- puis dans le document Colab --> "connexion à un environnement d’exécution local" 

		"http://127.0.0.1:9000/?token=…
http://127.0.0.1:9000/?token=05f804ed9df704084e2081ba86881ad50d6358cc220cbd9e

---



python3 -m venv --system-site-packages venv
source venv/bin/activate


pip install ultralytics==8.0.196
pip install roboflow



>>> import ultralytics
>>> ultralytics.checks()

Ultralytics YOLOv8.0.196 🚀 Python-3.10.12 torch-2.6.0+cu124 CUDA:0 (NVIDIA GeForce GTX 1060 6GB, 6063MiB)
Setup complete ✅ (8 CPUs, 39.1 GB RAM, 58.4/91.1 GB disk)
>>> 

from roboflow import Roboflow
rf = Roboflow(api_key="xxxxxxxxxxxxxxxxxxxxxx")
project = rf.workspace("fred-robotic").project("210125_4_shapes_test")
version = project.version(2)
dataset = version.download("yolov8")



yolo task=detect mode=train model=yolov8s.pt data=/content/210125_4_shapes_TEST-2/data.yaml epochs=1 batch=8 imgsz=640 plots=True



## 3.3 - Conversion du modèle

Le plus simple est de faire sous linux 

	# pour DFC de Hailo 

	https://hailo.ai/developer-zone/documentation/hailo-sw-suite-2025-01/
	https://hailo.ai/developer-zone/software-downloads/


	
	$ unzip hailo_ai_sw_suite_2025-01_docker.zip



Modification du script 
	
	ligne 226
        -v $(pwd)/${SHARED_DIR}/:/local/${SHARED_DIR}:rw \
		-v /data_1/:/local/${SHARED_DIR}:rw \

	ligne 352 
		# create_shared_dir



```bash





	$ ./hailo_ai_sw_suite_docker_run.sh
	
	
	plusieurs giga de dépendances lors du premier lancement 
	
Loading Docker image: /home/fredj21/FRED/hailo_ai_sw_suite_2025-01.tar.gz
INFO: Checking system requirements...
INFO: System requirements check finished successfully.
5baeb41057c7: Loading layer [==================================================>]  976.4MB/976.4MB
c361101a082c: Loading layer [==================================================>]   83.5MB/83.5MB
593a1325c5ed: Loading layer [==================================================>]  12.99MB/12.99MB
69b082334a83: Loading layer [==================================================>]  9.197MB/9.197MB
b2e1817da5c2: Loading layer [==================================================>]    384MB/384MB
71cf924c7ef0: Loading layer [==================================================>]  18.03MB/18.03MB
21f476235018: Loading layer [==================================================>]  3.072kB/3.072kB
11c4c6ec7d5d: Loading layer [==================================================>]  3.072kB/3.072kB
4b7ec45684e6: Loading layer [==================================================>]  3.072kB/3.072kB
9661444da425: Loading layer [==================================================>]  194.9MB/194.9MB
bba85803bb3e: Loading layer [==================================================>]  3.284GB/3.284GB
64951b6189b1: Loading layer [==================================================>]  485.1MB/485.1MB
92b2d02a49ee: Loading layer [==================================================>]  2.184GB/2.184GB
88eb41c2be66: Loading layer [==================================================>]  5.324GB/5.324GB
b3d3a14740d8: Loading layer [==================================================>]  895.5kB/895.5kB
2053f733bc05: Loading layer [==================================================>]  192.6MB/192.6MB
5f70bf18a086: Loading layer [==================================================>]  1.024kB/1.024kB
Loaded image: hailo_ai_sw_suite_2025-01:1	
	
	
		
	
	# autres options  :

		./hailo_ai_sw_suite_docker_run.sh
		./hailo_ai_sw_suite_docker_run.sh --help
		./hailo_ai_sw_suite_docker_run.sh --resume
		./hailo_ai_sw_suite_docker_run.sh --override


	Dans le docker Hailo :
	
		Welcome to Hailo AI Software Suite Container
		To list available commands, please type:	

		----------------------------------------------------

		HailoRT:                hailortcli -h
		Dataflow Compiler:      hailo -h
		Hailo Model Zoo:        hailomz -h
		TAPPAS:                 hailo_run_app -h

		----------------------------------------------------
	
	$ pip list | grep hailo
		hailo-dataflow-compiler      3.30.0
		hailo-model-zoo              2.14.0      /local/workspace/hailo_model_zoo
		hailo-tappas-dot-visualizer  3.31.0      /local/workspace/tappas/tools/trace_analyzer/dot_visualizer
		hailo-tappas-run-apps        3.31.0      /local/workspace/tappas/tools/run_app
		hailort                      4.20.0

	
	
		hailo -h
		
	Répertoire mappé avec le docker Hailo : 
			sour linux hote                                 Docker Hailo   
			/home.fredj21/FRED/shared_with_docker    -->    /local/shared_with_docker/



	je vais donc dans le répertoire de partage dans lequel un repertoire de travail , avec la date du jour, contient mon fichier onnx et les images de test de mon dataset 
	
	cp RPI5_AI_Hailo_tests/Results/20250125_result_from_210125_4_shapes_TEST.v3i.yolov8/weights/best.onnx shared_with_docker
	cp -rv RPI5_AI_Hailo_tests/Dataset/210125_4_shapes_TEST.v3i.yolov8/test   shared_with_docker
	cp -rv RPI5_AI_Hailo_tests/Dataset/210125_4_shapes_TEST.v3i.yolov8/valid  shared_with_docker
	cp -rv RPI5_AI_Hailo_tests/Dataset/210125_4_shapes_TEST.v3i.yolov8/train  shared_with_docker
	
	
	$ ./hailo_ai_sw_suite_docker_run.sh --resume
	$ cd /local/shared_with_docker
	$ sudo chown -R hailo:ht  
	$ cd 20250126 
	
	
	
	
	Architecture hailo8 ou hailo8l   !!! 
	
	
	$ hailomz compile yolov8s --ckpt=best.onnx --hw-arch hailo8 --calib-path test/images/ --classes 4 --performance


	cd /local/shared_with_docker/
	hailomz compile yolov8s --ckpt=my_yolo8s/train/weights/best.onnx --hw-arch hailo8 --calib-path my_dataset/test/images/ --classes 4 --performance



	TODO : 
		- tester avec les images de calibration du dataset
		- compiler pour hailo8l 	

	
	
	
	
	



---

## 3.4 - Déploiement et tests


	dans :
	~/FRED/GIT_RPI5_AI_Hailo_tests/Results/20250125_result_from_210125_4_shapes_TEST.v3i.yolov8/weights/Hailo_Compile
	
	Nous créons un fichier de définition des étiquettes : 
	
	my-labels.json


{
    "detection_threshold": 0.5,
    "max_boxes":200,
    "labels": [
      "unlabeled",
      "hexagon",
      "round",
	  "square",
	  "triangle"
    ]
}






on reprend le test plus haut  : 

	$ cd hailo-rpi5-examples
	$ source setup_env.sh

	
	mais, au lieu de lancer cette commande : 
	$ python basic_pipelines/detection.py
	
	
	nous spécifier le chemin vers notre IA et le fichiers de définition des étiquettes 
	dans mon cas :
	
	MY_HEF=/home/pi/FRED/GIT_RPI5_AI_Hailo_tests/Results/20250125_result_from_210125_4_shapes_TEST.v3i.yolov8/weights/Hailo_Compile/yolov8s.hef
	MY_LABELS=/home/pi/FRED/GIT_RPI5_AI_Hailo_tests/Results/20250125_result_from_210125_4_shapes_TEST.v3i.yolov8/weights/Hailo_Compile/my-labels.json
	
	
	python3 basic_pipelines/detection.py --hef-path $MY_HEF --labels-json $MY_LABELS --input rpi --camera 0
	



---
---
---


##
Documentation officielle Raspberry PI :
https://www.raspberrypi.com/documentation/computers/ai.html

##

Généralement, nous n'avons pas besoin de former son propre IA, car il existe une large gamme de modèle prè-formés pour les la gammes des accélérateurs Hailo : 

https://github.com/hailo-ai/hailo_model_zoo/tree/master/docs/public_models/HAILO8L
https://github.com/hailo-ai/hailo_model_zoo/tree/master/docs/public_models/HAILO8


