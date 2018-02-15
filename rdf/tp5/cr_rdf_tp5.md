ALDER Hugo - FEVRE Corwin

# TP5 - Binarisation par seuillage de Bayes

## Q1 - Seuillage fixe

Dans l'histogramme, la valeur du seuil correspond au moment où on considère un pixel comme étant noir ou blanc.

| Seuil de 0.5           | Seuil de 0.55          | Seuil de 0.6           |
|:----------------------:|:----------------------:|:----------------------:|
| ![](img/binaire50.png) | ![](img/binaire55.png) | ![](img/binaire60.png) |

On peut voir grâce aux images ci-dessus qu'aucune de ces valeurs ne donne une binarisation satisfaisante. Il y a toujours plus ou moins de points d'une couleur dans la partie de l'image censée être de l'autre couleur.

## Q2 - Probabilité à priori des classes

Cf. fichier priori.R

```
total <- sum(h$counts)

pw1 = sum(h1$counts) / total
pw2 = sum(h2$counts) / total

```

On obtient pw1 = 0.57 et pw2 = 0.43.

## Q3 - Probabilité conditionnelle

Cf. fichier priori.R

```
X = 141

pXI = h$counts[X] / sum(h$counts)
pXw1 = h1$counts[X] / sum(h1$counts)
pXw2 = h2$counts[X] / sum(h2$counts)

```

Avec X = 141, on obtient les résultats suivants :

| P(X/I) | P(X/ω1) | P(X/ω2) |
|:------:|:-------:|:-------:|
| 0      | 0       | 0       |

## Q4 - Seuillage automatique
