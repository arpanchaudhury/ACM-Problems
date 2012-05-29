#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

bool check_if_touched(char** board_pos, char** mine_pos, unsigned int dim){

	bool touched = false;
	
	for(int row=0; row<dim; row++){
			for(int col=0; col<dim; col++){
				if(board_pos[row][col] == 'x' && mine_pos[row][col] == '*')
					touched = true;		
			}
	}

	return touched;
}

int calculate_mines(char** mine_pos, unsigned int dim, int row, int col){
	
	int mines = 0;
	
	for(int i=row-1; i<=row+1; i++){
		if(i<0 || i>= dim)
			continue;
		for(int j=col-1; j<=col+1; j++){
			if(j<0 || j>=dim)
				continue;
			if(i==row && j==col)
				continue;
			if(mine_pos[i][j] == '*')
				mines++;			
		}	
	}	
	
	return mines;
}

int main(int argc, char* argv[]){
	
	ifstream infile;
	infile.open(argv[1]);
	if(!infile){
		cout << "ERROR:: File Missing..." << endl;
		exit(0);
	}
	
	const int size = 100;
	char line[size];
	infile.getline(line,size);
	unsigned int no_of_games = atoi(line);
	
	for(int i=0; i<no_of_games; i++){
		
		infile.getline(line,size);
		infile.getline(line,size);
		const unsigned int dim = atoi(line);
		
		char** mine_pos = (char**) malloc(dim * sizeof(char*));
		for(int j=0; j<dim; j++){
			mine_pos[j] = (char*) malloc(dim * sizeof(char));
		}

		for(int row=0; row<dim; row++){
			infile.getline(line,size);
			for(int col=0; col<dim; col++){
				mine_pos[row][col] = line[col];			
			}
		}
	
		char** board_pos = (char**) malloc(dim * sizeof(char*));
                for(int j=0; j<dim; j++){
                        board_pos[j] = (char*) malloc(dim * sizeof(char));
                }	
		
		for(int row=0; row<dim; row++){
                        infile.getline(line,size);
                        for(int col=0; col<dim; col++){
                                board_pos[row][col] = line[col];
                        }
                }

		if(check_if_touched(board_pos, mine_pos, dim)){
			for(int row=0; row<dim; row++){
                                for(int col=0; col<dim; col++){
                        	        cout << mine_pos[row][col];
                        	}
				cout << endl;
                	}		
		}
		else{
			for(int row=0; row<dim; row++){
                                for(int col=0; col<dim; col++){
                        		if(board_pos[row][col] == 'x')
						board_pos[row][col] = calculate_mines(mine_pos, dim, row, col) + '0';      
                        	}
                	}

			for(int row=0; row<dim; row++){
                                for(int col=0; col<dim; col++){
                        		cout << board_pos[row][col];      
                        	}
				cout << endl;
                	}		
		}		
		
		for(int row=0; row<dim; row++){
			free(mine_pos[row]);
			free(board_pos[row]);		
		}
		free(mine_pos);
		free(board_pos);
		cout << endl;

	}
	return 0;
}
