# Lake energy balance response to 21st century warming in the tropical high Andes
A repository for "Lake energy balance response to 21st century warming in the tropical high Andes" (Global and Planetary Change).

Citation:
Sae-Lim, J., Konecky, B.L., Morrill, C., Michelutti, N., Grooms, C., and Smol, J.P. Lake energy balance response to 21st century warming in the tropical high Andes. Global and Planetary Change. 248(6 PART 2):104741 DOI: 10.1016/j.gloplacha.2025.104741

## Abstract
The response of Andean high-alpine lakes (>4,000 m above sea level) to atmospheric warming is poorly understood, in part due to a lack of long-term limnological and meteorological observations. Here, we use in situ, reanalysis, satellite-derived data, and climate modeling output data paired with a one-dimensional lake energy balance model to investigate the response of lake thermal properties to observed and projected 21st century warming in the tropical high Andes of Peru. The lake model configuration is based on Lake Sibinacocha (13.86°S, 71.02°W, 4,860 m a.s.l.), the largest high-alpine lake in the Andes and one of the few such lakes with temperature observations sufficient for model calibration. Relationships between recent air and lake temperature changes were investigated using the model forced with 21st-century ERA5-Land climate reanalysis data, CERES satellite-based observations, and future relationships were investigated using two CMIP6 future climate scenarios with CESM2 (SSP2-4.5 and SSP5-8.5). Results show that Sibinacocha whole-lake average temperature stayed relatively consistent between 2000 and 2023 due to high interannual variability. Lake Sibinacocha temperatures also display interannual variability that aligns with air temperature variations, suggesting that broad climatic teleconnections that affect Andean air temperatures also influence lake temperature and stratification. Under the SSP2-4.5 and SSP5-8.5 scenarios, the model indicates an acceleration of Lake Sibinacocha’s whole-lake warming rate. By 2091-2100, Lake Sibinacocha is projected to increase 2.5 °C to 5.9 °C. Lake Sibinacocha is projected to warm unevenly, with greater warming in the top 20 m and austral spring, contributing to increased weak stratification in spring. Lake Sibinacocha is anticipated to respond more slowly to warming simply due to its large size. Therefore, our results should be considered a conservative end-member for other lakes in the tropical high Andes, which, due to their shallower sizes, will likely respond more quickly to atmospheric warming.

## Highlights
-	Sub-seasonal to seasonal lake thermal properties are well simulated by 1-D lake energy balance model.
-	High interannual temperature variability at Lake Sibinacocha overwhelms any possible warming signal from 2000-2023.
-	The whole-lake warming rate will accelerate mid-century under SSP2-4.5 and SSP5-8.5 scenarios.
-	Sibinacocha is projected to warm unevenly, with greater warming expected in spring.
-	Future warming will likely drive shifts in lake ecosystems throughout the Andes.

## Notes
- Lake temperature observation data used for data calibration and validation are provided by Neal Michelutti (Queen's University). 
- Weather observation data used for data bias correction are provided by SENAMHI (https://www.senamhi.gob.pe/?&p=estaciones; air temperature, relative humidity, wind speed), and Douglas Hardy (UMass Amherst; radiation data)
- We use ERA5-Land dataset, CERES, and CMIP6 CESM2 SSP2-4.5, SSP5-8.5, and historical which can be found at https://cds.climate.copernicus.eu/cdsapp#!/dataset/reanalysis-era5-land?tab=overview, https://ceres.larc.nasa.gov/, and https://www.cesm.ucar.edu/models/cesm2, respectively.
- The model used in this research can be found at https://github.com/carriemorrill/lake-model.
- Specific parameters used in the lake model are under the Part-1-calibration folder (lake.inc).
- 100 combinations of ETA and CDRN used during the calibration can be found in the Part-1-calibration folder (lake-params.txt).
- The 1-D lake model codes are excerpted and modified from https://github.com/carriemorrill/lake-model (Morrill et al., 2019).
