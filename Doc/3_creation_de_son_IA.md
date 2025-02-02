

Après notre petite introduction en partie 1 et la configuration du Raspberry PI en parti 2,<br>
Il est temps de rentrer dans le vif du sujet  !!!<br>

# Partie 3 -"Créer et entrainer son propre IA pour les modules HAILO du Raspberry PI5"

L'objectif est donc de :

* créer une IA de reconnaissance de formes simples
* sur la base de ses propres photos ( ou vidéos )
* et qui puisse exploiter la puissance d'un module IA d'un Raspberry PI5


Nous pouvons distinguer 4 grandes étapes décrites plus bas : 

1. --> la création de son jeu de données, de son dataset
2. --> l'entrainement du modèle IA
3. --> la conversion, ou compilation, du modèle
4. --> le déploiment et les tests    



_Archive du projet :_<br>
où l'on peut retrouver les images et vidéos sources, ainsi que quelques scripts<br>
https://github.com/FredJ21/RPI5_AI_Hailo_tests


---

## 3.1 - Création de son jeu de donnée

Pour la création du Dataset, plusieurs méthodes se présentent à nous : 
 
1. Tout réaliser en local à l'aide d'outils spécifiques et/ou scripts Python 
2. Utiliser une platforme spécialisée, en ligne, dans le cloud 

J'ai commencé, dans un premier temps, par réaliser mon jeu de donnée en local,<br>
pour ensuite réaliser des versions plus complexes et certainenement éfficaces sur *Roboflow*,
une platreforme particulière interressante pour notre besoin.<br>
Je vais donc décrire ces deux approches.


La création du dataset consiste à créer une collection d'images représentatives des objets que l'on souhaite détecter.<br> 
Ces images devront être annotés avec l'emplacement et le nom de l'objet visible.<br>

#### Mais il y a quelques éléménets à prendre en considération :

* le format du dataset : YOLOv8

YOLOv8 (You Only Look Once v8) est une version avancée de la célèbre famille de modèles YOLO 
utilisée pour la détection d’objets, la segmentation d’images et la classification. 

YOLOv8 est principalement un modèle d'IA de détection d'objets qui utilise un format spécifique pour les datasets.<br>
Ce modèle d'IA est particulièrement adapté et préconiser pour le module HAILO du Raspberry PI.


#### Autres éléments importants :

- YOLOv8, comme ses prédécesseurs, fonctionne mieux avec des images carrées.
- les images doivent avoir une dimention de 640x640 pixels (par défaut pour YOLOv8) 
   --> Un bon compromis entre précision et performance. 

- l'arboressence des répertoires 
- le format des fichiers d'annotation 
- le nombre de classes
- le nommage des classes ( ex: "carré vert", "rond rouge", triange "jaune", .... )


Voici un exemple d'oraganisation du dataset au format YOLOv8 :

```
	Mon_Dataset/
	├── data.yaml
	├── test
	│   ├── images
	│   └── labels
	├── train
	│   ├── images
	│   └── labels
	└── valid
		├── images
		└── labels
```

On y trouve : 

- le fichier *"data.yaml"* qui contient la liste des sous répertoires, le nombre et le nom des classes
- 3 répertoires : *"train", "valid", "test"*
- contenant chacun 2 sous répertoires : *"images" et "labels"* 

Le fichier label, au format texte (.txt) est donc stocké dans un répertoir différent de l'image correspondante,<br>
mais le lien entre ces deux fichiers est fait par leur nom ( mon_image_12345.jpg --> mon_image_12345.txt )

Enfin, les données doivent être répartis celon un certain ratio : 

* 70 % pour le trainning --> rep *"train"*
* 15 % pour la validation --> rep *"valid"*
* 15 % pour les tests --> rep *"test"*

Nous pourions également evisager un repartition de 70/20/10 , ou 75/15/10 .... à tester ...

---

### 3.1.1 Création du Dataset en local 

J'ai réalisé de nombreux tests de création de dataset, avec 12 objets différents (12 classes),
différents fonds, plusieurs type d'éclairage ...  mais ca commencait à se compiquer un peu ... 
surtout quand le résultat attendu n'était pas vraiment au rendez vous .... 

