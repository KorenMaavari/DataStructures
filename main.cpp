
#include "UnionFind.h"


int main(){
   int a[5] = {1,2,3,4,5};
   permutation_t perm(a);
   Player player1(1, 1, 1,1,1,true, perm);
  int b[5] = {1,3,2,5,4};
  
  player1.multPermutation(b);









    //  int a=3;
    //  int b= 5;
    //  int c = 64;
    // //  int key = 96;
    // HashTable<int, int, intHash>* new_hashTable = new HashTable<int, int,intHash>();
    
    // for(int i=1;i<1000001;i++)
    // {
    //   int val = std::rand()%100000;
    //   new_hashTable->insert(val, val);
    // }




    //  std::cout<<"table size is:" <<new_hashTable->getTableSize()<<std::endl;

    // for (int i = 0; i < 2; i++)
    // {
    //     new_hashTable->insert(&a, key);
    // }


    // (*new_hashTable)[key];


    //std::cout<<"table size is:" <<new_hashTable->getTableSize()<<std::endl;
     // new_hashTable->insert(&a ,b);
     // new_hashTable->insert(&a, a);
   //  std::cout<< *new_hashTable;
    // std::cout<< new_hashTable->doesExist(c) <<std::endl;
//     for (int i = 0; i < initialSize; i++)
//      {
//           std::cout<< new_hashTable->table[i];
//      }
     
    //  std::cout<<*new_hashTable<<std::endl;
     return 0;
}