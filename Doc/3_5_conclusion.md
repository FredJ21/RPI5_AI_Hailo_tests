
# Conclusion 

Nous avons donc décrit les grandes étapes de la mise en oeuvre d’une intelligence artificielle de traitement vidéo pour la reconnaissance d’objet par Rasberry PI5 
 
* création du Dataset, 
* entraînement avec Yolo, 
* conversion avec le compilateur Hailo 
* déploiement sur le Raspberry

Il est vrai que ce travail est assez fastidieux et plutôt chronophage. Le processus d’apprentissage de l’IA peut être perturbé par de nombreuses raisons et ne pas donner le résultat escompté. Certains biais peuvent rapidement parvenir selon le choix et/ou la qualité des images de son Dataset. Les erreurs seront alors visibles uniquement lors des tests finaux. Il faudra alors reprendre son travail dès le départ.         

De plus, ces traitements demandent de posséder une grosse machine équipée d’un CPU et d’un GPU puissants pour réaliser les calculs, même si certaines solutions restent possibles dans le cloud.

Mais l'arrivée des modules IA pour le Raspberry PI est une vraie révolution ! La puce Hailo est conçue pour accélérer l'exécution des réseaux de neurones en prenant en charge les calculs d'inférence, ce qui permet d'analyser rapidement des vidéos ou des images en temps réel. Cela se traduit par une faible consommation d'énergie et une réduction de la charge sur le processeur principal du Raspberry Pi, rendant ainsi le dispositif plus efficace pour des applications d'intelligence artificielle embarquée.

… et toujours au format carte de crédit ! 
