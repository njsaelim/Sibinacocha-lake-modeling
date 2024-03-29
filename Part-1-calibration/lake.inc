!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
!     Parameter declarations
!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

      real oblq, xlat, xlon, gmt                  ! geographical parameters
      real b_area, cdrn, eta, alb_slush           ! lake physical parameters
      real alb_snow, alb_sed, csed, condsed       ! lake physical parameters
      integer max_dep, mixfact                    ! lake physical parameters
      integer nzlk_begin                          ! initial conditions
      real readdt, z_screen, u_screen, sigma      ! simulation-specific parameters
      integer nspin                               ! simulation-specific parameters
      logical bndry_flag                          ! meteorological input flags
      logical K_flag, rh_flag, q_flag, dp_flag    ! meteorological input flags
      logical wb_flag, ice_flag, s_flag, sed_flag ! simulation options
	  logical endiff_flag                         ! simulation options
      real dz, dt, zo, delta                      ! physical constants
      real rhowat, rhoice, rhosnow, snowcut       ! physical constants
      real cpair, rair, rvap, cvap, Le, Lei       ! physical constants
      real ca, cb, c70, c71, c72, c73             ! physical constants
      real emis, fusion, surf, fraclim, fracmin   ! physical constants
      real cpw_ice, condw, beta                   ! physical constants
      real fsol1, fsol2, sical0, sical1           ! physical constants
      real kv, dm, pi, snocrit                    ! physical constants
      real lamisw, lamilw, lamssw, lamslw         ! physical constants
      real afrac1, afrac2, condi, conds           ! physical constants
      real raddeg, dpd, grav                      ! physical constants	  
      integer nzlk, nzsed

!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
!     Lake-specific parameters **CHANGE THESE**
!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

! geographical parameters
! Note: xlon and gmt used only if meteorological input is sub-daily

      parameter (xlat = -13.86)        ! local latitude (negative for South) [degrees North]
      parameter (xlon = -71.0)       ! local longitude (negative for West) [degrees East]
      parameter (gmt = -5 )        ! offset from Greenwich Mean Time [hours]

! lake physical parameters	
      parameter (max_dep = 92)        ! maximum number of lake layers [count]
      parameter (b_area = 13412)       ! area of catchment+lake [hectares]
      real area(max_dep)
      data area/2836.527214,2733.562177,2628.98983, &
      2532.850156,2449.07375,2380.320676, &
      2312.423068,2243.858458,2160.666742, &
      2085.884106,2017.43969,1961.820291,   &
      1911.40136,1862.365129,1813.993611, &
      1765.928329,1714.816184,1664.673214, &
      1615.050336,1568.709194,1523.094916, &
      1477.465991,1434.097517,1393.532585, &
      1354.439649,1317.241367,1277.767867, &
      1244.185093,1214.326482,1185.712374, &
      1160.143858,1135.647621,1112.09145, &
      1088.682072,1064.952931,1041.178946, &
      1016.977261,992.0221043,965.4618698, &
      936.4647852,901.9108513,863.619, &
      822.513,784.560735,745.985, &
	  716.6203353,688.7403346,668.1285256, &
      650.117,631.698,612.421, &
      50.0225013,569.1155748,549.9532007, &
      530.9745369,512.7865945,495.9521116, &
      478.6450302,460.797,442.564, &
      423.776,404.388,384.33, &
      363.1103047,341.6436615,318.0111062, &
      288.8058806,259.4753996,234.2553, &
      204.3729754,184.46248,165.3573218, &
      150.7292262,139.3892627,129.8682843, &
      121.550386,113.067711,103.610069, &
      92.950692,82.3093098,73.5318431, &
      63.23329652,50.871138,41.83677703, &
      34.0774008,26.88146,20.17486327, &
      14.35595923,10.26862837,6.88292, &
      4.64192,2.72087/  ! lake area by depth from top to bottom [hectares]  
      ! parameter (cdrn = 0.85e-3)       ! neutral drag coefficient [unitless]
      ! parameter (eta = 0.15)           ! shortwave extinction coefficient through water [1/m]
      parameter (alb_slush = 0.4)     ! albedo of melting snow [unitless]
      parameter (alb_snow = 0.7)      ! albedo of non-melting snow [unitless]
      parameter (nzsed = 2)          ! number of sediment layers [count]
      parameter (alb_sed = -999)       ! albedo of lake sediment [unitless]
      parameter (csed = -999)        ! specific heat of sediment [J/m3K]
      parameter (condsed = -999)       ! thermal conductivity of sediment [J/smK]
	  parameter (mixfact = 1000.)        ! multiplication factor for eddy diffusivity for deep lakes

