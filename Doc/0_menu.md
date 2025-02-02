# Créer et entraîner son propre IA pour les modules HAILO du Raspberry PI5


<img src="img/en_construction.webp" width="100%">

Je vous propose mon retour d’expérience sur la mise en œuvre d'une intelligence artificiel, sur une carte Raspberry PI5, capable de reconnaître et différentier un ensemble d'objets personnels.

Le principe est d’entraîner un réseau de neurones, de façon automatique, à l'aide d'un ensemble de données composés d'un certain nombre d'images : le "DataSet".

Ce réseau de neurones, ou "IA", sera ensuite capable de reconnaître les objets pour lequel nous l'avons entraîné.<br>
Ou plus exactement, l'IA sera capable d'effectuer une prédiction de reconnaissance avec un certain taux de certitude.
         

## Au sommaire :

1. [Introduction](1_intro.md)

    1.1 le "kit AI"<br>
    1.2 le compilateur Hailo DFC<br>
    1.3 la caméra AI<br>
    1.4 le Raspberry Pi AI HAT+<br>
    1.5 d'autres solutions AI<br>

2. [Configuration et tests rapides du module AI](2_config_et_tests.md)

    2.1 Premier configuration<br>
    2.2 Vérification de la présence du module AI<br>
    2.3 Vérification de la présence de la (ou des) camera(s) RPI<br>
    2.4 Tests de Détection, Segmentation, Estimation<br>  
    

3. [Création de son propre réseau de neurones](3_creation_de_son_IA.md)

    3.1 Création de son jeu de donnée<br>
    - 3.1.1 Création du Dataset en local<br>
    - 3.1.2  Création du Dataset sur le cloud<br>

    3.2 Entraînement du modèle IA<br>
    3.3 Conversion du modèle<br>
    3.4 Déploiement et tests<br>



4. Conclusionnnn

---