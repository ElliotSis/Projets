program cholesky

	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	!							Programme principal							! 
	!	pour résoudre un système linéaire avec la méthode de Cholesky		!
	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	
	! utilisation de modules externes 
	use matrice ! pour le traitement matriciel
	use factorisationCholesky ! pour la factorisation de cholesky
	use resolutionSysteme ! pour la résolution de systèmes linéaires

	implicit none

	integer           :: n      ! dimension de la matrice carrée A
	real, allocatable :: A(:,:), b(:) ! la matrice carrée A et le vecteur b

	! lecture de la dimension du système
	print *,'Rentrez la dimension de la matrice carrée A du système Ax = b : '
	read *,n

	! on alloue l'espace mémoire pour la matrice A et le vecteur b
	allocate(A(n,n))
	allocate(b(n))

	! on remplit la matrice A
	print *,'Rentrez les éléments de A (colonne par colonne) : '
	read*,A

	! on remplit le vecteur b
	print *,'Rentrez les éléments de b : '
	read*,b

	! on affiche la matrice A
	print*,'A = '
	call affichage(A,n)

	! on affiche le vecteur b
	print*,'b = '
	call affichageVecteur(b,n)

	! on vérifie que la matrice soit bien symétrique
	if (.not.estUneMatriceSymetrique(A, n)) then
		print*,'On ne peut pas appliquer la méthode de Cholesky : & 
		&la matrice n''est pas symétrique'
		! si ce n'est pas le cas alors fin du programme
		stop
	end if

	! on factorise la matrice A avec cholesky
	call factorisation(A, n)

	! affichage de la factorisation de cholesky
	print*,'La factorisation de Cholesky de la matrice carrée A est L*L^T = '
	call affichage(A,n)
	print*,'*'
	call affichage(transpose(A), n)

	! résolution du système linéaire
	call resolution(A, b, n)

	! affichage de la solution
	print*,'La solution du système est x = '
	call affichageVecteur(b, n)

	! fin du programme
	stop

end program cholesky