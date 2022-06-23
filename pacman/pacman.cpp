#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

// ----GENERAL CONFIGURATION ELEMENTS-----
const int SIZE = 15;//Dimensione del labirinto (maze); non comprende i muri perimetrali
const std::string MAZE_CONFIG_NAME = "maze.cfg";//nome del file con i dati iniziali del labirinto

//----LABIRINTH CONFIGURATION ELEMENTS-----
enum Labirinth_Elems { wall, empty, dot };

// Caratteri usati per stampare il labirinto a video
const char EMPTY_C = ' ';//spazio vuoto
const char WALL_C = '#';//muro
const char DOT_C = '.';//puntino

Labirinth_Elems char2lab_elem(char c);
char lab_elem2char(Labirinth_Elems e);

//----PACMAN ELEMENTS-----
enum PacmanDir { North, South, West, East };
struct PacMan
{
    PacmanDir direction;
    int X;
    int Y;
};

char PacmanDir2char(PacmanDir d);

//----COMMAND ELEMENTS-----
enum Command { Go_N, Go_S, Go_W, Go_E, Quit, Unknown };
Command char2command(const char c);
Command get_command(); //TODO

//-----GAME FUNCTIONS-------
void init_maze(std::string config_file_name, Labirinth_Elems mm[SIZE][SIZE]);
void set_pacman(PacMan& pac_man, int x, int y, PacmanDir d);
void init(std::string config_file_name, Labirinth_Elems M[SIZE][SIZE], PacMan& pac_man);
void display(Labirinth_Elems m[SIZE][SIZE], PacMan pac_man);
bool make_move(PacMan& pac_man, Command c, Labirinth_Elems M[SIZE][SIZE]);

//----------------------------------------------------------MyFUNCTIONS-----------------------------------------------------------------------------------------------------------

//Setta Pac-man
void set_pacman(PacMan& pac_man, int x, int y, PacmanDir d){
	pac_man.X = x;
	pac_man.Y = y;
	pac_man.direction = d;
}

//Inizializza la mappa e setta la posizione iniziale di Pac-man in alto a destra
void init(string config_file_name, Labirinth_Elems M[SIZE][SIZE], PacMan& pac_man){
	init_maze(config_file_name, M);
	set_pacman (pac_man, 0, 0, South);
	
}

//Fa comparire sullo schermo la mappa
void display(Labirinth_Elems m[SIZE][SIZE], PacMan pac_man){
	cout << endl;
	for(unsigned int i=0; i<SIZE+2; i++){
		cout << WALL_C;
	}
	cout << endl;
	
	for(unsigned int i=0; i<SIZE; i++){
		cout << WALL_C;
		for(unsigned int j=0; j<SIZE; j++){
			if(pac_man.X == j && pac_man.Y == i)
				cout << PacmanDir2char(pac_man.direction);
			else
				cout << lab_elem2char(m[j][i]);	
			
		}
		
	cout << WALL_C;
	cout << endl;		
		
	}
	
	for(unsigned int i=0; i<SIZE+2; i++){
		cout << WALL_C;
	}
	cout << endl;
}

//Prende un char (W A S D) e lo trasforma in comando di movimento (Command)
Command get_command(){
	char my_char;
	Command my_cmd;
	
	if(my_cmd != Unknown){
		cout << "Inserisci un comando (W/A/S/D): " << endl;
		cin >> my_char;
		my_cmd = char2command(my_char);
	}
	
	return my_cmd;
}

//Dato un comando di movimento restituisce la direzione in cui si deve muovere Pac-man
PacmanDir cmd2dir(Command c){
	if(c == Go_S) return South;
	else if(c == Go_N) return North;
	else if(c == Go_E) return East;
	else if(c == Go_W) return West;
	else throw "Err";
}

/*Dato lo stato del gioco (Pac-man e labirinto) e un comando di movimento, restituisce "true" se la mossa e' ammissimbile,
  altrimenti restituisce false, inoltre aggiorna lo stato di Pac-man, il quale e' passato per riferimento*/