J'ai donc réduit la voilure avec Dataset est composé de 2 classes  :  "carré vert"  & "carré rouge"<br>


Les fichiers sources, de mon derniers tests, son disponibles dans mon repo GitHub :

```
	https://github.com/FredJ21/RPI5_AI_Hailo_tests
	
	$ git clone https://github.com/FredJ21/RPI5_AI_Hailo_tests
	$ cd RPI5_AI_Hailo_tests
	$ ls -al Dataset/Fred_Dataset/images_HD_2
```

----

#### Les photos :

J'ai donc fait plein de photos de mes pièces en vaillant, bien évidement, à réaliser autant de photos pour chacune d'entre elle : 

- 75 photos pour le trainning  dans le repertoire *"train"* (*)
- 15 photos pour la validation dans le repertoire *"valid"* (*)
- 15 photos pour les tests dans le repertoire *"test"* (*)

**( pour chaque classe d'objet !!! )*

Pour réaliser ces photos, c'est très simple !  il suffit d'utiliser la camera du Raspberry PI ! <br>
Avec la commande suivante : 

```bash
rpicam-jpeg  --camera ${CAMERA} --output ${FILE} --timeout ${TIMEOUT} --autofocus-mode manual --lens-position 0.0
```
Cela produit une image haute définition de 4608x2592 pixels et d'environ 3,3 Mo.

<a href="photos/1734219226.jpg"><img src="photos/1734219226.jpg" width="49%"></a>
<a href="photos/1734220832.jpg"><img src="photos/1734220832.jpg" width="49%"></a>
<a href="photos/1734220572.jpg"><img src="photos/1734220572.jpg" width="49%"></a>
<a href="photos/1734219623.jpg"><img src="photos/1734219623.jpg" width="49%"></a>

Le script **"prendre_une_photo.sh"** ( dans le répertoire [GIT]Scripts/bin ) permet d'automatiser la séance !<br>
en premant une photo toutes les 2 secondes et en répartissant les clichés des les repertoires : train, valid, et test.<br>
Le nom des fichiers correspond à un horodatage de type timestamp. 

```bash
$ ls -al Dataset/Fred_Dataset/images_HD_2/test/*jpg
-rw-r--r-- 1 pi pi 2994083 15 déc.  00:47 Dataset/Fred_Dataset/images_HD_2/test/1734220016.jpg
-rw-r--r-- 1 pi pi 3009538 15 déc.  00:47 Dataset/Fred_Dataset/images_HD_2/test/1734220032.jpg
-rw-r--r-- 1 pi pi 3367522 15 déc.  00:47 Dataset/Fred_Dataset/images_HD_2/test/1734220038.jpg
-rw-r--r-- 1 pi pi 3281630 15 déc.  00:47 Dataset/Fred_Dataset/images_HD_2/test/1734220046.jpg
-rw-r--r-- 1 pi pi 3273484 15 déc.  00:47 Dataset/Fred_Dataset/images_HD_2/test/1734220051.jpg
../..
```

----

#### Les labels :

Il est temps maintenant d'annoter les images.<br>

Cette opération d'étiquetage consiste à dessiner un cadre de délimitation autour des objets présents sur les photos, tout en précisant sa classe ( "carré vert" ou "carré rouge" ) ?<br>

Cette opération nécessite une certaine précision et un peu de patience !!!<br>
Le cadres doit etre serré mais pas trop proche.<br>
Il ne doit pas y avoir de surajustement dans le cas ou plusieurs objets sont présents sur la même photo.<br>
*( mais par soucis de simplification, mes images ne comportent q'un seul objet )*

Dans mon cas, j'ai choisi de réaliser des photos distinctes par type d'objet. J'ai donc qu'un seul objet par photo. 

Je souhaitais également réaliser cette opération complètement en local, sur mon Raspberry PI5, à l'aide d'un utilistaire très léger.<br>
J'ai utilisé **"YOLO-Label"** que l'on peut trouver ici : https://github.com/developer0hye/Yolo_Label

"YOLO-Label" est également dispo dans une verions pré-compilé pour le Raspberry PI 64bits (version Debian/PiOS 12 bookworm) sur mon GIT :  

```bash
cd RPI5_AI_Hailo_tests//Scripts/bin/Yolo_Label/
chmod +x YoloLabel
./YoloLabel
```

<img src="img/47698872-5bc80980-dc54-11e8-8984-e3e1230eccaf.gif">

*(annimation d'exemple du site officiel)*


L'utilisation est très simple et doit être réalisé sur l'ensemble des photos de DataSet.<br>
- on sélectionne le répertoire de travail qui contien les images
- on selectionne la liste des classes ( *labels_list.txt* )
- on choisi une classe 
- on dessinne en carré pour délimiter notre pièce 
- next ... 

<img src="photos/Capture_YoloLabel_1.png" width="49%"></a>
<img src="photos/Capture_YoloLabel_2.png" width="49%"></a>

Tous les fichiers jpeg sont maintenant accompagnés par un fichier text du même nom mais avec l'extention .txt .   

	1734219226.jpg	-->  1734219226.txt
	1734220832.jpg  -->  1734220832.txt
	1734220572.jpg  -->  1734220572.txt
	1734219623.jpg  -->  1734219623.txt

Ces fichiers contiennent 5 valeurs numérique :

```bash
$ cat train/1734219226.txt 

1 0.637242 0.526384 0.053579 0.094291
```

* l'index de la classe d'objet (0->carré route, 1->carré vert) et les 
* la position en X du centre de l’objet
* la position en Y du centre de l’objet
* la largeur de l’objet 
* la hauteur de l’objet

Les coordonnées sont normalisées de 0 à 1

----

####  Augementation du nombre d'image

Nous avons donc, pour l'ensemble de nos objets : 
- 150 photos d'entrainement, 
- 30 photos de validation, 
- 30 photos de test,
- les photos sont au format .jpg et d'une dimention de 4608x2592 pixels,
- chaque photo est acompagné de son fichier lablel au format .txt


Il maintenant necessaire de redimentionner les photos au format 640x640 pixels (pour YOLOv8),<br>
de plus, il est interressant d'**augmenter artifitiellement** le nombre de photos !!<br>
En effet l'entrainenement de l'IA sur un plus grand nombre de photos permettra d'obtenir de meilleurs résultats 


Plusieurs solutions permettent d'augmenter le nombre de photos : 

* **recadrer** l'image par rapport à l'objet en positionnant l'objet plus ou mois sur la droite ou plus ou mois sur la gauche <br>
--> cette opération permet de passer d'un format de 4608x2592 pixels  à un format carré de 640x640 pixels
* réaliser une ou plusieurs **rotation** d'image
* ajouter artificièlement du **bruit** ( des points blancs ou noirs )
* réaliser plusieurs **itérations** par image source


J'ai dévoloppé un script Python pour réaliser cela  :

```bash 
	$ cd RPI5_AI_Hailo_tests/Scripts/
	
	$ python3 -m venv --system-site-packages venv
	$ source venv/bin/activate
	$ pip install -r requirements.txt

	$ cd bin

	$ cat dataset_HD_to_640x640.conf

		{
    		"REP_IN"  : "../../Dataset/Fred_Dataset/images_HD_2",
    		"REP_OUT" : "/home/pi/My_Dataset/",
    		"IMG_FILE_EXT"   : ".jpg",
    		"LABEL_FILE_EXT" : ".txt",
    		"Nb_Iteration_par_image" : 15,
    		"Add_Noise" : 1,
    		"Retournement" : 3
		}
```

Le fichier de configuration défini les répertoires source et destination, le nombre de bruit, le nombre de retournent d'image<br>
Le script se chargera également de recalculer la nouvelle position, en x et y, de l'objet et ses dimentions afin de produire un nouveau fichier label.<br>    
Le répertoire cibe (REP_OUT) n'est pas obligé d'exister, le script se chargera de créer toute l'arboressance de répertoires.

*GO !!!* 


```bash 

	$ python dataset_HD_to_640x640.py

```

Puisque nous avons réaliseé 15 itérations, pour lesquels nous avons une version avec et sans bruit, et 3 retournents en plus de la position de départ    

- 150 * 15 * 2 * 4 --> 18000 photos le repertoire *"train"* 
- 30 * 15 * 2 * 4 --> 3600 photos dans le repertoire *"valid"* 
- 30 * 15 * 2 * 4 --> 3600 photos dans le repertoire *"test"*

cd qui donne un total de 25200 photos accompagnées de leurs annotations !<br>
en effet : 

```bash
	$ find /home/pi/My_Dataset -name *jpg | wc -l

	25200
```
<img src="photos/Capture_YoloLabel_4.png" ></a>

Notre Dataset en prêt à être utilisé pour l'aprentissage  !!! 

---


### 3.1.2 Création du Dataset sur Roboflow

Une autre solution pour réaliser son dataset et l'annotation de ses images, est d'utiliser un outil en ligne.<br>

**Roboflow** ( https://roboflow.com/ ) est une plateforme tout-en-un qui facilite la gestion, l'annotation, l'augmentation et l'exportation de datasets pour l'entraînement de modèles de vision par ordinateur. Elle est particulièrement utile pour des modèles comme YOLOv8, Faster R-CNN, SSD, et d'autres.

On peut identifier plusieurs fonctionnalités très intéressantes :  

* Annotation d’images : Interface web collaborative pour annoter rapidement les objets.
* Augmentation des données : Ajout automatique de variations (rotation, flou, contraste, etc.) pour améliorer la robustesse du modèle.
* Conversion de formats : Compatible avec YOLO, COCO, Pascal VOC, et d'autres standards.
* Hébergement & API : Stocke et gère les datasets, avec accès via API pour automatiser les workflows.
* Entraînement et déploiement : Intégration avec des frameworks d'IA (PyTorch, TensorFlow) et déploiement dans le cloud ou en edge computing.



Une dès première fonctionnalité très interressante :  

* **Roboflow permet d'extraire une série de photos depuis une vidéo !!!**

#### Nouveau Dataset :

Cette fois ci, pour ce nouveau Dataset, j'ai choisi un nouvel énoncé de départ :

* un Dataset avec 4 classes : round, square, triangle, hexagon
* les 4 objets sont de couleur identique ( vert )
* les images sont extraites de 4 vidéos distinctes
* chaque vidéo dure exactement de 20 secondes 


Pour réaliser les vidés, c'est très simple !  il suffit d'utiliser la camera du Raspberry PI ! <br>
Avec la commande suivante : 

```bash
	rpicam-vid --camera 0 -t20000 --autofocus-range normal --autofocus-speed fast -o square.mp4
```

Nous pouvons bien évidement ajuster les parametres d'autofocus et autres ... 

Ces vidéos de départ sont dans le répertoire :  *Dataset/210125_4_shapes_TEST.sources* du dépo Git :

```bash
	$ ls -al Dataset/210125_4_shapes_TEST.sources/
		total 19516
		-rw-rw-r-- 1 fredj21 fredj21 4881188 janv. 29 13:37 hexagon.mp4
		-rw-rw-r-- 1 fredj21 fredj21 4985373 janv. 29 13:37 round.mp4
		-rw-rw-r-- 1 fredj21 fredj21 4848499 janv. 29 13:37 square.mp4
		-rw-rw-r-- 1 fredj21 fredj21 5261945 janv. 29 13:37 triange.mp4
```

Direction donc  --> http://www.roboflow.com/  

Après s'être indentifier,<br>
on crée un nouveau projet **public** de type "Object Detection" avec le mon des diférentes classes

<img src="photos/robotflow_1.png" width="70%"></a>

ensuite, nous ajoutons les classes à notre projet 
* round, 
* square, 
* triangle, 
* hexagon

<img src="photos/robotflow_2.png" width="70%"></a>


Maintenant, dans la section "Upload Data", nous importons chaque vidéo, l'une après l'autre<br>
avec une fréquence d'échantillonage de **5 images par seconde** (choix arbitraire à adapter à ses besoins) <br> 

<img src="photos/robotflow_3.png" width="45%">  <img src="photos/robotflow_4.png" width="45%">

On crée des tache de type  **"Manual Labeling"**,  que l'on assigne à soi même.<br>

En effet, la plateforme est collaborative, et permet d'assigner des taches à différentes personnes<br>
Dans la section "Annotate", nous pouvous visualiser les différentes taches restants, la personne en charge de cette tache, le taux de réalisation    

<img src="photos/robotflow_5.png" width="80%"><br>


Pas de difficulté lors du labeling, il faut juste veiller à selectionner la bonne classe ....  et avoir un peu de patience !!! <br>

<img src="photos/robotflow_annotate_1.png" width="45%"> <img src="photos/robotflow_annotate_2.png" width="45%">
<img src="photos/robotflow_annotate_3.png" width="45%"> <img src="photos/robotflow_annotate_4.png" width="45%">


Après avoir annoter l'ensemble des images, nous allons ajouter ces images à notre Dataset en utilisant la méthode *"Split Images Between Train/Valid/Test"* qui permetra de répartir aléatoirement nos photos pour les besoins de trainning, validation et test.

<img src="photos/robotflow_10.png" width="80%"><br>


Enfin, il nous reste à générer une nouvelle version de notre Dataset en apliquant des opérations de **rotation**, ajout de **bruit**, passage de certaines photos en **niveau de gris**, .... <br>

Dans la section "Dataset" --> "Generate Version"

Le but étant, ici, d'augmenter artificiellement le nombre de photos de notre Dataset<br>

<img src="photos/robotflow_11.png" width="40%"><br>


#### Pour résumer :

Nous sommes parti sur la base de :
* 4 vidéos de 20 secondes 
* un échantillonage de 5 images par seconde
* ce qui donne : **99 images par classe** 

Après l"opération de "split", nous obtenons :

* 70 %  Train			--> 69 images
* 20 %  Validation		--> 20 images	
* 10 %  Test			--> 10 images

Un total donc, pour l'ensemble des classes de  :

* 276 image de trainning
* 80 images de Validation
* 40 image de Test
   
ensuite, la création d'une version du Dataset ( augmentation du nombre d'image)

* rotation horizontal et vertical
* gris 	15% des images
* bruit 1.96%

Lors de cet augmentation, nous sommes limité, dans la version gratuite de Roboflow, à 1500 images !<br>
Nous avons donc maintenant : 	

* 1380 image de trainning
* 80 images de Validation
* 40 image de Test

#### Download Dataset


Nous pouvons maintenant télécharger notre Dataset dans de nombreux formats<br>
mais plus particulièrement au format **YOLOv8** pour la suite de notre projet<br>

<img src="photos/robotflow_12.png" width="40%"><br>


l'ensemble des fichiers sont dans le répertoire :  *Dataset/210125_4_shapes_TEST.v2i.yolov8/* du dépo Git :


$ ls -l Dataset/210125_4_shapes_TEST.v2i.yolov8
total 24
-rw-rw-r-- 1 fredj21 fredj21  299 févr.  2 08:08 data.yaml
-rw-rw-r-- 1 fredj21 fredj21  150 févr.  2 08:08 README.dataset.txt
-rw-rw-r-- 1 fredj21 fredj21 1190 févr.  2 08:08 README.roboflow.txt
drwxrwxr-x 4 fredj21 fredj21 4096 févr.  2 08:08 test
drwxrwxr-x 4 fredj21 fredj21 4096 févr.  2 08:08 train
drwxrwxr-x 4 fredj21 fredj21 4096 févr.  2 08:08 valid


```


































```















---

## 3.2 - Entraînement du modèle IA

2 solutions :  entraîner le modèle en local sous linux,  ou sur Google Colab


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

## 3.3 - Conversion du modèle

Le plus simple est de faire sous linux 

	# pour DFC de Hailo 

	https://hailo.ai/developer-zone/documentation/hailo-sw-suite-2025-01/
	https://hailo.ai/developer-zone/software-downloads/


	
	$ unzip hailo_ai_sw_suite_2025-01_docker.zip
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


