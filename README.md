# RPI5_AI_Hailo_tests

Test du module AI sur Raspberry PI 5

```
$ cat /proc/cpuinfo | tail -1 
Model		: Raspberry Pi 5 Model B Rev 1.0
```

```
$ cat /etc/os-release 
PRETTY_NAME="Debian GNU/Linux 12 (bookworm)"
NAME="Debian GNU/Linux"
VERSION_ID="12"
VERSION="12 (bookworm)"
VERSION_CODENAME=bookworm
ID=debian
```



## Installation 

```
git clone git@github.com:FredJ21/RPI5_AI_Hailo_tests.git
cd RPI5_AI_Hailo_tests

python3 -m venv --system-site-packages venv
source venv/bin/activate

pip install -r requirements.txt
```

## Tests

dans : ```RPI5_AI_Hailo_tests/bin```

ne pas oublier d'activer l'environnement virtuel python : ```source venv/bin/activate```

#### vérification du chargement des images et de l'interprétation du fichier label 
```
python read_dataset.py
```
#### capture une nouvelle image et sauvegarde dans ```../Dataset/Fred_Dataset/images_HD/```
```
bash prendre_une_photo.sh
```
#### Labelisation des images au format Yolov8
```
Yolo_Label/YoloLabel
```
- sources : https://github.com/developer0hye/Yolo_Label
- Directory : ```Dataset/Fred_Dataset/images_HD/```
- LabelList file : ```Dataset/Fred_Dataset/Fred_Dataset_Labels.txt```

#### création des images dérivées 
```
python dataset_HD_to_640x640.py
```
- au format 640x640
- avec du bruit ( points blancs et noirs )
- 10 itérations par photo
- Source Directory : ```Dataset/Fred_Dataset/images_HD/```
- Destination Directory : ```Dataset/Fred_Dataset/images/```




