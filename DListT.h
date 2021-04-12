#ifndef DLIST_HEADER
#define DLIST_HEADER

struct DListNodeT;

class DListT{
    public:
        DListT();
        DListT(const DListT & src);
        ~DListT();

        DListT & operator = (const DListT & rhs);

        void Home();
        void Left();
        void Right();

        std::string Data() const;
        size_t Size() const;

        void Insert(std::string newData);
        void InsertAfter(std::string newData);
        void Delete();

    private:
        size_t FindCurrent(const DListT & playlist);
      	DListNodeT* head;
        DListNodeT* current;
        size_t nodeCount;
};
#endif
