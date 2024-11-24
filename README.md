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
#### capture une nouvelle image et la sauvegarde dans ```../Dataset/Fred_Dataset/images_HD/```
```
bash prendre_une_photo.sh
```
#### Labelisation des images 
```
Yolo_Label/YoloLabel
```
--> sources : https://github.com/developer0hye/Yolo_Label






