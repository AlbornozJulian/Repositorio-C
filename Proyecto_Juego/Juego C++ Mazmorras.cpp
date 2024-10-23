#include <iostream>   //cout<< , <<end y cin>>.
#include <conio.h>    //Para la instruccion getch().
#include <cstring>    //Para la instruccion string.
#include <windows.h>  //Para la funcion gotoxy.
#include <ctime>      //Para generar números aleatorios, intrucciones srand y rand
//Matriz 1
#define V 41  //Altura de la matriz de submenu
#define H 128 //Ancho de la matriz de submenu
//Matriz 2
#define C 23  //Altura de la matriz del Juego
#define F 80  //Ancho de la matriz del Juego
//Matriz 3
#define I 8   // Altura de la matriz del Puente
#define J 2   // Ancho de la matriz del Puente
using namespace std;
//Estructura de registro
struct jugador{
	int num;
	string nombre;
	int vida;
	int vidaFull;
	int ataque;
    int defensa;
	int x,y;        //Posicion
	int modX,modY;  //Modificadores
	char imagen;
};
struct npc{
    int num;
    string nombre;
    int vida;
	int ataque;
    int defensa;
    int x,y;        //Posición
    int modX,modY;  //Modificadores
    char imagen;
};
//Estructura de la monedas
struct pun{
	int x,y;//Posición
};
//Declaracion global
jugador personaje[2];
npc enemigo[3];
pun dinero;
int puntaje=0;
int siguienteNivel=0;               //0 Nivel 1, 1 Nivel 2, etc
bool personajeSeleccionado=false;   //False para aventurero, true para elfo
bool dificultadSeleccionado=false;  //False para normal, true para dificil
char direccion = 'w';               //Dirección inicial del movimiento
//Funciones
//Diseño de la pantalla
void desactivar_Maximizar();
void gotoxy(int,int);
void recuadro(int,int,int,int);
void centrar_Texto(const char*,int);
//Carga entidades
void personajes();
void enemigos();
//Menu
void Menu();
void portada(char campo[V][H]);
//Matriz
void carga_Matriz(char campo[V][H]);
void dibujo_Titulo(char campo[V][H]);
void dibujo(char campo[V][H]);
void dibujo2(char campo[C][F]);
void carga_Campo(char campo[V][H]);
//Dibujo de entidades
void dibujo_Aventurero(char campo[V][H],int,int);
void dibujo_Aventurero2(char campo_Peque[C][F],int,int);
void dibujo_Elfo(char campo[V][H],int,int);
void dibujo_Elfo2(char campo_Peque[C][F],int,int);
void dibujo_Ogro(char campo_Peque[C][F],int,int);
void dibujo_Esqueleto(char campo_Peque[C][F],int,int);
void dibujo_Arbol(char campo[V][H],int,int);
void dibujo_Leon(char campo[V][H],int,int);
//Intermediario entre Portada
void selecctorNiveles(char campo_Peque [C][F]);
void pasoNivel();
//Nivel 1
void escenarioBatalla1(char campo_Peque[C][F]);
void movimiento_Enemigos(char campo_Peque[C][F]);
void movimiento_Jugador(char campo_Peque[C][F]);
void recoleccion(char campo_Peque[C][F],int*,int*);
void vidas(char campo_Peque[C][F],int*);
//Nivel 2
void escenarioBatalla2(char campo_Peque[C][F]);
void inicializarTrampas(int puente[I][J]);
void mostrarFila(int);
void carga_Campo3(char campo_Peque[C][F]);
//Nivel 3
void escenarioBatalla3(char campo_Peque[C][F]);
void mostrar_Estadisticas_j();
void mostrar_Estadisticas_e();
void carga_Campo2(char campo_Peque[C][F]);
void turno_Jugador();
void turno_Jefe();
void dibujo_Titulo2(char campo_Peque[C][F]);
void dibujo_Leon2(char campo_Peque[C][F],int,int);
void dibujo_Ataque_leon2(char campo_Peque[C][F],int,int);
void analizarVida(bool*);
void fin_Leon(char campo_Peque[C][F],int,int);

int main(){
	desactivar_Maximizar();
	system("mode con: cols=130 lines=45"); //Cambiar el tamaño de la pantalla
	char campo[V][H];
    personajes();
    enemigos();
    Menu();
    return 0; 
}

