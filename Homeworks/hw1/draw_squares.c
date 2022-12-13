int main(){
	draw_square(3, 3, '#');
}                          // NO command line arguments
int main( void ){
	draw_square(3,3,'*');
}              
      // NO command line arguments
int main( int argc, char * argv[] ){
	draw_square(argc, argc, argv[]);
} // command line arguments
int main( int argc, char ** argv ){
	draw_square(argc, argc, argv);
}  // command line arguments

int main( int argc, char ** argv, char *envp[] ){
	draw_square(argc, argc, argv);
	draw_square(argc, argc, envp);
} // environment vars>

void draw_square [int side, int indent, char ch]{
	for (int i = 0; i < side; i = i + 1){
		for(int j = 0; j < indent; j++){
			printf(ch);
		}
		printf("%d\n");
	}
}
