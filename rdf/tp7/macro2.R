library(MASS)

# Chargement des fichiers

load(file='x_app.data')
load(file='classe_app.data')

load(file='x_test.data')
load(file='classe_test.data')

# Couleurs des classes des donnees d'apprentissages

n_app <- length(x_app)

couleur <- rep('red', n_app)
couleur[classe_app == 2] = 'green'
couleur[classe_app == 3] = 'blue'

# Q5

# Moyennes des classes
mean1 <- colMeans(x_app[classe_app==1,])
mean2 <- colMeans(x_app[classe_app==2,])
mean3 <- colMeans(x_app[classe_app==3,])

mean <- (mean1 + mean2 + mean3) / 3

# Covariances intra-classe
S1 <- cov(x_app[classe_app==1,])
S2 <- cov(x_app[classe_app==2,])
S3 <- cov(x_app[classe_app==3,])

# Covariance inter-classe
Sw = S1 + S2 + S3
Sb = (mean1-mean)%*%t(mean1-mean) + (mean2-mean)%*%t(mean2-mean)+ (mean3-mean)%*%t(mean3-mean)

# Q6

# Resolution equation
invSw = solve(Sw)
invSw_by_Sb = invSw %*% Sb
vp <- eigen(invSw_by_Sb)

# Affichage de la droite correspondant au vecteur propre dont la valeur propre est la plus elevee
plot(x_app, col=couleur)
pente <- vp$vectors[2,1] / vp$vectors[1,1]
abline(a = 0, b = pente, col = "black")

# Projection des points
scalarProduct_app_ACP <- x_app %*% (vp$vectors[,1] / sqrt(sum(vp$vectors[,1] * vp$vectors[,1])))
XP <- x_app
XP[,1] = scalarProduct_app_ACP * vp$vectors[1,1]
XP[,2] = scalarProduct_app_ACP * vp$vectors[2,1]

# Affichage des points projetes
points(XP[classe_app == 1,], col = "red")
points(XP[classe_app == 2,], col = "green")
points(XP[classe_app == 3,], col = "blue")

# Q7

# Ceci est un seuil
x_app.lda <- lda(scalarProduct_app_ACP, classe_app)
assigne_test <- predict(x_app.lda, newdata = scalarProduct_app_ACP)

# Taux de bonnes classifications
table_classification_app <- table(classe_app, assigne_app$class)

# table of correct class vs. classification
diag(prop.table(table_classification_app, 1))

# total percent correct
taux_bonne_classif_app <-sum(diag(prop.table(table_classification_app)))

# Formes des classes
shape<-rep(1, n_app) ;
shape[assigne_app$class==2] = 2
shape[assigne_app$class==3] = 3

# Affichage des projections apprentissage classees
plot(x_app, col=couleur, pch=shape, xlab = "X1", ylab = "X2")
abline(a = 0, b = pente, col = "blue")

points(XP[classe_test==1,], col="red")
points(XP[classe_test==2,], col="green")
points(XP[classe_test==3,], col="blue")