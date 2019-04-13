#ifndef LLIST2_HPP
#define LLIST2_HPP 
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstring>
using namespace std;

template <class ST> class OrderedSet;
template <class ST> ostream & operator <<
(ostream & outs, const OrderedSet<ST> & L);

template <class ST>

class OrderedSet
{
private:
      struct LNode
      {
	LNode ();
	ST data;
	LNode * next;
	LNode * prev;
      };
public:
  class Iterator
  {
  public:
    Iterator ();
    Iterator (LNode * NP);
    ST & operator * () const;
    Iterator operator ++ ();
    Iterator operator ++ (int);
    Iterator operator -- ();
    Iterator operator -- (int);
    bool operator == (const Iterator & other) const;
    bool operator != (const Iterator & other) const;
    

 private:
    LNode * current;
  };
class Exception
  {
  public:
    Exception ();
    Exception (string msg);
    Exception (int idx);
    string Message () const;
  private:
    string message;
  };
  OrderedSet ();
  OrderedSet (const OrderedSet & other);
  ~OrderedSet ();
  OrderedSet & operator = (const OrderedSet & other);
  bool operator == (const OrderedSet & other);
  int Size () const;
  friend ostream & operator << <> (ostream & outs, const OrderedSet<ST> & L);
  bool InsertFirst (const ST & value);
  bool InsertLast (const ST & value);
  bool DeleteFirst ();
  bool DeleteLast ();
  void Forward (void function (const ST & param));
  void Backward (void function (const ST & param));
  Iterator begin () const;
  Iterator rbegin () const;
  Iterator end () const;
  Iterator rend () const;
  ST & operator [] (const int & index) const;
  void  ();
  bool IsEmpty () const;
  bool IsIn (const ST & value) const;
  bool Insert (const ST & value);
  bool Delete (const ST & value);
  OrderedSet operator + (const OrderedSet & other);
  OrderedSet operator * (const OrderedSet & other);
private:
  LNode * first;
  LNode * last;
  int size;
};
  

template <class ST>
ST & OrderedSet<ST>::Iterator::operator * () const
{
  if (current == NULL)
    throw (Exception("Cannot dereference a NULL pointer"));
  return current -> data;
}

template <class ST>
ST & OrderedSet<ST>::operator [] (const int & index) const
{
  if(index < 0)
    throw (Exception(index));
  if (index >= size)
    throw (Exception(index));
  typename OrderedSet<ST>::LNode * n = first;
  for (int i = 0; i < index; i++)
    n=n->next;
  return n->data;
}

template <class ST>
OrderedSet<ST>::LNode::LNode()
{ 
	next = NULL;  
	prev = NULL;
}

template <class ST>
OrderedSet<ST>::OrderedSet ()
{
   // Set up a default OrderedSet.
  size = 0; 
  first = NULL;
  last = NULL;
}
template <class ST>
OrderedSet<ST>::OrderedSet (const OrderedSet & other)
{ 

  first = NULL;
  size = 0;
  LNode * n = other.first;
  for (LNode * n = other.first; n != NULL; n = n -> next)
    InsertLast (n -> data);
  

}
template <class ST>
OrderedSet<ST>::~OrderedSet ()
{ //Destructor
  while (first)
    DeleteFirst();

}


template <class ST>
OrderedSet<ST> & OrderedSet<ST>::operator = (const OrderedSet<ST> & other)
{ //Overrides the = opperator to allow for altering OrderedSet objects
  if (this == & other)
    {
      return * this;
    }  
  while (first) 
    (DeleteFirst());
  for (LNode * n = other.first; n != NULL; n = n -> next)
    {
      InsertLast(n -> data);
    }  
  
  
  return * this;
}
template <class ST>
bool OrderedSet<ST>::operator == (const OrderedSet<ST> & other)
{ //Overrides == operator for OrderedSet comparison
  if (size != other.size)
    {
      return false;
    }
  LNode * n = first;
  LNode * othern = other.first;
  while (n != NULL)
    {
      if (n -> data != othern -> data)
	return false;
      othern = othern -> next;
      othern = othern -> next;
    }  

  return true;
}
template <class ST>
int OrderedSet<ST>::Size () const
{
    return size;
}

