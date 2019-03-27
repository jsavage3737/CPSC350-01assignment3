#include<iostream>

using namespace std;
namespace hw3{

  template <class T>
  class GenStack{
  public:
    GenStack(int startcapacity);
    void push(T newItem);
    void peek();
    int size();
    bool isEmpty();
    T pop();
    int idx;

  private:
    T *stackValues;
    int capacity;
  };

  /* Because this is a template class, all implementations included within header */
  // constructor allowing for specified starting capacity
  template<class T>
  GenStack<T>::GenStack(int startcapacity){
    capacity=startcapacity; // setting capacity
    stackValues = new T[capacity]; // setting internal pointer = to new array
    idx = -1; // starting index = -1, once element is added idx = 0
  }

  // returning total capacity of the stack
  template<class T>
  GenStack<T>::size(){return idx+1;}

  // pushing a new item into the stack
  template<class T>
  void GenStack<T>::push(T newItem){
    if(idx==capacity-1){ // checking if new stack array needs to be made
      T *temp; temp = new T[capacity+1]; // creating new stack array
      // copying old contents to new array
      for(int x=0;x<capacity;x++){
        temp[x] = stackValues[x];
      }
      stackValues = temp; // switching old array for new one
      capacity = capacity+1; // increasing capacity variable
    }
    idx++; // incrementing index
    stackValues[idx] = newItem;
  }

  // popping an item from the stack
  template<class T>
  T GenStack<T>::pop(){
    T target = stackValues[idx]; // finding target variable
    idx --; // setting index to next item in stack
    return target;
  }

  // viewing the top of the stack
  template<class T>
  void GenStack<T>::peek(){cout<<stackValues[idx]<<endl;}

  // checks if stack is empty
  template<class T>
  bool GenStack<T>::isEmpty(){if(idx<0){return true;}}
}
