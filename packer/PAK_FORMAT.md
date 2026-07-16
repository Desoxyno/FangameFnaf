# PAK Format

## Objectif

Le format `.pak` sert à regrouper les assets du jeu dans un seul fichier.

Au lieu d'avoir :

```text
assets/
├── sounds/
│   ├── night.mp3
│   └── door.wav
├── models/
│   └── office.glb
└── textures/
    └── wall.png
```

On aura :

```text
Game.exe
data.pak
```

Le jeu chargera les ressources depuis l'archive.

Les objectifs sont :

- simplifier la distribution du jeu
- éviter d'avoir beaucoup de fichiers séparés
- gérer les ressources directement depuis le moteur
- empêcher une modification simple des assets


# Principe général

Un fichier `.pak` est un fichier binaire.

Il contient une suite d'octets, mais le lecteur ne sait pas ce qu'ils représentent sans connaître le format.

Le packer et le lecteur doivent donc utiliser exactement la même structure.

Exemple :

Le packer écrit :

```text
Taille du nom
Nom
Taille du fichier
Données
```

Le lecteur lit :

```text
Taille du nom
Nom
Taille du fichier
Données
```


# Structure globale

```text
HEADER

FILE 1

FILE 2

FILE 3

...
```


# Header

Le header contient les informations générales sur l'archive.

Il pourra contenir :

- Signature
- Version
- Nombre de fichiers


Exemple :

```text
PAK
1
50
```

La signature permet de vérifier que le fichier est bien une archive `.pak`.

La version permet de modifier le format plus tard.


# Structure d'un fichier

Chaque fichier est stocké comme ceci :

```text
filenameSize
filename
fileSize
data
```


# filenameSize

`filenameSize` contient la taille du nom du fichier.

Type utilisé :

```cpp
uint32_t
```

Le lecteur sait donc qu'il doit lire 4 octets pour récupérer cette valeur.

Exemple :

```text
17
```

Signifie :

```text
Les 17 prochains octets correspondent au nom du fichier.
```


# filename

Contient le nom du fichier.

Exemple :

```text
night.mp3
```

Le lecteur lit exactement le nombre d'octets indiqué par `filenameSize`.

Il ne cherche pas un caractère de fin.


# fileSize

Contient la taille des données du fichier.

Type utilisé :

```cpp
uint32_t
```

Exemple :

```text
45231
```

Signifie :

```text
Les 45231 prochains octets appartiennent au fichier.
```


# Data

Les données réelles du fichier.

Le format `.pak` ne cherche pas à comprendre ce qu'il contient.

Cela peut être :

- MP3
- WAV
- PNG
- GLB
- Shader
- Texte

Les données sont simplement copiées sous forme d'octets.


# Exemple

Ajout du fichier :

```text
night.mp3
```

L'archive contient :

```text
[filenameSize]

[9]

[filename]

[night.mp3]

[fileSize]

[123456]

[data]

[octets du mp3]
```

Le lecteur fait :

```text
Lire filenameSize

↓

Lire filenameSize octets

↓

Lire fileSize

↓

Lire fileSize octets
```

Après avoir lu les données, le curseur arrive directement au fichier suivant.


# Lecture d'un fichier

## Version simple

La première version du lecteur utilise une lecture séquentielle.

Le lecteur parcourt les fichiers un par un.

Exemple :

Recherche :

```text
office.glb
```

Fonctionnement :

```text
Lire fichier 1

Comparer le nom

Pas trouvé

Passer au fichier suivant


Lire fichier 2

Comparer le nom

Trouvé

Charger les données
```

Avantage :

- simple à créer

Inconvénient :

- plus lent avec beaucoup de fichiers


# Offset

Un offset représente la position d'une donnée dans le fichier.

Exemple :

```text
data.pak

0 ---------------- 50000 ---------------- 100000
                    ^
                    |
                 fichier
```

Avec un offset, le lecteur peut aller directement à un fichier.


# Index

Une amélioration possible est d'ajouter un index.

L'index contiendrait :

```text
Nom
Offset
Taille
```

Exemple :

```text
office.glb

offset : 50000
size : 200000
```

Le jeu peut alors trouver directement une ressource sans parcourir toute l'archive.


# Compression

Possible dans une version future.

Objectif :

Réduire la taille du fichier `.pak`.

Exemple :

```text
texture.png

5 MB

↓

2 MB
```

Problème :

Les fichiers doivent être décompressés avant utilisation.


# Chiffrement

Possible mais pas obligatoire.

Le chiffrement ne rend pas les assets impossibles à récupérer.

Si le jeu peut lire les données, quelqu'un peut toujours trouver comment les lire.

Il sert surtout à éviter une extraction simple.


# Intégrité

Un checksum peut être ajouté pour vérifier qu'un fichier n'est pas corrompu.

Principe :

Création :

```text
Données

↓

Checksum
```

Chargement :

```text
Données

↓

Nouveau checksum
```

Comparaison :

```text
Même résultat :

Fichier valide


Résultat différent :

Fichier corrompu
```


# Développement prévu

## Version 1

- [x] Ajouter un fichier dans une archive
- [x] Lire un fichier depuis une archive


## Version 2

- [ ] Ajouter plusieurs fichiers
- [ ] Ajouter un header
- [ ] Ajouter le nombre de fichiers


## Version 3

- [ ] Ajouter un index
- [ ] Ajouter les offsets


## Version 4

- [ ] Compression
- [ ] Checksum
- [ ] Chiffrement


# Notes

Le format doit rester simple.

Le but est d'avoir une base fonctionnelle avant d'ajouter des fonctionnalités.

Un format simple qui marche est plus utile qu'un format complexe impossible à maintenir.