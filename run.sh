#!/bin/bash
cd server_remoteLoginSystem
make clean
echo "------------------------------------server------------------------------------" > ../runError.txt
make 2>>../runError.txt
cd ../client_remoteLoginSystem
make clean
echo "------------------------------------client------------------------------------" >> ../runError.txt
make 2>>../runError.txt
cd ..
less runError.txt
