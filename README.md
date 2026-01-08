# Ressources pour les Travaux Pratiques de Microcontrôleurs

Ce dépôt contient l’ensemble des fichiers de base nécessaires pour la réalisation des travaux pratiques de microcontrôleurs : 
- Dans l'IDE MPLAB X (v6.25)
- En langage C
- Avec le compilateur xc8

Il est conçu pour servir de point de départ à chaque étudiant : vous devez forker ce dépôt dans votre propre espace GitHub avant de commencer votre travail.

---

## Contenu du dépôt

* **`/`** : dossier racine : créez vos projets MPLABX ici
* **`/Ressources/`** : modèles de code (fichiers de démarrage, exemples de structure de projet, en-têtes types, etc.).
* **`/.gitignore`** : fichier préconfiguré pour exclure les éléments non pertinents du dépôt (fichiers temporaires, binaires compilés, etc.).

---

## Objectif

L’objectif de ce dépôt est de :
* standardiser la structure des projets en langage C utilisés pendant les TP ;
* faciliter la prise en main des outils et la gestion du code avec Git ;
* assurer la compatibilité avec les environnements de développement fournis.

---

## Instructions d’utilisation

1. **Forkez** ce dépôt sur votre propre compte GitHub.
2. **Clonez** votre fork sur votre machine locale :
```bash
git clone https://github.com/<votre-utilisateur>/<nom-du-repo>.git
```
3. Travaillez dans votre fork (ajout de code, tests, commits réguliers).
4. **Ne modifiez pas** la structure du dépôt sauf indication contraire.
5. Pour les remises de TP, push simplement vos modifications sur votre dépôt forké.

Pour correctement organiser vos fichiers de TP, votre répertoire de travail devrait être constitué ainsi :

```
TP_Microcontroleurs_AP4/
└───Ressources/
|   └───configbits.h/
|   └───main.c/
└───Votre_premier_TP.X/
|   ...
└───Votre_dernier_TP.X/
└───.gitignore
```

Vous placerez chaque nouveau projet créé dans MPLABX dans le répertoire `TP_Microcontroleurs_AP4/`. Il y sera automatiquement créé un sous-répertoire `Nom_du_projet.X/` dans lequel seront rassemblées les sources du projet.

---

## Bonnes pratiques

* Commitez souvent, avec des messages clairs et explicites.
* Vérifiez que votre dépôt reste propre (aucun fichier compilé, binaire ou temporaire).
* Utilisez le `.gitignore` fourni pour éviter d’ajouter des fichiers inutiles.
* Respectez les conventions de nommage indiquées pendant les séances de TP.

---

## Ressources complémentaires

Des références et documents d’appui seront disponibles sur la plateforme de cours ou communiqués lors des séances.
N’hésitez pas à poser vos questions sur le forum du cours ou à votre enseignant.

---

## Auteur

Ce dépôt a été préparé par A.Pirog dans le cadre des travaux pratiques de microcontrôleurs.
Toute modification substantielle du contenu doit être approuvée par l’enseignant.