bool make_move(PacMan& pac_man, Command c, Labirinth_Elems M[SIZE][SIZE]){
	int x = pac_man.X;
	int y = pac_man.Y;
	
	if(c == Quit || c == Unknown) throw "Uscita dal gioco";
	else if(c == Go_S) y++;
	else if(c == Go_N) y--;
	else if(c == Go_E) x++;
	else if(c == Go_W) x--;
	
	if(x >= 0 && x < SIZE-1 && y >= 0 && y < SIZE-1) return false;
	
	if (lab_elem2char(M[x][y]) == WALL_C) return false;	
	
	set_pacman(pac_man, x, y, cmd2dir(c));
	return true;
}




//---------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main()
{

	
	
	
	
	
	
	
	
	
	Labirinth_Elems maze[SIZE][SIZE];
	PacMan p;
	cout << "PAC MAN BASIC";
	try {
		init(MAZE_CONFIG_NAME, maze, p);
	}
	catch (string& e) {
		cout << e;
		return -1;
	}
    display(maze, p);
	Command cmd = Unknown; 
	
	/*Testing di get_command
	char my_char;
	Command my_cmd;
	
	do{
		my_cmd = get_command();
		cout << endl << "hai chiesto di ";
		
		switch(my_cmd) {
			case Go_N: cout << "andare a nord";
				break;
			case Go_S: cout << "andare a sud";
				break;
			case Go_E: cout << "andare a est";
				break;
			case Go_W: cout << "andare a ovest";
				break;
			case Quit: cout << "uscire dal programma";
				break;
			case Unknown: cout << "..non ho capito che cosa vuoi. Non dovrebbe succedere mai!!!";
				break;
		}
		cout << endl;
		cout << "Vuoi continuare? [y/n]: " << endl;
		cin >> my_char;
		
	}while(my_char == 'y' || my_char == 'Y'); */
	
	/* UNCOMMENT WHEN get_command() FUNCTION IS READY TO BE TESTED*/
	
     do {
		display(maze, p);
		cmd = get_command();
		switch (cmd) {
		case Quit: cout << "Grazie di aver giocato con me, alla prossima!" << endl;
			return 0;
		case Unknown: throw "unexpected command";
		case Go_E:
		case Go_W:
		case Go_S:
		case Go_N: if (!make_move(p, cmd, maze))
					cout << "Mossa impossibile: non puoi passare attraverso i muri!" << endl;
			break;
		default: throw "not a command!";
		}
	}
	while (true); 
     
} 

//--------------------------------------------------------

Labirinth_Elems char2lab_elem(char c) {
    switch (c) {
    case WALL_C:
        return  wall;
    case EMPTY_C:
     //   return Labirinth_Elems::empty;
    case DOT_C:
        return dot;
    default:return Labirinth_Elems::empty;
    }
}
char lab_elem2char(Labirinth_Elems e) {
    switch (e) {
    case wall:
        return  WALL_C;
    case Labirinth_Elems::empty:
        return EMPTY_C;
    case dot:
        return DOT_C;
    default: throw "not a valid labirinth element";
    }
}

Command char2command(const char c) {
    switch (c) {
    case 'w':
    case'W': return Go_N;
        break;
    case 'a':
    case'A': return Go_W;
    case 'd':
    case'D': return Go_E;
    case 's':
    case'S': return Go_S;
    case 'q':
    case'Q': return Quit;
    default: return Unknown;
    }
}

char PacmanDir2char(PacmanDir d) {
    switch (d) {
    case South: return '^';
    case East:return '<';
    case West:return '>';
    case North:return 'v';
    default: throw "not a valid direction";
    }
}


void init_maze(string config_file_name, Labirinth_Elems mm[SIZE][SIZE]) {
    ifstream cfgfile;
    cfgfile.open(config_file_name);
    if (!cfgfile)
        throw "file not found: missing " + config_file_name;

    for (int y = 0; y<SIZE; ++y) {
        std::string line;
        if (!getline(cfgfile, line))
            line = "";
        std::istringstream line_stream(line);
        for (int x = 0; x < SIZE; ++x) {
            char c;
            if (line_stream >> c)
                mm[x][y] = char2lab_elem(c);
            else
                mm[x][y] = Labirinth_Elems::empty;//missing input is integrated by empty spaces
        }
    }
    cfgfile.close();
}


