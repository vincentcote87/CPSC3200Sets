// Problem 793 - Network Connections
// Vincent Cote - CPSC 3200
// Approach - Using given union find data structure to maintain connections. When input is c i j use the merge function, when it is q i j
// use the find function and see if they are equal to eachother, if so it is a successful connection.

#include <iostream>
#include <sstream>

// UnionFind class -- based on Howard Cheng's C code for UnionFind
// Modified to use C++ by Rex Forsyth, Oct 22, 2003                                                                                                                                                          
//                                                                                                                                                                                                           
// Constuctor -- builds a UnionFind object of size n and initializes it                                                                                                                                      
// find -- return index of x in the UnionFind                                                                                                                                                                
// merge -- updates relationship between x and y in the UnionFind                                                                                                                                            


class UnionFind
{
      struct UF { int p; int rank; };

   public:
      UnionFind(int n) {          // constructor                                                                                                                                                             
         howMany = n;
         uf = new UF[howMany];
         for (int i = 0; i < howMany; i++) {
            uf[i].p = i;
            uf[i].rank = 0;
         }
      }

      ~UnionFind() {
         delete[] uf;
      }

      int find(int x) { return find(uf,x); }        // for client use                                                                                                                                        

      bool merge(int x, int y) {
         int res1, res2;
         res1 = find(uf, x);
         res2 = find(uf, y);
         if (res1 != res2) {
            if (uf[res1].rank > uf[res2].rank) {
               uf[res2].p = res1;
            }
            else {
               uf[res1].p = res2;
               if (uf[res1].rank == uf[res2].rank) {
                  uf[res2].rank++;
               }
            }
            return true;
         }
         return false;
      }

   private:
      int howMany;
      UF* uf;

      int find(UF uf[], int x) {     // recursive funcion for internal use                                                                                                                                   
         if (uf[x].p != x) {
            uf[x].p = find(uf, uf[x].p);
         }
         return uf[x].p;
      }
};

int main(void) {
  int sets;
  std::cin>>sets;

  while(sets--) {
		int n;
		std::string line;
		std::cin>>n;
		std::getline(std::cin, line);
		UnionFind uf(n + 1);
		int successfull = 0;
		int unsuccessfull = 0;
		while(true) {
			std::getline(std::cin, line);
			if (line == "")
				break;
			std::stringstream ss(line);
			char query;
			int i, j;
			ss>>query>>i>>j;
			if (query == 'c') {
				uf.merge(i,j);
			}
			else {
				uf.find(i) == uf.find(j) ? successfull++ : unsuccessfull++;
			}
		}
		std::cout<<successfull<<","<<unsuccessfull<<std::endl;
		if (sets != 0)
			std::cout<<std::endl;

	}
	return 0;
}