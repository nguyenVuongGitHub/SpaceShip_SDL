# SpaceShip_SDL



cách build bằng terminal:
+ mở terminal tới đường dẫn hiện tại vd: D:\IT\SpaceShip_SDL>
+ gõ lệnh sau : g++ -I src/include  -L src/lib -o src/<fileBienDich> src/<fileBienDich>.c -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
vd : g++ -I src/include  -L src/lib -o src/main src/main.c -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
    g++ -I src/include  -L src/lib -o src/test src/test.c -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
+ gõ tiếp lệnh : ./src/<fileBienDich>.exe 
vd : ./src/main.exe
     ./src/test.exe   

