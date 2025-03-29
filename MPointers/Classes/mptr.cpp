#include <iostream>
#include <client.cpp>

template<typename T>
class MPointer {
    
    private:
        int id; 
    
    public:

        ~MPointer () {
            // client->DecreaseRefCount(this->id);
        }

        static void Init(int port) {
            // Conect with MemMgr via Client
        }

        static MPointer<int> New() {
            // this->id = Client -> MemMgr.Create()
        }

        void operator*=(const T& value) {
            // Client->Set
        }

        int operator=(const T& variable) {
            //Client->Get
            // Increase count
        }

        int operator&() {
            return id;
        }
};