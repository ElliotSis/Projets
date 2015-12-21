FC = gfortran
OPT = -g

# compiler cholesky
cholesky: cholesky.f90
	$(FC) $(OPT) matrice.f90 factorisationCholesky.f90 resolutionSysteme.f90 cholesky.f90 -o cholesky

# nettoyer
clean:
	rm *.mod cholesky
