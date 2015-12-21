module factorisationCholesky

	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	!	Module pour la factorisation de cholesky	!
	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	implicit none

contains

	! factorisation de cholesky
	subroutine factorisation(A, n)
		implicit none
	
		integer, intent(in) :: n ! dimension de la matrice carrée A à factoriser
		double precision, intent(inout) :: A(n,n) ! matrice carrée A qui sera transformée en L le résultat du procédé de cholesky
		integer :: j ! variable locale pour boucler 

		do j = 1,n
			! calcul partiel des éléments diagonaux (pour éviter de faire une racine négative)
			A(j,j) = A(j,j) - dot_product(A(j,1:j-1),A(j,1:j-1))

			! on ne peut pas diviser par 0 ou mettre un nombre négatif dans la racine
			if (A(j,j) <= 0) then 
				print*,'Impossible de factoriser, la matrice est-elle définie positive ?'
				! on arrête le massacre
				stop
			end if

			! calcul des éléments diagonaux
			A(j,j) = sqrt(A(j,j))

			if (j < n) then
				! calcul des éléments sous la diagonale
				A(j+1:n,j) = (A(j+1:n,j) - matmul(A(j+1:n,1:j-1),A(j,1:j-1))) &
				& / A(j,j)
				! les éléments au dessus de la diagonale sont nuls (la matrice sera triangulaire inférieure)
				A(j,j+1:n) = 0.
			end if

		end do
	end subroutine factorisation

end module factorisationCholesky