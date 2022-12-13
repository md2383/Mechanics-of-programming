#!/bin/bash
# A sample welcome Bash script

echo 'My home path is: ' $PATH

echo 'Files in my HOME:'
tree -a . 

mkdir temp$$

cd temp$$

mkdir Courses

cd Courses

mkdir cs243

echo 'My tdmp folder: '

echo ""

echo "Translation steps: "
echo "1. Print Files in 'Home' Directory"
echo "2. Create temporary subdirectory"
echo "3. Create subdirectory 'Courses' under the temp directory"
echo "4. Create Subdirectory 'cs243' under 'Courses'"
echo "5. Print 'My Temp folder'"

echo "Warning flags: " $?
echo "C dialect flags: " $?
echo "Debug flags required: " $?
echo "LoginId: " $USER

exit
