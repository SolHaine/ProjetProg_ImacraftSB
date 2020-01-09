# Projet ImacraftSB (Solène et Baptiste)

Éditeur-visualiseur de terrains et de scènes en 3D, dans le cadre de la formation ingénieur IMAC.

*https://github.com/SolHaine/ProjetProg_ImacraftSB*

## Prérequis

Le programme fonctionne sur Linux. 
Assurez-vous d'avoir SDL 2.0, OpenGL 3.3, GLEW, Eigen 3 et Boost.

```
sudo apt-get update
sudo apt-get install libglu1-mesa-dev freeglut3-dev mesa-common-dev
sudo apt-get install libsdl2-dev
sudo apt-get install libglew-dev
sudo apt-get install libeigen3-dev
sudo apt-get install libboost-all-dev
```

## Démarrer

Placez-vous dans un dossier de build dans le même répertoire que le projet (ex : ProjetProg_ImacraftSB_build), créez le build avec CMake, compilez et lancez le programme :

```
cmake ../ProjetProg_ImacraftSB
make
bin/ImacraftSB
```

L'exécutable est dans le dossier /bin.

## Commandes

* Echap : quitter
* Caméra :
	* Z / Q / S / D : déplacer la caméra horizontalement et verticalement
	* A / E : déplacer la caméra en hauteur
	* Clic gauche + glisser : tourner la caméra
* Curseur :
	* O / K / L / M : déplacer le curseur horizontalement et verticalement
	* I / P : déplacer le curseur en hauteur
* Interface :
	* Fenêtre bas-droit (Toolbox) : ajouter/supprimer un cube, extruder/creuser, choisir une couleur pour le prochain cube ajouté, ajouter/supprimer la couleur du cube sélectionné, ajouter/supprimer la texture du cube sélectionné
	* Fenêtre bas-gauche (Texturebox) : choisir une texture pour le prochain cube ajouté
	* Fenêtre haut-droit (Lightbox) : changer entre le jour et la nuit, ajouter/supprimer des lumières ponctuelles, réinitialiser les lumières
	* Fenêtre haut-droit 2 (Worldbox) : générer un nouveau monde aléatoire, générer un nouveau monde plat
	* Barre de menu (en haut) : sauvegarder/charger une scène (dans/bin/savedScenes)

## Version

1.0 *- janvier 2020*

## Crédits

* **Baptiste Ory** - (https://github.com/BaptisteOry)
* **Solène Mary-Vallée** - (https://github.com/SolHaine)

*Programme réalisé au cours du deuxième semestre de la formation ingénieur IMAC pour les cours de « Synthèse d'image », « Programmation objet » et « Mathématiques pour l'informatique ».*

## Bon à savoir

* Documentation (dont rapport) : /doc
* Scènes sauvegardés : /bin/savedScenes