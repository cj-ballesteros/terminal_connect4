template <typename T>
class LL 
{
    //contents of each node
    struct node 
    {
        T data;
        node* prev;
        node* next;
    };
    //iterator class to allow access of each node in main
   public:
    class Iterator 
    {
       public:
        friend class LL;
        Iterator();
        Iterator(node*);
        T operator*() const;
        Iterator operator++(int); // a++
        Iterator operator++(); // ++a
        Iterator operator--(int); // a--
        Iterator operator--(); // --a
        bool operator==(const Iterator&) const; // Returns true if LL1 == LL2
        bool operator!=(const Iterator&) const; // LL1 != LL2

       private:
        node* current;
    };

    LL();
    LL(const LL<T>&);
    const LL<T>& operator=(const LL<T>&);
    ~LL();
    void headInsert(const T&);
    void tailInsert(const T&);
    void headRemove();
    bool isEmpty() const;
    std::size_t size() const;
    Iterator begin() const;
    Iterator end() const;
    void printLL() const;

   private:
    node * portal;
};

//iterator class implementation

//Default constructor that sets the current to nullptr
template <typename T>
LL<T>::Iterator::Iterator() 
{
    current = nullptr;
}

// Constructor that sets current to a pointer.
template <typename T>
LL<T>::Iterator::Iterator(node* ptr) 
{
    current = ptr;
}

// * overload that returns data field.
template <typename T>
T LL<T>::Iterator::operator*() const 
{
    return current->data;
}

// Moves the iterator object one node to the right and
// returns the current.
template <typename T>
typename LL<T>::Iterator LL<T>::Iterator::operator++(int) 
{
   this->current = this->current->next;
   return Iterator(this->current);
}

// Moves the iterator object one node to the right and
// returns a current that's pointing to the previous.
template <typename T>
typename LL<T>::Iterator LL<T>::Iterator::operator++() 
{
    this->current = this->current->next;
    return Iterator(this->current->prev);
}

// Moves the iterator object one node to the left and
// returns the current.
template <typename T>
typename LL<T>::Iterator LL<T>::Iterator::operator--(int) 
{
    this->current = this->current->prev;
    return Iterator(this->current);
}

// Moves the iterator object one node to the left and
// returns a current that's pointing to the previous.
template <typename T>
typename LL<T>::Iterator LL<T>::Iterator::operator--() 
{
    this->current = this->current->prev;
    return Iterator(this->current->next);
}

// Compares if the two linked lists are equal
template <typename T>
bool LL<T>::Iterator::operator==(const Iterator& rhs) const 
{
    return this->current == rhs.current;
}

// Compares if the two linked lists are not equal.
template <typename T>
bool LL<T>::Iterator::operator!=(const Iterator& rhs) const 
{
   return this->current != rhs.current;
}

//Linked list class implementation
template <typename T>
LL<T>::LL() 
{
    portal = new node;
    portal->prev = portal;
    portal->next = portal;
}

//copy constructor
template <typename T>
LL<T>::LL(const LL<T>& copy) 
{
   // Creates portal node.
   portal = new node;
   portal->prev = portal;
   portal->next = new node;

   node* tempCurrent;

   // Temporary pointer.
   tempCurrent = portal->next;
   tempCurrent->next = portal;
   tempCurrent->prev = portal;

   // Sets tempCurrent to get the data from the
   // copy linked list.
   node* copyCurrent = copy.portal->next;
   tempCurrent->data = copyCurrent->data;
   copyCurrent = copyCurrent->next;

   // Deep copies.
   while (copyCurrent != copy.portal)
   {
       tempCurrent->next = new node;
       tempCurrent->next->prev = tempCurrent;
       tempCurrent = tempCurrent->next;
       tempCurrent->data = copyCurrent->data;
       tempCurrent->next = portal;
       copyCurrent = copyCurrent->next;
   }

   portal->prev = tempCurrent;
}

