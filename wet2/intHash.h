class intHash
{
private:
int size;

public:
     intHash():size(0){}
     intHash(int& size):size(size){}
     int operator()(int &num) const{
          return num%size;
     }
     ~intHash() = default;
};
