#/bin/bash

project_folder=( `pwd` )
build_folder=${project_folder}/../build-Urim-Release
dll_folder=${project_folder}/../urim-dlls
app_name=Urim

#echo $project_folder
#echo $build_folder
#echo $dll_folder

echo "Version:"
read version

if [ "${version}" == "" ]; then
	echo "No version given"
	exit 1
fi

package_folder=${app_name}_v${version}
cd ${build_folder}
mkdir ${package_folder}
cp ./app/release/${app_name}.exe ${package_folder}
cp ./core/release/core.dll ${package_folder}
cp ./gui/release/gui.dll ${package_folder}
cp ${dll_folder}/* ${package_folder}/

windeployqt ${package_folder}/${app_name}.exe

echo ""
echo "Done"
