module resolutionSysteme

	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	!	Module de résolution de système linéaires	!
	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	implicit none

contains

	! résolution par descente d'un systéme linéaire
	subroutine descente(L, b, n)
		implicit none
	
		integer, intent(in) :: n ! dimension de la matrice carrée triangulaire inférieure L et du vecteur b
		real, intent(in) :: L(n,n) ! matrice carrée triangulaire inférieure
		real, intent(inout) :: b(n) ! vecteur b sera modifié en vecteur resultant à la résolution
		integer :: i,j ! variables locales pour boucler 

		do i=1,n
			do j=1,i-1,1
				b(i) = b(i) - L(i,j)*b(j)
			end do
			b(i) = b(i) / L(i,i)
		end do
	end subroutine descente

	! résolution par remontée d'un système linéaire
	subroutine remontee(U, b, n)
		implicit none
	
		integer, intent(in) :: n ! dimension de la matrice carrée triangulaire supérieure U et du vecteur b
		real, intent(in) :: U(n,n) ! matrice carrée triangulaire supérieure
		real, intent(inout) :: b(n) ! vecteur b sera modifié en vecteur resultant à la résolution
		integer :: i,j ! variables locales pour boucler 

		do i=n,1,-1
			do j=n,i+1,-1
				b(i) = b(i) - U(i,j)*b(j)
			end do
			b(i) = b(i) / U(i,i)
		end do
	end subroutine remontee

	! résolution d'un systeme factorisé avec cholesky
	subroutine resolution(L, b, n)
		implicit none
	
		integer, intent(in) :: n ! dimension de la matrice carrée triangulaire inférieure L et du vecteur b
		real, intent(in) :: L(n,n) ! matrice carrée triangulaire inférieure obtenue avec cholesky
		real, intent(inout) :: b(n) ! vecteur b sera modifié en vecteur resultant à la résolution
		
		! descente avec L
		call descente(L, b, n)
		
		! remontée avec L^T
		call remontee(transpose(L), b, n)
	end subroutine resolution

end module resolutionSysteme