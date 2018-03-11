ALDER Hugo - FEVRE Corwin

# TP7 - Réduction de la dimension par analyse en composante principale et analyse factorielle discriminante

## Q1 - Affichage des données

| Données d'apprentissage | Données test          |
|:-----------------------:|:---------------------:|
| ![](img/fig_app.png)    | ![](img/fig_test.png) |

On remarque grâce aux figures ci-dessus que les données d'apprentissage sont regroupées par classe. Il en va de même pour les données de test.

On peut cependant noter que les données d'apprentissage sont plus centrées que les données de test, qui sont elles plus éparpillées.

On peut donc imaginer qu'il sera plus facile de trouver un axe de projection optimal pour les données de test que pour les données d'apprentissage, même si cela ne semble pas évident dans chacun de ces cas.

## Q2 - ACP sur données d'apprentissage

Grâce à l'image page suivante, on se rend compte que les données d'apprentissage ne peuvent pas être correctement disciminées.

Les données de la classe 3 (en bleu) ne posent pas de problème. En revanche, les données des classes 1 (en rouge) et 2 (en vert) se retrouvent sur la même portion de la droite qui représente le vecteur propre. On ne peut donc pas les différencier, alors qu'on observe clairement sur l'image que ces points font partie d'ensembles différents.

<div style="page-break-after: always;"></div>

| Données d'apprentissage projetées |
|:---------------------------------:|
| ![](img/app_proj.png =472x380)    |

## Q3 - Classification par ALD des données test projetées

| Données test projetées et classifiées |
|:-------------------------------------:|
| ![](img/ald_test.png =472x380)                 |

<div style="page-break-after: always;"></div>

## Q4 - Taux de bonne classification

Grâce à la question précédente, on obtient le tableau `table_classification_test` suivant :

| | 1 | 2 | 3 |
|:--:|:--:|:--:|:--:|
| **1** | 67 | 32 | 1 |
| **2** | 12 | 88 | 0 |
| **3** | 0  | 0  | 100 |

On obient un taux de bonne classification général de 85%.

On peut remarquer que 100% des données de la classe 3 ont été correctement classifiées : il n'existe que des croix de couleur bleue.

En revanche, on obient un pourcentage de réussite de 67% pour la classe 1. En effet, 12% des données ont été assignées, à tort, à la classe 2 et 1% à la classe 3. C'est pour cette raison qu'on observe des cercles verts et bleus.

Il en va de même pour les données de la classe 2. On obient un pourcentage de réussite de 88%, mais 12% des données ont été assignées à la classe 1, ce qui explique l'existence de triangles rouges.