void desactivar_Maximizar(){
	HWND consoleWindow;
	consoleWindow = GetConsoleWindow();
	SetWindowLong(consoleWindow,GWL_STYLE,GetWindowLong(consoleWindow,GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
}
void gotoxy(int x,int y){
	HANDLE hcon;
	hcon=GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X=x;
	dwPos.Y=y;
	SetConsoleCursorPosition(hcon,dwPos);
}
void recuadro(int xs,int ys,int xi,int yi){
	int i;
	for (i=xs;i<=xi;i++){
		gotoxy(i,ys);cout<<static_cast<char>(196);
		gotoxy(i,yi);cout<<static_cast<char>(196);	
	}
	for (i=ys;i<=yi;i++){
		gotoxy(xs,i);cout<<static_cast<char>(179);
		gotoxy(xi,i);cout<<static_cast<char>(179);	
	}
	//Simbolos para esquinas
	gotoxy(xs,ys);cout<<static_cast<char>(218);
	gotoxy(xi,ys);cout<<static_cast<char>(191);
	gotoxy(xs,yi);cout<<static_cast<char>(192);
	gotoxy(xi,yi);cout<<static_cast<char>(217);
}
void centrar_Texto(const char *texto,int y){
	int longitud=strlen(texto);
	gotoxy(65-(longitud/2),y);cout<<texto;
}

void carga_Matriz(char campo[V][H]){
    int i,j;
    for(i=0;i<23;i++){
        for(j=0;j<47;j++){
            if(i==0 or i==22){
                campo[i][j]='-';
            }
            else {
                if(j==0 or j==46){
                    campo[i][j]='|';
                }
                else{
                    campo[i][j]=' ';
                }
            }
        }
    }
    for(i=0;i<23;i++){
        for(j=80;j<H;j++){
            if(i==0 or i==22){
                campo[i][j]='-';
            }
            else {
                if(j==80 or j==H-1){
                    campo[i][j]='|';
                }
                else{
                    campo[i][j]=' ';
                }
            }
        }
    }
    //Dibujar una frace en el inicio del juego, dentro de la matriz
    dibujo_Titulo(campo);
    //Fila 1 Arbol
    dibujo_Arbol(campo, 7, 24);
	dibujo_Arbol(campo, 7, 30);
	dibujo_Arbol(campo, 7, 36);
	dibujo_Arbol(campo, 120, 24);
	dibujo_Arbol(campo, 120, 30);
	dibujo_Arbol(campo, 120, 36);
	//Fila 2 Arbol
	dibujo_Arbol(campo, 17, 24);
	dibujo_Arbol(campo, 17, 30);
	dibujo_Arbol(campo, 17, 36);
	dibujo_Arbol(campo, 110, 24);
	dibujo_Arbol(campo, 110, 30);
	dibujo_Arbol(campo, 110, 36);
	//Fila 3 Arbol
	dibujo_Arbol(campo, 27, 24);
	dibujo_Arbol(campo, 27, 30);
	dibujo_Arbol(campo, 27, 36);
	dibujo_Arbol(campo, 100, 24);
	dibujo_Arbol(campo, 100, 30);
	dibujo_Arbol(campo, 100, 36);
	//Leon
	dibujo_Leon(campo, 22, 9);
	dibujo_Leon(campo, 103, 9);
    // Dibujar una frace en el inicio del juego, dentro de la matriz
    dibujo_Titulo(campo);
    //Dibuja un personaje, dentro de la matriz
    if(personajeSeleccionado==false){
		dibujo_Aventurero(campo,62,23);
	}
	else{
		dibujo_Elfo(campo,62,23);
	}
}
void dibujo_Titulo(char campo[V][H]){
    string title = "M A Z M O R R A   D E L   G U A R D I \xB5 N   B L A N C O"; //Devulve un valor de la cantidad de letras de la frase 
    int titleLength = title.length();
    int startCol = (H - titleLength) / 2; //Centrar el título horizontalmente
    for(int i = 0; i < titleLength; i++){
        campo[1][startCol + i] = '>'; //Línea superior del título
        campo[2][startCol + i] = title[i];  // Línea del texto del título
        campo[3][startCol + i] = '<'; //Línea inferior del título
    }
}
void dibujo_Titulo2(char campo_Peque[C][F]){
	int i;
    string title = "C \xB5 M A R A   D E L   J E F E"; //Devulve un valor de la cantidad de letras de la frase 
    int titleLength = title.length();
    int startCol = (F - titleLength) / 2; //Centrar el título horizontalmente
    for(i=0;i<titleLength;i++){
        campo_Peque[1][startCol+i] = '\x01';  //Línea superior del título
        campo_Peque[2][startCol+i] = title[i];  //Línea del texto del título
        campo_Peque[3][startCol+i] = '\x02';  //Línea inferior del título
    }
}

void dibujo(char campo[V][H]){
	int i,j;
    for(i=0;i<V;i++){
        for(j=0;j<H;j++){
            cout<<campo[i][j];
        }
        cout<<"\n";
    }
}
void carga_Campo(char campo[V][H]){
    int i,j;
    for(i=0;i<V;i++){
        for(j=0;j<H;j++){
            if(i==0 or i==V-1){
                campo[i][j]='-';
            }
            else{
                if(j==0 or j==H-1){
                    campo[i][j]='|';
                }
                else{
                    campo[i][j]=' ';
                }
            }
        }
    }
}
void dibujo2(char campo_Peque[C][F]){
	int i,j;
    for(i=0;i<C;i++){
        for(j=0;j<F;j++){
            cout<<campo_Peque[i][j];
        }
        cout<<"\n";
    }
}
void carga_Campo2(char campo_Peque[C][F]){
    int i,j;
    for(i=0;i<C;i++){
        for(j=0;j<F;j++){
            if(i==0 or i==C-1){
            	campo_Peque[i][j]='-';
            }
            else {
                if(j==0 or j==F-1){
                    campo_Peque[i][j]='|';
                }
                else{
                    campo_Peque[i][j]=' ';
                }
            }
        }
    }
}

void dibujo_Aventurero(char campo[V][H],int posX,int posY){
    campo[posY][posX] = '+';           //Cabeza
    campo[posY + 1][posX] = '|';       //Cuerpo
    campo[posY + 2][posX - 1] = '/';   //Pierna izquierda
    campo[posY + 2][posX + 1] = '\\';  //Pierna derecha
    campo[posY + 1][posX - 1] = '/';   //Brazo izquierdo
    campo[posY + 1][posX + 1] = '\\';  //Brazo derecho
    campo[posY + 1][posX + 2] = '^';   //Mango espada
    campo[posY][posX + 2] = '|';       //Espada
}
void dibujo_Elfo(char campo[V][H],int posX,int posY){
    campo[posY][posX-1] = '-';         //Oreja izquierda
    campo[posY][posX+1] = '-';         //Oreja derecha
    campo[posY][posX] = '&';           //Cabeza
    campo[posY + 1][posX] = '|';       //Cuerpo
    campo[posY + 1][posX - 1] = '/';   //Brazo izquierdo
    campo[posY + 1][posX + 1] = '\\';  //Brazo derecho
    campo[posY + 2][posX-1] = '/';     //Pierna izquierda
    campo[posY + 2][posX + 1] = '\\';  //Pierna derecha
    campo[posY + 1][posX + 2] = '|';   //Base arco
	campo[posY + 1][posX + 3] = ')';   //Cuerda arco
}
void dibujo_Aventurero2(char campo_Peque[C][F],int posX,int posY){
    campo_Peque[posY][posX] = '+';           //Cabeza
    campo_Peque[posY + 1][posX] = '|';       //Cuerpo
    campo_Peque[posY + 2][posX - 1] = '/';   //Pierna izquierda
    campo_Peque[posY + 2][posX + 1] = '\\';  //Pierna derecha
    campo_Peque[posY + 1][posX - 1] = '/';   //Brazo izquierdo
    campo_Peque[posY + 1][posX + 1] = '\\';  //Brazo derecho
    campo_Peque[posY + 1][posX + 2] = '^';   //Mango espada
    campo_Peque[posY][posX + 2] = '|';       //Espada
}
void dibujo_Elfo2(char campo_Peque[C][F],int posX,int posY){
    campo_Peque[posY][posX-1] = '-';         //Oreja izquierda
    campo_Peque[posY][posX+1] = '-';         //Oreja derecha
    campo_Peque[posY][posX] = '&';           //Cabeza
    campo_Peque[posY + 1][posX] = '|';       //Cuerpo
	campo_Peque[posY + 1][posX - 1] = '/';   //Brazo izquierdo
    campo_Peque[posY + 1][posX + 1] = '\\';  //Brazo derecho
    campo_Peque[posY + 2][posX-1] = '/';     //Pierna izquierda
    campo_Peque[posY + 2][posX + 1] = '\\';  //Pierna derecha
    campo_Peque[posY + 1][posX + 2] = '|';   //Base arco
	campo_Peque[posY + 1][posX + 3] = ')';   //Cuerda arco
}
void dibujo_Ogro(char campo_Peque[C][F], int posX,int posY){
    campo_Peque[posY][posX - 1] = '"';       //Oreja izquierda
    campo_Peque[posY][posX + 1] = '"';       //Oreja derecha
    campo_Peque[posY][posX] = '@';           //Cabeza
    campo_Peque[posY + 1][posX] = '|';       //Cuerpo
    campo_Peque[posY + 2][posX - 1] = '/';   //Pierna izquierda
    campo_Peque[posY + 2][posX + 1] = '\\';  //Pierna derecha
    campo_Peque[posY + 1][posX - 1] = '/';   //Brazo izquierdo
    campo_Peque[posY + 1][posX + 1] = '\\';  //Brazo derecho
    campo_Peque[posY + 1][posX + 2] = '|';   //Mango maza
    campo_Peque[posY][posX + 2] = '*';       //Trinchadora con cuchillas
}
void dibujo_Esqueleto(char campo_Peque[C][F],int posX,int posY){
    campo_Peque[posY][posX] = '!';           //Cabeza
    campo_Peque[posY + 1][posX] = '|';       //Cuerpo
    campo_Peque[posY + 2][posX - 1] = '/';   //Pierna izquierda
    campo_Peque[posY + 2][posX + 1] = '\\';  //Pierna derecha
    campo_Peque[posY + 1][posX - 1] = '/';   //Brazo izquierdo
    campo_Peque[posY + 1][posX + 1] = '\\';  //Brazo derecho
    campo_Peque[posY + 1][posX + 2] = '|';   //Base arco
    campo_Peque[posY + 1][posX + 3] = ')';   //Cuerda arco
}

void dibujo_Arbol(char campo[V][H],int posX,int posY){
	campo[posY-1][posX-1] = '/'; 
	campo[posY-1][posX+1] = '\\';
	campo[posY][posX+1] = '\\'; 
	campo[posY][posX-1] = '/'; 
	campo[posY][posX+2] = '\\'; 
	campo[posY][posX-2] = '/'; 
    campo[posY+1][posX - 2] = '/';        
    campo[posY+1][posX + 2] = '\\';
    campo[posY+2][posX - 2] = '/';
    campo[posY+2][posX + 2] = '\\';
    campo[posY+1][posX - 3] = '/';        
    campo[posY+1][posX + 3] = '\\';
    campo[posY+2][posX - 3] = '/';
    campo[posY+2][posX + 3] = '\\';
    campo[posY+1][posX-1] = '|';
    campo[posY+1][posX+1] = '|';
	campo[posY+2][posX+1] = '|'; 
	campo[posY+2][posX-1] = '|'; 
    campo[posY+3][posX-1] = '|';
	campo[posY+3][posX+1] = '|';    
    campo[posY+3][posX-2] = '_'; 
	campo[posY+3][posX+2] = '_';   
	campo[posY+1][posX] = '='; 
	campo[posY+2][posX] = '='; 
    campo[posY+3][posX] = '=';
}
void dibujo_Leon(char campo[V][H],int posX,int posY){
	campo[posY-3][posX+11] = '\\';
	campo[posY-3][posX-9] = '/';
	campo[posY-4][posX+1] = '_';
	campo[posY-4][posX+2] = '_';
	campo[posY-4][posX+3] = '_';
	campo[posY-4][posX+4] = '_';
	campo[posY-4][posX+5] = '_';
	campo[posY-4][posX+6] = '_';
	campo[posY-4][posX+7] = '_';
	campo[posY-4][posX+8] = '_';
	campo[posY-4][posX+9] = '_';
	campo[posY-4][posX+10] = '_';
	campo[posY-4][posX-8] = '_';
	campo[posY-4][posX-7] = '_';
	campo[posY-4][posX-6] = '_';
	campo[posY-4][posX-5] = '_';
	campo[posY-4][posX-4] = '_';
	campo[posY-4][posX-3] = '_';
	campo[posY-4][posX-2] = '_';
	campo[posY-4][posX-1] = '_';
	campo[posY-4][posX] = '_';
	campo[posY-2][posX+3] = '0';
	campo[posY-2][posX-1] = '0';
	campo[posY-1][posX+2] = '\\';
    campo[posY-1][posX] = '/';
	campo[posY][posX + 1] = '-';
    campo[posY][posX] = '\\';
    campo[posY][posX + 2] = '/';
    campo[posY+1][posX+1] = '|';
    campo[posY+2][posX+2] = '\\';
    campo[posY+2][posX] = '/';
    campo[posY+3][posX+2] = '/';
    campo[posY+3][posX] = '\\';
    campo[posY+4][posX+1] = '"';
    campo[posY+2][posX+3] = ')';
    campo[posY+2][posX-1] = '(';
    campo[posY+2][posX+4] = ')';
    campo[posY+2][posX-2] = '(';
    campo[posY+1][posX+4] = '/';
    campo[posY+1][posX-2] = '\\';
    campo[posY][posX+5] = '/';
    campo[posY][posX-3] = '\\';
    campo[posY-1][posX+5] = ')';
    campo[posY-1][posX-3] = '(';
    campo[posY-2][posX+5] = ')';
    campo[posY-2][posX-3] = '(';
    campo[posY-2][posX+7] = '>';
    campo[posY-2][posX-5] = '<';
    campo[posY+5][posX+1] = '_';
    campo[posY+5][posX+3] = '/';
    campo[posY+5][posX-1] = '\\';
    campo[posY+4][posX+5] = ')';
    campo[posY+4][posX-3] = '(';
    campo[posY+3][posX+6] = ')';
    campo[posY+3][posX-4] = '(';
    campo[posY+2][posX+7] = ')';
    campo[posY+2][posX-5] = '(';
    campo[posY+1][posX+8] = ')';
    campo[posY+1][posX-6] = '(';
    campo[posY][posX+9] = ')';
    campo[posY][posX-7] = '(';
    campo[posY-1][posX+10] = ')';
    campo[posY-1][posX-8] = '(';
    campo[posY-2][posX+10] = ')';
    campo[posY-2][posX-8] = '(';
    campo[posY-3][posX+9] = ')';
    campo[posY-3][posX-7] = '(';
}
void dibujo_Leon2(char campo_Peque[C][F],int posX,int posY){
	campo_Peque[posY-4][posX+1] = '_';
	campo_Peque[posY-4][posX+2] = '_';
	campo_Peque[posY-4][posX+3] = '_';
	campo_Peque[posY-4][posX+4] = '_';
	campo_Peque[posY-4][posX+5] = '_';
	campo_Peque[posY-4][posX+6] = '_';
	campo_Peque[posY-4][posX+7] = '_';
	campo_Peque[posY-4][posX+8] = '_';
	campo_Peque[posY-4][posX-6] = '_';
	campo_Peque[posY-4][posX-5] = '_';
	campo_Peque[posY-4][posX-4] = '_';
	campo_Peque[posY-4][posX-3] = '_';
	campo_Peque[posY-4][posX-2] = '_';
	campo_Peque[posY-4][posX-1] = '_';
	campo_Peque[posY-4][posX] = '_';
	campo_Peque[posY-2][posX+3] = '\x04'; //Ojo
	campo_Peque[posY-2][posX-1] = '\x04'; //Ojo
	campo_Peque[posY-1][posX+2] = '\\';
    campo_Peque[posY-1][posX] = '/';
	campo_Peque[posY][posX + 1] = '-';
    campo_Peque[posY][posX] = '\\';
    campo_Peque[posY][posX + 2] = '/';
    campo_Peque[posY+1][posX+1] = '|';
    campo_Peque[posY+2][posX+2] = '\\';
    campo_Peque[posY+2][posX] = '/';
    campo_Peque[posY+2][posX+1] = '='; //Boca
    campo_Peque[posY+3][posX+2] = '/';
    campo_Peque[posY+3][posX] = '\\';
    campo_Peque[posY+4][posX+1] = '"';
    campo_Peque[posY+2][posX+3] = ')';
    campo_Peque[posY+2][posX-1] = '(';
    campo_Peque[posY+2][posX+4] = ')';
    campo_Peque[posY+2][posX-2] = '(';
    campo_Peque[posY+1][posX+4] = '/';
    campo_Peque[posY+1][posX-2] = '\\';
    campo_Peque[posY][posX+5] = '/';
    campo_Peque[posY][posX-3] = '\\';
    campo_Peque[posY-1][posX+5] = ')';
    campo_Peque[posY-1][posX-3] = '(';
    campo_Peque[posY-2][posX+5] = ')';
    campo_Peque[posY-2][posX-3] = '(';
    campo_Peque[posY-2][posX+7] = '>'; //Oreja
    campo_Peque[posY-2][posX-5] = '<'; //Oreja
    campo_Peque[posY+5][posX+1] = '_';
    campo_Peque[posY+5][posX+3] = '/';
    campo_Peque[posY+5][posX-1] = '\\';
    campo_Peque[posY+4][posX+5] = ')';
    campo_Peque[posY+4][posX-3] = '(';
    campo_Peque[posY+3][posX+6] = ')';
    campo_Peque[posY+3][posX-4] = '(';
    campo_Peque[posY+2][posX+7] = ')';
    campo_Peque[posY+2][posX-5] = '(';
    campo_Peque[posY+1][posX+8] = ')';
    campo_Peque[posY+1][posX-6] = '(';
    campo_Peque[posY][posX+9] = ')';
    campo_Peque[posY][posX-7] = '(';
    campo_Peque[posY-1][posX+10] = ')';
    campo_Peque[posY-1][posX-8] = '(';
    campo_Peque[posY-2][posX+10] = ')';
    campo_Peque[posY-2][posX-8] = '(';
    campo_Peque[posY-3][posX+9] = ')';
    campo_Peque[posY-3][posX-7] = '(';
	//Cuello
    campo_Peque[posY+3][posX+7] = '|'; 
    campo_Peque[posY+3][posX-5] = '|';
    campo_Peque[posY+4][posX+7] = '|';
    campo_Peque[posY+4][posX-5] = '|';
    campo_Peque[posY+5][posX+7] = '|';
    campo_Peque[posY+5][posX-5] = '|';
    campo_Peque[posY+6][posX+7] = '\\';
    campo_Peque[posY+6][posX-5] = '/';
}
void dibujo_Ataque_leon2(char campo_Peque[C][F],int posX,int posY){
	campo_Peque[posY-3][posX+1] = '\x04'; //Ojo superio
		//Mano derecha
    campo_Peque[posY+2][posX+15] = '|'; //Garra 
    campo_Peque[posY+2][posX+17] = '|';
    campo_Peque[posY+2][posX+13] = '|';
    campo_Peque[posY+3][posX+15] = '\xDB'; //Dedo
    campo_Peque[posY+3][posX+17] = '\xDB';
    campo_Peque[posY+3][posX+13] = '\xDB';
    campo_Peque[posY+4][posX+15] = '\x0F'; //Huella
    campo_Peque[posY+6][posX+15] = '\x06'; //Adorno
    campo_Peque[posY+4][posX+17] = '|'; //Mano
    campo_Peque[posY+4][posX+13] = '|';
    campo_Peque[posY+5][posX+16] = '/';
    campo_Peque[posY+5][posX+14] = '\\';
    campo_Peque[posY+6][posX+16] = '|'; //Brazo
    campo_Peque[posY+6][posX+14] = '|';
    campo_Peque[posY+7][posX+16] = '|';
    campo_Peque[posY+7][posX+14] = '|';
    campo_Peque[posY+8][posX+16] = '\\';
    campo_Peque[posY+8][posX+14] = '/';
    //Mano izquierda
    campo_Peque[posY+2][posX-15] = '|'; //Garra 
    campo_Peque[posY+2][posX-13] = '|';
    campo_Peque[posY+2][posX-11] = '|';
    campo_Peque[posY+3][posX-15] = '\xDB'; //Dedo
    campo_Peque[posY+3][posX-11] = '\xDB';
    campo_Peque[posY+3][posX-13] = '\xDB';
    campo_Peque[posY+4][posX-13] = '\x0F'; //Huella
    campo_Peque[posY+6][posX-13] = '\x05'; //Adorno
    campo_Peque[posY+4][posX-15] = '|'; //Mano
    campo_Peque[posY+4][posX-11] = '|';
    campo_Peque[posY+5][posX-14] = '\\';
    campo_Peque[posY+5][posX-12] = '/';
    campo_Peque[posY+6][posX-14] = '|'; //Brazo
    campo_Peque[posY+6][posX-12] = '|';
    campo_Peque[posY+7][posX-14] = '|';
    campo_Peque[posY+7][posX-12] = '|';
    campo_Peque[posY+8][posX-14] = '/';
    campo_Peque[posY+8][posX-12] = '\\';
}
void fin_Leon(char campo_Peque[C][F],int posX,int posY){
	campo_Peque[posY+6][posX+1] = '\x03'; //Corazon
}

void personajes(){
	personaje[0].num=1;
	personaje[0].nombre="H U M A N O";
	personaje[0].vida=3;
	personaje[0].vidaFull=150;
	personaje[0].ataque=360;
	personaje[0].defensa=270;
	personaje[0].imagen='+';
	personaje[0].x=20; //F
	personaje[0].y=39; //C
	personaje[1].num=2;
	personaje[1].nombre="E l F O";
	personaje[1].vida=3;
	personaje[1].vidaFull=200;
	personaje[1].ataque=340;
	personaje[1].defensa=250;
	personaje[1].imagen='&';
	personaje[1].x=20; //F
	personaje[1].y=39; //C
}
void enemigos(){
    enemigo[0].num=1;
    enemigo[0].nombre ="O G R O";
    enemigo[0].vida=50;
    enemigo[0].ataque=20;
    enemigo[0].defensa=10;
    enemigo[0].imagen='@';
    enemigo[0].x=20;
    enemigo[0].y=10;
    enemigo[1].num=2;
    enemigo[1].nombre="E S Q U E L E T O";
    enemigo[1].vida=40;
    enemigo[1].ataque=15;
    enemigo[1].defensa=10;
    enemigo[1].imagen='!';
    enemigo[1].x=60;
    enemigo[1].y=10;
    enemigo[2].num = 3;
    enemigo[2].nombre="L E \xE0 N   E C L I P S E";
    enemigo[2].vida=1000;
    enemigo[2].ataque=310;
    enemigo[2].defensa=500;
    enemigo[2].imagen='#';
    enemigo[2].x=38; //C
    enemigo[2].y=8;  //F
}

void Menu(){
    char campo[V][H];
    int Op;
    do{
    	//Marcos del Menu
		recuadro(0,0,127,42);
		recuadro(1,1,126,3);
        system("COLOR 37");//Cambia el color de la pantalla
        centrar_Texto("M A Z M O R R A   D E L   G U A R D I \xB5 N   B L A N C O",2);//Titulo
        gotoxy(2,4);cout<<">> Seleccione una Opci\xA2n: [1-6]";
        gotoxy(2,6);cout<<"<< I N I C I O......................[1]"<<endl;
        gotoxy(2,8);cout<<"<< D I F I C U L T A D A D..........[2]"<<endl;
        gotoxy(2,10);cout<<"<< P E R S O N A J E................[3]"<<endl;
        gotoxy(2,12);cout<<"<< P A R T I D A S..................[4]"<<endl;
        gotoxy(2,14);cout<<"<< I D I O M A......................[5]"<<endl;
        gotoxy(2,16);cout<<"<< S A L I R........................[6]"<<endl;
        gotoxy(2,18);cin>>Op;
        switch(Op){
            case 1:{
            	portada(campo);
            	system("cls");
                break;
            }
            case 2:{
            	int dif;
            	char si='s'; 
            	do{
            		system("cls");
            		//Marcos del Menu
					recuadro(0,0,127,42);
					recuadro(1,1,126,3);
					system("COLOR C0");//Cambia el color de la pantalla
            		centrar_Texto("M A Z M O R R A   D E L   G U A R D I \xB5 N   B L A N C O",2);//Titulo
            		gotoxy(2,4);cout<<">> Niveles de Dificultad: ";
            		gotoxy(2,6);cout<<"1...N O R M A L";
            		gotoxy(2,8);cout<<"2...D I F I C \xD6 L";
            		gotoxy(2,10);cout<<"Seleccione una dificultad:  [1-2]";
            		gotoxy(2,11);cin>>dif;
            		if(dif==1){
            			gotoxy(2,13);cout<<"<< Has seleccionado la Dificultad NORMAL";
            			dificultadSeleccionado=false;
					}
					else{
						gotoxy(2,13);cout<<"<< Has seleccionado la Dificultad DIFIC\xD6L";
						dificultadSeleccionado=true;
					}
					gotoxy(2,15);cout<<"<< Para regresar al Men\xA3, presione: (s)";
					gotoxy(2,16);cout<<">> Caso contrario, presione: (n)";
					gotoxy(2,17);cin>>si;
				}while(si!='s');
                system("cls");
                break;
            }
            case 3:{
            	int i,per,fila;
            	char si='s';
            	do{
            		fila=8;
            		system("cls");
            		//Marcos del Menu
					recuadro(0,0,127,42);
					recuadro(1,1,126,3);
            		system("COLOR 27");//Cambia el color de la pantalla
            		centrar_Texto("M A Z M O R R A   D E L   G U A R D I \xB5 N   B L A N C O",2);//Titulo
            		gotoxy(2,4);cout<<">> Los personajes disponibles son:";
            		gotoxy(2,6);cout<<"N U M E R O        N O M B R E        V I D A        D E F E N S A        A T A Q U E        I M A G E N";
            		gotoxy(2,7);cout<<"---------------------------------------------------------------------------------------------------------";
					for(i=0;i<2;i++){
            			gotoxy(7,fila);cout<< personaje[i].num;
            			gotoxy(21,fila);cout<< personaje[i].nombre;
						gotoxy(42,fila);cout<< personaje[i].vidaFull;
						gotoxy(60,fila);cout<< personaje[i].defensa;
						gotoxy(80,fila);cout<< personaje[i].ataque;
						gotoxy(100,fila);cout<< personaje[i].imagen;
						fila++;
					}
					gotoxy(2,12);cout<<">> Seleccione un personaje:  [1-2]";
					gotoxy(2,13);cin>>per;
					if (per==1){
						gotoxy(2,15);cout<<"<< Has seleccionado al HUMANO";
						personajeSeleccionado=false;
					}
					else{
						gotoxy(2,15);cout<<"<< Has seleccionado al ELFO";
						personajeSeleccionado=true;
					}	
					gotoxy(2,18);cout<<"<< Para regresar al Men\xA3, presione: (s)";
					gotoxy(2,19);cout<<">> Caso contrario, presione: (n)";
					gotoxy(2,20);cin>>si;
				}while(si!='s');
				system("cls");
                break;
            }
            case 4:{
            	gotoxy(2,30);cout<<"P R O X I M A M E N T E...";
            	getch();
            	system("cls");
                break;
            }
            case 5:{
            	gotoxy(2,30);cout<<"P R O X I M A M E N T E...";
            	getch();
            	system("cls");
                break;
            }
            case 6:{
            	gotoxy(2,30);cout<<"C E R R A N D O   J U E G O...";
            	getch();
            	system("cls");
				break;
			}
            default:{
                gotoxy(2,36);cout<<">> Opci\xA2n Incorrecta!!!.";
                gotoxy(2,37);cout<<"<< Vuelva a Ingresar la Opci\xA2n!!!.";
                getch();
                system("cls");
                break;
            }    
        }         
    }while(Op!=6);
}
void portada(char campo[V][H]){
	char campo_Peque[C][F];
	int i;
	char si='s';
	bool aux=false;
	do{
		//Reinicio despues de completar el juego
		if(siguienteNivel == 3){
			siguienteNivel=0;
		}
		if(aux==false){
			//Barra de carga
			centrar_Texto("C A R G A N D O...", 40);
			for(i=3;i<=124;i++){
				gotoxy(i,41);cout<<static_cast<char>(177);
			}
			for(i=3;i<=124;i++){
				gotoxy(i,41);cout<<static_cast<char>(219);
				Sleep(35);//Milisegundos 1000==1 segundo
			}
			aux=true;
		}
        system("cls");
	    system("COLOR F0");//Cambia el color de la pantalla
	    carga_Campo(campo);
	    carga_Matriz(campo);
	    dibujo(campo);
		cout<<"\t<< Desea regresar al Men\xA3, presione: (s)... >> Para empezar el juego presione: (n).\n";
		cout<<"\t";
		cin>>si;
		//Empieza el Juego
		if(si=='n'){
			selecctorNiveles(campo_Peque);
			system("mode con: cols=130 lines=45");//Cambiar el tamaño de la pantalla
		}		
	}while(si!='s');
	system("cls"); 
}
void selecctorNiveles(char campo_Peque [C][F]){
	system("mode con: cols=82 lines=50");
	//Llamada Niveles
	switch(siguienteNivel){
		case 0:{
			escenarioBatalla1(campo_Peque);
			puntaje=0;
			direccion = 'w';
			personajes();
    		enemigos();
			break;
		}
		case 1:{
			//Inicializa Vida
			if(dificultadSeleccionado == false){
				personaje[0].vida=7;
				personaje[1].vida=7;
				
			}
			else{
				personaje[0].vida=5;
				personaje[1].vida=5;
			}
			carga_Campo3(campo_Peque);
			escenarioBatalla2(campo_Peque);
			
			personajes();
			break;
		}
		case 2:{
			personajes();
    		enemigos();
			escenarioBatalla3(campo_Peque);	
			break;
		}
	}
}
void pasoNivel(){
	//Incrementa para pasar de nivel
	siguienteNivel=siguienteNivel+1;
}

void escenarioBatalla1(char campo_Peque[C][F]){
    int muerte = 0,distancia=5,i;
    srand(time(NULL));//Inicializar posición de la moneda
    dinero.x = rand() % (F-2* distancia) + distancia;
    dinero.y = rand() % (C-2* distancia) + distancia;
    //Bucle del Juego
    while(muerte == 0) {
        carga_Campo2(campo_Peque);
        //Dibujo personajes
        if(personajeSeleccionado==false){
            dibujo_Aventurero2(campo_Peque,personaje[0].y,personaje[0].x);
        } 
		else{
            dibujo_Elfo2(campo_Peque,personaje[1].y,personaje[1].x);
        }
        //Dibujo enemigos
        if(dificultadSeleccionado==false){
            dibujo_Esqueleto(campo_Peque, enemigo[1].x, enemigo[1].y);
        } 
		else{
            dibujo_Ogro(campo_Peque,enemigo[0].x,enemigo[0].y);
        	dibujo_Esqueleto(campo_Peque, enemigo[1].x, enemigo[1].y);
        }
        //Muestra vidas
        if(personajeSeleccionado == false) {
            for(i=0; i<personaje[0].vida;i++) {
            	cout << static_cast<char>(3);
            }
        } else {
            for(i=0;i<personaje[1].vida;i++) {
                cout << static_cast<char>(3);
            }
        }
        campo_Peque[dinero.y][dinero.x] = '$'; //Dibujar la moneda en la pantalla
        system("cls");
        dibujo2(campo_Peque);
        vidas(campo_Peque, &muerte);
        recoleccion(campo_Peque,&muerte,&distancia);
        movimiento_Jugador(campo_Peque);
        movimiento_Enemigos(campo_Peque);
        Sleep(150);
    }
}
void movimiento_Enemigos(char campo_Peque[C][F]){
	int Probabilidad;
	if(dificultadSeleccionado == false){
		Probabilidad = rand() % 10;//Probabilidad del 10%
	    if(Probabilidad < 3){
		    if (personajeSeleccionado){
		        //Seguir al elfo
		        if(enemigo[1].x < personaje[1].y){
		        	enemigo[1].modX=1;
				} 
		        else{
		        	if(enemigo[1].x > personaje[1].y){
		        		enemigo[1].modX=-1;
					}
				}  
		        if(enemigo[1].y < personaje[1].x){
		        	enemigo[1].modY=1;
				} 
		        else{
		        	if(enemigo[1].y > personaje[1].x){
		        		enemigo[1].modY=-1;
					}
				}  
		    } 
			else{
		        //Seguir al humano
		        if(enemigo[1].x < personaje[0].y){
		        	enemigo[1].modX=1;
				} 
		        else{
		        	if(enemigo[1].x > personaje[0].y){
		        		enemigo[1].modX=-1;
					} 
				}
		        if(enemigo[1].y < personaje[0].x){
		        	enemigo[1].modY=1;
				} 
		        else{
		        	if(enemigo[1].y > personaje[0].x){
		        		enemigo[1].modY=-1;
					}
				} 
		    }    
		}	
	}
	else{
		Probabilidad = rand() % 15;//Probabilidad del 15%
	    if(Probabilidad < 5) {
		    if(personajeSeleccionado){
		        //Seguir al elfo
		        if(enemigo[0].x < personaje[1].y){
		        	enemigo[0].modX=1;
				} 
		        else{
		        	if(enemigo[0].x > personaje[1].y){
					enemigo[0].modX=-1;
					} 
				} 
		        if(enemigo[0].y < personaje[1].x){
		        	enemigo[0].modY=1;	
				} 
		        else{
		        	if(enemigo[0].y > personaje[1].x){
					enemigo[0].modY=-1;
					} 
				} 
		    } 
			else {
		        //Seguir al humano
		        if(enemigo[0].x < personaje[0].y){
		        	enemigo[0].modX=1;
				} 
		        else{
		        	if(enemigo[0].x > personaje[0].y){
					enemigo[0].modX=-1;
					} 
				} 
		        if(enemigo[0].y < personaje[0].x){
		        	enemigo[0].modY=1;
				} 
		        else{
			        if(enemigo[0].y > personaje[0].x){
						enemigo[0].modY=-1;
					} 	
				} 
			}
		    if (personajeSeleccionado){
		        //Seguir al elfo
		        if(enemigo[1].x < personaje[1].y){
		        	enemigo[1].modX=1;
				} 
		        else{
		        	if(enemigo[1].x > personaje[1].y){
		        		enemigo[1].modX=-1;
					}
				}  
		        if(enemigo[1].y < personaje[1].x){
		        	enemigo[1].modY=1;
				} 
		        else{
		        	if(enemigo[1].y > personaje[1].x){
		        		enemigo[1].modY=-1;
					}
				}  
		    } 
			else{
		        //Seguir al humano
		        if(enemigo[1].x < personaje[0].y){
		        	enemigo[1].modX=1;
				} 
		        else{
		        	if(enemigo[1].x > personaje[0].y){
		        		enemigo[1].modX=-1;
					} 
				}
		        if(enemigo[1].y < personaje[0].x){
		        	enemigo[1].modY=1;
				} 
		        else{
		        	if(enemigo[1].y > personaje[0].x){
		        		enemigo[1].modY=-1;
					}
				} 
		    }    
		}
	}
    //Actualizar posición del enemigo
    enemigo[0].x +=enemigo[0].modX;
    enemigo[0].y +=enemigo[0].modY;
    enemigo[1].x +=enemigo[1].modX;
    enemigo[1].y +=enemigo[1].modY;
	//Verificación de bordes
    if (enemigo[0].x <= 1 or enemigo[0].x >= F-3){
        enemigo[0].modX = -enemigo[0].modX;  //Cambiar dirección horizontal
    }
    if (enemigo[0].y <= 1 or enemigo[0].y >= C-3){
        enemigo[0].modY = -enemigo[0].modY;  //Cambiar dirección vertical
    }
    if (enemigo[1].x <= 1 or enemigo[1].x >= F-3){
        enemigo[1].modX = -enemigo[1].modX;  //Cambiar dirección horizontal
    }
    if (enemigo[1].y <= 1 or enemigo[1].y >= C-3){
        enemigo[1].modY = -enemigo[1].modY;  //Cambiar dirección vertical
    }
}
void movimiento_Jugador(char campo_Peque[C][F]){
	//Detectar la dirección de movimiento del jugador
    if (kbhit()){
        char key = getch();
        if(key == 'w'){
        	direccion = 'w';
		} 
        if(key == 's'){
        	direccion = 's';
		} 
        if(key == 'a'){
        	direccion = 'a';
		} 
        if(key == 'd'){
        	direccion = 'd';
		} 
    }
    //Mover el jugador en la dirección actual
    if(personajeSeleccionado == false){
        if(direccion == 's' and personaje[0].x < C-3){  //Verificar límite inferior
            personaje[0].x++;
        }
        if(direccion == 'w' and personaje[0].x > 2){    //Verificar límite superior
            personaje[0].x--;
        }
        if(direccion == 'a' and personaje[0].y > 2){    //Verificar límite izquierdo
            personaje[0].y--;
        }
        if(direccion == 'd' and personaje[0].y < F-3){  //Verificar límite derecho
            personaje[0].y++;
        }
    } 
	else{
        if(direccion == 's' and personaje[1].x < C-3){  //Verificar límite inferior
            personaje[1].x++;
        }
        if(direccion == 'w' and personaje[1].x > 2){    //Verificar límite superior
            personaje[1].x--;
        }
        if(direccion == 'a' and personaje[1].y > 2){    //Verificar límite izquierdo
            personaje[1].y--;
        }
        if(direccion == 'd' and personaje[1].y < F-3){  //Verificar límite derecho
            personaje[1].y++;
        }
    }
}
void recoleccion(char campo_Peque[C][F],int* muerte,int* distancia){
    //Verificar si el jugador recoge la moneda
    if (!personajeSeleccionado and campo_Peque[personaje[0].x][personaje[0].y] == '$') {
        puntaje=puntaje+50;
        dinero.x = rand() % (F-2* *distancia) + *distancia;
    	dinero.y = rand() % (C-2* *distancia) + *distancia;
    } 
	else{
		if (personajeSeleccionado and campo_Peque[personaje[1].x][personaje[1].y] == '$') {
	        puntaje=puntaje+50;
	            dinero.x = rand() % (F-2* *distancia) + *distancia;
    			dinero.y = rand() % (C-2* *distancia) + *distancia;
    	}
	} 
    cout<<"\n\n<< Puntaje: " << puntaje <<"\t\t";
    //Condicion de dificultad para pasar de nivel 
    if(dificultadSeleccionado==false){
    	if(puntaje==100){
    		cout<<"\n\n>> Felicidades pasaste de Nivel!!!.";
    		pasoNivel();
    		*muerte = 1;
    		getch();
		}
	}
	else{
		if(puntaje==200){
    		cout<<"\n\n>> Felicidades pasaste de Nivel!!!.";
    		pasoNivel();
    		*muerte = 1;
    		getch();
		}
	}	
}
void vidas(char campo_Peque[C][F],int* muerte){
    //Verificar colision con enemigos
    if((enemigo[0].x == personaje[0].y and enemigo[0].y == personaje[0].x) or (enemigo[1].x == personaje[0].y and enemigo[1].y == personaje[0].x)){
        personaje[0].vida--;//Disminuir la vida del jugador 1 (Humano)
        cout<<"\n\n<< Vida Perdida...";
        getch();
        //Actualizar visualmente las vidas restantes
        cout<<"<< Vidas: "<< personaje[0].vida << "\n ";
        if(personaje[0].vida == 0) {
            *muerte = 1;
            cout<< "\n\n>> Fuiste Derrotado. Suerte la Proxima!!!.";
            getch();
        }
    } 
	else{
		if((enemigo[0].x == personaje[1].y and enemigo[0].y == personaje[1].x) or (enemigo[1].x == personaje[1].y and enemigo[1].y == personaje[1].x)){
	        personaje[1].vida--;//Disminuir la vida del jugador 2 (Elfo)
	        cout<<"\n\n<< Vida Perdida...";
	        getch();
	        //Actualizar visualmente las vidas restantes
	        cout<<"<< Vidas: " << personaje[1].vida << "\n ";
	        if(personaje[1].vida == 0) {
	            *muerte = 1;
	            cout<<"\n\n>> Fuiste Derrotado. Suerte la Proxima!!!.";
	            getch();
	        }
		}	
	}
}

void escenarioBatalla2(char campo_Peque[C][F]){
	int puente[I][J],i,columna,aux=0;
    bool finPuente=false,final=false;
    inicializarTrampas(puente);
	carga_Campo3(campo_Peque);
	//Dibuja Personaje
	if(personajeSeleccionado == false){
	    dibujo_Aventurero2(campo_Peque, personaje[0].y, personaje[0].x);
	} 
	else{
	    dibujo_Elfo2(campo_Peque, personaje[1].y, personaje[1].x);    
	}
	//Muestra la cantidad de Vida
	if(personajeSeleccionado == false){
		cout<<">> Vidas iniciales: " << personaje[0].vida <<endl;
	}
	else{
		cout<<">> Vidas iniciales: " << personaje[1].vida <<endl;
	}    
	//Bucle del Juego
    for (i=0;i<I and final==false;i++){
    	analizarVida(&final);
    	dibujo2(campo_Peque);
	    cout<<" \n" <<endl;
        mostrarFila(aux);
        aux++;
        cout<<"\n\n>> Selecciona una Tabla del Puente: [1|2] \n";
        cout<<"\t";
        cin>>columna;
        if(columna<1 or columna>2){
            cout<<"\n\n<< Saltaste al Acantilado!!!\n";
            //Resta Vida
            if(personajeSeleccionado == false){
			    personaje[0].vida--;
			} 
			else{
				personaje[1].vida--;  
			}
			getch();
            system("cls");
        }
		else{
        	if(puente[i][columna-1] == 1){ //La posicion es 1 (Trampa)
            	cout<<"\n\n<< Ca\xA1ste porque la Tabla estaba Floja!!!. Pierdes una Vida...\n";
            	//Resta VIda
            	if(personajeSeleccionado == false){
				    personaje[0].vida--;
				} 
				else{
					personaje[1].vida--;  
				}
				carga_Campo3(campo_Peque);
				//Movimiento de personaje
	            if(personajeSeleccionado == false){
				    personaje[0].x -= 2; // Mover al personaje hacia arriba
				    dibujo_Aventurero2(campo_Peque, personaje[0].y, personaje[0].x);
				} 
				else{
					personaje[1].x -= 2; // Mover al personaje hacia arriba
					dibujo_Elfo2(campo_Peque, personaje[1].y, personaje[1].x);
				}
            	getch();
            	system("cls");
        	}
			else{
	            cout<<"\n\n>> Avanzas sin problema.\n";
	            carga_Campo3(campo_Peque);
	            //Movimiento de personaje
	            if(personajeSeleccionado == false){
				    personaje[0].x -= 2; // Mover al personaje hacia arriba
				    dibujo_Aventurero2(campo_Peque, personaje[0].y, personaje[0].x);
				} 
				else{
					personaje[1].x -= 2; // Mover al personaje hacia arriba
					dibujo_Elfo2(campo_Peque, personaje[1].y, personaje[1].x);
				}
	            getch();
	            system("cls");
        	}	
		}
		 if(personajeSeleccionado == false){
			if(i == I-1 and personaje[0].vida > 0){
             finPuente=true;
        	}
        	cout<<"\n\n<< Vidas restantes: " << personaje[0].vida <<"\n";
		} 
		else{
			if(i == I-1 and personaje[1].vida > 0){
             finPuente=true;
        	}
			cout<<"\n\n<< Vidas restantes: " << personaje[1].vida <<"\n";  
		}  
    }
    if(finPuente == true){
        cout<<"\n\n>> Felicidades pasaste de Nivel!!!.\n";
        pasoNivel();
        getch();
        system("cls");
    } 
	else{
        cout<<"\n\n>> Fuiste Derrotado por el Puente. Suerte la Proxima!!!\n";
        getch();
        system("cls");
    }
}
void carga_Campo3(char campo_Peque[C][F]){
    int i,j;
    for(i=0;i<C;i++){
        for(j=0;j<F;j++){
            if(i==0 || i==C-1){
            	campo_Peque[i][j]='-';
            }
            else {
                if(j==0 || j==F-1){
                    campo_Peque[i][j]='|';
                }
                else{
                    campo_Peque[i][j]=' ';
                }
            }
            if(j==46){
            	campo_Peque[i][j]=')';
            	
       	 	}
        	if(j==32){
        		campo_Peque[i][j]='(';
        	}
        }
    }  
}
void inicializarTrampas(int puente[I][J]){
	int i,j,trampa;
    srand(time(0));
    for(i=0;i<I;i++){
        trampa = rand() % J; //Eleccion aleatoria
        for(j=0;j<J;j++) {
            puente[i][j] = (j == trampa) ? 1 : 0; //Operador Ternario
        }
    }
}
void mostrarFila(int aux){
	int j;
    cout<<">> Escal\xA2n " << aux+1 << ": ";
    for(j=0;j<J; j++){
        cout << "[ ] ";
    }
}

void escenarioBatalla3(char campo_Peque[C][F]){
	//system("cls");
	int A=0,B=0,D=0;
	bool final=false;
	carga_Campo2(campo_Peque);
	dibujo_Titulo2(campo_Peque);
	if (personajeSeleccionado == false) {
        dibujo_Aventurero2(campo_Peque, personaje[0].y, personaje[0].x);
    } 
	else {
        dibujo_Elfo2(campo_Peque, personaje[1].y, personaje[1].x);
    }
	srand(time(0));
	bool turno_Inicial=rand()%2;
	//Bucle del Juego
	while(final == false){
		dibujo_Leon2(campo_Peque,enemigo[2].x,enemigo[2].y);
		if(dificultadSeleccionado == true){
			if(enemigo[2].vida < 500){
				A=1;//Bandera
			}
			if(A==1){
				if(B==0){
					B=1;//Bandera
					cout<<"\n\n>> Esta pasando algo Raro!!!\n";
					cout<<">> Preparate...";
					getch();
					system ("cls");
				}
				dibujo_Ataque_leon2(campo_Peque,enemigo[2].x,enemigo[2].y);
				if(D==0){
					D=1;//Bandera
					enemigo[2].vida=2000;
					enemigo[2].ataque=600;
					enemigo[2].defensa=800;	
				}	
			}
		}
		if(enemigo[2].vida<500){
			fin_Leon(campo_Peque,38,8);
		}
   		dibujo2(campo_Peque);
		mostrar_Estadisticas_j();
		cout<<"\n";
		mostrar_Estadisticas_e();
		cout<<"--------------------------------------------------------------------------------\n";
		if(turno_Inicial){
			turno_Jefe();
		}
		else{
			turno_Jugador();
		}
		analizarVida(&final);
		turno_Inicial=!turno_Inicial; //Alternar el turno
		getch();
		system("cls");	
	}
	if(personajeSeleccionado == false){
		if(personaje[0].vidaFull<=0){
			cout<<"\n\n>> Fuiste Derrotado... Suerte la Proxima!!!\n";
			getch();
		}
		else{
			cout<<"\n\n>> Venciste al Jefe!!!. Felicidades Ganaste!!!\n";
			pasoNivel();
			getch();
		}	
	}
	else{
		if(personaje[1].vidaFull<=0){
			cout<<"\n\n>> Fuiste Derrotado... Suerte la Proxima!!!\n";
			getch();
		}
		else{
			cout<<"\n\n>> Venciste al Jefe!!!. Felicidades Ganaste!!!\n";
			pasoNivel();
			getch();
		}
	}
}
void mostrar_Estadisticas_j(){
	if(personajeSeleccionado == false){
	cout<<">> H U M A N O \n";
	cout<<"\n";
	cout<<"<< A T A Q U E: " << personaje[0].ataque <<"\t";
	cout<<"<< D E F E N S A: " << personaje[0].defensa <<"\t";
	cout<<"<< V I D A: " << personaje[0].vidaFull <<"\n";
	}
	else{
	cout<<">> E L F O \n";
	cout<<"\n";
	cout<<"<< A T A Q U E: " << personaje[1].ataque <<"\t";
	cout<<"<< D E F E N S A: " << personaje[1].defensa <<"\t";
	cout<<"<< V I D A: " << personaje[1].vidaFull <<"\n";
	}
	
}
void mostrar_Estadisticas_e(){
	cout<<">> L E \xE0 N   E C L I P S E \n";
	cout<<"\n";
	cout<<"<< A T A Q U E: " << enemigo[2].ataque <<"\t";
	cout<<"<< D E F E N S A: " << enemigo[2].defensa <<"\t";
	cout<<"<< V I D A: " << enemigo[2].vida <<"\n";
}
void turno_Jugador(){
	if(dificultadSeleccionado == false){
		int eleccion;
		cout<<">> Es tu turno. Elige una movimiento: \n";
		cout<<"\n";
		cout<<"1_ I N C R E M E N T O   D E F E N S A \n";
		cout<<"\n2_ I N C R E M E N T O   A T A Q U E \n";
		cout<<"\n3_ C U R A R S E \n";
		cout<<"\n4_ A T A Q U E \n\n";
		cin>>eleccion;
		switch (eleccion){
	        case 1:{
	        	if(personajeSeleccionado == false){
	        		personaje[0].defensa += 10;
	            	cout<<"\n>> Aumentaste tu defensa en 10 puntos!\n";
				}
				else{
					personaje[1].defensa += 10;
	            	cout<<"\n>> Aumentaste tu defensa en 10 puntos!\n";
				}
				break;
			}
	        case 2:{
	        	if(personajeSeleccionado == false){
	        		personaje[0].ataque += 10;
	            	cout<<"\n>> Aumentaste tu ataque en 10 puntos!\n";
				}
				else{
					personaje[1].ataque += 10;
	            	cout<<"\n>> Aumentaste tu ataque en 10 puntos!\n";
				}
				break;
			} 
	        case 3:{
	        	if(personajeSeleccionado == false){
	        		personaje[0].vidaFull += 20;
	            	cout<<"\n>> Te curaste 20 puntos de vida!\n";
				}
				else{
					personaje[1].vidaFull += 20;
	            	cout<<"\n>> Te curaste 20 puntos de vida!\n";
				}
				break;
			}
	        case 4:{
	        	if(personajeSeleccionado == false){
	        		int golpe = personaje[0].ataque - enemigo[2].defensa;
	            	if (golpe > 0) {
	                enemigo[2].defensa -= personaje[0].ataque;
	                if (enemigo[2].defensa < 0) {
	                    enemigo[2].vida += enemigo[2].defensa; // Restar el valor negativo de defensa a la vida
	                    enemigo[2].defensa = 0;
	                }
	                cout<<"\n>> Atacaste al Jefe del Nivel y le hiciste " << golpe << " puntos de Da\xA4o!\n";
	            	} 
					else {
	                	cout<<"\n\n<< El Jefe del Nivel bloque\xA2 tu ataque!\n";
	            	}
				}
				else{
					
					int golpe2 = personaje[1].ataque - enemigo[2].defensa;
	            	if (golpe2 > 0) {
	                	enemigo[2].defensa -= personaje[1].ataque;
	                	if (enemigo[2].defensa < 0) {
	                    enemigo[2].vida += enemigo[2].defensa; // Restar el valor negativo de defensa a la vida
	                    enemigo[2].defensa = 0;
	                	}
	                cout<<"\n>> Atacaste al Jefe del Nivel y le hiciste " << golpe2 << " puntos de Da\xA4o!\n";
	            	} 
					else {
	                	cout<<"\n\n<< El Jefe del Nivel bloque\xA2 tu Ataque!\n";
	            	}
				}
				break;
			}
	        default:{
	        	cout<<"\n\n>> Movimiento no Programado... Pierdes tu Turno.\n";
				break;
			}
	    }	
	}
	else{
		int eleccion;
		cout<<">> Es tu turno. Elige una Movimiento: \n";
		cout<<"\n";
		cout<<"1_ I N C R E M E N T O   D E F E N S A \n";
		cout<<"\n2_ I N C R E M E N T O   A T A Q U E \n";
		cout<<"\n3_ C U R A R S E \n";
		cout<<"\n4_ A T A Q U E \n\n";
		cin>>eleccion;
		
		switch (eleccion) {
	        case 1:{
	        	if(personajeSeleccionado == false){
	        		personaje[0].defensa += 50;
	            	cout<<"\n>> Aumentaste tu defensa en 50 puntos!\n";
				}
				else{
					personaje[1].defensa += 50;
	            	cout<<"\n>> Aumentaste tu defensa en 50 puntos!\n";
				}
				break;
			}
	        case 2:{
	        	if(personajeSeleccionado == false){
	        		personaje[0].ataque += 70;
	            	cout<<"\n>> Aumentaste tu ataque en 70 puntos!\n";
				}
				else{
					personaje[1].ataque += 70;
	            	cout<<"\n>> Aumentaste tu ataque en 70 puntos!\n";
				}
				break;
			} 
	        case 3:{
	        	if(personajeSeleccionado == false){
	        		personaje[0].vidaFull += 60;
	            	cout<<"\n>> Te curaste 60 puntos de vida!\n";
				}
				else{
					personaje[1].vidaFull += 60;
	            	cout<<"\n>> Te curaste 60 puntos de vida!\n";
				}
				break;
			}
	        case 4:{
	        	if(personajeSeleccionado == false){
	        		int golpe = personaje[0].ataque - enemigo[2].defensa;
	            	if (golpe > 0) {
	                enemigo[2].defensa -= personaje[0].ataque;
	                if (enemigo[2].defensa < 0) {
	                    enemigo[2].vida += enemigo[2].defensa; // Restar el valor negativo de defensa a la vida
	                    enemigo[2].defensa = 0;
	                }
	                cout<<"\n>> Atacaste al Jefe del Nivel y le hiciste " << golpe << " puntos de Da\xA4o!\n";
	            	} 
					else {
	                	cout<<"\n\n<< El Jefe del Nivel bloque\xA2 tu ataque!\n";
	            	}
				}
				else{
					
					int golpe2 = personaje[1].ataque - enemigo[2].defensa;
	            	if (golpe2 > 0) {
	                	enemigo[2].defensa -= personaje[1].ataque;
	                	if (enemigo[2].defensa < 0) {
	                    enemigo[2].vida += enemigo[2].defensa; // Restar el valor negativo de defensa a la vida
	                    enemigo[2].defensa = 0;
	                	}
	                cout<<"\n>> Atacaste al Jefe del Nivel y le hiciste " << golpe2 << " puntos de Da\xA4o!\n";
	            	} 
					else {
	                	cout<<"\n\n<< El Jefe del Nivel bloque\xA2 tu Ataque!\n";
	            	}
				}
				break;
			}
	        default:{
	        	cout<<"\n\n>> Movimiento no Programado... Pierdes tu Turno.\n";
				break;
			}
	    }	
	}	
}
void turno_Jefe(){
	if (enemigo[2].vida<500){
        cout<<"\n\n<< El Le\xA2n acepta su Destino...\n";
        return;
	}
	if(personajeSeleccionado==false){
	    	 int golpe = enemigo[2].ataque - personaje[0].defensa;
	    if (golpe > 0) {
	        personaje[0].vidaFull-=golpe;
	        cout<<"\n\n>> El Jefe te Atac\xA2 y te hizo " << golpe << " Puntos de Da\xA4o!!!\n";
	    } else {
	        cout<<"\n\n<< Tu Defensa Bloque\xA2 el Ataque del Jefel!!!\n";
	    }	
	}
	else{
	    int golpe2 = enemigo[2].ataque - personaje[1].defensa;
		if (golpe2 > 0) {
		    personaje[1].vidaFull-=golpe2;
		    cout<<"\n\n>> El Jefe te Atac\xA2 y te hizo " << golpe2 << " Puntos de Da\xA4o!!!\n";
		} 
		else {
		    cout<<"\n\n<< Tu Defensa Bloque\xA2 el Ataque del Jefe!!!\n";
		}
	}
}
void analizarVida(bool *final){
	if(personajeSeleccionado == false){
		if(personaje[0].vidaFull < 0){
			*final=true;
		}
		if(personaje[0].vida == 0){
			*final=true;
		}
	}
	else{
		if(personaje[1].vidaFull < 0){
			*final=true;
		}
		if(personaje[1].vida == 0){
			*final=true;
		}
	}
	if(enemigo[2].vida < 0){
		*final=true;
	}
}
