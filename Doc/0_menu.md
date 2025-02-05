# Créer et Entraîner son propre IA<br>pour le module AI HAILO du Raspberry PI5


<img src="img/en_construction.webp" width="20%">

Je vous propose mon retour d’expérience sur la mise en œuvre d'une intelligence artificielle sur le nouveau module HAILO 8 (ou HAILO 8L) équipant un Raspberry PI5, et capable de reconnaître et différencier un ensemble d'objets personnels.

Le principe est d’entraîner un réseau de neurones, de façon automatique, à l'aide des outils YOLO et du compilateur HAILO, sur la base d'un ensemble de données composé d'un certain nombre d'images : Le "DataSet".

Ce réseau de neurones, ou "IA", sera ensuite capable de reconnaître les objets pour lequel nous l'avons entraîné.<br>
Ou plus exactement, l'IA sera capable d'effectuer des prédictions de reconnaissance avec un certain taux de certitude sur des images ou sur un flux vidéo.
         
<a href="img/test_1.png"><img src="img/test_1.png" width="49%"></a> <a href="img/test_2.png"><img src="img/test_2.png" width="49%"></a> <br>

## Au sommaire :

1. [Introduction](1_intro.md)

    1.1 le "kit AI"<br>
    1.2 le compilateur Hailo DFC<br>
    1.3 la caméra AI<br>
    1.4 le Raspberry Pi AI HAT+<br>
    1.5 d'autres solutions AI<br>

2. [Configuration et tests rapides du module AI HAILO](2_config_et_tests.md)

    2.1 Premier configuration<br>
    2.2 Vérification de la présence du module AI<br>
    2.3 Vérification de la présence de la (ou des) caméra(s) RPI<br>
    2.4 Tests de Détection, Segmentation, Estimation<br>  
    

3. Création de son propre réseau de neurones pour le module HAILO

    3.1 [Création de son jeu de donnée](3_1_creation_du_Dataset.md)<br>
    - 3.1.1 Création du Dataset en local<br>
    - 3.1.2 Création du Dataset sur le cloud<br>

    3.2 [Entraînement du modèle de notre IA](3_2_entrainement_du_modele.md)<br>
    3.3 [Conversion du modèle pour le module HAILO](3_3_conversion_du_modele.md)<br>
    3.4 [Déploiement et tests sur le Raspberry PI5](3_4_deploiement_du_modele.md)<br>



4. [Conclusion](4_conclusion.md)<br>

---

<a href="https://youtu.be/b6qGFZ387_Y"><img src="img/test_youtube.png" width=80%/></a>
https://youtu.be/b6qGFZ387_Y
 

---