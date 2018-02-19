ALDER Hugo
FEVRE Corwin

# TP5 - Binarisation par seuillage de Bayes

## Q1 - Seuillage fixe

**Cf. fichier segment_par_seuillage_etudiant.R**

Dans l'histogramme, la valeur du seuil correspond au moment où on considère un pixel comme étant noir ou blanc.

| Seuil de 0.5           | Seuil de 0.55          | Seuil de 0.6           |
|:----------------------:|:----------------------:|:----------------------:|
| ![](img/binaire50.png) | ![](img/binaire55.png) | ![](img/binaire60.png) |

On peut voir grâce aux images ci-dessus qu'aucune de ces valeurs ne donne une binarisation satisfaisante. Il y a toujours plus ou moins de points d'une couleur dans la partie de l'image censée être de l'autre couleur.

## Q2 - Probabilité à priori des classes

**Cf. fichier probas.R**

```
total <- sum(h$counts)

pw1 = sum(h1$counts) / total
pw2 = sum(h2$counts) / total

```

On obtient pw1 = 0.57 et pw2 = 0.43.

## Q3 - Probabilité conditionnelle

**Cf. fichier probas.R**

```
X = 142

pXI = h$counts[X] / total
pXw1 = h1$counts[X] / sum(h1$counts)
pXw2 = h2$counts[X] / sum(h2$counts)

```
<div style="page-break-after: always;"></div>

Avec X = 142, afin d'avoir le nombre de pixels dont le niveau de gris est de 141, on obtient les résultats suivants :

| P(X/I) | P(X/ω1) | P(X/ω2) |
|:------:|:-------:|:-------:|
| 0.0118      | 0.008947368       | 0.0155814       |

## Q4 - Seuillage automatique

**Cf. fichier probas.R**

```
somme1 = 0:255 # pE1 soit pw1X
somme2 = 0:255 # pE2 soit pw2X
erreur = 0:255 # pX

minimum_erreur = 1;
seuil_minimum_erreur = 0;

for (X in 1:255)
{
  somme1[X+1] = sum(h1$density[(X+1):256])/sum(h1$density[1:256])
  somme1[X+1] = somme1[X+1] * omega1

  somme2[X+1] = sum(h2$density[1:(X+1)])/sum(h2$density[1:256])
  somme2[X+1] = somme2[X+1] * omega2

  erreur[X+1] = somme1[X+1] + somme2[X+1]

  if (erreur[X+1] < minimum_erreur ) {
    seuil_minimum_erreur = X
    minimum_erreur = erreur[X+1]
  }
}

final_image <- (image - seuil_minimum_erreur/255) >= 0
display(final_image, method="raster")
```

On trouve un seuil optimal de 136 et l'image seuillée ci-dessous :

![](img/seuil_optimal.png =250x250)

<div style="page-break-after: always;"></div>

## Q5 - Extraction de la région représentant le chiffre par seuillage automatique

**Cf. fichier chiffre_1.R**

On effectue les mêmes opérations que lors des opérations précédentes, mais avec ces nouvelles images.

On obtient alors un seuil optimal de 146 et l'image ci-dessous :

![](img/chiffre_0.png)

Si on segmente l'image du chiffre 1 avec le seuil optimal précédent, on obient l'image suivante.

![](img/chiffre_1.png)

On peut constater que le résultat obtenu est satisfaisant car la nature des images de base des chiffres 0 et 1 est semblable.

<div style="page-break-after: always;"></div>

## Q6 - Taux d'erreur de classification

**Cf. fichier chiffre_1.R**

Les calculs réalisés pour répondre à cette question n'ont malheureusement pas donné de résultats satisfaisants.