template <class ST>
ostream & operator << (ostream & outs, const OrderedSet<ST> & L)
{ //Overrides the << operator to print out the list 
  if (L.first == NULL)
    {
      outs << "{}";
      return outs;
    }  
  outs << "{";
  outs << L.first -> data;
  typename OrderedSet<ST>::LNode * n;
  for (n = L.first -> next; n != NULL; n = n -> next)
    outs << ',' << n -> data;
  outs <<"}";
  return outs;
}

template <class ST>
bool OrderedSet<ST>::InsertFirst (const ST & value)
{  //Creates a new node and inserts it at the begining of the list
  LNode * nnp = new LNode;
  if (nnp == NULL)
    return false;
  nnp -> data = value;
  nnp -> next = first;
  if (size > 0)
    first -> prev = nnp;
  else
    {
      last = nnp;
    }
  first = nnp;
  size++;
  return true;
}

template <class ST>
bool OrderedSet<ST>::InsertLast (const ST & value)
{  //Creates a new node and inserts it at the end of the list
  if (size == 0)
    return InsertFirst(value);
  LNode * nnp = new LNode;
  if (nnp == NULL)
    return false;
  nnp -> data = value;
  nnp -> prev = last;
  nnp -> next = NULL;
  last -> next = nnp;
  last = nnp;
  size++;
  return true;
}
template <class ST>
bool OrderedSet<ST>::DeleteFirst ()
{ //Deletes the first value in the list
  if (first == NULL)
    return false;
  if (size == 1)
    {
      delete first;
      first = NULL;
      last = NULL;
      size = 0;
      return true;
    }
  LNode * n = first;
  first = first ->next;
  delete n;  //deletes first value in list
  size--;  //decrement size
  return true;
}
template <class ST>
bool OrderedSet<ST>::DeleteLast ()
{//Deletes the last value in the list
  if (size == 0)
    return false;
  if (size == 1)
    return DeleteFirst();
  LNode * n = first;
  while (n -> next -> next != NULL)
    n = n -> next;
  last = n;
  delete n -> next;
  n -> next = NULL;
  size --;
  return true;
}

template <class ST>
void OrderedSet<ST>::Forward (void function (const ST & param))
{
  for (LNode * n = first; n; n = n -> next)
        function (n -> data);
}

template <class ST>
void OrderedSet<ST>::Backward (void funciton (const ST & param))
{
  for (LNode * n = last; n; n = n -> prev)
      function (n -> data);
}

void PrintValue (const string & value)
{
  cout << "The value in the list is: " << value << endl;
}

template <class ST>
OrderedSet<ST>::Iterator::Iterator ()
{
  current = NULL;
}

template <class ST>
OrderedSet<ST>::Iterator::Iterator (LNode * NP)
{
  current = NP;
}

template <class ST>
typename OrderedSet<ST>::Iterator OrderedSet<ST>::Iterator::operator ++ ()
{
    if(current == NULL)
      throw("Cannot dereference a NULL pointer)");
    
  current = current -> next;
  return *this;
}
template <class ST>
typename OrderedSet<ST>::Iterator OrderedSet<ST>::Iterator::operator ++ (int)
{
  if(current == NULL)
    throw(Exception("Cannot increment a NULL iterator"));
  Iterator temp = *this; 
current = current -> next;
  return temp;
}

