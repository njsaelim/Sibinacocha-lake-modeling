!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
!                     EDDY
!     compute eddy diffusion profile using the calculation of
!     Henderson-Sellers 1985 Applied Mathematical Modelling 9: 441-446
!     with enhanced diffusion and enhanced mixing options of 
!     Subin et al. (2012) JAMES: 10.1029/2011MS000072
!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

      subroutine eddy (iwater, u2, t, de, nzlk, salty)

      implicit none
      include 'lake.inc'
  
      real u2             ! screen-height wind speed [m/s]
      real t(nzlk)        ! lake surface temperature [degrees C]
      real de(nzlk)       ! eddy diffusivity [m2/s]
      real salty(max_dep) ! lake salinity [ppt]  
      integer iwater      ! open water or ice flag
  
      real dnsty(nzlk)  ! water density anomaly from 1000 [kg/m3]	  	  
      real u            ! screen-height wind speed with minimum of 0.5 [m/s]
      real ks           ! parameter in Ekman profile [1/m]
      real ws           ! surface friction velocity [m2/s2]
      real Po           ! neutral value of turbulent Prandtl number [unitless]
	  real N2min        ! minimum value of N2 from Fang and Stefan (1996) [1/s2]
      real zhalf        ! distance between layer nodes [m]
      real dpdz         ! density gradient with depth [kg/m3/m] 
      real N2           ! Brunt-Vaisala frequency [1/s2]
      real z            ! depth from lake surface at layer bottom [m]
      real num          ! numerator term for Ri calculation [unitless]
	  real den          ! denominator term for Ri calculation [unitless]
      real Ri           ! Richardson number [unitless]
      integer k         ! counter for looping through lake layers

      do k = 1,nzlk
         call density (t(k), salty(k), dnsty(k))
      enddo

      u = amax1(u2, 0.5) ! avoid NAN in ks 
      ks = 6.6 * sqrt(abs(sin(xlat * raddeg))) * u**(-1.84)
      ws = 0.0012 * u2
      Po = 1.0
	  N2min = 7.5e-5

      do k = 1,nzlk-1
        if (k.eq.1) then  ! for surface layer different depth
          zhalf = (surf + dz) * 0.5 
        else
          zhalf = dz
        endif
        dpdz = (dnsty(k+1) - dnsty(k)) / zhalf
        N2 = (dpdz / (1.e3 + dnsty(k))) * grav
        if (iwater.eq.1) then	! open water calculation	
           z = surf + float(k - 1) * dz
		   num = 40. * N2 * (kv * z)**2.
		   den = max(ws**2. * exp(-2. * ks * z), 1.e-10)
		   Ri = (-1.0 + sqrt(max(1. + num/den, 0.))) / 20.
           de(k) = dm + kv * ws * z / Po * exp(-ks * z) /            &
                   (1.0 + 37.0 * Ri**2)
	    else					! ice-covered calculation
		   de(k) = dm
		endif   
		if (endiff_flag)                                             &
		   de(k) = de(k) + 1.039e-8 * max(N2, N2min)**(-0.43) ! enhanced diffusion
        de(k) = de(k) * mixfact		               ! enhanced mixing
      enddo
	  
      if (nzlk.gt.1) de(nzlk) = de(nzlk-1)    ! necessary for cn solution to work	  

      return
      end
