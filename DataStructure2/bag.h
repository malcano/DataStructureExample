//
//  bag.h
//  DataStructure2
//
//  Created by Minho Lee on 2021/11/07.
//
#include <iostream>
#include <fstream>
#include "dnode.h"

#ifndef bag_h
#define bag_h

using namespace std;

template <class Vtype>
class bag
{
public:
    typedef Vtype value_type;
    typedef std::size_t size_type;
//    bag();
//    bag(const bag& source);
//    ~bag();
    
    
public:
//    void operator = (const bag& source);
//    void operator += (const bag& addend);
//
//
//
//    bag operator + (const bag& addend);//have to write below operator myself
//    bool operator ==(const bag& source);
//    bool operator != (const bag& source);
    
public:
//    bool erase_one(const value_type& target);
//    size_type count(const value_type& target) const;
//    void insert(const value_type& entry);
//    void show_contents() const;
//    size_type listSize();
//
//    bag mergesort(bag baggage) const;
//    bag merge(bag leftbag, bag rightbag) const;
public:
    bag()
    {
        head_ptr=NULL;
        many_nodes=0;
    }
    bag(const bag<Vtype>& source)
    {
        dnode<Vtype> *tail_ptr;
        list_copy(source.head_ptr, head_ptr, tail_ptr);
    }
    
    
    ~bag()
    {
        list_clear(head_ptr);
        many_nodes = 0;
    }
    void operator=(const bag<Vtype>& source)
    {
        dnode<Vtype>* tail_ptr;
        if(this == & source)
            return;
        list_clear(head_ptr);
        list_copy(source.head_ptr, head_ptr, tail_ptr);
        many_nodes=source.many_nodes;
    }
    void operator+=(const bag& addend)
    {
        dnode<Vtype>* copy_tail_ptr;
        dnode<Vtype>* copy_head_ptr;
        
        if(addend.many_nodes>0)
        {
            list_copy(addend.head_ptr, copy_head_ptr, copy_tail_ptr);
            copy_tail_ptr->set_fore(head_ptr);
            head_ptr = copy_head_ptr;
            many_nodes+=addend.many_nodes;
        }
    }

    bag operator+(const bag<Vtype> &addend)
    {
        dnode<Vtype>* copy_tail_ptr;
        dnode<Vtype>* copy_head_ptr;
        bag returnvalue;
        
        if(addend.many_nodes>0)
        {
            
            list_copy(addend.head_ptr, copy_head_ptr, copy_tail_ptr);
            copy_tail_ptr->set_fore(head_ptr);
            head_ptr = copy_head_ptr;
            many_nodes+=addend.many_nodes;
        }
        returnvalue = addend;
        
        return returnvalue;
    }

    bool operator==(const bag<Vtype>& source)
    {
        if (source.head_ptr == this->head_ptr && source.many_nodes == this->many_nodes)
            return true;
        else
            return false;
    }
    bool operator!=(const bag<Vtype>& source)
    {
        if (source.head_ptr != this->head_ptr || source.many_nodes != this->many_nodes)
            return true;
        else
            return false;
    }
    bool erase_one(const value_type &target)
    {
        dnode<Vtype>* target_ptr;
        target_ptr   = list_search(head_ptr, target);
        if(target_ptr == NULL)
            return false;
        target_ptr->set_data(head_ptr->data());
        list_head_remove(head_ptr);
        --many_nodes;
        return true;
    }

    void insert(const value_type &entry)
    {
        list_head_insert(head_ptr, entry);
        ++many_nodes;
    }

    size_type count (const value_type & target) const
    {
        size_type answer = 0;
        const dnode<Vtype>* cursor;
        cursor = list_search(head_ptr, target);
        
        while(cursor!=NULL)
        {
            ++answer;
            cursor = cursor->fore();
            cursor = list_search(cursor, target);
        }
        return answer;
    }

    void show_contents() const
    {
        dnode<Vtype>* cursor;
        
        for(cursor = head_ptr; cursor != NULL; cursor = cursor->fore())
        {
            cout<<cursor->data()<<" ";
        }
        std::cout << " "<<endl;
    }

    size_type listSize()
    {
        size_type answer=0;
        dnode<Vtype>* cursor;
        for(cursor = head_ptr; cursor != NULL; cursor = cursor->fore())
        {
            answer++;
        }

        return answer;
    }

    bag mergesort(bag baggage) const
    {
        dnode<Vtype>* leftcursor;
        

        int listsize=0;
        
        bag rightbag;
        bag leftbag;
        bag tempbag;
        
        leftcursor = baggage.head_ptr;

        if(baggage.listSize()==1)
        {
            return baggage;
        }
        
        listsize = (int)baggage.listSize();
        
        for(int i=0;i < listsize/2;i++)
        {
            leftbag.insert(leftcursor->data());
            leftcursor = leftcursor->fore();
            baggage.head_ptr = baggage.head_ptr->fore();
        }
        
        leftbag = mergesort(leftbag);

        for(int i=0;i< listsize - (int)leftbag.listSize();i++)
        {
            rightbag.insert(baggage.head_ptr->data());
            leftcursor = leftcursor->fore();
            baggage.head_ptr = baggage.head_ptr->fore();

        }
        
        rightbag = mergesort(rightbag);
       
        
        return merge(leftbag, rightbag);
        
        
    }
    


    bag merge(bag leftbag, bag rightbag) const
    {
        bag mergedbag;
        bag tempbag;
        dnode<Vtype>* leftcursor;
        dnode<Vtype>* rightcursor;
        int tempsize;
        
        int i=0;
    //
        
        leftcursor = leftbag.head_ptr;
        rightcursor = rightbag.head_ptr;
       
        while(leftcursor != NULL && rightcursor!=NULL)
        {
                
            if(leftcursor->data()<rightcursor->data())//left is small
            {
                mergedbag.insert(leftcursor->data());
                leftcursor = leftcursor->fore();
                if(leftcursor == NULL)
                {
                    while(rightcursor != NULL)
                    {
                        mergedbag.insert(rightcursor->data());
                        rightcursor = rightcursor -> fore();
                    }
                }
                
            }else//right is small
            {
                mergedbag.insert(rightcursor->data());
                rightcursor = rightcursor->fore();
                if(rightcursor == NULL)
                {
                    while(leftcursor != NULL)
                    {
                        mergedbag.insert(leftcursor->data());
                        leftcursor = leftcursor -> fore();
                    }
                }
            }
            
        }
        
        
        tempsize = (int)mergedbag.listSize();
        
        if(mergedbag.head_ptr->data() > mergedbag.head_ptr->fore()->data())//reverse
        {
                tempbag=mergedbag;
                list_clear(mergedbag.head_ptr);
                for(i=0;i<tempsize;i++)
                {
                    mergedbag.insert(tempbag.head_ptr->data());
                    tempbag.head_ptr = tempbag.head_ptr->fore();
                }
        }
        
        return mergedbag;
    }
    Vtype getHeaddata()
    {
        return head_ptr->data();
    }
    Vtype headOut()
    {
        Vtype rValue=NULL;
        if(head_ptr!=NULL){
            rValue = head_ptr->data();
            head_ptr = head_ptr->fore();
        
        }
        return rValue;
    }
    bag reverse(bag original)
    {
        bag reversebag;
        
        for(int i=0;i<original.listSize();i++){
            reversebag.insert(original.getHeaddata());
            original.headOut();
        }
        return reversebag;
        
    }
   

  
    
  
private:
    dnode<Vtype>* head_ptr;
    size_type many_nodes;
};


#endif /* bag_h */