! initial conditions
      parameter (nzlk_begin = 92)     ! number of lake layers to begin [count] 
      real salty_begin(nzlk_begin)
      data salty_begin /92*0.0/       ! lake salinity by depth from top to bottom [ppt]
      real tlake_begin(nzlk_begin)
      data tlake_begin /92*8.0/       ! lake temperature by depth from top to bottom [degrees C]
      real tsed_begin(nzsed)
      data tsed_begin /2*8.0/        ! sediment temperature by depth from top to bottom [degrees C]

!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
!     Simulation-specific parameters **CHANGE THESE IF NECESSARY**
!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

      parameter (readdt = 60.*60.)     ! frequency of input reads [seconds]
      parameter (oblq = 23.4)              ! Earth's obliquity [degrees]
      parameter (nspin = 4)               ! model spin-up [years]
      parameter (z_screen = 2.0)           ! height of temperature and humidity inputs [meters]
      parameter (u_screen = 10.0)          ! height of wind input [meters]	  

      parameter (bndry_flag = .false.)     ! is explicit boundary layer computation needed (i.e., input is sigma level)?
      parameter (sigma = 0.96)             ! sigma level when boundary flag is true [unitless]
      parameter (K_flag = .true.)          ! is temperature input in degrees Kelvin?
      parameter (rh_flag = .true.)        ! is humidity input in relative humidity?
      parameter (q_flag = .false.)         ! is humidity input in specific humidity?
      parameter (dp_flag = .false.)         ! is humidity input in dewpoint?
	  
	  parameter (endiff_flag = .true.)     ! use Fang and Stefan (1996) enhanced diffusivity?

      parameter (wb_flag = .false.)        ! calculate lake water balance?
      parameter (ice_flag = .true.)        ! calculate variable ice cover?
      parameter (s_flag = .false.)         ! calculate variable salinity?
      parameter (sed_flag = .false.)       ! calculate sediment temperature profile?

