make clean
rm output.txt
make
echo ""
echo "Running... writing to output.txt"
bin/main input.txt > output.txt
echo "Done!"
