#Powershell script
#=================================================================

cd Parameter-files
gfortran -o parameter writeParameter.f90
cd ..

$j=38
while($j -le 38){
	cd Parameter-files
    Set-Content .\row.txt "$j"
    ./parameter.exe
    Get-Content lake.inc.save,fort.23 | Set-Content lake.inc
    mv lake.inc ..
    cd ..
	
	cd met-input-files
	$files = Get-ChildItem *.txt
	foreach ($k in $files){ Copy-Item $k "met-input.txt"
		$name = $k.BaseName
		echo "Running parameter combination = $j , Met-input = $name"
		mv met-input.txt ..
		cd ..
    
		gfortran -c *.f90
		gfortran -o lake *.o
		./lake.exe
		mv profile.dat profile-"$j"-"$name".txt
        mv surface.dat surface-"$j"-"$name".txt
		rm met-input.txt
		echo "Next."
		echo ""
		cd met-input-files
    }
	cd ..
	rm lake.inc
	$j++
echo "Done!"
}   
 
