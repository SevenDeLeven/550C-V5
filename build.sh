if ! [ "$1" == "" ]
then
if [ "$1" == "quick" ]
then
prosv5 make
sudo prosv5 upload
fi #If arg1 is quick
if [ "$1" == "autonomous" ]
then
rm bin/autonomous.cpp.o
prosv5 make
sudo prosv5 upload
fi #If arg1 is autonomous	
fi #If not arg1 is empty