template <class ST>
typename OrderedSet<ST>::Iterator OrderedSet<ST>::Iterator::operator -- ()
{
    if(current == NULL)
      throw(Exception("Cannot dereference a NULL pointer."));
    
  current = current -> prev;
  return *this;
}
template <class ST>
typename OrderedSet<ST>::Iterator OrderedSet<ST>::Iterator::operator -- (int)
{
  if(current == NULL)
    throw(Exception("Cannot decrement a NULL iterator"));
  Iterator temp = *this;
  current = current -> prev;
  return temp;
}
template <class ST>
bool OrderedSet<ST>::Iterator::operator == (const Iterator & other) const
{
  return current == other.current;
}
template <class ST>
bool OrderedSet<ST>::Iterator::operator != (const Iterator & other) const
{
  return current != other.current;
}
template <class ST>
typename OrderedSet<ST>::Iterator OrderedSet<ST>::begin () const
{
  Iterator temp (first);
  return temp;
}
template <class ST>
typename OrderedSet<ST>::Iterator OrderedSet<ST>::rbegin () const
{
  Iterator temp (last);
  return temp;
}
template <class ST>
typename OrderedSet<ST>::Iterator OrderedSet<ST>::end () const
{
  Iterator temp;
  return temp;
}

template <class ST>
typename OrderedSet<ST>::Iterator OrderedSet<ST>::rend () const
{
  Iterator temp;
  return temp;
}
template <class ST>
void OrderedSet<ST>::()
{
  while(Size() > 0)
    DeleteFirst();
}
template <class ST>
bool OrderedSet<ST>::IsEmpty () const
{
  if(Size() == 0)
    return true;
  else
    return false;
}
template <class ST>
bool OrderedSet<ST>::IsIn (const ST & value) const
{
  for(LNode * n = first;n;n=n->next)
    
      if(n -> data == value)
          return true;
      
    
  return false;
}
template <class ST>
bool OrderedSet<ST>::Insert(const ST & value)
{
  if (size == 0)
    return InsertFirst(value);
  
  if (value < first -> data)
    return InsertFirst(value);
    
  if (value > last -> data)
    return InsertLast(value);

  if (IsIn(value))
    return false;
  
  LNode * np = new LNode;
  if (np == NULL)
    return false;
  np -> data = value;
  LNode * nn;
  LNode * qq;
  for (nn = first; nn -> data < value; nn = nn -> next)
    qq = nn -> next;
  nn = nn -> prev;
  np -> prev = nn;
  np -> next = qq;
  nn -> next = np;
  qq -> prev = np;
  size++;
  return true;
}
template <class ST>
bool OrderedSet<ST>::Delete(const ST & value)
{
  if(!IsIn(value))
    return false;
  if (value == last -> data)
    return DeleteLast();
  if (value == first -> data)
    return DeleteFirst();
  

      LNode * np = first;
      while (value > np -> data)
	np = np -> next;
      np -> next -> prev = np -> next;
      np -> prev -> next = np -> next;
      delete np;
      size--;
      return true;
    
}
template <class ST>
OrderedSet<ST> OrderedSet<ST>:: operator + (const OrderedSet & other)
{
  OrderedSet<ST> Union;
  for(LNode * np = first; np != NULL; np = np -> next)
    
      Union.Insert(np -> data);
     
  for(LNode * np = other.first; np != NULL;np=np -> next)
    
      Union.Insert(np->data);
    
  return Union;
  
}
template <class ST>
OrderedSet<ST> OrderedSet<ST>:: operator * (const OrderedSet & other)
{
  OrderedSet<ST> q;
  for (LNode * np = other.first; np != NULL; np = np -> next)
    
      for (LNode * nn = first; nn != NULL; nn = nn -> next)
	
        if (np -> data == nn -> data)
            q.Insert(np -> data);
	
    
  return q;
}
template <class ST>
OrderedSet<ST>::Exception::Exception ()
{
  message = ",";
}
template <class ST>
OrderedSet<ST>::Exception::Exception (string msg)
{
  message = msg;
}
template <class ST>
OrderedSet<ST>::Exception::Exception (int idx)
{
  stringstream ss (stringstream::in | stringstream::out);
  ss << "Subscript [" << idx << "] out of range";
  getline(ss, message);
}
template <class ST>
string OrderedSet<ST>::Exception::Message() const
{
  return message;
}
#endif
