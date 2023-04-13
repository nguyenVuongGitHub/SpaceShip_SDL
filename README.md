# SpaceShip_SDL



cách build bằng terminal:
- mở terminal tới đường dẫn hiện tại vd: D:\IT\SpaceShip_SDL>
- gõ lệnh sau : g++ -I src/include  -L src/lib -o src/ " file name " src/ " file name ".c -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
+ vd : 
g++ -I src/include  -L src/lib -o src/main src/main.c -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

- gõ tiếp lệnh : ./src/ " file name ".exe 
+ vd : 
./src/main.exe
