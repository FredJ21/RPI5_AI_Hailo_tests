
# 3.3 - Conversion du modèle pour le module HAILO

DFC (Dataflow Compiler) est un outil clé du Hailo SDK utilisé pour compiler et optimiser des modèles d’intelligence artificielle (IA) pour les exécuter efficacement sur les accélérateurs Hailo-8.

DFC prend en entrée un modèle d’IA, tel que notre modèle YOLOv8  au format ONNX, et le transforme en un fichier HEF (Hailo Executable Format), qui est un format binaire optimisé pour l’inférence sur les puces HAILO.

Étapes principales du  traitement par le compilateur DFC :

* **Parsing** → Charge le modèle ONNX.
* **Quantization** → Convertit les poids du modèle en entiers 8 bits (INT8) pour accélérer l'inférence.
* **Optimization** → Réorganise le modèle pour minimiser la latence et la consommation mémoire.
* **Compilation en HEF** → Génère un fichier .hef pouvant être exécuté directement sur le module HAILO 8.


Comme pour l'apprentissage, la conversion du modèle est réaliser sur un "Gros" PC sous Linux ! <br>
car cette conversion, ou compilation, demande également beaucoup de ressource Cpu, Gpu, Mémoire<br>


## Installation de DFC 

Le Dataflow Compiler (DFC) fait partie de la suite logiciel proposée par Hailo<br>
Ces suite inclut les outils nécessaires pour compiler, optimiser et exécuter des modèles sur l'accélérateur Hailo-8.<br>
Hailo propose cette suite sous la forme d'un conteneur Docker, ce qui va nous faciliter grandement la tâche !!<br>


Donc, direction :  https://hailo.ai/developer-zone/software-downloads/ <br>
et téléchargement de l'image Docker

<img src="img/hailo_1.png" width="100%"><br>

Décompression du fichier :
```bash
unzip hailo_ai_sw_suite_2025-01_docker.zip

	Archive:  hailo_ai_sw_suite_2025-01_docker.zip
	inflating: hailo_ai_sw_suite_2025-01.tar.gz  
	inflating: hailo_ai_sw_suite_docker_run.sh 

```
Nous voici un script Shell pour la création et le lancement de l'image Docker<br> 

Petit problème : ce script crée un répertoire partagé entre l'image Docker et l'hôte Linux dans le répertoire de l'utilisateur courant.<br>
J'ai donc réalisé quelques modifications pour l'image Docker "monte" mon disque "/data_1" :<br>

```bash
vi hailo_ai_sw_suite_docker_run.sh

	ligne 226 - modification
        avant :		-v $(pwd)/${SHARED_DIR}/:/local/${SHARED_DIR}:rw \
		après :		-v /data_1/:/local/${SHARED_DIR}:rw \

	ligne 352 - mise en commentaire (ajout de #)
		# create_shared_dir

```

Il suffit maintenant de lancer le script :

```bash
./hailo_ai_sw_suite_docker_run.sh
	
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
	
```	

Documentation de la suite Hailo :
https://hailo.ai/developer-zone/documentation/hailo-sw-suite-2025-01/



## Dans le DOCKER HAILO

... après le télécharge de plusieurs Giga de dépendances .... nous voici dans le Docker HAILO

le répertoire *"/local/shared_with_docker"* est bien mappé avec le répertoire de l'hôte Linux *"/data_1"*<br>
Ce qui permet d'avoir accès au Dataset, au modèle que nous avons entraîné, et à la documentation Hailo.<br>

```bash
ls -l /local/shared_with_docker/
	drwxrwxrwx 2 hailo ht   4096 Feb  2 22:33 doc
	drwxr-xr-x 5  1000 1000 4096 Feb  2 16:21 my_dataset
	drwxrwxrwx 8  1000 1000 4096 Feb  3 10:59 my_yolo8s
```

Nous pouvons également vérifier la présence et la version des modules Python/Hailo

```bash
pip list | grep hailo
	hailo-dataflow-compiler      3.30.0
	hailo-model-zoo              2.14.0      /local/workspace/hailo_model_zoo
	hailo-tappas-dot-visualizer  3.31.0      /local/workspace/tappas/tools/trace_analyzer/dot_visualizer
	hailo-tappas-run-apps        3.31.0      /local/workspace/tappas/tools/run_app
	hailort                      4.20.0
```
	

### Compilation

Il temps maintenant de lancer la compilation de notre fichier ONNX en fichier HEF

A noter : 
* l'architecture cible est dépendante type de carte HAILO pour Raspberry PI que nous possédons : **hailo8l** ou **hailo8**
* la calibration peut être réalisée sur les images de test, validation, ou training ( à tester )

```bash
cd /local/shared_with_docker/

	hailomz compile yolov8s --ckpt=my_yolo8s/train/weights/best.onnx --hw-arch hailo8 --calib-path my_dataset/test/images/ --classes 4 --performance

```

Après quelques heures de patience, nous obtenons LE fichier HEF compatible avec le module HAILO 8 du notre Raspberry PI<br>

```bash 
ls *hef 

	yolov8s.hef

```

### Résultats

Vous pouvez retrouver l'ensemble des résultats de cette compilation, log et fichier Hef, sur mon dépôt GitHub :<br>
https://github.com/FredJ21/RPI5_AI_Hailo_tests

```bash
ls -l Results/20250203_result_from_210125_4_shapes_test_v2/hail_result_1

ls -l Results/20250203_result_from_210125_4_shapes_test_v2/hail_result_2

ls -l Results/20250203_result_from_210125_4_shapes_test_v2/hail_result_3

```

Nous pouvons maintenant sortir de notre conteneur Docker HAILO

```bash
exit
```