!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
!     Other parameters **DO NOT CHANGE** without good reason 
!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

      parameter (dz = 1.0)                ! vertical layer thickness [m]
      parameter (surf = 1.0)              ! vertical layer thickness of top layer [m]
      parameter (dt = 60.*30.)            ! model time step [seconds]
      parameter (zo = 0.0004)             ! water surface roughness length [m]
      parameter (delta = 5.67e-8)         ! Stefan-Boltzmann constant [W/mK4]
      parameter (rhowat = 1000.)          ! density of water [kg/m3]
      parameter (rhosnow = 330.)          ! density of snow  [kg/m3]
      parameter (rhoice = 917.)           ! density of ice   [kg/m3]
      parameter (snowcut = 2.2)           ! air temperature at which precipitation is snow [degrees C]
      parameter (cpair = 1.00464e3)       ! specific heat capacity of dry air [J/kgK]
      parameter (rair = 287.05)           ! specific gas constant of dry air [J/kgK]
      parameter (rvap = 461.495)          ! specific gas constant of water vapor [J/kgK]
      parameter (cvap = 1.81e3)           ! specific heat capacity of water vapor [J/kgK]
      parameter (Le = 2.45e6)             ! latent heat of vaporization for water [J/kg]
      parameter (Lei = 2.5e6)             ! latent heat of vaporization for ice [J/kg]
      parameter (ca = 6.11e2)             ! constant for Tetens equation [unitless]
      parameter (cb = 273.16)             ! constant for Tetens equation [unitless]
      parameter (c72 = 17.269)            ! constant for Tetens equation over water [unitless]
      parameter (c73 = 35.86)             ! constant for Tetens equation over water [unitless]
      parameter (c70 = 21.874)            ! constant for Tetens equation over ice [unitless]
      parameter (c71 = 7.66)              ! constant for Tetens equation over ice [unitless]
      parameter (emis = 0.97)             ! longwave emissivity [unitless]
      parameter (fusion=3.34e5)           ! latent heat of fusion [J/kg]
      parameter (fracmin = 0.01)          ! minimum ice thickness [m]
      parameter (fraclim = 0.02)          ! minimum ice fraction [fraction]
      parameter (cpw_ice = 4200.)         ! specific heat capacity of water for ice calculations [J/kgK]
      parameter (condw = 0.58)            ! thermal conductivity of water [W/mK]
      parameter (beta = 0.0)              ! shortwave absorbed in water surface layer [fraction]
      parameter (fsol1 = 0.5)             ! sw weighting for surface albedo [fraction]
      parameter (fsol2 = 0.5)             ! lw weighting for surface albedo [fraction]
      parameter (sical0 = 0.6)            ! shortwave albedo for ice [unitless]
      parameter (sical1 = 0.4)            ! longwave albedo for ice [unitless]
      parameter (kv = 0.4)                ! von Karman constant [unitless]
      parameter (dm = 1.38889E-07)        ! thermal molecular diffusivity of water [m2/s]
      parameter (pi = 3.141592654)        ! pi [unitless]
      parameter (snocrit = 0.05)          ! snow depth at which surface albedo is snow albedo [m]
      parameter (lamisw = 3.0)            ! shortwave extinction coefficient through ice [1/m]
      parameter (lamilw = 20.)            ! longwave extinction coefficient through ice [1/m]
      parameter (lamssw = 3.0)            ! shortwave extinction coefficient through snow [1/m]
      parameter (lamslw = 20.)            ! longwave extinction coefficient through snow [1/m]
      parameter (afrac1 = 0.7)            ! light in shortwave band for ice model [fraction]
      parameter (afrac2 = 0.3)            ! light in longwave band for ice model [fraction]
      parameter (condi = 2.3)             ! thermal conductivity of ice [W/mK]
      parameter (conds = 0.31)            ! thermal conductivity of snow [W/mK]
      parameter (raddeg = 0.0174533)      ! radians per degree
      parameter (dpd = 360./365.)         ! degrees per day
      parameter (grav = 9.80616)          ! gravity [m/s2]

!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
!     Common block variables
!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

      integer nzlk_a
      real tsed_a, dfrac_a, tice_a, hice_a
      real hsnow_a, salty_a, mixmax_a, fraci_a, tlake_a
      logical snow_flag_a, melt_flag_a, hour_flag	  
	  
      real tsurf_ave, fice_ave, tsed_ave, evap_ave, hice_ave
      real hsnow_ave, runout_sum, temp_ave
      integer mix_ave

      common nzlk_a                 ! number of lake layers [count]
      common tsed_a(nzsed)          ! temperature of sediment layers [degrees C]
      common dfrac_a                ! fraction of lake depth above/below top lake layer [m]
      common tice_a                 ! temperature of lake ice [degrees C]
      common hice_a                 ! ice thickness [m]
      common hsnow_a                ! snow on ice thickness [m]
      common salty_a(max_dep)       ! lake salinity [ppt]
      common mixmax_a               ! maximum value of lake layer to which mixing occurs over one day of simulation [count] 
      common fraci_a                ! lake ice cover [fraction] 
      common tlake_a(max_dep)       ! lake water temperature averaged across open water and ice covered columns [degrees C]
      common snow_flag_a            ! is snow present on ice?
      common melt_flag_a            ! are snow and ice melting?
      common hour_flag              ! is meteorological input sub-daily?

      common mix_ave                ! average lake layer to which mixing occurs across multiple dt [count]
      common tsurf_ave              ! average lake surface temperature across multiple dt [degrees C]
      common fice_ave               ! average ice fraction across multiple dt [fraction]
      common tsed_ave(nzsed)        ! average sediment temperature across multiple dt [degrees C]
      common evap_ave               ! average lake evaporation across multiple dt [mm/s]
      common hice_ave               ! average ice thickness across multiple dt [m]
      common hsnow_ave              ! average snow thickness across multiple dt [m]
      common runout_sum             ! sum of lake discharge across multiple dt [m3]
      common temp_ave(max_dep)      ! average lake temperature across multiple dt [degrees C]
 