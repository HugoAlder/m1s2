library(MASS)

# Chargement des fichiers

load(file='x_app.data')
load(file='classe_app.data')

load(file='x_test.data')
load(file='classe_test.data')

# Q1

# Apprentissage

n_app <- length(x_app)

# Couleurs des classes des données d'apprentissages
#couleur <- rep('red', n_app)
#couleur[classe_app == 2] = 'green'
#couleur[classe_app == 3] = 'blue'

#plot(x_app, col = couleur)

# Test

n_test <- length(x_test)

# Couleurs des classes des données test
couleur <- rep('red', length(x_test))
couleur[classe_app == 2] = 'green'
couleur[classe_app == 3] = 'blue'

#plot(x_test, col=couleur)

# Q2

# Estimation de la co-variance des données d'apprentissage
cov_app <- cov(x_app)

# Identification du vecteur propre associé à la valeur propre la plus élevée
vp <- eigen(cov_app)

# Affichage de la droite correspondant à vp
pente <- vp$vectors[2,1] / vp$vectors[1,1]
#abline(a = 0, b = pente, col = "blue")

#scalarProduct_app_ACP <- x_app %*% (vp$vectors[,1] / sqrt(sum(vp$vectors[,1] * vp$vectors[,1])))
#XP <- x_app
#XP[,1] = scalarProduct_app_ACP * vp$vectors[1,1]
#XP[,2] = scalarProduct_app_ACP * vp$vectors[2,1]
#points(XP[classe_app == 1,], col = "red")
#points(XP[classe_app == 2,], col = "green")
#points(XP[classe_app == 3,], col = "blue")

# Q3

cov_test <- cov(x_test)
vp_test <- eigen(cov_test)

scalarProduct_test_ACP <- x_test %*% (vp_test$vectors[,1] / sqrt(sum(vp_test$vectors[,1] * vp_test$vectors[,1])))

x_test.lda <- lda(scalarProduct_test_ACP, classe_test)
assigne_test <- predict(x_test.lda, newdata = scalarProduct_test_ACP)

table_classification_test <- table(classe_test, assigne_test$class)

# Table of correct class vs. classification
diag(prop.table(table_classification_test, 1))

# Tableau des pourcentages de bonne classification
taux_bonne_classif_test <- sum(diag(prop.table(table_classification_test)))

# Formes des classes
shape<-rep(1, n_test);
shape[assigne_test$class==2] = 2
shape[assigne_test$class==3] = 3

# Affichage des projections des données test classées
plot(x_test, col = couleur, pch = shape, xlab = "X1", ylab = "X2")

pente <- vp_test$vectors[2,1] / vp_test$vectors[1,1]
abline(a = 0, b = pente, col = "blue")

XP_test <- x_test
XP_test[,1] = scalarProduct_test_ACP * vp_test$vectors[1,1]
XP_test[,2] = scalarProduct_test_ACP * vp_test$vectors[2,1]

points(XP_test[classe_test == 1,], col= "red")
points(XP_test[classe_test == 2,], col= "green")
points(XP_test[classe_test == 3,], col= "blue")