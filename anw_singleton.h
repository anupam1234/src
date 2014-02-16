#ifndef ANW_SINGLETON_H
#define ANW_SINGLETON_H
#include <stdio.h>
#include <assert.h>
#include <iostream>

//Singleton class
//note that this is not thread safe
//
//
using namespace std;

template <typename T>
class Singleton
{
  public:
    static T* CreateInstance()
    {
      if (NULL == m_instance )
      {
        m_instance = new T;
        if(ANW_STATUS_SUCCESS != m_instance->init())
        {
        	DestroyInstance();
        }
      }
      assert(NULL != m_instance);
      return m_instance; 
    }
    
    static void DestroyInstance()
    {
    	if(NULL != m_instance)
    	{
    		delete m_instance;
    		m_instance = NULL;
    	}
    }
   virtual ANW_RSP_STATUS init()
    {
    	return ANW_STATUS_SUCCESS;
    }

 protected:
    //Singleton constructor and destructor cant be called directly
    
    //default constructor
    Singleton() 
    {
    };
    
    //desturctor
    virtual ~Singleton()
    {
    }

  private:
    Singleton(const Singleton&) 
    {
    };

    static T* m_instance;
};


//initialize the static class member
template <typename T> T* Singleton <T>::m_instance = NULL;

#endif //ANW_SINGLETON_H

