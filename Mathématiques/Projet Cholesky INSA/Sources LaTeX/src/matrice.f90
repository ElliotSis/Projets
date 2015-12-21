module matrice

	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	!	Module pour effectuer des traitements matriciels	!
	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	implicit none

contains

	! affichage d'une matrice carrée
	subroutine affichage(A, n)
		implicit none
	
		integer, intent(in) :: n ! dimension de la matrice carrée A
		double precision, intent(in) :: A(n,n) ! matrice A
		integer :: i ! variable locale pour boucler 
		
		! affichage ligne par ligne
		do i=1,n
			print*, A(i,:)
		end do
	end subroutine affichage

	! affichage d'un vecteur
	subroutine affichageVecteur(b, n)
		implicit none
	
		integer, intent(in) :: n ! dimension du vecteur b
		double precision, intent(in) :: b(n) ! vecteur b
		integer :: i ! variable locale pour boucler 
		
		! affichage élément par élément
		do i=1,n
			print*, b(i)
		end do
	end subroutine affichageVecteur

	! savoir si une matrice est symétrique
	logical function estUneMatriceSymetrique(A, n)
		implicit none
	
		integer, intent(in) :: n ! dimension de la matrice carrée A
		double precision, intent(in) :: A(n,n) ! matrice A 
		integer :: i,j ! variables locales pour boucler 
		
		estUneMatriceSymetrique = .true.

		! on ne parcoure que les éléments triangulaire inférieur pour tester l'égalité
		do i=1,n
			do j=1,i-1,1
				estUneMatriceSymetrique = estUneMatriceSymetrique.and. &
				& (A(i,j) == A(j,i))
			end do
		end do
	end function estUneMatriceSymetrique

end module matrice