//deep copy assignment operator
template <typename T>
const LL<T>& LL<T>::operator=(const LL<T>& rhs) 
{
    // If the linked list is self-assigning, return this.
    if(&rhs == this){
        return *this;
    }

    // Deletes old linked list and deallocates.
    node* temp = portal->next;
    while(temp != portal){
        node*next = temp->next;
        delete temp;
        temp = next;
    }

   // Creates portal node.
   portal->prev = portal;
   portal->next = new node;

   node* tempCurrent;

   // Creates temporary pointer.
   tempCurrent = portal->next;
   tempCurrent->next = portal;
   tempCurrent->prev = portal;

   // Sets up tempCurrent to transfer data from rhs.
   node* copyCurrent = rhs.portal->next;
   tempCurrent->data = copyCurrent->data;
   copyCurrent = copyCurrent->next;

   // Uses tempCurrent to deep copy rhs to linked list.
   while (copyCurrent != rhs.portal)
   {
       tempCurrent->next = new node;
       tempCurrent->next->prev = tempCurrent;
       tempCurrent = tempCurrent->next;
       tempCurrent->data = copyCurrent->data;
       tempCurrent->next = portal;
       copyCurrent = copyCurrent->next;
   }

   portal->prev = tempCurrent;

   return *this;
}

//destructor
template <typename T>
LL<T>::~LL() 
{
    node* temp = portal->next;
    while(temp != portal){
        node* next = temp->next;
        delete temp;
        temp=next;
    }

    delete portal;
}

//head insert
template <typename T>
void LL<T>::headInsert(const T& item) 
{
    node* temp = new node();
    temp->data = item;

    // If there's only one node and it's the portal
    // Create a new object adjacent to the portal.
    if(portal->next == portal){
        temp->prev = portal;
        temp->next = portal;
        portal->prev = temp;
        portal->next = temp;
    }
    else {
        node* head_node = portal->next; //temp 1 has information of the first node

        head_node->prev = temp;
        portal->next = temp;
        temp->next = head_node;
        temp->prev = portal;
    }
}

//tail insert
template <typename T>
void LL<T>::tailInsert(const T& item) 
{
    node* temp = new node();
    temp->data = item;

    // If there's only one node and it's the portal
    // Create a new object adjacent to the portal.
    if(portal->prev == portal){
        temp->prev = portal;
        temp->next = portal;
        portal->prev = temp;
        portal->next = temp;
    }
    else{
        node* prev_node = portal->prev;

        portal->prev = temp;
        temp->prev = prev_node;
        temp->next = portal;
        prev_node->next = temp;
    }
}

// Removes the head of the linked list.
template <typename T>
void LL<T>::headRemove()
{
    if(!isEmpty()){
        node* temp = portal->next;
        portal->next = temp->next;
        temp->next->prev = portal;
        temp->next = nullptr;
        temp->prev = nullptr;
        delete temp;
    }
}

// Checks whether or not a linked list is empty.
template <typename T>
bool LL<T>::isEmpty() const
{
    return portal->next == portal;
}

// Counts how many elements are in the linked list.
template <typename T>
std::size_t LL<T>::size() const
{
   std::size_t count=0;
   node* temp = portal->next;
   while(temp != portal){
       count++;
       temp=temp->next;
   }
   return count;
}

// Returns the first element of the linked list.
template <typename T>
typename LL<T>::Iterator LL<T>::begin() const 
{
    return Iterator(portal->next);
}

// Returns the portal of the linked list (or the end)
template <typename T>
typename LL<T>::Iterator LL<T>::end() const 
{
   return Iterator(portal);
}

// Professor Junggab Son function to test out things.
template <typename T>
void LL<T>::printLL() const{
    node* temp= portal->next;
    while(temp!=portal){
        std::cout << temp->data << "->";
        temp=temp->next;
    }

    std::cout << "portal" << std::endl;
}