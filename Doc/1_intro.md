
# Partie 1 - Introduction

## Voici une rétrospective des modules IA pour Raspberry PI


L'année 2024 fut marquée, particulièrement pour nos chères cartes Raspberry PI, par l'arrivée de multiples modules AI officiels.

Ces modules, proposés par la fondation Raspberry, sont capables de réaliser les traitements requis par l’utilisation de réseaux de neurones de l'IA que l'on souhaite mettre en œuvre.
Comme le ferait un GPU  (Graphics Processing Unit) dans une grosse machine ... 
et ainsi, réduire considérablement les sollicitations du microprocesseur principal (CPU) .   

En pratique, les modules accélérateur d'IA permettent de créer des applications complexes de traitement vidéo en temps réel, 
ou de "vision intelligente par ordinateur", avec une très faible latence, même sur des ordinateurs de taille modeste !

Les domaines d'application sont très nombreux ! On peut citer par exemple : la détection d'objets, la détection de personne, de visage,la segmentation d'image, la classification, la détection de pose, le suivi (ou tracking).

---
  
## 1.1 le "kit AI" - juin 2024

<img src="img/AI-Kit-on-Pi-5-small.jpg" width=500 />

Ce kit est composé d'une carte d’extension au format Raspberry disposant d'un connecteur M2 , la carte **M2 HAT.+**<br>
Le connecteur M2 utilise le bus PCIe 3.0 à une vitesse de 8Gbit/s et peut éventuellement accueillir un disque SSD.<br>
Mais dans le cadre de notre Kit AI, le connecteur accueille un module accélérateur d'IA **Hailo-8L**.<br>
Le puce accélératrice  Hailo-8L est capable de réaliser 13 Téra-opérations par seconde (13 TOPS) et est évidemment compatible avec les modules caméra du RPI. <br>
Le kit est accompagné d'une suite logiciel permettant de faire ses premiers pas autour des libs rpicam-apps ( on en parle plus bas )

---

## 1.2 le compilateur Hailo DFC - juillet 2024

Très rapidement, le mois suivant, Hailo annonce la sorti de son compilateur Dataflow (DFC) qui permet de personnaliser le réseau de neurone selon ses besoins.<br> 
Un conteneur Docker est proposé pour faciliter l'installation.

<img src="img/Hailo-Dataflow-Compiler.png"  width=500 />

_2 méthodes sont proposées :_

* **Bring Your Own Data (BYOD)** - Apportez vos propres données<br>
   qui consiste à "recycler" un modèle déjà entraîné, mais cette fois ci avec son propre jeu de données.<br>
	https://github.com/hailo-ai/hailo-rpi5-examples/blob/main/doc/retraining-example.md<br>
* **Bring Your Own Model (BYOM)** - "Apportez votre propre modèle"<br>
	qui nécessite une compréhension plus approfondie du modèle de données et du flux de conversion (le "workflow") vers le format HEF des modules Hailo.<br>
	Documentation complète ici :<br>
	https://hailo.ai/developer-zone/documentation/dataflow-compiler/latest<br>
	

---

## 1.3 la caméra AI - septembre 2024 

<img src="img/AI-Camera-hero-Large-1024x682.jpeg" width=500 />

Là où le Kit AI Hailo est uniquement compatible avec la carte PI 5 , la caméra officielle Raspberry AI est utilisable sur l'ensemble de la gamme des cartes, y compris la Raspberry PI Zero.<br>
Cette caméra embarque un capteur Sony IMX500 de 12 millions de pixel avec une vision à 78 degrés et également le micro-contrôleur RP2040 ( oui ! le même que sur le Raspberry PICO !) pour la gestion du réseau de neurone et du firmware.<br>

La suite logiciel d'IA de Sony permet de mettre en œuvre les réseaux de neurones de type TensorFlow ou PyTorch après conversion et chargement dans la flash de la caméra.


_Pour bien démarrer :_<br>
> https://www.raspberrypi.com/documentation/accessories/ai-camera.html<br>
> https://github.com/raspberrypi/imx500-models<br>


---

## 1.4 le Raspberry Pi AI HAT+ - septembre 2024 

<img src="img/AI-HAT-1024x683.jpg" width=500 />

Cette fois ci, l'accélérateur Hailo AI n'est plus au format d'une carte M2 !<br>
C'est bien une carte d’extension pour Raspberry PI5 : un module HAT, en deux versions : 
* le modèle 13 TOPS (téra-opérations par seconde), doté du même accélérateur Hailo-8L que le kit AI
* le modèle 26 TOPS, plus puissant ! équipé de l’accélérateur Hailo-8

Toujours raccordé au bus PCIe Gen 3.0

https://www.raspberrypi.com/products/ai-hat/

---

## 1.5 d'autres solutions AI 

Une autre solution, mais moins officielle, consiste à utiliser une carte d’extension de type **Hat uPCIty Lite** pour disposer d'un bus PCIe x4  sur son Raspberry PI.<br>

Ce Bus PCIe x4  permet ensuite de connecter une carte de type **Alftel 12x PCI Express M.2 Carrier Board** ... qui dispose de **12 slots PCI Express M2 !!!** <br>

Nous pourrions donc installer 12 modules Hailo-8L au format M2 !!! <br>

<a href="img/Hat_uPCIty_Lite.png"><img src="img/Hat_uPCIty_Lite.png" width=400></a>  <a href="img/m2-alftel-12x-pcie-m2-carrier-board.png"><img src="img/m2-alftel-12x-pcie-m2-carrier-board.png" width=400></a>


<img src="img/Screenshot-2024-11-11-at-14.13.31-800x400.png" width=700/><br> 

https://youtu.be/oFNKfMCGiqE

🤔 Mais puisque nous disposons d'un bus PCIe x4, il serait donc possible de plugger directement une carte graphique (GPU) type GTXxxxx sur le Hat uPCIty Lite  ... !!!<br>  
**Ok ! cette solution reste plutôt expérimentale ...!!**<br>


A noter également qu'il existe d'autres modules AI, comme par exemple le module Accélérateur Google Coral M.2 (A+E).<br>
Une solution économique doté du processeur Google Edge TPU capable d'atteindre une performance de 4 tera-opérations par seconde.<br>

<img src="img/Google_Coral_M2.jpg" width=300 />


<br>
...mais comment mettre en oeuvre ces modules AI ???<br>


---

