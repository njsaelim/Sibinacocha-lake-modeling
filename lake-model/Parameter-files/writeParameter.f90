    program writeParameter

      open(unit=20,file="lake-params.txt",status="old")  ! latin hypercube scalings
      open(unit=22,file="row.txt",status="old")     ! row of LHS file to use, from shell script

      read(22,*) inum

      do j=1,inum
        read(20,*) v1, v2  ! CHANGE this line to match number of parameters in lake-params.txt
!  80    format(a7,1x,f12.10,1x,f12.10,1x,f12.10)
      end do

! CHANGE following lines to specify ranges for parameters you wish to vary
      v1 = 2.5e-3*v1 + 0.5e-3   ! CDRN from 0.5 to 3 e-3
      v2 = 0.49*v2 + 0.01       ! eta from 0.1 to 0.5 


! CHANGE following lines to write lake.inc parameter statements for parameters you wish to vary
      write(23,*) "      parameter (cdrn = ", v1,")"
      write(23,*) "      parameter (eta = ", v2,")"

      end